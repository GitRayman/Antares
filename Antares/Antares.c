//Antares.h - FTDI/Bridgetek Eve 2,3,4 driver for Propeller2 and FlexSpin C
//Copyright 2020-2021 Raymond Allen, MIT licence (except parts from "gd2-lib", which have BSD-3 license)

//This code is based on "gd2-lib" by James Bowman (BSD-3 license) and "EVE2-Library" by Matrix Orbital (MIT license)
//We are very appreciative of these codes
//"gd2-lib" and license info can be found here:  https://github.com/jamesbowman/gd2-lib
//"EVE2-Library" and license info can be found here:  https://github.com/MatrixOrbital/EVE2-Library

//Do we want to use a cog for SPI comms to get faster speed?
#define USECOGFORSPI

#ifndef USECOGFORSPI
#include "..\Antares\SPI.c"  //This version doesn't use a cog
Spi SPI;
#else
struct __using("..\\Antares\\SPI.spin2") SPI; //RJA: //This version uses a cog  //Visual Studio will show an error here, but it's OK
#endif // !USECOGFORSPI




// This list of headers is for functionality required by this library and should not change.  Also fine for Arduino.
#include <stdint.h>              // Find integer types like "uint8_t"  
#include <stdbool.h>             // bool
#include <stdlib.h>              // calloc(), free()
#include <string.h>              // strlen()

#include "Antares.h"  //RJA:  This circular include not needed, but added so code editor doesn't mark some things as undefined




void Eve_Reset_HW(void)
{//Power Cycle EVE
    printf("Power Cycling EVE\n");

    if (FT800_PD_N < 0)
    {//dazzler doesn't have access to PDn, but need to bring other CSs high
        _pinh(Dazzler_CS); //dazzler doesn't have access to this
        _pinh(DazzlerSD_CS);
        return;  
    }

    //for (int i=0;i<500000;i++)
    {
        _pinl(FT800_PD_N);
        MyDelay(50);
        _pinh(FT800_PD_N);
        MyDelay(200);
    }

}

void SPI_Enable()
{
    _pinl(FT800_CS);
}

void SPI_Disable()
{//Raise Chip select
#ifdef USECOGFORSPI  //For the cogged version, need to wait for command to complete before raising CS
    SPI.SendCommand(0,0);  //wait until it's finished
#endif
    _pinh(FT800_CS);
}

void SPI_Write(unsigned char c)
{//send byte over spi
    SPI.Write8(FT800_MOSI, FT800_CLK, c & 0xFF);
}

void SPI_WriteBuffer(uint8_t* buff, int TransferSize)
{//send bytes over spi
    SPI.WriteN(FT800_MOSI, FT800_CLK, buff, TransferSize);
}

void SPI_ReadBuffer(unsigned char *pBuffer, int n)
{//read bytes over spi
    //unsigned char c = SPI.SHIFTIN(FT800_MISO, FT800_CLK, SPI.MSBPRE, 8); //RJA dummy read (could also have been a dummy write, as in FTDI's Gpu_Hal_StartTransfer())
    unsigned char c = SPI.Read8(FT800_MISO, FT800_CLK); //RJA dummy read (could also have been a dummy write, as in FTDI's Gpu_Hal_StartTransfer())
    for (int i = 0; i < n; i++)
    {
        pBuffer[i] = SPI.Read8(FT800_MISO, FT800_CLK);//RJA trying to speed it up SPI.SHIFTIN(FT800_MISO, FT800_CLK, SPI.MSBPRE, 8);
    }
    
}

// Call this function once at powerup to reset and initialize the Eve chip
void FT81x_Init(void)
{  
    ////REMOVE ME
    //_drvh(13);  //PSAVE:  select EVE as source for sync signals and not P2 on Eval Board Adapter

    //Start up P2 SPI driver
    //for cogless version of SPI:  With clockdelay==0, get max bitrate ~6 MHz with 297 MHz P2 clock 
    //for cogged version of SPI:  With clockdelay==0, get max bitrate ~24 MHz with 297 MHz P2 clock
    SPI.Start(10+0, 0); //(ClockDelay, ClockState) 
    printf("SPI Started\n");

    Eve_Reset(); // Hard reset of the Eve chip
    printf("EVE powercycle complete.\n");

  uint32_t Ready = false;



  //Turn on 12.375 MHz pin output for EVE, if needed
#ifdef NCOPIN
  __asm {
      wrpin   #(P_NCO_FREQ | P_TT_11), #NCOPIN //smartpin NCO // 0b00000000000000000000000011001100, #NCOPIN //smartpin NCO
      WXPIN   #NCOXPIN, #NCOPIN//##$0000_0080,#45'55  //base period
      WYPIN   ##NCOYPIN, #NCOPIN//##$2000_0000,#45'55  //add amount per clock
      drvh    #NCOPIN
  }
#endif  


  // Wakeup Eve
  printf("Waking up EVE.\n");
  HostCommand(HCMD_SLEEP);  
  HostCommand(HCMD_CLKEXT);
  MyDelay(300);
  //HostCommand(HCMD_CLKINT);
  HostCommand(HCMD_ACTIVE);
  MyDelay(300);



  //Change to 72 MHz (Note: For VGA also possible to do 48 MHz with PCLK lowered from 3 to 2)
  HostCommand(HCMD_SLEEP);
  HostCommand3((uint32_t)0x61 | (0x40 << 8) | (0x06 << 8));  //72MHz
  //HostCommand3((uint32_t)0x61 | (0x40 << 8) | (0x05 << 8));  //60 MHz
  HostCommand(HCMD_ACTIVE);
  MyDelay(300);
  


  do
  {
    Ready = Cmd_READ_REG_ID();
  }while (!Ready);

  Log("Eve now ACTIVE\n");         //
  
  Ready = rd32(REG_CHIP_ID);
  uint16_t ValH = Ready >> 16;
  uint16_t ValL = Ready & 0xFFFF;
  Log("Chip ID = 0x%04x%04x\n", ValH, ValL);

  wr32(REG_FREQUENCY + RAM_REG, 0x44AA200);//72 MHz // Configure the system clock to 72MHz
  //wr32(REG_FREQUENCY + RAM_REG, 0x3938700); // Configure the system clock to 60MHz

  // Before we go any further with Eve, it is a good idea to check to see if it is wigging out about something 
  // that happened before the last reset.  If Eve has just done a power cycle, this would be unnecessary.
  if( rd16(REG_CMD_READ + RAM_REG) == 0xFFF )
  {
    // Eve is unhappy - needs a paddling.
    uint16_t Patch_Add = rd16(REG_COPRO_PATCH_PTR + RAM_REG);
    wr32(REG_CPU_RESET + RAM_REG, 1);
    wr32(REG_CMD_READ + RAM_REG, 0);
    wr32(REG_CMD_WRITE + RAM_REG, 0);
    wr32(REG_CMD_DL + RAM_REG, 0);
    wr32(REG_PCLK + RAM_REG, 0);
    FifoWriteLocation = 0;                    // reset our marker tracker variables
    wr32(REG_CPU_RESET + RAM_REG, 0);
    MyDelay(100);
    wr16(REG_COPRO_PATCH_PTR + RAM_REG, Patch_Add);
    Log( "Eve Needed Whacking\n" );
    printf("Eve Needed Whacking\n");
  }




  // turn off screen output during startup
  wr8(REG_GPIOX + RAM_REG, 0);             // Set REG_GPIOX to 0 to turn off the LCD DISP signal
  wr8(REG_PCLK + RAM_REG, 0);              // Pixel Clock Output disable




  // load parameters of the physical screen to the Eve
  // All of these registers are 32 bits, but most bits are reserved, so only write what is actually used
  wr16(REG_HCYCLE + RAM_REG, HCYCLE);         // Set H_Cycle to 548
  wr16(REG_HOFFSET + RAM_REG, HOFFSET);       // Set H_Offset to 43
  wr16(REG_HSYNC0 + RAM_REG, HSYNC0);         // Set H_SYNC_0 to 0
  wr16(REG_HSYNC1 + RAM_REG, HSYNC1);         // Set H_SYNC_1 to 41
  wr16(REG_VCYCLE + RAM_REG, VCYCLE);         // Set V_Cycle to 292
  wr16(REG_VOFFSET + RAM_REG, VOFFSET);       // Set V_OFFSET to 12
  wr16(REG_VSYNC0 + RAM_REG, VSYNC0);         // Set V_SYNC_0 to 0
  wr16(REG_VSYNC1 + RAM_REG, VSYNC1);         // Set V_SYNC_1 to 10
  wr8(REG_SWIZZLE + RAM_REG, SWIZZLE);        // Set SWIZZLE to 0
  wr8(REG_PCLK_POL + RAM_REG, PCLK_POL);      // Set PCLK_POL to 1
  wr16(REG_HSIZE + RAM_REG, HSIZE);           // Set H_SIZE to 480
  wr16(REG_VSIZE + RAM_REG, VSIZE);           // Set V_SIZE to 272
  wr8(REG_CSPREAD + RAM_REG, CSPREAD);        // Set CSPREAD to 1    (32 bit register - write only 8 bits)
  wr8(REG_DITHER + RAM_REG, DITHER);          // Set DITHER to 1     (32 bit register - write only 8 bits)

  // configure touch & audio
  wr16(REG_TOUCH_RZTHRESH + RAM_REG, 1200);          // set touch resistance threshold
  wr8(REG_TOUCH_MODE + RAM_REG, 0x02);               // set touch on: continous - this is default
  wr8(REG_TOUCH_ADC_MODE + RAM_REG, 0x01);           // set ADC mode: differential - this is default
  wr8(REG_TOUCH_OVERSAMPLE + RAM_REG, 15);           // set touch oversampling to max

  wr16(REG_GPIOX_DIR + RAM_REG, 0x8000);             // Set Disp GPIO Direction 
  wr16(REG_GPIOX + RAM_REG, 0x8000 );                 // Enable Disp (if used)

  wr16(REG_PWM_HZ + RAM_REG, 0x00FA);                // Backlight PWM frequency
  wr8(REG_PWM_DUTY + RAM_REG, 0x00);                 // Backlight PWM duty (off)   

    //New for EVE4
  //wr32(0x614 + RAM_REG, 0x08c1);// 0x8c1);//REG_PCLK_FREQ 
  //wr32(0x618 + RAM_REG, 0x1);//REG_PCLK_2X
  //Send_CMD(CMD_PCLKFREQ);
  //Send_CMD(72000000);
  //Send_CMD(00);  //nearest
  //Send_CMD(0);
  //UpdateFIFO();
  //Wait4CoProFIFOEmpty();

  // write first display list (which is a clear and blank screen)
  wr32(RAM_DL+0, CLEAR_COLOR_RGB(0,0,0));
  wr32(RAM_DL+4, CLEAR(1,1,1));
  wr32(RAM_DL+8, DISPLAY());
  wr8(REG_DLSWAP + RAM_REG, DLSWAP_FRAME);          // swap display lists
  wr8(REG_PCLK + RAM_REG, PCLK);                       // after this display is visible on the LCD


  Log("First screen written\n");


  //RJA This example code didn't turn on backlight! (or, am I missing something?)
  //RJA:  Turn on backlight
  wr8(REG_PWM_DUTY + RAM_REG, 128);                 // Backlight PWM duty (on)

  ////turn off audio and set volume to midrange
  wr8(REG_VOL_SOUND + RAM_REG, 128);
  wr8(REG_PLAY + RAM_REG, 0);

  Ready = rd32(REG_FREQUENCY + RAM_REG);
  printf("Clock freq = %d\n", Ready);

}

// Reset Eve chip via the hardware PDN line
void Eve_Reset(void)
{
  Eve_Reset_HW();
}

// *** Host Command - FT81X Embedded Video Engine Datasheet - 4.1.5 **********************************************
// Host Command is a function for changing hardware related parameters of the Eve chip.  The name is confusing.
// These are related to power modes and the like.  All defined parameters have HCMD_ prefix
void HostCommand(uint8_t HCMD) 
{
//  Log("Inside HostCommand\n");

  SPI_Enable();
  
/*  SPI_Write(HCMD | 0x40); // In case the manual is making you believe that you just found the bug you were looking for - no. */       
  SPI_Write(HCMD);        
  SPI_Write(0x00);          // This second byte is set to 0 but if there is need for fancy, never used setups, then rewrite.  
  SPI_Write(0x00);   
  
  SPI_Disable();
}

///***************************************************************************
//* Interface Description    : This API sends a 3byte command from host to EVE
//* Implementation           :
//* Return Value             : void
//* Author                   :
//****************************************************************************/
//void Gpu_HostCommand_Ext3(Gpu_Hal_Context_t* host, uint32_t cmd)
//{
//    _pinl(host->hal_config.spi_cs_pin_no);
//    SPI.SHIFTOUT(FT800_MOSI, FT800_CLK, SPI.MSBFIRST, 8, cmd & 0xFF);  //RJA needs to see what is going on here...  Not something I did in Spin2 version...
//    SPI.SHIFTOUT(FT800_MOSI, FT800_CLK, SPI.MSBFIRST, 8, (cmd >> 8) & 0xff);
//    SPI.SHIFTOUT(FT800_MOSI, FT800_CLK, SPI.MSBFIRST, 8, (cmd >> 16) & 0xff);
//    _pinh(host->hal_config.spi_cs_pin_no);
//
//}

void HostCommand3(uint32_t cmd)
{//RJA adding this one to write 3 bytes
    //  Log("Inside HostCommand\n");

    SPI_Enable();

    /*  SPI_Write(HCMD | 0x40); // In case the manual is making you believe that you just found the bug you were looking for - no. */
    SPI_Write(cmd & 0xFF);
    SPI_Write((cmd >> 8) & 0xff);          // This second byte is set to 0 but if there is need for fancy, never used setups, then rewrite.  
    SPI_Write((cmd >> 16) & 0xff);

    SPI_Disable();
}

// *** Eve API Reference Definitions *****************************************************************************
// FT81X Embedded Video Engine Datasheet 1.3 - Section 4.1.4, page 16
// These are all functions related to writing / reading data of various lengths with a memory address of 32 bits
// ***************************************************************************************************************
void wr32(uint32_t address, uint32_t parameter)
{
  SPI_Enable();
  
  SPI_Write((uint8_t)((address >> 16) | 0x80));   // RAM_REG = 0x302000 and high bit is set - result always 0xB0
  SPI_Write((uint8_t)(address >> 8));             // Next byte of the register address   
  SPI_Write((uint8_t)address);                    // Low byte of register address - usually just the 1 byte offset
  
  SPI_Write((uint8_t)(parameter & 0xff));         // Little endian (yes, it is most significant bit first and least significant byte first)
  SPI_Write((uint8_t)((parameter >> 8) & 0xff));
  SPI_Write((uint8_t)((parameter >> 16) & 0xff));
  SPI_Write((uint8_t)((parameter >> 24) & 0xff));
  
  SPI_Disable();
}

void wr16(uint32_t address, uint16_t parameter)
{
  SPI_Enable();
  
  SPI_Write((uint8_t)((address >> 16) | 0x80)); // RAM_REG = 0x302000 and high bit is set - result always 0xB0
  SPI_Write((uint8_t)(address >> 8));           // Next byte of the register address   
  SPI_Write((uint8_t)address);                  // Low byte of register address - usually just the 1 byte offset
  
  SPI_Write((uint8_t)(parameter & 0xff));       // Little endian (yes, it is most significant bit first and least significant byte first)
  SPI_Write((uint8_t)(parameter >> 8) & 0xff);
  
  SPI_Disable();
}

void wr8(uint32_t address, uint8_t parameter)
{
  SPI_Enable();
  
  SPI_Write((uint8_t)((address >> 16) | 0x80)); // RAM_REG = 0x302000 and high bit is set - result always 0xB0
  SPI_Write((uint8_t)(address >> 8));           // Next byte of the register address   
  SPI_Write((uint8_t)(address));                // Low byte of register address - usually just the 1 byte offset
  
  SPI_Write(parameter);             
  
  SPI_Disable();
}

uint32_t rd32(uint32_t address)
{
  uint8_t buf[4];
  uint32_t Data32;
  
  SPI_Enable();
  
  SPI_Write((address >> 16) & 0x3F);    
  SPI_Write((address >> 8) & 0xff);    
  SPI_Write(address & 0xff);
  
  SPI_ReadBuffer(buf, 4);
  
  SPI_Disable();

  //printf("RD32 gives %d, %d, %d, %d", buf[0], buf[1], buf[2], buf[3]);
  
  Data32 = buf[0] + ((uint32_t)buf[1] << 8) + ((uint32_t)buf[2] << 16) + ((uint32_t)buf[3] << 24);
  return (Data32);  
}

uint16_t rd16(uint32_t address)
{
  uint8_t buf[2];
    
  SPI_Enable();
  
  SPI_Write((address >> 16) & 0x3F);    
  SPI_Write((address >> 8) & 0xff);    
  SPI_Write(address & 0xff);
  
  SPI_ReadBuffer(buf, 2);
  
  SPI_Disable();
  
  //uint16_t Data16 = buf[0] + ((uint16_t)buf[1] << 8);
  return ((uint16_t)*buf);// Data16);
}

uint8_t rd8(uint32_t address)
{
  uint8_t buf[1];
  
  SPI_Enable();
  
  SPI_Write((address >> 16) & 0x3F);    
  SPI_Write((address >> 8) & 0xff);    
  SPI_Write(address & 0xff);
  
  SPI_ReadBuffer(buf, 1);
  
  SPI_Disable();
  
  return (buf[0]);  
}

// *** Send_Cmd() - this is like cmd() in (some) Eve docs - sends 32 bits but does not update the write pointer ***
// FT81x Series Programmers Guide Section 5.1.1 - Circular Buffer (AKA "the FIFO" and "Command buffer" and "CoProcessor")
// Don't miss section 5.3 - Interaction with RAM_DL
void Send_CMD(uint32_t data)
{
  wr32(FifoWriteLocation + RAM_CMD, data);                         // write the command at the globally tracked "write pointer" for the FIFO

  FifoWriteLocation += FT_CMD_SIZE;                                // Increment the Write Address by the size of a command - which we just sent
  FifoWriteLocation %= FT_CMD_FIFO_SIZE;                           // Wrap the address to the FIFO space
}

// UpdateFIFO - Cause the CoProcessor to realize that it has work to do in the form of a 
// differential between the read pointer and write pointer.  The CoProcessor (FIFO or "Command buffer") does
// nothing until you tell it that the write position in the FIFO RAM has changed
void UpdateFIFO(void)
{
  wr16(REG_CMD_WRITE + RAM_REG, FifoWriteLocation);               // We manually update the write position pointer
}

// Read the specific ID register and return TRUE if it is the expected 0x7C otherwise.
uint8_t Cmd_READ_REG_ID(void)
{
  uint8_t readData[2];
  
  SPI_Enable();
  SPI_Write(0x30);                   // Base address RAM_REG = 0x302000
  SPI_Write(0x20);    
  SPI_Write(REG_ID);                 // REG_ID offset = 0x00
  SPI_ReadBuffer(readData, 1);       // There was a dummy read of the first byte in there
  SPI_Disable();
  
  if (readData[0] == 0x7C)           // FT81x Datasheet section 5.1, Table 5-2. Return value always 0x7C
  {
    Log("\nGood ID: 0x%02x\n", readData[0]);
    return 1;
  }
  else
  {
      Log("need %d, got %d\n", 0x7C, readData[0]);
    //Log("need 0x7C, got 0x%02x \n", readData[0]);
    return 0;
  }
}

// **************************************** Co-Processor/GPU/FIFO/Command buffer Command Functions ***************
// These are discussed in FT81x Series Programmers Guide, starting around section 5.10
// While display list commands can be sent to the CoPro, these listed commands are specific to it.  They are 
// mostly widgets like graphs, but also touch related functions like cmd_track() and memory operations. 
// Essentially, these commands set up parameters for CoPro functions which expand "macros" using those parameters
// to then write a series of commands into the Display List to create all the primitives which make that widget.
// ***************************************************************************************************************

// ******************** Screen Object Creation CoProcessor Command Functions ******************************

// *** Draw Slider - FT81x Series Programmers Guide Section 5.38 *************************************************
void Cmd_Slider(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range)
{
  Send_CMD(CMD_SLIDER);
  Send_CMD( ((uint32_t)y << 16) | x );
  Send_CMD( ((uint32_t)h << 16) | w );
  Send_CMD( ((uint32_t)val << 16) | options );
  Send_CMD( (uint32_t)range );
}

// *** Draw Spinner - FT81x Series Programmers Guide Section 5.54 *************************************************
void Cmd_Spinner(uint16_t x, uint16_t y, uint16_t style, uint16_t scale)
{    
  Send_CMD(CMD_SPINNER);
  Send_CMD( ((uint32_t)y << 16) | x );
  Send_CMD( ((uint32_t)scale << 16) | style );
}

// *** Draw Gauge - FT81x Series Programmers Guide Section 5.33 **************************************************
void Cmd_Gauge(uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range)
{
  Send_CMD(CMD_GAUGE);
  Send_CMD( ((uint32_t)y << 16) | x );
  Send_CMD( ((uint32_t)options << 16) | r );
  Send_CMD( ((uint32_t)minor << 16) | major );
  Send_CMD( ((uint32_t)range << 16) | val );
}

// *** Draw Dial - FT81x Series Programmers Guide Section 5.39 **************************************************
// This is much like a Gauge except for the helpful range parameter.  For some reason, all dials are 65535 around.
void Cmd_Dial(uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t val)
{
  Send_CMD(CMD_DIAL);
  Send_CMD( ((uint32_t)y << 16) | x );
  Send_CMD( ((uint32_t)options << 16) | r );
  Send_CMD( (uint32_t)val );
}

// *** Make Track (for a slider) - FT81x Series Programmers Guide Section 5.62 ************************************
// tag refers to the tag # previously assigned to the object that this track is tracking.
void Cmd_Track(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t tag)
{
    Send_CMD(CMD_TRACK);
    Send_CMD( ((uint32_t)y << 16) | x );
    Send_CMD( ((uint32_t)h << 16) | w );
    Send_CMD( (uint32_t)tag );
}

// *** Draw Number - FT81x Series Programmers Guide Section 5.43 *************************************************
void Cmd_Number(uint16_t x, uint16_t y, uint16_t font, uint16_t options, uint32_t num)
{
  Send_CMD(CMD_NUMBER);
  Send_CMD( ((uint32_t)y << 16) | x );
  Send_CMD( ((uint32_t)options << 16) | font );
  Send_CMD(num);
}

// *** Draw Smooth Color Gradient - FT81x Series Programmers Guide Section 5.34 **********************************
void Cmd_Gradient(uint16_t x0, uint16_t y0, uint32_t rgb0, uint16_t x1, uint16_t y1, uint32_t rgb1)
{
  Send_CMD(CMD_GRADIENT);
  Send_CMD( ((uint32_t)y0<<16)|x0 );
  Send_CMD(rgb0);
  Send_CMD( ((uint32_t)y1<<16)|x1 );
  Send_CMD(rgb1);
}

void Cmd_AnimDraw(int8_t AnimID)
{
  Send_CMD(CMD_ANIMDRAW);
  Send_CMD( (int32_t)AnimID );
}

void Cmd_AnimDrawFrame(uint32_t addr, uint16_t Xpos, uint16_t Ypos, uint8_t Frame)
{
  Send_CMD(CMD_ANIMFRAME);
  Send_CMD(((uint32_t)Ypos << 16) + Xpos);
  Send_CMD(addr);
  Send_CMD( (uint32_t)Frame );
}

// *** Draw Button - FT81x Series Programmers Guide Section 5.28 **************************************************
void Cmd_Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t font, uint16_t options, const char* str)
{ 
  uint16_t DataPtr, LoopCount, StrPtr;
  
  uint16_t length = strlen(str);
  if(!length) 
    return;
  
  uint32_t* data = (uint32_t*) calloc((length/4)+1, sizeof(uint32_t));
  
  StrPtr = 0;
  for(DataPtr=0; DataPtr<(length/4); DataPtr++, StrPtr += 4)
    data[DataPtr] = (uint32_t)str[StrPtr+3]<<24 | (uint32_t)str[StrPtr+2]<<16 | (uint32_t)str[StrPtr+1]<<8 | (uint32_t)str[StrPtr];
  
  for(LoopCount=0; LoopCount<(length%4); LoopCount++, StrPtr++)
    data[DataPtr] |= (uint32_t)str[StrPtr] << (LoopCount * 8);
  
  Send_CMD(CMD_BUTTON);
  Send_CMD( ((uint32_t)y << 16) | x ); // Put two 16 bit values together into one 32 bit value - do it little endian
  Send_CMD( ((uint32_t)h << 16) | w );
  Send_CMD( ((uint32_t)options << 16) | font );
  
  for(LoopCount=0; LoopCount <= length/4; LoopCount++)
    Send_CMD(data[LoopCount]);

  free(data);
}

// *** Draw Text - FT81x Series Programmers Guide Section 5.41 ***************************************************
void Cmd_Text(uint16_t x, uint16_t y, uint16_t font, uint16_t options, const char* str)
{
  uint16_t DataPtr, LoopCount, StrPtr;
  
  uint16_t length = strlen(str);
  if(!length) 
    return; 
  
  uint32_t* data = (uint32_t*) calloc((length / 4) + 1, sizeof(uint32_t)); // Allocate memory for the string expansion
  
  StrPtr = 0;
  for(DataPtr=0; DataPtr<(length/4); ++DataPtr, StrPtr=StrPtr+4)
    data[DataPtr] = (uint32_t)str[StrPtr+3]<<24 | (uint32_t)str[StrPtr+2]<<16 | (uint32_t)str[StrPtr+1]<<8 | (uint32_t)str[StrPtr];
  
  for(LoopCount=0; LoopCount<(length%4); ++LoopCount, ++StrPtr)
    data[DataPtr] |= (uint32_t)str[StrPtr] << (LoopCount*8);

  // Set up the command
  Send_CMD(CMD_TEXT);
  Send_CMD( ((uint32_t)y << 16) | x );
  Send_CMD( ((uint32_t)options << 16) | font );

  // Send out the text
  for(LoopCount = 0; LoopCount <= length/4; LoopCount++)
    Send_CMD(data[LoopCount]);  // These text bytes get sucked up 4 at a time and fired at the FIFO

  free(data);
}

// ******************** Miscellaneous Operation CoProcessor Command Functions ******************************

// *** Cmd_SetBitmap - generate DL commands for bitmap parms - FT81x Series Programmers Guide Section 5.65 *******
void Cmd_SetBitmap(uint32_t addr, uint16_t fmt, uint16_t width, uint16_t height)
{
  Send_CMD( CMD_SETBITMAP );
  Send_CMD( addr );
  Send_CMD( ((uint32_t)width << 16) | fmt );
  Send_CMD( (uint32_t)height);
}


// *** Cmd_Memcpy - background copy a block of data - FT81x Series Programmers Guide Section 5.27 ****************
void Cmd_Memcpy(uint32_t dest, uint32_t src, uint32_t num)
{
  Send_CMD(CMD_MEMCPY);
  Send_CMD(dest);
  Send_CMD(src);
  Send_CMD(num);
}

// *** Cmd_GetPtr - Get the last used address from CoPro operation - FT81x Series Programmers Guide Section 5.47 *
void Cmd_GetPtr(void)
{
  Send_CMD(CMD_GETPTR);
  Send_CMD(0);
}

// *** Set Highlight Gradient Color - FT81x Series Programmers Guide Section 5.32 ********************************
void Cmd_GradientColor(uint32_t c)
{
  Send_CMD(CMD_GRADCOLOR);
  Send_CMD(c);
}

// *** Set FG color - FT81x Series Programmers Guide Section 5.30 ************************************************
void Cmd_FGcolor(uint32_t c)
{
  Send_CMD(CMD_FGCOLOR);
  Send_CMD(c);
}

// *** Set BG color - FT81x Series Programmers Guide Section 5.31 ************************************************
void Cmd_BGcolor(uint32_t c)
{
  Send_CMD(CMD_BGCOLOR);
  Send_CMD(c);
}

// *** Translate Matrix - FT81x Series Programmers Guide Section 5.51 ********************************************
void Cmd_Translate(uint32_t tx, uint32_t ty)
{
  Send_CMD(CMD_TRANSLATE);
  Send_CMD(tx);
  Send_CMD(ty);
}

// *** Rotate Matrix - FT81x Series Programmers Guide Section 5.50 ***********************************************
void Cmd_Rotate(uint32_t a)
{
  Send_CMD(CMD_ROTATE);
  Send_CMD(a);
}

// *** Rotate Screen - FT81x Series Programmers Guide Section 5.53 ***********************************************
void Cmd_SetRotate(uint32_t rotation)
{
  Send_CMD(CMD_SETROTATE);
  Send_CMD(rotation);
}

// *** Scale Matrix - FT81x Series Programmers Guide Section 5.49 ************************************************
void Cmd_Scale(uint32_t sx, uint32_t sy)
{
  Send_CMD(CMD_SCALE);
  Send_CMD(sx);
  Send_CMD(sy);
}

void Cmd_SetFont(uint32_t font, uint32_t ptr) //Added by RJA
{
    Send_CMD(CMD_SETFONT);
    Send_CMD(font);
    Send_CMD(ptr);
}

void Cmd_SetFont2(uint32_t font, uint32_t ptr, uint32_t firstchar) //Added by RJA
{
    Send_CMD(CMD_SETFONT2);
    Send_CMD(font);
    Send_CMD(ptr);
    Send_CMD(firstchar);
}





// *** Calibrate Touch Digitizer - FT81x Series Programmers Guide Section 5.52 ***********************************
// * This business about "result" in the manual really seems to be simply leftover cruft of no purpose - send zero
void Cmd_Calibrate(uint32_t result)
{
  Send_CMD(CMD_CALIBRATE);
  Send_CMD(result);
}

// An interactive calibration screen is created and executed.  
// New calibration values are written to the touch matrix registers of Eve.
void Calibrate_Manual(uint16_t Width, uint16_t Height, uint16_t V_Offset, uint16_t H_Offset)
{
  uint32_t displayX[3], displayY[3];
  uint32_t touchX[3], touchY[3]; 
  uint32_t touchValue = 0, storedValue = 0;  
  int32_t tmp, k;
  int32_t TransMatrix[6];
  uint8_t count = 0;
  char num[2];
  uint8_t touch_lock = 1;

  // These values determine where your calibration points will be drawn on your display
  displayX[0] = (Width * 0.15) + H_Offset;
  displayY[0] = (Height * 0.15) + V_Offset;
  
  displayX[1] = (Width * 0.85) + H_Offset;
  displayY[1] = (Height / 2) + V_Offset;
  
  displayX[2] = (Width / 2) + H_Offset;
  displayY[2] = (Height * 0.85) + V_Offset;

  while (count < 3) 
  {
    Send_CMD(CMD_DLSTART);
    Send_CMD(CLEAR_COLOR_RGB(64, 64, 64));
    Send_CMD(CLEAR(1,1,1));

    // Draw Calibration Point on screen
    Send_CMD(COLOR_RGB(255, 0, 0));
    Send_CMD(POINT_SIZE(20 * 16));
    Send_CMD(BEGIN(POINTS));
    Send_CMD(VERTEX2F((uint32_t)(displayX[count]) * 16, (uint32_t)((displayY[count])) * 16)); 
    Send_CMD(END());
    Send_CMD(COLOR_RGB(255, 255, 255));
    Cmd_Text((Width / 2) + H_Offset, (Height / 3) + V_Offset, 27, OPT_CENTER, "Calibrating");
    Cmd_Text((Width / 2) + H_Offset, (Height / 2) + V_Offset, 27, OPT_CENTER, "Please tap the dots");
    num[0] = count + 0x31; num[1] = 0;                                            // null terminated string of one character
    Cmd_Text(displayX[count], displayY[count], 27, OPT_CENTER, num);

    Send_CMD(DISPLAY());
    Send_CMD(CMD_SWAP);
    UpdateFIFO();                                                                 // Trigger the CoProcessor to start processing commands out of the FIFO
    Wait4CoProFIFOEmpty();                                                        // wait here until the coprocessor has read and executed every pending command.

    while(1)
    {
      touchValue = rd32(REG_TOUCH_DIRECT_XY + RAM_REG); 	// Read for any new touch tag inputs
			
      if(touch_lock)
      {
        if(touchValue & 0x80000000) // check if we have no touch
          {
            touch_lock = 0;
          }
      }
      else
      {
        if (!(touchValue & 0x80000000)) // check if a touch is detected
          {
            touchX[count] = (touchValue>>16) & 0x03FF;	// Raw Touchscreen Y coordinate
            touchY[count] = touchValue & 0x03FF;		// Raw Touchscreen Y coordinate
            touch_lock = 1;
            count++;
            break; // leave while(1)
          }
      }
    }
  }

  k = ((touchX[0] - touchX[2]) * (touchY[1] - touchY[2])) - ((touchX[1] - touchX[2]) * (touchY[0] - touchY[2])); 
  
  tmp = (((displayX[0] - displayX[2]) * (touchY[1] - touchY[2])) - ((displayX[1] - displayX[2])*(touchY[0] - touchY[2])));
  TransMatrix[0] = CalcCoef(tmp, k);

  tmp = (((touchX[0] - touchX[2]) * (displayX[1] - displayX[2])) - ((displayX[0] - displayX[2])*(touchX[1] - touchX[2])));  
  TransMatrix[1] = CalcCoef(tmp, k);
  
  tmp = ((touchY[0] * (((touchX[2] * displayX[1]) - (touchX[1] * displayX[2])))) + (touchY[1] * (((touchX[0] * displayX[2]) - (touchX[2] * displayX[0])))) + (touchY[2] * (((touchX[1] * displayX[0]) - (touchX[0] * displayX[1])))));    
  TransMatrix[2] = CalcCoef(tmp, k);
    
  tmp = (((displayY[0] - displayY[2]) * (touchY[1] - touchY[2])) - ((displayY[1] - displayY[2])*(touchY[0] - touchY[2])));  
  TransMatrix[3] = CalcCoef(tmp, k);
    
  tmp = (((touchX[0] - touchX[2]) * (displayY[1] - displayY[2])) - ((displayY[0] - displayY[2])*(touchX[1] - touchX[2])));  
  TransMatrix[4] = CalcCoef(tmp, k);
    
  tmp = ((touchY[0] * (((touchX[2] * displayY[1]) - (touchX[1] * displayY[2])))) + (touchY[1] * (((touchX[0] * displayY[2]) - (touchX[2] * displayY[0])))) + (touchY[2] * (((touchX[1] * displayY[0]) - (touchX[0] * displayY[1])))));  
  TransMatrix[5] = CalcCoef(tmp, k);
  
  count = 0;
  do
  {
    wr32(REG_TOUCH_TRANSFORM_A + RAM_REG + (count * 4), TransMatrix[count]);  // Write to Eve config registers

//    uint16_t ValH = TransMatrix[count] >> 16;
//    uint16_t ValL = TransMatrix[count] & 0xFFFF;
//    Log("TM%d: 0x%04x %04x\n", count, ValH, ValL);
    
    count++;
  }while(count < 6);
}

// ***************************************************************************************************************
// *** Utility and helper functions ******************************************************************************
// ***************************************************************************************************************

// Find the space available in the GPU AKA CoProcessor AKA command buffer AKA FIFO
uint16_t CoProFIFO_FreeSpace(void)
{
  uint16_t cmdBufferDiff, cmdBufferRd, cmdBufferWr, retval;
  
  cmdBufferRd = rd16(REG_CMD_READ + RAM_REG);
  cmdBufferWr = rd16(REG_CMD_WRITE + RAM_REG);
    
  cmdBufferDiff = (cmdBufferWr-cmdBufferRd) % FT_CMD_FIFO_SIZE; // FT81x Programmers Guide 5.1.1
  retval = (FT_CMD_FIFO_SIZE - 4) - cmdBufferDiff;
  return (retval);
}

// Sit and wait until there are the specified number of bytes free in the <GPU/CoProcessor> incoming FIFO
void Wait4CoProFIFO(uint32_t room)
{
   uint16_t getfreespace;
   
   do {
     getfreespace = CoProFIFO_FreeSpace();
     //usleep(100);
   }while(getfreespace < room);
}

// Sit and wait until the CoPro FIFO is empty
// Detect operational errors and print the error and stop.
bool Wait4CoProFIFOEmpty(void)
{
  uint16_t ReadReg;
  uint16_t WriteReg;
  uint8_t ErrChar;
  uint8_t buffy[2];
  uint8_t LoopCount = 0;

  WriteReg = rd16(REG_CMD_WRITE + RAM_REG);
  do
  {
    ReadReg = rd16(REG_CMD_READ + RAM_REG);

    if(ReadReg == 0xFFF)
    {
      Log("\nW4CPFE: ");
      uint8_t Offset = 0;
      do
      {
        // Get the error character and display it
        ErrChar = rd8(RAM_ERR_REPORT + Offset);
        Offset++;
        sprintf(buffy, "%c", ErrChar);
        Log(buffy);
      }while ( (ErrChar != 0) && (Offset < 128) ); // when the last stuffed character was null, we are done
      Log("\n");

      // Eve is unhappy - needs a paddling.
      uint16_t Patch_Add = rd16( REG_COPRO_PATCH_PTR + RAM_REG );
      wr32( REG_CPU_RESET + RAM_REG, 1 );
      wr32( REG_CMD_READ + RAM_REG, 0 );
      wr32( REG_CMD_WRITE + RAM_REG, 0 );
      wr32( REG_CMD_DL + RAM_REG, 0 );
      wr32( REG_PCLK + RAM_REG, 0 );
      WriteReg = FifoWriteLocation = 0;                     // reset our marker tracker variables
      wr32( REG_CPU_RESET + RAM_REG, 0 );
      MyDelay( 100 );
      wr16( REG_COPRO_PATCH_PTR + RAM_REG, Patch_Add );

      // If this is a BT81x and you were previously in fast flash mode, you will not be any more 
      //  - probably need to track the state and redo fast mode here.
    }

    if (LoopCount++ == 100) // 100 times around is waaay too much
    {
      Log("Eve stuck - W:%lu R:%lu\n", WriteReg, ReadReg);
      return false;
    }
    MyDelay(2);            // normalize operation for processor speed
  }while( ReadReg != WriteReg );

  return true;
}


// Every CoPro transaction starts with enabling the SPI and sending an address
void StartCoProTransfer(uint32_t address, uint8_t reading)
{
  SPI_Enable();
  if (reading){
    SPI_Write(address >> 16);
    SPI_Write(address >> 8);
    SPI_Write(address);
    SPI_Write(0);
  }else{
    SPI_Write((address >> 16) | 0x80); 
    SPI_Write(address >> 8);           
    SPI_Write(address);                
  }
}

// *** CoProWrCmdBuf() - Transfer a buffer into the CoPro FIFO as part of an ongoing command operation ***********
void CoProWrCmdBuf(const uint8_t *buff, uint32_t count)
{
  uint32_t TransferSize = 0;
  int32_t Remaining = count; // signed

  do {                
    // Here is the situation:  You have up to about a megabyte of data to transfer into the FIFO
    // Your buffer is LogBuf - limited to 64 bytes (or some other value, but always limited).
    // You need to go around in loops taking 64 bytes at a time until all the data is gone.
    //
    // Most interactions with the FIFO are started and finished in one operation in an obvious fashion, but 
    // here it is important to understand the difference between Eve RAM registers and Eve FIFO.  Even though 
    // you are in the middle of a FIFO operation and filling the FIFO is an ongoing task, you are still free 
    // to write and read non-FIFO registers on the Eve chip.
    //
    // Since the FIFO is 4K in size, but the RAM_G space is 1M in size, you can not, obviously, send all
    // the possible RAM_G data through the FIFO in one step.  Also, since the Eve is not capable of updating
    // it's own FIFO pointer as data is written, you will need to intermittently tell Eve to go process some
    // FIFO in order to make room in the FIFO for more RAM_G data.    

    //RJA:  Not sure what is going on, but had to reduce WorkBuffSz to get it to work with faster SPI frequencies...

     Wait4CoProFIFO(WorkBuffSz);                            // It is reasonable to wait for a small space instead of firing data piecemeal

    if (Remaining >  WorkBuffSz)                            // Remaining data exceeds the size of our buffer
        TransferSize = WorkBuffSz;                          // So set the transfer size to that of our buffer
    else
    {
      TransferSize = Remaining;                            // Set size to this last dribble of data
      TransferSize = (TransferSize + 3) & 0xFFC;           // 4 byte alignment
    }
    
    StartCoProTransfer(FifoWriteLocation + RAM_CMD, false);// Base address of the Command Buffer plus our offset into it - Start SPI transaction
    
    SPI_WriteBuffer((uint8_t*)buff, TransferSize);         // write the little bit for which we found space
    buff += TransferSize;                                  // move the working data read pointer to the next fresh data

    FifoWriteLocation  = (FifoWriteLocation + TransferSize) % FT_CMD_FIFO_SIZE;  
    
    SPI_Disable();                                         // End SPI transaction with the FIFO
    
    wr16(REG_CMD_WRITE + RAM_REG, FifoWriteLocation);      // Manually update the write position pointer to initiate processing of the FIFO
    Remaining -= TransferSize;                             // reduce what we want by what we sent
    
    
  }while (Remaining > 0);                                  // keep going as long as we still want more
}

// Write a block of data into Eve RAM space a byte at a time.
// Return the last written address + 1 (The next available RAM address)
uint32_t WriteBlockRAM( uint32_t Add, uint8_t *buff, uint32_t count )
{
  uint16_t index;
  uint32_t WriteAddress = Add;  // I want to return the value instead of modifying the variable in place

  SPI_Enable();

  SPI_Write((uint8_t)((WriteAddress >> 16) | 0x80)); // RAM_REG = 0x302000 and high bit is set - result always 0xB0
  SPI_Write((uint8_t)(WriteAddress >> 8));           // Next byte of the register address   
  SPI_Write((uint8_t)(WriteAddress));                // Low byte of register address - usually just the 1 byte offset
  SPI_WriteBuffer(buff, count);


  SPI_Disable();
  WriteAddress += count;
  return (WriteAddress);
}

// LoadFile() ( 5.76 - CMD_FLASHREAD )
// dest - Destination address in RAM_G.  Must be 4-byte aligned.
// src - Source address in flash memory.  Must be 64-byte aligned.
// num - Number of bytes to write.  Must be multiple of 4
void LoadFile( uint32_t src, uint32_t dest, uint32_t num )
{
  Send_CMD( CMD_FLASHREAD );
  Send_CMD( dest );                                                  // Address we are writing to
  Send_CMD( src );                                                   // Address we are reading from
  Send_CMD( num );                                                   // number of bytes to transfer
  UpdateFIFO();                                                      // Trigger the CoProcessor to start processing commands out of the FIFO
  Wait4CoProFIFOEmpty();                                             // wait here until the co-processor has read and executed every pending command.
  MyDelay( 50 );  // YES OR NOT????????????????????????????????????????????????????????????

  Log( "LoadFile: File Copied %ld to %ld from %ld\n", num, dest, src & 0x7FFFFF );
}

// CalcCoef - Support function for manual screen calibration function
int32_t CalcCoef(int32_t Q, int32_t K)
{
  int8_t sn = 0;

  if (Q < 0)                                       // We need to work with positive values
  {
    Q *= -1;                                       // So here we make them positive
    sn++;                                          // and remember that fact
  }

  if (K < 0)                                       
  {
    K *= -1;
    sn++;                                          // 1 + 1 = 2 = 0b00000010
  }  
  
  uint32_t I = ((uint32_t)Q / (uint32_t)K) << 16;  // get the integer part and shift it by 16
  uint32_t R = Q % K;                              // get the remainder of a/k;
  R = R << 14;                                     // shift by 14 
  R = R / K;                                       // divide
  R = R << 2;                                      // Make up for the missing bits  
  int32_t returnValue = I + R;                     // combine them

  if (sn & 0x01)                                   // If the result is supposed to be negative
    returnValue *= -1;                             // then return it to that state.
      
  return (returnValue);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Here starts stuff from "process.c"

// This define is for the size of the buffer we are going to use for data transfers.  It is 
// sitting here so uncomfortably because it is a silly tiny buffer in Arduino Uno and you
// will want a bigger one if you can get it.  Redefine this and add a nice buffer to Load_ZLIB()
#define COPYBUFSIZE (1024) //Should probably be multiple of 512 Plan9 currently has limit... (2000)//RJA WorkBuffSz
char LogBuf[COPYBUFSIZE];//COPYBUFSIZE];

// Load a JPEG image from SD card into RAM_G at address "BaseAdd"
// Return value is the last RAM_G address used during the jpeg decompression operation.
// The function is virtually identical to Load_ZLIB as the only difference is the memory operation
uint32_t Load_JPG(uint32_t BaseAdd, uint32_t Options, char* filename)
{
    uint32_t Remaining;
    uint16_t ReadBlockSize = 0;

    // Open the file on SD card by name
    FILE* f = fopen(filename, "rb");
    if (!f)
    {
        Log("%s not open\n", filename);
        fclose(f);
        return 0;
    }


    Send_CMD(CMD_LOADIMAGE);                                   // Tell the CoProcessor to prepare for compressed data
    Send_CMD(BaseAdd);                                         // This is the address where decompressed data will go 
    Send_CMD(Options);                                         // Send options (options are mostly not obviously useful)


    printf("copying jpg to eve...\n");
    int n;
    while ((n = fread(LogBuf, 1, 512, f)) > 0)  //RJA we seem to have a limit somewhere between 1000 and 2000
    {
        CoProWrCmdBuf(LogBuf, n);
        //printf("%d bytes written\n", n);
        //do
        //{
        //} while (CoProFIFO_FreeSpace() < 1014);
    }
    fclose(f);

    printf("copy complete.\n");

    //Wait4CoProFIFOEmpty();                                     // wait here until the coprocessor has read and executed every pending command.

    // Get the address of the last RAM location used during inflation
    Cmd_GetPtr();                                              // FifoWriteLocation is updated twice so the data is returned to it's updated location - 4
    UpdateFIFO();                                              // force run the GetPtr command
    printf("load jpg result= %d\n", rd32(FifoWriteLocation + RAM_CMD-4)); //RJA:  Why is this zero?  Maybe this doesn't work with EVE3?
    return (rd32(FifoWriteLocation + RAM_CMD - 4));            // The result is stored at the FifoWriteLocation - 4 (Yes, this is unexpected and random)
}

// Load a raw (image data) bitmap from SD card into RAM_G at address 0
// The file will have been processed by "img_cvt.exe" from FTDI
// While the memory usage is not a mystery, the next available address is returned for convenience.
uint32_t Load_RAW(uint32_t BaseAdd, char* filename)
{
    uint32_t Remaining;
    uint16_t ReadBlockSize = 0;
    uint32_t Add_GRAM = BaseAdd;

    int r;  //How Eric Smith can tell filesize
    struct stat s;

    r = stat(filename, &s);
    if (r) {
        perror("Unable to stat file");
        return false;
    }

    // Open the file on SD card by name
    FILE* f = fopen(filename, "rb");
    if (!f)
    {
        Log("%s not open\n", filename);
        fclose(f);
        return false;
    }

    Remaining = s.st_size;                                      // Store the size of the currently opened file

    //printf("copying data to eve...\n");
    while (Remaining)
    {
        if (Remaining > COPYBUFSIZE)
            ReadBlockSize = COPYBUFSIZE;
        else
            ReadBlockSize = Remaining;

        fread(LogBuf, 1, ReadBlockSize, f);  //FileReadBuf(LogBuf, ReadBlockSize);                        // Read a block of data from the file
        //printf("writing %d bytes to address %d\n", ReadBlockSize, Add_GRAM);
        Add_GRAM = WriteBlockRAM(Add_GRAM, LogBuf, ReadBlockSize); // write the block to RAM_G
        Remaining -= ReadBlockSize;                                // Reduce remaining data value by amount just read
    }

    fclose(f);

    return (Add_GRAM);
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RJA adding some higher level functions


#define RGB(red, green, blue) ((((red) & 255UL) << 16) | (((green) & 255UL) << 8) | (((blue) & 255UL) << 0))

void ClearScreen(COLORREF c)  //clear screen with color c
{
    ClearColorRGB24(c);  
    Clear();
}

void DrawFilledCircle(int x, int y, COLORREF c, int r)  //draw a filled circle at pixel (x,y) in color c with radius r
{
    ColorRGB24(c);      // change colour
    PointSize(r * 16);    // set point size to DotSize pixels. Points = (pixels x 16)
    Begin(POINTS);                // start drawing point
    Vertex2f(x, y);  //assumes vertext format #0
}

void DrawLine(int x1, int y1, int x2, int y2, COLORREF c, int t)  //draw a line from pixel (x1,y1) to pixel (x2,y2) in color c that is t pixels thick
{
    ColorRGB24(c);      // change colour
    LineWidth(t << 4);
    Begin(LINES);                // start drawing point
    Vertex2f(x1, y1);  //assumes vertext format #0
    Vertex2f(x2, y2);  //assumes vertext format #0
}

void Cmd_RomFont(uint32_t FontHandle, uint32_t FontNumber)  //Section 5.61 in EVE Programming Guide
{//RJA this is useful for big fonts 32..34, where you need to assign them a handle
    Send_CMD(CMD_ROMFONT);
    Send_CMD(FontHandle);
    Send_CMD(FontNumber);
}

void DrawText(uint16_t x, uint16_t y, uint16_t font, uint16_t options, char* str, COLORREF c)
{
    ColorRGB24(c);      // change colour
    if ((font >= 32) && (font <= 34))
    {//Need to call CMD_ROMFONT for the big ones
        Cmd_RomFont(15, font);
        Cmd_Text(x, y, 15, options, str);
    }
    else
    {//easy with small fonts
        Cmd_Text(x, y, font, options, str);
    }
    
}

void TranslateXY(int x, int y)
{//translate to location (x,y)
    Send_CMD(VERTEX_TRANSLATE_X((x << 4) & 0x1FFFF));
    Send_CMD(VERTEX_TRANSLATE_Y((y << 4) & 0x1FFFF));
}

void TranslateX(int x)
{//translate to location (x,y)
    Send_CMD(VERTEX_TRANSLATE_X((x << 4) & 0x1FFFF));
}

void TranslateY(int y)
{//translate to location (x,y)
    Send_CMD(VERTEX_TRANSLATE_Y((y << 4) & 0x1FFFF));
}

void Cmd_Color_RGB(COLORREF c)
{
    Send_CMD(COLOR_RGB24(c));
}

void Configure_Bitmap_Handle(int nHandle, int address, int filter, int wrapx, int wrapy, int width, int height, int stride, int format) //prepare loaded raw image for display
{//Configure a bitmap in GRAM for use by handle
    Send_CMD(BITMAP_HANDLE(nHandle)); //set handle to nAsset
    Send_CMD(BITMAP_SOURCE(address)); //address in GRAM
    Send_CMD(BITMAP_SIZE(filter, wrapx, wrapy, width, height));
    //if width or height >511, need extra command for upper bits of size
    if ((width > 511) || (height > 511))
    {
        Send_CMD(BITMAP_SIZE_H(width >> 9, height >> 9));
    }
    Send_CMD(BITMAP_LAYOUT(format, stride, height));
    if ((stride > 1023) || (height > 511))
    {
        Send_CMD(BITMAP_LAYOUT_H(stride >> 10, height >> 9));
    }
}

void PrintRAM_G(int Source, int n)
{//Print n bytes from RAM_G starting at address Source
    for (int i = Source; i < n; i++)
    {
        printf("%#02X ", rd8(i));
        if (i % 16 == 7)
            printf(" ");
        if (i % 16 == 15)
            printf("\n");
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Here starts code needed for playing .avi videos, adapted from gd2-lib

#ifndef UsingMyYield
void Yield()
{//This is provided as a place to put code to run while playing the video
    //Cut this out from here and put in your code to use
    //Or, #define UsingMyYield
    usleep(100); //just for testing
}
#endif // !UsingMyYield

uint32_t mf_size, mf_base, mf_wp, mf_rp; //Media Fifo Size, Base address, write pointer and read pointer
FILE* f;
int filesize, bytesleft;
bool bEof;

void playVideo(const char* filename)
{//Play a .avi video using media fifo we will set up and top of RAM_G
    bEof = false; //flag for end of file

    mf_size = 0x40000UL;  //Using upper 262,144 bytes of megabyte RAM_G for media fifo
    mf_base = 0x100000UL - mf_size;  //base address of media fifo.  Note:  0x0FFFFF is the end of RAM_G, this puts the media fifo at the end of RAM_G 

    // Configure MEDIA FIFO
    cmd_mediafifo(mf_base, 0x40000UL);
    UpdateFIFO();
    Wait4CoProFIFOEmpty();  //Wait for this to process

    // stop media fifo
    wr32(REG_MEDIAFIFO_WRITE + RAM_REG, 0);

    // Check the read pointer where the GPU is working currently (should be zero)
    mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
    printf("Read pointer= %d\n", mf_rp);

    

    //RJA:  Now, fill the media fifo completely to get started, takes a second, maybe should load less?
    InitFifo(filename);

    // USE MEDIA_FIFO to play video
    Send_CMD(CMD_PLAYVIDEO);
    Send_CMD(OPT_MEDIAFIFO  | OPT_SOUND| OPT_FULLSCREEN); //OPT_FULLSCREEN| OPT_NOTEAR

    //Once we update the fifo write pointer using the next line, the GPU will begin decoding the image and sending to RAM_G
    mf_wp = mf_size / 2; //start by telling only half full
    wr32(REG_MEDIAFIFO_WRITE + RAM_REG, mf_wp);
    UpdateFIFO();
    Wait4CoProFIFOEmpty();

    do
    {//wait for processing to start
        mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
        printf("Read pointer= %X\n", mf_rp);
    } while (mf_rp == 0);


    mf_wp = 0;  //now that processing started, tell GPU that media fifo is actually full and wrapped around
    wr32(REG_MEDIAFIFO_WRITE + RAM_REG, mf_wp);
    UpdateFIFO();
    Wait4CoProFIFOEmpty();



    while (1)
    {//keep media fifo full
        RefillFifo();
        if (bEof)
            break;
        //You can do other things inside this loop by redefining Yield() in your app
        Yield();
    }

    fclose(f);

    //Wait for playback to complete
    WaitVideoEnd();
}

void WaitVideoEnd()
{//wait for video to end, disable and then enable again
    int last_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
    while (1)
    {//the read pointer with stop changing when playback is done.
        // Check the read pointer where the GPU is working currently
        usleep(1000);
        mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
        printf("\nRead pointer= %d, Last read pointer= %d\n", mf_rp, last_rp);
        if (mf_rp == last_rp)
            break;
        last_rp = mf_rp;
    }

    CycleVideoEnable();
}

void CycleVideoEnable()
{   //Disable video playback and then enable again
    wr32(REG_PLAY_CONTROL + RAM_REG, -1);  //Note:  This part seems necessary when SPI bitrate exceeds ~ 2 MBPS, not sure why
    //swap();
    UpdateFIFO();
    Wait4CoProFIFOEmpty();
    printf("Video playback complete.\n");
    wr32(REG_PLAY_CONTROL + RAM_REG, 1);
}

void RefillFifo()
{//if there's some room in media fifo, add data to it until full and then return
    // Check the read pointer, where the GPU is working currently
    uint32_t mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
    //printf("Read pointer= %X\n", mf_rp);
    //calculate space left in fifo
    uint32_t fullness = (mf_wp - rd32(REG_MEDIAFIFO_READ + RAM_REG)) & (mf_size - 1);
    //printf("Fullness= %d\n", fullness);
    while (fullness < (mf_size - COPYBUFSIZE))
    {//fill fifo up, while there's room
        mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
        //printf("Read pointer= %X, Write pointer=%X\n", mf_rp,mf_wp);
        LoadFifo();
        fullness += COPYBUFSIZE;
        wr32(REG_MEDIAFIFO_WRITE + RAM_REG, mf_wp);
        if (bEof)
            return;
    }
}

void LoadFifo()
{//read from file and write to media fifo
    int n = fread(LogBuf, 1, COPYBUFSIZE, f);
    bytesleft -= COPYBUFSIZE;
    //printf(".");
    if (n < COPYBUFSIZE)
    {
        bEof = true;
        n = ((n + 3) / 4) * 4; //long align n at end of file
    }
    WriteBlockRAM(mf_base + mf_wp, LogBuf, n); // write the block to RAM_G
    //printf("Wrote to: %X \n", mf_base + mf_wp);
    mf_wp = (mf_wp + n) & (mf_size - 1);
}


void InitFifo(const char* filename)  //adapted from Load_RAW to fill media fifo with beginning of video
{//Open the video file and load the media fifo with it
    uint32_t Remaining;
    uint16_t ReadBlockSize = 0;
    uint32_t Add_GRAM = mf_base;

    int r;  //How Eric Smith can tell filesize
    struct stat s;
    r = stat(filename, &s);
    if (r) {
        Log("Error:  Unable to stat file: %s", filename);
        return false;
    }
    // Open the file on SD card by name
    f = fopen(filename, "rb");
    if (!f)
    {
        Log("%s not open\n", filename);
        fclose(f);
        return false;
    }

    filesize = s.st_size;  // Store the size of the currently opened file in case needed by application
    Remaining = mf_size;  //Filling media fifo completely

    while (Remaining)
    {//read from file and write to media fifo
        if (Remaining > COPYBUFSIZE)
            ReadBlockSize = COPYBUFSIZE;
        else
            ReadBlockSize = Remaining;

        fread(LogBuf, 1, ReadBlockSize, f);  //FileReadBuf(LogBuf, ReadBlockSize);                        // Read a block of data from the file
        Add_GRAM = WriteBlockRAM(Add_GRAM, LogBuf, ReadBlockSize); // write the block to RAM_G
        Remaining -= ReadBlockSize;                                // Reduce remaining data value by amount just read
    }

    bytesleft = filesize - mf_size;  //assuming video size is bigger than media fifo
    return;
}

void cmd_getprops(uint32_t* ptr, uint32_t* width, uint32_t* height)
{//This code (adapted) from https://github.com/nutechsoftware/esp32toft81x gets the properties of the decoded image
    //This works in a strange way...  We write three 0xffffffff longs into the CMD FIFO and the GPU updates them with the info while processing the command.
    //So, we need to know our current position in the CMD FIFO, which is FifoWriteLocation

    Send_CMD(CMD_GETPROPS);

    // The data will be written starting here in the buffer so get the pointer
    uint32_t r = FifoWriteLocation + RAM_CMD;

    // Fill in memory where results will go with dummy data
    Send_CMD(0xffffffff); // Will be ptr
    Send_CMD(0xffffffff); // Will be width
    Send_CMD(0xffffffff); // Will be height

    // report back memory locations of the results to caller
    *ptr = r;
    r += 4;
    *width = r;
    r += 4;
    *height = r;
}

void cmd_getimage(uint32_t* ptr, uint32_t* fmt, uint32_t* width, uint32_t* height, uint32_t* pPalette)
{//Similar to cmd_getprops(), this new command also returns format of image
    //RJA Need EVE4 for this one
    Send_CMD(CMD_GETIMAGE);

    // The data will be written starting here in the buffer so get the pointer
    uint32_t r = FifoWriteLocation + RAM_CMD;

    // Fill in memory where results will go with dummy data
    Send_CMD(0xffffffff); // Will be ptr to image data
    Send_CMD(0xffffffff); // Will be format
    Send_CMD(0xffffffff); // Will be width
    Send_CMD(0xffffffff); // Will be height
    Send_CMD(0xffffffff); // Will be pointer to palette data


    //get the results
    *ptr = rd32(r);
    *fmt = rd32(r + 4);
    *width = rd32(r + 8);
    *height = rd32(r + 12);
    *pPalette = rd32(r + 16);
}



////////////////////////////////////////////////////////////////////////////////////////////////
// RJA adding some font metric support routines


int GetFontHeight(int nFont)
 {
     int pFontRoot = rd32(ROM_FONTROOT);
     int pWidths = pFontRoot + 148 * (nFont - 16);  //table starts at font 16
     return rd32(pWidths + 140);
 }

int GetFontCharWidth(int nFont, char c)
{
    int pFontRoot = rd32(ROM_FONTROOT);
    int pWidths = pFontRoot + 148 * (nFont - 16);  //table starts at font 16
    return rd8(pWidths + c);
}

int GetFontTextWidth(int nFont, char* p)
{
    int pFontRoot = rd32(ROM_FONTROOT);
    int pWidths = pFontRoot + 148 * (nFont - 16);  //table starts at font 16
    int width = 0;
    //printf("String len=%d\n", strlen(p));
    for (int i = 0; i < strlen(p); i++)
    {
        //printf("Len of %c = %d\n", p[i], rd8(pWidths + p[i]));
        width+= rd8(pWidths + p[i]);
    }
    return width;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//RJA Adding Flash support from Matrix Orbital example https://github.com/MatrixOrbital/EVE3-BT81x-Flash



bool FlashAttach(void)
{//Tell EVE to connect to it's flash chip
    Send_CMD(CMD_FLASHATTACH);
    UpdateFIFO();                                                        // Trigger the CoProcessor to start processing commands out of the FIFO
    Wait4CoProFIFOEmpty();                                               // wait here until the coprocessor has read and executed every pending command.

    uint8_t FlashStatus = rd8(REG_FLASH_STATUS + RAM_REG);
    if (FlashStatus != FLASH_STATUS_BASIC)
    {
        Log("FlashAttach: NOT attached\n");
        return false;
    }
    Log("FlashAttach: Attached\n");
    return true;
}

bool FlashDetach(void)
{//Tell EVE to disconnect from it's flash chip
    Send_CMD(CMD_FLASHDETACH);
    UpdateFIFO();                                                        // Trigger the CoProcessor to start processing commands out of the FIFO
    Wait4CoProFIFOEmpty();                                               // wait here until the coprocessor has read and executed every pending command.

    uint8_t FlashStatus = rd8(REG_FLASH_STATUS + RAM_REG);
    if (FlashStatus != FLASH_STATUS_DETACHED)
    {
        Log("FlashDetach: NOT detached\n");
        return false;
    }
    Log("FlashDetach: Detached\n");
    return true;
}

bool FlashFast(void)
{//Tell EVE to try to go to high speed mode, QPI
    Send_CMD(CMD_FLASHFAST);
    Send_CMD(0);
    UpdateFIFO();                                                        // Trigger the CoProcessor to start processing commands out of the FIFO
    Wait4CoProFIFOEmpty();                                               // wait here until the coprocessor has read and executed every pending command.

    uint8_t FlashStatus = rd8(REG_FLASH_STATUS + RAM_REG);
    if (FlashStatus != FLASH_STATUS_FULL)
    {//Fast mode failed, print out why
        Log("FlashFast: NOT full mode\n");
        //Get return value from CMD_FLASHFAST to see what went wrong
        usleep(1000);
        // Read the return code in cmd_buffer
        int ret_addr = (FifoWriteLocation - 4) & FIFO_SIZE_MASK;
        ret_addr = (ret_addr + 3) & FIFO_BYTE_ALIGNMENT_MASK;
        int error_code = rd32(RAM_CMD + ret_addr);
        printf("Error code= %X\n", error_code);
        return false;
    }
    Log("FlashFast: Full speed ahead\n");
    return true;
}

bool FlashErase(void)
{//Tell EVE to erase the flash chip.  Note:  Erasing the flash takes several seconds after this function returns, allow time or EVE will get stuck
    //Log("FlashErase: Erasing Flash\n");
    Send_CMD(CMD_FLASHERASE);
    UpdateFIFO();                                                        // Trigger the CoProcessor to start processing commands out of the FIFO
    //Log("FlashErase: Flash will be erased after 40 to 200 seconds for 16 MB flash.\n");
    Send_CMD(CMD_NOP);  //EVE3+ only
    Wait4CoProFIFO(4092);  //wait for erase to complete, CoPro moves from flash erase command to NOP command when done.
}


void FlashInit()//this one by RJA
{//Attach and try to switch to fast mode
    FlashAttach();
    FlashFast();
    UpdateFIFO();                                                       // Trigger the CoProcessor to start processing commands out of the FIFO
    Wait4CoProFIFOEmpty();                                              // wait here until the coprocessor has read and executed every pending command.
    // Read the return code in cmd_buffer
#define FIFO_SIZE_MASK                (4095)   // FIFO valid range from 0 to 4095
#define FIFO_BYTE_ALIGNMENT_MASK      (0xFFC)
    int ret_addr = (FifoWriteLocation - 4) & FIFO_SIZE_MASK;
    ret_addr = (ret_addr + 3) & FIFO_BYTE_ALIGNMENT_MASK;

    int error_code = rd32(RAM_CMD + ret_addr);
    printf("Flash Fast return code= %X\n", error_code);
}

void FlashRead(int Dest, int Source, int num)
{//Read num bytes from from flash address, Dest, into RAM_G address, Source
    Send_CMD(CMD_FLASHREAD);
    Send_CMD(Dest); //Dest
    Send_CMD(Source);  //Source
    Send_CMD(num); //num
    UpdateFIFO();
    Wait4CoProFIFOEmpty(); //wait here until done
}

//
//bool FlashGetFileParms(void)
//{
//    // Transfer the first 1024 bytes of flash into RAM_G or you could just transfer enough to get the actual size of the map and then do it again
//  //  Log("FlashGetFileParms Reading Flash\n");
//    Send_CMD(CMD_FLASHREAD);
//    Send_CMD(RAM_G);                                                    // Address we are writing to
//    Send_CMD(RAM_FLASH_POSTBLOB);                                       // Address we are reading from
//    Send_CMD(0x00000400);                                               // It will be 1K bytes - enough for quite a large list but check this
//    UpdateFIFO();                                                       // Trigger the CoProcessor to start processing commands out of the FIFO
//    Wait4CoProFIFOEmpty();                                              // wait here until the coprocessor has read and executed every pending command.
//
//    // File format for the .map is: 
//    // Filename = 12 characters padded with spaces
//    // a space and a colon and a space
//    // beginning address field of 6 characters padded with spaces
//    // a space and a colon and a space
//    // file size field of variable length - no padding
//    // end of line and carriage return (0D 0A)
//    // More of the same if needed
//    // One or more zeros to pad to 0x10 boundary.  I have no proof that this zero will be provided if the previous data happens to fall on the boundary.
//
//    uint32_t WorkingAddress = RAM_G;
//    for (uint8_t i = 0; i < NUM_IMAGES; i++)                             // One must assume that things are as planned and there are NUM_IMAGES images
//    {
//        uint8_t CharCount = 0;
//        uint8_t tmpBuf[LINE_LIMIT];
//
//        while (CharCount < LINE_LIMIT)
//        {
//            // get bytes and place in buffer.
//            tmpBuf[CharCount] = rd8(WorkingAddress++);
//
//            // Before going any further check for a zero.  There are no zeros anywhere until we have run out of map file
//            // Since we are done when we read enough lines, the zero should never be seen by us, so any zero encountered is an error
//            if (tmpBuf[CharCount] == 0x00)                                  // if we got a zero
//                return false;
//
//            if (tmpBuf[CharCount] == 0x0D)                                  // if we got the line end
//            {
//                if (rd8(WorkingAddress++) == 0x0A)                            // then see if we get the carriage return
//                {
//                    // We found an entry and we know where we are so let's monopolize on that and store the rest of the parameters now
//                    // If Bridgetek also save media parameters in the map file, we could parse and store things like bitmap dimensions
//                    // or number of frames of an animation and many other such useful information that we are now forced to hardcode.
//                    // We could make our own map file in a text editor
//
//                    CharCount = 0;
//                    while (tmpBuf[CharCount++] != 0x20);                        // run through the tmpbuf again looking for the first space
//                    tmpBuf[CharCount - 1] = 0x00;                                 // null terminate the filename string
//                    memcpy(FoundFiles[i].FileName, tmpBuf, strlen(tmpBuf) + 1);   // Copy the file name
//
//                    // the rest of the buffer is still valid - go to start of the start address (index = 15)
//                    // look for the next occurance of a space and replace that with a zero to make a string of it
//                    CharCount = 15;
//                    while (tmpBuf[CharCount++] != 0x20);
//                    tmpBuf[CharCount - 1] = 0x00;                                 // null terminate the start address string
//
//                    // I intended to use something like atol() or strtoul(), but could get neither to work properly 
//                    uint32_t tmp = 0;
//                    for (uint8_t i = 15; i < CharCount - 1; i++)
//                    {
//                        tmp *= 10;
//                        tmp += (tmpBuf[i] - '0');
//                    }
//                    FoundFiles[i].FlashAddress = tmp;
//                    Log("%s: %s = %lu\n", FoundFiles[i].FileName, &tmpBuf[15], FoundFiles[i].FlashAddress);
//                    break;                                                      // Entry complete, leave while loop
//                }
//            }
//            CharCount++;
//        }
//    }
//    return true;
//}





//// Load the output.bin file into flash if it exists
//// Return indicates whether it was done or not
//bool FlashLoad(void)
//{
//    // Check for the existence of the packed flash file (output.bin)
//    if (!FileExists("output.bin"))
//        return false; // File does not exist, so we do not need to load it into flash
//
//      // Check for the existence of the completion flag file (transfer.fin)
//    if (FileExists("transfer.fin"))
//        return false; // File exists indicating that the transfer has already occurred in the past
//
//      // upload file to flash
//    if (!FileTransfer2Flash("output.bin", RAM_FLASH))
//    {
//        //    Log("FlashLoad: File Operation Failed\n");
//        return false;
//    }
//
//    // Rename the file to "output.fin" <-- This is what you want, but Arduino has no
//    // rename function.  The rename was essentially a "flag" to tell this system
//    // whether the file transfer had already taken place or not.  I am going to
//    // make a file with a specific name ("transfer.fin") to indicate that it's done.
//    FileOpen("transfer.fin", FILEWRITE);
//    if (!myFileIsOpen())
//    {
//        //    Log("FlashLoad: No create file\n");
//        FileClose();
//        return false;
//    }
//    FileClose();
//
//    //  Log("output.bin automatically transferred to flash\n");
//    return true;
//}

uint32_t GetFlashSize()
{//return the size of attached flash in bytes
    return rd32(REG_FLASH_SIZE + RAM_REG) * 0x100000;            // A flash of 8M bytes which will report size = 8
}

void Cmd_FlashSource(int pSource)
{//Set the source of next image operation to be from flash with zero based address, pSource
    Send_CMD(CMD_FLASHSOURCE);                        // Tell the next command where to get it's data from in flash
    Send_CMD(pSource);//RAM_FLASH | tmp);                        // This is the address in Eve attached flash
}

void Cmd_FlashRead(int dest, int src, int num)
{//Read num bytes from flash starting at address src and store at RAM_G address dest
    Send_CMD(CMD_FLASHREAD);
    Send_CMD(dest);
    Send_CMD(src);
    Send_CMD(num);
}

//RJA:  This was doomed because cannot use assets the same way as done from uSD because can't insert flash loading commands into the command stream...
//void LoadAssetsFromFlash(int src, int size)
//{//Load assets from flash after initilizing the flash
//    FlashInit();
//
//    // Open the file on SD card by name
//    FILE* f = fopen("Assets.ant", "rb");
//    if (!f)
//    {
//        Log("%s not open\n", "Assets.ant");
//        fclose(f);
//        return 0;
//    }
//    int uadd = 0;
//    int nerrors = 0;
//
//    while (size>0)
//    {//read command flash and then send it to CoProcessor
//        printf("reading")
//        Cmd_FlashRead(RAM_G_WORKING, src, 1024);  //load 256 commands
//        src += 1024;
//        UpdateFIFO();                                                       // Trigger the CoProcessor to start processing commands out of the FIFO
//        Wait4CoProFIFOEmpty();                                              // wait here until the coprocessor has read and executed every pending command.
//        usleep(10000);
//
//        //printf("%08X = %08X \n", src-4, rd32(RAM_G_WORKING));
//        int nToSend = 1024;
//        if (size < nToSend)
//            nToSend = size;
//
//
//        printf("Sending %d...\n", nToSend);
//        int address = RAM_G_WORKING;
//
//        uint8_t u;
//        for (int i = 0; i < nToSend; i++)
//        {
//            LogBuf[i]= rd8(address);
//            address += 1;
//            fread(&u, 1, 1, f);
//            uadd++;
//            if (LogBuf[i] != u)
//            {
//                printf("Memory missmatch at %d, %d<>%d\n", uadd, LogBuf[i],u);
//                if (nerrors++>10)
//                    for (;;) {}
//            }
//        }
//        CoProWrCmdBuf(LogBuf, 1024);
//        
//
//        //int address = RAM_G_WORKING;
//        //for (int i=0;i<nToSend;i++) 
//        //{
//        //    //printf("%08x  ", rd32(address));
//        //    Send_CMD(rd32(address));
//        //    address += 4;
//        //    //if (true)// i % 256 == 0)
//        //    //{//wait for CoPro to catch up
//
//        //    //    
//        //    //}
//
//        //    //CoProWrCmdBuf(LogBuf, n);
//        //}
//        size -= nToSend;
//        printf("%d left\n",size);
//        //for (;;){}
//        //UpdateFIFO();                                                       // Trigger the CoProcessor to start processing commands out of the FIFO
//        //Wait4CoProFIFOEmpty();                                              // wait here until the coprocessor has read and executed every pending command.
//    }
//    //swap();
//
//}

// FileTransfer2Flash
// FlashAddress should be on a 4K boundary (multiple of 0x1000) - this is really important
bool FileTransfer2Flash(char* filename, uint32_t FlashAddress)
{// Transfer a file from SD card to Eve attached flash
    uint8_t FlashStatus;
    uint32_t FlashSize;

    // Read file size
    //uint32_t Remaining = FileSize();
    int r;  //How Eric Smith can tell filesize
    struct stat s;
    r = stat(filename, &s);
    if (r) {
        perror("Unable to stat file");
        return false;
    }
    // Open the file on SD card by name
    FILE* f = fopen(filename, "rb");
    if (!f)
    {
        Log("Cannot open file %s\n", filename);
        fclose(f);
        return false;
    }
    uint32_t Remaining = s.st_size;                                      // Store the size of the currently opened file    
    
    
    uint32_t FileSectors = Remaining / 0x1000;                        // Number of 4K sectors required to store file
    if (Remaining % 0x1000)                                            // If the file is not on 4K boundary (and when is it?)
        FileSectors++;                                                  // Add a 4K sector for the partial
    printf("# of 4k sectors in input file = %d\n", FileSectors);

    // Calculate file fitting and number of 4K blocks
    FlashSize = GetFlashSize();            // A flash of 8M bytes which will report size = 8
    printf("Flash size = %d, File Size=%d\n", FlashSize,Remaining);
    uint32_t SectorsAvailable = (FlashSize - (FlashAddress - RAM_FLASH)) / 0x1000;    // Number of 4K sectors available in the flash chip from the requested base address
    if (FileSectors > SectorsAvailable)
    {
        Log("FT2F: File does not fit\n");
        return false;                                                   // We can not continue without flash space to store file
    }

    printf("Copying...\n");
    uint32_t BufPerSector = 0x1000 / COPYBUFSIZE;
    // Write file in sectors to RAM_G at the working RAM space (RAM_G_WORKING)
    for (uint16_t h = 0; h < FileSectors; h++)                           // Loop through file data in 4K chunks until all 4K chunks have been processed
    {
        // Read file data COPYBUFSIZE at a time and write to RAM_G_WORKING space until 4K is reached
        // Each execution of this loop will stuff a 4K block into RAM_G
        for (uint16_t i = 0; i < BufPerSector; i++)
        {
            // Check each buffer load to see whether there is still more file than buffer
            // If there is enough data, then get the data into the buffer and subtract that amount from Remaining
            if (Remaining > COPYBUFSIZE)
            {
                //FileReadBuf(LogBuf, COPYBUFSIZE);
                fread(LogBuf, 1, COPYBUFSIZE, f);
                Remaining -= COPYBUFSIZE;
            }
            else
            {
                // There is not enough file data to fill buffer. Get what there is (if any) and fill the rest with ones
                // this should result in some number of manually padded buffer-loads being placed into RAM_G
                for (uint32_t j = 0; j < COPYBUFSIZE; j++)
                {
                    if (Remaining)
                    {
                        //LogBuf[j] = FileReadByte();
                        fread(&LogBuf[j], 1, 1, f);
                        Remaining--;
                       // printf("Remaining= %d\n", Remaining);
                    }
                    else
                    {
                        LogBuf[j] = 0xFF;
                        //printf("Last %d..  \n", j);
                    }
                        
                }
            }

            // Write the buffer to RAM_G
            WriteBlockRAM(RAM_G_WORKING + (i * COPYBUFSIZE), LogBuf, COPYBUFSIZE);
        }

        // Send the 4K buffer of data to flash via FIFO command
        Send_CMD(CMD_FLASHUPDATE);                                          // Transfer data from RAM_G into flash
        Send_CMD(FlashAddress + ((uint32_t)h * 0x1000));                    // Destination address in Flash 
        Send_CMD(RAM_G_WORKING);                                            // Source address in RAM_G
        Send_CMD(0x1000);                                                   // Number of bytes to transfer (4096)
        UpdateFIFO();                                                       // Trigger the CoProcessor to start processing commands out of the FIFO
        Wait4CoProFIFOEmpty();                                              // wait here until the coprocessor has read and executed every pending command.

    }
    fclose(f); // We are done with that file so close it
    printf("Returning true.\n");
    return true;
}


////RJA's code here not working...
////  Load a flash image from SD card into flash at address 0
////  Flash image .bin file created by Eve Asset Builder and includes the 4k Blob header
//void Load_Flash(char* filename)
//{
//    uint32_t Remaining;
//    uint16_t ReadBlockSize = 0;
//    uint32_t Add_GRAM = RAM_G;
//
//    int r;  //How Eric Smith can tell filesize
//    struct stat s;
//
//    r = stat(filename, &s);
//    if (r) {
//        perror("Unable to stat file");
//        return false;
//    }
//
//    // Open the file on SD card by name
//    FILE* f = fopen(filename, "rb");
//    if (!f)
//    {
//        Log("Cannot open file %s\n", filename);
//        fclose(f);
//        return false;
//    }
//    //Remaining = s.st_size;                                      // Store the size of the currently opened file
//
//    //sleep(2);
//    //Send_CMD(CMD_LOGO);
//    //Wait4CoProFIFOEmpty(); //wait here until done
//    //swap();
//    //sleep(10);
//
//
//    printf("Initializing flash...");
//    Send_CMD(CMD_FLASHDETACH);
//    Wait4CoProFIFOEmpty(); //wait here until done
//    Send_CMD(CMD_FLASHATTACH);
//    // Now check if the flash is in basic mode after attaching 
//    while (FLASH_STATUS_BASIC != rd8(REG_FLASH_STATUS+RAM_REG))
//    {
//        printf("Flash Status= %X\n", rd8(REG_FLASH_STATUS + RAM_REG));
//        usleep(100000);
//        Send_CMD(CMD_FLASHDETACH);
//        Send_CMD(CMD_FLASHATTACH);
//        Wait4CoProFIFOEmpty(); //wait here until done
//    };
//    
//
//    ////Load the blob into RAM_G and then copy to flash
//    //printf("copying Blob to RAM_G...\n");
//    //Remaining = 4096;
//    //while (Remaining)
//    //{
//    //    if (Remaining > COPYBUFSIZE)
//    //        ReadBlockSize = COPYBUFSIZE;
//    //    else
//    //        ReadBlockSize = Remaining;
//
//    //    fread(LogBuf, 1, ReadBlockSize, f);  //FileReadBuf(LogBuf, ReadBlockSize);                        // Read a block of data from the file
//    //    //printf("writing %d bytes to address %d\n", ReadBlockSize, Add_GRAM);
//    //    Add_GRAM = WriteBlockRAM(Add_GRAM, LogBuf, ReadBlockSize); // write the block to RAM_G
//    //    Remaining -= ReadBlockSize;                                // Reduce remaining data value by amount just read
//    //    Wait4CoProFIFOEmpty(); //wait here until done
//    //}
//
//    //printf("slow copying Blob from RAM_G to flash...\n");
//    //Send_CMD(CMD_FLASHUPDATE);
//    //Send_CMD(RAM_FLASH); //Dest
//    //Send_CMD(0); //Source
//    //Send_CMD(4096); //num
//    //Wait4CoProFIFOEmpty(); //wait here until done
//
//    //sleep(1);
//
//    //Send_CMD(CMD_FLASHWRITE);
//    //Send_CMD(0); //Dest
//    //Send_CMD(256);//num
//    //for (int i = 0; i < 256 / 4; i++)
//    //{
//    //    Send_CMD(0x1a2b3c4d);
//    //}    
//    //Wait4CoProFIFOEmpty(); //wait here until done
//
//    //Send_CMD(CMD_FLASHREAD);
//    //Send_CMD(4096); //Dest
//    //Send_CMD(0); //Source
//    //Send_CMD(4); //num
//    //Wait4CoProFIFOEmpty(); //wait here until done
//
//    //printf("%X = %X ?\n", rd32(0), rd32(4096));
//
//    ////Now, double check that we are in full speed mode
//    //while (true)
//    //{
//    //    printf("Flash Status= %X\n", rd8(REG_FLASH_STATUS + RAM_REG));
//    //    printf(".");
//    //    sleep(1);
//    //};
//
//    //for (;;) {}
//
//    ////read blob back from flash
//    //Send_CMD(CMD_FLASHREAD);
//    //Send_CMD(4096+RAM_G); //Dest
//    //Send_CMD(0); //Source
//    //Send_CMD(4096); //num
//    //Wait4CoProFIFOEmpty(); //wait here until done
//
//    ////compare readback to source
//    //for (int i = 0; i < 4096; i++)
//    //{
//    //    printf("%X = %X ?\n", rd8(i), rd8(i + 4096));
//    //}
//    //for (;;) {}
//
//
//    //Try to switch flash to full speed mode
//    // To check if the blob is valid , try to switch to full mode
//    uint32_t ret = FifoWriteLocation + RAM_CMD;  //location of result
//    Send_CMD(CMD_FLASHFAST);
//    Wait4CoProFIFOEmpty(); //wait here until done
//    
//    //Send_CMD(0xABCD); //result of above operation will be stored here, *r
//    //Wait4CoProFIFOEmpty(); //wait here until done
//    int result = rd32(ret); //fetch result
//    printf("Result of CMD_FLASHFAST= %X\n", result);
//    for (;;) {}
//
//    //Now, double check that we are in full speed mode
//    while (FLASH_STATUS_FULL != rd8(REG_FLASH_STATUS + RAM_REG))
//    {
//        printf("Flash Status= %X\n", rd8(REG_FLASH_STATUS + RAM_REG));
//        printf(".");
//        usleep(100000);
//    };
//
//    //Now, copy the rest of the data to flash
//    printf("Now copying remaining data to flash...");
//    Remaining= s.st_size-4096;
//    uint32_t Add_Flash = 4096; //start just past Blob
//    while (Remaining)
//    {
//        if (Remaining > COPYBUFSIZE)
//            ReadBlockSize = COPYBUFSIZE;
//        else
//            ReadBlockSize = Remaining;
//
//        //fread(LogBuf, 1, ReadBlockSize, f);  //FileReadBuf(LogBuf, ReadBlockSize);                        // Read a block of data from the file
//        Send_CMD(CMD_FLASHWRITE);
//        Send_CMD(Add_Flash);
//        Send_CMD(COPYBUFSIZE);
//        uint32_t buff;
//        while (ReadBlockSize > 0)
//        {//send over data, one long at a time
//            fread(&buff, 1, 4, f);
//            ReadBlockSize -= 4;
//            Send_CMD(buff);
//        }
//        Remaining -= ReadBlockSize;                                // Reduce remaining data value by amount just read
//        Wait4CoProFIFOEmpty(); //wait here until done
//        printf("*");
//    }
//
//    printf("Copy to flash complete.\n");
//    fclose(f);
//    return;
//}





