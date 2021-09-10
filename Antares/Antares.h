//Antares.h - FTDI/Bridgetek Eve 2,3,4 driver for Propeller2 and FlexSpin C
//Copyright 2020-2021 Raymond Allen, MIT licence (except parts from "gd2-lib", which have BSD-3 license)

//This code is based on "gd2-lib" by James Bowman (BSD-3 license) and "EVE2-Library" by Matrix Orbital (MIT license)
//We are very appreciative of these codes
//"gd2-lib" and license info can be found here:  https://github.com/jamesbowman/gd2-lib
//"EVE2-Library" and license info can be found here:  https://github.com/MatrixOrbital/EVE2-Library

#ifndef _ANTARES_H_
#define _ANTARES_H_

//RJA:  Note:  To make the build line simpler, Anteres.c is included below, near line 428

#include "..\Platform\Platform.h"  //type of display and P2 pin#s to use and more are here

// Global Variables 
uint16_t FifoWriteLocation = 0;  // Don't allow this variable to get out of synch - be careful about manually constructing FIFO commands
typedef uint32_t COLORREF;
typedef uint32_t* LPCOLORREF;

#define WorkBuffSz 16//64 larger buffer doesn't seem to work with higher SPI speeds

#define MyDelay _waitms
#define Log  printf

#define FIFO_SIZE_MASK                (4095)   // FIFO valid range from 0 to 4095
#define FIFO_BYTE_ALIGNMENT_MASK      (0xFFC)

#define HCMD_ACTIVE      0x00
#define HCMD_STANDBY     0x41
#define HCMD_SLEEP       0x42
#define HCMD_PWRDOWN     0x50
#define HCMD_CLKINT      0x48
#define HCMD_CLKEXT      0x44
#define HCMD_CLK48M      0x62
#define HCMD_CLK36M      0x61
#define HCMD_CORERESET   0x68

#define CMD_APPEND           0xFFFFFF1E
#define CMD_BGCOLOR          0xFFFFFF09
#define CMD_BUTTON           0xFFFFFF0D
#define CMD_CALIBRATE        0xFFFFFF15 // 4294967061UL
#define CMD_CLOCK            0xFFFFFF14
#define CMD_COLDSTART        0xFFFFFF32
#define CMD_CRC              0xFFFFFF18
#define CMD_DIAL             0xFFFFFF2D
#define CMD_DLSTART          0xFFFFFF00
#define CMD_FGCOLOR          0xFFFFFF0A
#define CMD_GAUGE            0xFFFFFF13
#define CMD_GETMATRIX        0xFFFFFF33
#define CMD_GETPROPS         0xFFFFFF25
#define CMD_GETPTR           0xFFFFFF23
#define CMD_GRADCOLOR        0xFFFFFF34
#define CMD_GRADIENT         0xFFFFFF0B
#define CMD_INFLATE          0xFFFFFF22
#define CMD_INFLATE2         0xFFFFFF50
#define CMD_INTERRUPT        0xFFFFFF02
#define CMD_KEYS             0xFFFFFF0E
#define CMD_LOADIDENTITY     0xFFFFFF26
#define CMD_LOADIMAGE        0xFFFFFF24
#define CMD_LOGO             0xFFFFFF31
#define CMD_MEDIAFIFO        0xFFFFFF39
#define CMD_MEMCPY           0xFFFFFF1D
#define CMD_MEMCRC           0xFFFFFF18
#define CMD_MEMSET           0xFFFFFF1B
#define CMD_MEMWRITE         0xFFFFFF1A
#define CMD_MEMZERO          0xFFFFFF1C
#define CMD_NUMBER           0xFFFFFF2E//RJA fixed this 0xFFFFFF38
#define CMD_PLAYVIDEO        0xFFFFFF3A
#define CMD_PROGRESS         0xFFFFFF0F
#define CMD_REGREAD          0xFFFFFF19
#define CMD_ROTATE           0xFFFFFF29
#define CMD_SCALE            0xFFFFFF28
#define CMD_SCREENSAVER      0xFFFFFF2F
#define CMD_SCROLLBAR        0xFFFFFF11
#define CMD_SETBITMAP        0xFFFFFF43
#define CMD_SETFONT          0xFFFFFF2B
#define CMD_SETFONT2         0xFFFFFF3B //RJA
#define CMD_SETMATRIX        0xFFFFFF2A
#define CMD_SETROTATE        0xFFFFFF36
#define CMD_SKETCH           0xFFFFFF30
#define CMD_SLIDER           0xFFFFFF10
#define CMD_SNAPSHOT         0xFFFFFF1F
#define CMD_SPINNER          0xFFFFFF16
#define CMD_STOP             0xFFFFFF17
#define CMD_SWAP             0xFFFFFF01
#define CMD_TEXT             0xFFFFFF0C
#define CMD_TOGGLE           0xFFFFFF12
#define CMD_TRACK            0xFFFFFF2C
#define CMD_TRANSLATE        0xFFFFFF27
#define CMD_VIDEOFRAME       0xFFFFFF41
#define CMD_VIDEOSTART       0xFFFFFF40

// BT81X COMMANDS 
#define CMD_FLASHERASE       0xFFFFFF44
#define CMD_FLASHWRITE       0xFFFFFF45
#define CMD_FLASHREAD        0xFFFFFF46
#define CMD_FLASHUPDATE      0xFFFFFF47
#define CMD_FLASHDETACH      0xFFFFFF48
#define CMD_FLASHATTACH      0xFFFFFF49
#define CMD_FLASHFAST        0xFFFFFF4A
#define CMD_FLASHSPIDESEL    0xFFFFFF4B
#define CMD_FLASHSPITX       0xFFFFFF4C
#define CMD_FLASHSPIRX       0xFFFFFF4D
#define CMD_FLASHSOURCE      0xFFFFFF4E
#define CMD_CLEARCACHE       0xFFFFFF4F
#define CMD_FLASHAPPENDF     0xFFFFFF59
#define CMD_VIDEOSTARTF      0xFFFFFF5F
#define CMD_ANIMSTART        0xFFFFFF53
#define CMD_ANIMSTOP         0xFFFFFF54
#define CMD_ANIMXY           0xFFFFFF55
#define CMD_ANIMDRAW         0xFFFFFF56
#define CMD_ANIMFRAME        0xFFFFFF5A

//RJA adding
#define CMD_ROMFONT         0xFFFFFF3F
#define CMD_GETIMAGE        0xFFFFFF64
#define CMD_PCLKFREQ        0xFFFFFF6A  //EVE4 only


#define DLSWAP_FRAME         2UL

#define OPT_CENTER           1536UL
#define OPT_CENTERX          512UL
#define OPT_CENTERY          1024UL
#define OPT_FLASH            64UL
#define OPT_FLAT             256UL
#define OPT_FULLSCREEN       8UL
#define OPT_MEDIAFIFO        16UL
#define OPT_MONO             1UL
#define OPT_NOBACK           4096UL
#define OPT_NODL             2UL
#define OPT_NOHANDS          49152UL
#define OPT_NOHM             16384UL
#define OPT_NOPOINTER        16384UL
#define OPT_NOSECS           32768UL
#define OPT_NOTEAR           4UL
#define OPT_NOTICKS          8192UL
#define OPT_RGB565           0UL
#define OPT_RIGHTX           2048UL
#define OPT_SIGNED           256UL
#define OPT_SOUND            32UL

//RJA this one seems new
#define OPT_OVERLAY 128UL

// Definitions for FT8xx co processor command buffer
#define FT_DL_SIZE           (8*1024)  // 8KB Display List buffer size
#define FT_CMD_FIFO_SIZE     (4*1024)  // 4KB coprocessor Fifo size
#define FT_CMD_SIZE          (4)       // 4 byte per coprocessor command of EVE

// Memory base addresses
#define RAM_G                    0x0
#define RAM_G_WORKING            0x0FF000 // This address may be used as the start of a 4K block to be used for copying data
#define RAM_DL                   0x300000
#define RAM_REG                  0x302000
#define RAM_CMD                  0x308000
#define RAM_ERR_REPORT           0x309800 // max 128 bytes null terminated string
#define RAM_FLASH                0x800000
#define RAM_FLASH_POSTBLOB       0x801000

// Graphics Engine Registers - FT81x Series Programmers Guide Section 3.1
// Addresses defined as offsets from the base address called RAM_REG and located at 0x302000
// Discussion: Defining this way leads to an additional add operation in code that can be avoided by defining
// these addresses as 32 bit values, but this is easily paid for in clarity and coorelation to documentation.
// Further, you can add defines together in code and allow the precompiler to do the add operation (as here).
#define REG_CSPREAD               0x68
#define REG_DITHER                0x60
#define REG_DLSWAP                0x54
#define REG_HCYCLE                0x2C
#define REG_HOFFSET               0x30    
#define REG_HSIZE                 0x34
#define REG_HSYNC0                0x38
#define REG_HSYNC1                0x3C
#define REG_OUTBITS               0x5C
#define REG_PCLK                  0x70
#define REG_PCLK_POL              0x6C
#define REG_PLAY                  0x8C
#define REG_PLAYBACK_FORMAT       0xC4
#define REG_PLAYBACK_FREQ         0xC0
#define REG_PLAYBACK_LENGTH       0xB8
#define REG_PLAYBACK_LOOP         0xC8
#define REG_PLAYBACK_PLAY         0xCC
#define REG_PLAYBACK_READPTR      0xBC
#define REG_PLAYBACK_START        0xB4
#define REG_PWM_DUTY              0xD4
#define REG_ROTATE                0x58
#define REG_SOUND                 0x88
#define REG_SWIZZLE               0x64
#define REG_TAG                   0x7C
#define REG_TAG_X                 0x74
#define REG_TAG_Y                 0x78
#define REG_VCYCLE                0x40
#define REG_VOFFSET               0x44
#define REG_VOL_SOUND             0x84
#define REG_VOL_PB                0x80
#define REG_VSYNC0                0x4C
#define REG_VSYNC1                0x50
#define REG_VSIZE                 0x48 

// Touch Screen Engine Registers - FT81x Series Programmers Guide Section 3.3
// Addresses defined as offsets from the base address called RAM_REG and located at 0x302000
#define REG_TOUCH_CONFIG          0x168
#define REG_TOUCH_TRANSFORM_A     0x150
#define REG_TOUCH_TRANSFORM_B     0x154
#define REG_TOUCH_TRANSFORM_C     0x158
#define REG_TOUCH_TRANSFORM_D     0x15C
#define REG_TOUCH_TRANSFORM_E     0x160
#define REG_TOUCH_TRANSFORM_F     0x164

// Resistive Touch Engine Registers - FT81x Series Programmers Guide Section 3.3.3 - Document confused
// Addresses defined as offsets from the base address called RAM_REG and located at 0x302000
#define REG_TOUCH_ADC_MODE        0x108
#define REG_TOUCH_CHARGE          0x10C
#define REG_TOUCH_DIRECT_XY       0x18C
#define REG_TOUCH_DIRECT_Z1Z2     0x190 
#define REG_TOUCH_MODE            0x104
#define REG_TOUCH_OVERSAMPLE      0x114
#define REG_TOUCH_RAW_XY          0x11C
#define REG_TOUCH_RZ              0x120
#define REG_TOUCH_RZTHRESH        0x118
#define REG_TOUCH_SCREEN_XY       0x124
#define REG_TOUCH_SETTLE          0x110
#define REG_TOUCH_TAG             0x12C
#define REG_TOUCH_TAG_XY          0x128

// Capacitive Touch Engine Registers - FT81x Series Programmers Guide Section 3.3.4
// Addresses defined as offsets from the base address called RAM_REG and located at 0x302000
#define REG_CTOUCH_MODE           0x104
#define REG_CTOUCH_EXTEND         0x108
#define REG_CTOUCH_RAW_XY         0x11C
#define REG_CTOUCH_TOUCH_XY       0x124
#define REG_CTOUCH_TOUCH1_XY      0x11C
#define REG_CTOUCH_TOUCH2_XY      0x18C
#define REG_CTOUCH_TOUCH3_XY      0x190
#define REG_CTOUCH_TOUCH4_X       0x16C
#define REG_CTOUCH_TOUCH4_Y       0x120
#define REG_CTOUCH_TAG            0x12C
#define REG_CTOUCH_TAG1           0x134
#define REG_CTOUCH_TAG2           0x13C
#define REG_CTOUCH_TAG3           0x144
#define REG_CTOUCH_TAG4           0x14C
#define REG_CTOUCH_TAG_XY         0x128
#define REG_CTOUCH_TAG1_XY        0x130
#define REG_CTOUCH_TAG2_XY        0x138
#define REG_CTOUCH_TAG3_XY        0x140
#define REG_CTOUCH_TAG4_XY        0x148

// Co-processor Engine Registers - FT81x Series Programmers Guide Section 3.4
// Addresses defined as offsets from the base address called RAM_REG and located at 0x302000
#define REG_CMD_DL                0x100
#define REG_CMD_READ              0xF8
#define REG_CMD_WRITE             0xFC
#define REG_CMDB_SPACE            0x574
#define REG_CMDB_WRITE            0x578
#define REG_COPRO_PATCH_PTR       0x7162

// Special Registers - FT81x Series Programmers Guide Section 3.5 
// Addresses assumed to be defined as offsets from the base address called RAM_REG and located at 0x302000
#define REG_TRACKER               0x7000
#define REG_TRACKER_1             0x7004
#define REG_TRACKER_2             0x7008
#define REG_TRACKER_3             0x700C
#define REG_TRACKER_4             0x7010
#define REG_MEDIAFIFO_READ        0x7014
#define REG_MEDIAFIFO_WRITE       0x7018

// Flash related registers
#define REG_FLASH_STATUS          0x5F0
#define REG_FLASH_SIZE            0x7024
#define CMD_NOP              4294967131UL

// Miscellaneous Registers - FT81x Series Programmers Guide Section 3.6 - Document inspecific about base address
// Addresses assumed to be defined as offsets from the base address called RAM_REG and located at 0x302000
#define REG_CPU_RESET             0x20
#define REG_PWM_DUTY              0xD4
#define REG_PWM_HZ                0xD0
#define REG_INT_MASK              0xB0
#define REG_INT_EN                0xAC
#define REG_INT_FLAGS             0xA8
#define REG_GPIO                  0x94
#define REG_GPIO_DIR              0x90
#define REG_GPIOX                 0x9C
#define REG_GPIOX_DIR             0x98
#define REG_FREQUENCY             0x0C
#define REG_CLOCK                 0x08
#define REG_FRAMES                0x04
#define REG_ID                    0x00
#define REG_TRIM                  0x10256C
#define REG_SPI_WIDTH             0x180
#define REG_CHIP_ID               0xC0000   // Temporary Chip ID location in RAMG

//RJA adding
#define REG_PLAY_CONTROL            0x714E 

// Primitive Type Reference Definitions - FT81x Series Programmers Guide Section 4.5 - Table 6
#define BITMAPS                    1
#define POINTS                     2
#define LINES                      3
#define LINE_STRIP                 4
#define EDGE_STRIP_R               5
#define EDGE_STRIP_L               6
#define EDGE_STRIP_A               7
#define EDGE_STRIP_B               8
#define RECTS                      9

// Bitmap Layout Format Definitions - FT81x Series Programmers Guide Section 4.7 - Table 7
#define ARGB1555                           0
#define L1                                 1
#define L4                                 2
#define L8                                 3
#define RGB332                             4
#define ARGB2                              5
#define ARGB4                              6
#define RGB565                             7
#define TEXT8X8                            9
#define TEXTVGA                           10
#define BARGRAPH                          11
#define PALETTED565                       14
#define PALETTED4444                      15
#define PALETTED8                         16
#define L2                                17

// Bitmap Layout Format Definitions - BT81X Series Programming Guide Section 4.6
#define COMPRESSED_RGBA_ASTC_4x4_KHR   37808  // 8.00
#define COMPRESSED_RGBA_ASTC_5x4_KHR   37809  // 6.40
#define COMPRESSED_RGBA_ASTC_5x5_KHR   37810  // 5.12
#define COMPRESSED_RGBA_ASTC_6x5_KHR   37811  // 4.27
#define COMPRESSED_RGBA_ASTC_6x6_KHR   37812  // 3.56
#define COMPRESSED_RGBA_ASTC_8x5_KHR   37813  // 3.20
#define COMPRESSED_RGBA_ASTC_8x6_KHR   37814  // 2.67
#define COMPRESSED_RGBA_ASTC_8x8_KHR   37815  // 2.56
#define COMPRESSED_RGBA_ASTC_10x5_KHR  37816  // 2.13
#define COMPRESSED_RGBA_ASTC_10x6_KHR  37817  // 2.00
#define COMPRESSED_RGBA_ASTC_10x8_KHR  37818  // 1.60
#define COMPRESSED_RGBA_ASTC_10x10_KHR 37819  // 1.28
#define COMPRESSED_RGBA_ASTC_12x10_KHR 37820  // 1.07
#define COMPRESSED_RGBA_ASTC_12x12_KHR 37821  // 0.89

// Bitmap Parameters
#define REPEAT                     1
#define BORDER                     0
#define NEAREST                    0
#define BILINEAR                   1

// Animation Parameters
#define ANIM_HOLD                  2UL
#define ANIM_LOOP                  1UL
#define ANIM_ONCE                  0UL

// Flash Status
#define FLASH_STATUS_INIT          0UL
#define FLASH_STATUS_DETACHED      1UL
#define FLASH_STATUS_BASIC         2UL
#define FLASH_STATUS_FULL          3UL

// These defined "macros" are supplied by FTDI - Manufacture command bit-fields from parameters
// FT81x Series Programmers Guide is refered to as "FT-PG"
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))                                                                                           // CLEAR - FT-PG Section 4.21
#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))     
#define CLEAR_COLOR_RGB24(RGBQUAD) ((2UL<<24)|RGBQUAD)  // CLEAR_COLOR_RGB - FT-PG Section 4.23
#define COLOR_RGB(red,green,blue) ((4UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))                                                               // COLOR_RGB - FT-PG Section 4.28
#define COLOR_RGB24(RGBQUAD) ((4UL<<24)|RGBQUAD)																													// COLOR_RGB - FT-PG Section 4.28
#define VERTEX2II(x,y,handle,cell) ((2UL<<30)|(((x)&511UL)<<21)|(((y)&511UL)<<12)|(((handle)&31UL)<<7)|(((cell)&127UL)<<0))                                              // VERTEX2II - FT-PG Section 4.48
#define VERTEX2F(x,y) ((1UL<<30)|(((x)&32767UL)<<15)|(((y)&32767UL)<<0))                                                                                                 // VERTEX2F - FT-PG Section 4.47
#define CELL(cell) ((6UL<<24)|(((cell)&127UL)<<0))                                                                                                                       // CELL - FT-PG Section 4.20
#define BITMAP_HANDLE(handle) ((5UL<<24) | (((handle) & 31UL) << 0))                                                                                                     // BITMAP_HANDLE - FT-PG Section 4.06
#define BITMAP_SOURCE(addr) ((1UL<<24)|(((addr)&4194303UL)<<0))                                                                                                        // BITMAP_SOURCE - FT-PG Section 4.11
#define BITMAP_LAYOUT(format,linestride,height) ((7UL<<24)|(((format)&31UL)<<19)|(((linestride)&1023UL)<<9)|(((height)&511UL)<<0))                                       // BITMAP_LAYOUT - FT-PG Section 4.07
#define BITMAP_SIZE(filter,wrapx,wrapy,width,height) ((8UL<<24)|(((filter)&1UL)<<20)|(((wrapx)&1UL)<<19)|(((wrapy)&1UL)<<18)|(((width)&511UL)<<9)|(((height)&511UL)<<0)) // BITMAP_SIZE - FT-PG Section 4.09
#define TAG(s) ((3UL<<24)|(((s)&255UL)<<0))                                                                                                                              // TAG - FT-PG Section 4.43
#define POINT_SIZE(sighs) ((13UL<<24)|(((sighs)&8191UL)<<0))                                                                                                             // POINT_SIZE - FT-PG Section 4.36
#define BEGIN(PrimitiveTypeRef) ((31UL<<24)|(((PrimitiveTypeRef)&15UL)<<0))                                                                                              // BEGIN - FT-PG Section 4.05
#define END() ((33UL<<24))                                                                                                                                               // END - FT-PG Section 4.30
#define DISPLAY() ((0UL<<24))            // DISPLAY - FT-PG Section 4.29

//RJA adding VERTEX_FORMAT
#define VERTEX_FORMAT(f) ((0x27<<24)|(f&0b111))                                                                                                 // VERTEX2F - FT-PG Section 4.47
#define VERTEX_FORMAT_ONE (0)
#define VERTEX_FORMAT_HALF (1)
#define VERTEX_FORMAT_QUARTER (2)
#define VERTEX_FORMAT_EIGTH (3)
#define VERTEX_FORMAT_SIXTEENTH (4)

//RJA adding size h and layout h
#define BITMAP_SIZE_H(width,height) ((41UL<<24)|(((width)&3UL)<<2)|(((height)&3UL)<<0))
#define BITMAP_LAYOUT_H(linestride,height) ((40UL<<24)|(((linestride)&3UL)<<2)|(((height)&3UL)<<0))
//RJA adding translateX and translateY
#define VERTEX_TRANSLATE_X(x) ((0x2b<<24)|(x<<0))
#define VERTEX_TRANSLATE_Y(y) ((0x2c<<24)|(y<<0))

// Non FTDI Helper Macros
#define MAKE_COLOR(r,g,b) (( r << 16) | ( g << 8) | (b))

// Global Variables
//extern uint16_t FifoWriteLocation; //RJA

// Function Prototypes
void FT81x_Init(void);
void Eve_Reset(void);

void HostCommand(uint8_t HostCommand);
void wr32(uint32_t address, uint32_t parameter);
void wr16(uint32_t, uint16_t parameter);
void wr8(uint32_t, uint8_t parameter);
uint8_t rd8(uint32_t RegAddr);
uint16_t rd16(uint32_t RegAddr);
uint32_t rd32(uint32_t RegAddr);
void Send_CMD(uint32_t data);
void UpdateFIFO(void);
uint8_t Cmd_READ_REG_ID(void);

// Widgets and other significant screen objects
void Cmd_Slider(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range);
void Cmd_Spinner(uint16_t x, uint16_t y, uint16_t style, uint16_t scale);
void Cmd_Gauge(uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range);
void Cmd_Dial(uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t val);
void Cmd_Track(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t tag);
void Cmd_Number(uint16_t x, uint16_t y, uint16_t font, uint16_t options, uint32_t num);
void Cmd_Gradient(uint16_t x0, uint16_t y0, uint32_t rgb0, uint16_t x1, uint16_t y1, uint32_t rgb1);
void Cmd_AnimDraw(int8_t AnimID);
void Cmd_AnimDrawFrame(uint32_t addr, uint16_t Xpos, uint16_t Ypos, uint8_t Frame);
void Cmd_Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t font, uint16_t options, const char* str);
void Cmd_Text(uint16_t x, uint16_t y, uint16_t font, uint16_t options, const char* str);

void Cmd_SetBitmap(uint32_t addr, uint16_t fmt, uint16_t width, uint16_t height);
void Cmd_Memcpy(uint32_t dest, uint32_t src, uint32_t num);
void Cmd_GetPtr(void);
void Cmd_GradientColor(uint32_t c);
void Cmd_FGcolor(uint32_t c);
void Cmd_BGcolor(uint32_t c);
void Cmd_Translate(uint32_t tx, uint32_t ty);
void Cmd_Rotate(uint32_t a);
void Cmd_SetRotate(uint32_t rotation);
void Cmd_Scale(uint32_t sx, uint32_t sy);
void Cmd_Calibrate(uint32_t result);
bool FlashAttach(void);
bool FlashDetach(void);
bool FlashFast(void);
bool FlashErase(void);

void Calibrate_Manual(uint16_t Width, uint16_t Height, uint16_t V_Offset, uint16_t H_Offset);

uint16_t CoProFIFO_FreeSpace(void);
void Wait4CoProFIFO(uint32_t room);
bool Wait4CoProFIFOEmpty(void);
void StartCoProTransfer(uint32_t address, uint8_t reading);
void CoProWrCmdBuf(const uint8_t* buffer, uint32_t count);
void LoadFile(uint32_t src, uint32_t dest, uint32_t num);
uint32_t WriteBlockRAM(uint32_t Add, const uint8_t* buff, uint32_t count);
int32_t CalcCoef(int32_t Q, int32_t K);

//Here starts stuff from process.h
uint32_t Load_JPG(uint32_t BaseAdd, uint32_t Options, char* filename);

//Defines for fonts
#define ROM_FONTROOT 0x2FFFFC 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Add in the low level code here
#include "Antares.c"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int w = HSIZE;
int h = VSIZE;
byte vxf;   // Vertex Format

#define F16(x)          ((int32_t)((x) * 65536L))  //RJA: Shifts x 16 bits left

uint32_t loadptr;

void begin()
{//Initialize EVE, make initial display list, and start another

    _setbaud(_BAUD); //we are using a faster baud (2000000 bps) to speed this up

    printf("ftinit..\n");
    FT81x_Init();
 
    //Make inital display list the prime swap()
    //Cmd_SetBase(10);
    Send_CMD(CMD_DLSTART);                   // Start a new display list
    ClearColorRGB(0, 0, 0);
    Clear();
    swap();

    vxf = 4;  //RJA:  EVE starts out with the need to shift pixel coordinates <<4 for vertex2f

    //get filesystem ready
#if defined(USE_SD)
    //mount("/files", _vfs_open_sdcard());  //For Eval pins
    mount("/files", _vfs_open_sdcardx(uSD_CLK, uSD_SS, uSD_MOSI, uSD_MISO));//clock pin, select pin, data in, and data out pins, in that order
//#define uSD_MISO  44 
//#define uSD_MOSI  46 
//#define uSD_SS  47 
//#define uSD_CLK  45
    chdir("/files");
#elif defined(USE_HOST)
    mount("/files", _vfs_open_host());
    chdir("/files");
#else
    #warning no file system specified, I hope you are compiling for PC
#endif
}



void Clear()
{// Clear the screen and the current display list
    Send_CMD(CLEAR(1, 1, 1));                
}

void ClearColorRGB(int r, int g, int b)
{ // Determine the clear screen color
    Send_CMD(CLEAR_COLOR_RGB(r, g, b));     
}

void ClearColorRGB24(int RGBQUAD)
{ // Determine the clear screen color
    Send_CMD(CLEAR_COLOR_RGB24(RGBQUAD));
}

void swap()
{//end and start this display list and then start another
    Send_CMD(DISPLAY());                     // End the display list
    Send_CMD(CMD_SWAP);                      // Swap commands into RAM
    UpdateFIFO();                            // Trigger the CoProcessor to start processing the FIFO
    Wait4CoProFIFOEmpty();                   // wait here until the coprocessor has read and executed every pending command.    
    Send_CMD(CMD_DLSTART);                   // Start a new display list
}


void cmd_text(uint16_t x, uint16_t y, uint16_t font, uint16_t options, const char* str)
{//draw text
    Cmd_Text(x, y, font, options, str);
}

void ColorRGB(byte red, byte green, byte blue)
{//change color
    Send_CMD(COLOR_RGB(red, green, blue));
}

void ColorRGB24(int RGBQUAD)
{//change color
    Send_CMD(COLOR_RGB24(RGBQUAD));
}

void PointSize(uint16_t size)
{// set point size to DotSize pixels. Points = (pixels x 16)
    Send_CMD(POINT_SIZE(size));      
}

void Begin(byte prim)
{// start drawing point
    Send_CMD(BEGIN(prim));                 
}

void Tag(byte s) 
{// Tag the blue dot with a touch ID
    Send_CMD(TAG(s));
}

void Vertex2ii(uint16_t x, uint16_t y, byte handle=0, byte cell=0)//, byte handle, byte cell)  //RJA:  Note Gameduino does not apper to use handle and cell parameters...
{// place point
    Send_CMD(VERTEX2II(x, y, handle, cell));// handle, cell));
}

//void Vertex2ii3(uint16_t x, uint16_t y, byte handle)
//{// place point
//    Send_CMD(VERTEX2II(x, y, handle, 0));
//}
//
//void Vertex2ii4(uint16_t x, uint16_t y, byte handle, byte cell)
//{// place point
//    Send_CMD(VERTEX2II(x, y, handle, cell));
//}

void End(void)
{// end drawing
    Send_CMD(END());
}

// convert integer pixels to subpixels
#define PIXELS(x)  (int)((x) * 16)

typedef struct  xyStruct {
    int x, y;
    //void set(int _x, int _y);
    //void rmove(int distance, int angle);
    //int angleto(class xy& other);
    void draw(byte offset)
    {//RJA Special class-like construct in FlexC
        Send_CMD(VERTEX2F(x - PIXELS(offset), y - PIXELS(offset)));
    }
    void set(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    //void rotate(int angle);
    //int onscreen(void);
    //class xy operator<<=(int d);
    //void LeftShiftEquals(int d);
    //class xy operator+=(class xy &other);
    //void PlusEquals(class xy& other);
    //class xy operator-=(class xy &other);
    //void MinusEquals(class xy& other);
    //long operator*(class xy &other);
    //int Times(class xy& other);
    //class xy operator*=(int);
    //void TimesEquals(int s);
    //int nearer_than(int distance, class xy& other);
} xy;

struct {

    uint16_t track_tag;
    uint16_t track_val;
    uint16_t rz;
    uint16_t __dummy_1;

    int16_t tag_y;
    int16_t tag_x;
    uint8_t tag;
    uint8_t ptag;
    uint8_t touching;


    int16_t x;
    int16_t y;
    xy xytouch;
} inputs;

void get_inputs()
{//TODO:  Fix this when have touchscreen

}


uint32_t BMPBaseAdd = RAM_G + 0x00000UL;                           // Hard-coded Address lacks panache

uint32_t load(char* filename)
{
    return Load_JPG(BMPBaseAdd, 0, filename);                           // Load a bitmap into RAM_G
}

uint32_t rseed = 0x77777777;

void seed(uint16_t n) 
{
    rseed = n ? n : 7;
}

uint16_t random() 
{
    rseed ^= rseed << 2;
    rseed ^= rseed >> 5;
    rseed ^= rseed << 1;
    return rseed;
}

uint16_t random1(uint16_t n) 
{//RJA with one parameter
    uint16_t p = random();
    if (n == (n & -n))
        return p & (n - 1);
    return (((uint32_t) p) * n) >> 16;
}

uint16_t random2(uint16_t n0, uint16_t n1) 
{//RJA with two parameters
    return n0 + random1(n1 - n0);
}

void ColorA(byte alpha) 
{
    cI((16UL << 24) | ((alpha & 255L) << 0));
}

void cI(int cmd)
{
    Send_CMD(cmd);
}

void Vertex2f(int16_t x, int16_t y) 
{
    // x = int(16 * x);
    // y = int(16 * y);
    cI((1UL << 30) | ((x & 32767L) << 15) | ((y & 32767L) << 0));
}

// 'instrument' argument to GD.play()

#define SILENCE              0x00

#define SQUAREWAVE           0x01
#define SINEWAVE             0x02
#define SAWTOOTH             0x03
#define TRIANGLE             0x04

#define BEEPING              0x05
#define ALARM                0x06
#define WARBLE               0x07
#define CAROUSEL             0x08

#define PIPS(n)              (0x0f + (n))

#define HARP                 0x40
#define XYLOPHONE            0x41
#define TUBA                 0x42
#define GLOCKENSPIEL         0x43
#define ORGAN                0x44
#define TRUMPET              0x45
#define PIANO                0x46
#define CHIMES               0x47
#define MUSICBOX             0x48
#define BELL                 0x49

#define CLICK                0x50
#define SWITCH               0x51
#define COWBELL              0x52
#define NOTCH                0x53
#define HIHAT                0x54
#define KICKDRUM             0x55
#define POP                  0x56
#define CLACK                0x57
#define CHACK                0x58

#define MUTE                 0x60
#define UNMUTE               0x61



void play(uint8_t instrument, uint8_t note) {
    wr16(REG_SOUND+RAM_REG, (note << 8) | instrument);
    wr(REG_PLAY + RAM_REG, 1);
}

void wr(uint32_t address, uint8_t parameter)
{
    wr8(address, parameter);
}

void delay(int ms)
{//Arduino has this in milliseconds
    usleep(ms * 1000);
}

// Generated by mk_bsod.py. Blue screen with 'ERROR' text
static uint8_t __bsod[48] = {
0, 255, 255, 255, 96, 0, 0, 2, 7, 0, 0, 38, 12, 255, 255, 255, 240, 0,
90, 0, 31, 0, 0, 6, 67, 111, 112, 114, 111, 99, 101, 115, 115, 111,
114, 32, 101, 120, 99, 101, 112, 116, 105, 111, 110, 0, 0, 0
};
static uint8_t __bsod_815[56] = {
0, 255, 255, 255, 96, 0, 0, 2, 7, 0, 0, 38, 12, 255, 255, 255, 240, 0,
136, 0, 28, 0, 0, 22, 67, 111, 112, 114, 111, 99, 101, 115, 115, 111,
114, 32, 101, 120, 99, 101, 112, 116, 105, 111, 110, 58, 10, 10, 37,
115, 0, 0, 0, 0, 0, 0
};
static uint8_t __bsod_badfile[44] = {
0, 255, 255, 255, 96, 0, 0, 2, 7, 0, 0, 38, 12, 255, 255, 255, 240, 0,
90, 0, 29, 0, 0, 6, 67, 97, 110, 110, 111, 116, 32, 111, 112, 101,
110, 32, 102, 105, 108, 101, 58, 0, 0, 0
};


void safeload(char* filename)
{
    if (!Load_File(filename)) {// Load_File(0,filesize,filename)){ //load(filename)) {
        __end();
        begin();
        copy(__bsod_badfile, sizeof(__bsod_badfile));
        cmd_text(240, 190, 29, OPT_CENTER, filename);
        swap();
        for (;;);
    }
}

typedef struct {
    byte handle;
    uint16_t w, h;
    uint16_t size;
} shape_t;

void copy(const uint8_t* src, int count) 
{
    CoProWrCmdBuf(src, count);

}


byte cprim;       // current primitive

void cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1) 
{
    Cmd_Gradient(x0, y0, rgb0, x1, y1, rgb1);
    cprim = 0xff;
}

void BlendFunc(byte src, byte dst) 
{
    cI((11UL << 24) | ((src & 7L) << 3) | ((dst & 7L) << 0));
}

#define ZERO                 0
#define ONE                  1
#define SRC_ALPHA            2
#define DST_ALPHA            3
#define ONE_MINUS_SRC_ALPHA  4
#define ONE_MINUS_DST_ALPHA  5
void RestoreContext(void) 
{//send restore contect command
    return cI(35UL << 24);
}


//send commands from a file
uint32_t Load_File(char* filename)  
{
    uint32_t Remaining;
    uint16_t ReadBlockSize = 0;

    printf("Filename=%s\n", filename);

    // Open the file on SD card by name
    FILE* f = fopen(filename, "rb");
    if (!f)
    {
        Log("%s not open\n", filename);
        fclose(f);
        return false;
    }

    //printf("copying data to eve...\n");
    int n;
    while ((n = fread(LogBuf, 1, 1000, f)) > 0)  //RJA we seem to have a limit somewhere between 1000 and 2000
    {
        n = 4*((n + 3) / 4);
        CoProWrCmdBuf(LogBuf, n);
    }
    fclose(f);

    //printf("copy complete.\n");
    Wait4CoProFIFOEmpty();                                     // wait here until the coprocessor has read and executed every pending command.
    return true;
}


// *** CoProWrCmdBuf() - Transfer a buffer into the CoPro FIFO as part of an ongoing command operation ***********
void CoProWrCmdBuf2(const uint8_t* buff, uint32_t count)
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
        Wait4CoProFIFO(WorkBuffSz);                            // It is reasonable to wait for a small space instead of firing data piecemeal

        if (Remaining > WorkBuffSz)                            // Remaining data exceeds the size of our buffer
            TransferSize = WorkBuffSz;                           // So set the transfer size to that of our buffer
        else
        {
            TransferSize = Remaining;                            // Set size to this last dribble of data
            TransferSize = (TransferSize + 3) & 0xFFC;           // 4 byte alignment
        }
        //TransferSize = count;

        StartCoProTransfer(FifoWriteLocation + RAM_CMD, false);// Base address of the Command Buffer plus our offset into it - Start SPI transaction

        SPI_WriteBuffer((uint8_t*)buff, TransferSize);         // write the little bit for which we found space
        buff += TransferSize;                                  // move the working data read pointer to the next fresh data

        FifoWriteLocation = (FifoWriteLocation + TransferSize) % FT_CMD_FIFO_SIZE;
        SPI_Disable();                                         // End SPI transaction with the FIFO

        wr16(REG_CMD_WRITE + RAM_REG, FifoWriteLocation);      // Manually update the write position pointer to initiate processing of the FIFO
        Remaining -= TransferSize;                             // reduce what we want by what we sent

    } while (Remaining > 0);                                  // keep going as long as we still want more
}

void BitmapSize(byte filter, byte wrapx, byte wrapy, uint16_t width, uint16_t height)
{
    Send_CMD(BITMAP_SIZE(filter, wrapx, wrapy, width, height));
}

void BitmapHandle(byte handle) 
{
    Send_CMD(BITMAP_HANDLE(handle));
}

void ColorMask(byte r, byte g, byte b, byte a) {
    Send_CMD((32UL << 24) | ((r & 1L) << 3) | ((g & 1L) << 2) | ((b & 1L) << 1) | ((a & 1L) << 0));
}

void cmd_translate(uint32_t tx, uint32_t ty)
{
    Cmd_Translate(tx, ty);
}

void cmd_scale(uint32_t sx, uint32_t sy)
{
    Cmd_Scale(sx, sy);
}

void cmd_setmatrix(void) {
    Send_CMD(CMD_SETMATRIX);
}

void LineWidth(uint16_t width) {
    Send_CMD((14UL << 24) | ((width & 4095L) << 0));
}

void cmd_rotate(uint32_t a)
{
    Cmd_Rotate(a);
}

typedef struct  BitmapStruct {

    xy size, center;
    uint32_t source;
    uint16_t format;
    int8_t handle;

    //void fromtext(int font, const char* s);
    //void fromfile(const char* filename, int format = 7);

    //void bind(uint8_t handle);

    //void wallpaper();
    //void draw(int x, int y, int16_t angle = 0);
    //void draw(const class xy& pos, int16_t angle = 0);


    //void defaults(uint8_t f);
    //void setup(void);
} Bitmap;


#define KEEP                 1
#define REPLACE              2
#define INCR                 3
#define DECR                 4
#define INVERT               5

#define NEVER                0
#define LESS                 1
#define LEQUAL               2
#define GREATER              3
#define GEQUAL               4
#define EQUAL                5
#define NOTEQUAL             6
#define ALWAYS               7

typedef struct PolyStruct {
    int x0, y0, x1, y1;
    int x[8], y[8];
    byte n;

    int w;  //RJA added these locally as FlexSpin does not recognize global variables in this "class"
    int h;
    byte vxf;   // Vertex Format

    void restart() {
        n = 0;
        x0 = (1 << vxf) * w;
        x1 = 0;
        y0 = (1 << vxf) * h;
        y1 = 0;
    }
    void perim() {
        for (byte i = 0; i < n; i++)
            Vertex2f(x[i], y[i]);
        Vertex2f(x[0], y[0]);
    }

    void begin() {
        restart();

        ColorMask(0, 0, 0, 0);
        StencilOp(KEEP, INVERT);
        StencilFunc(ALWAYS, 255, 255);
    }
    void v(int _x, int _y) {
        x0 = min(x0, _x >> vxf);
        x1 = max(x1, _x >> vxf);
        y0 = min(y0, _y >> vxf);
        y1 = max(y1, _y >> vxf);
        x[n] = _x;
        y[n] = _y;
        n++;
    }
    void paint() {
        x0 = max(0, x0);
        y0 = max(0, y0);
        x1 = min((1 << vxf) * w, x1);
        y1 = min((1 << vxf) * h, y1);
        ScissorXY(x0, y0);
        ScissorSize(x1 - x0 + 1, y1 - y0 + 1);
        Begin(EDGE_STRIP_B);
        perim();
    }
    void finish() {
        ColorMask(1, 1, 1, 1);
        StencilFunc(EQUAL, 255, 255);

        Begin(EDGE_STRIP_R);
        Vertex2f(0, 0);
        Vertex2f(0, (1 << vxf) * h);
    }
    void draw() {
        paint();
        finish();
    }
    void outline() {
        Begin(LINE_STRIP);
        perim();
    }
} Poly;

void polar(int& x, int& y, int16_t r, uint16_t th) 
{
    x = (int)(-rsin(r, th));
    y = (int)(rcos(r, th));
}

// >>> [int(65535*math.sin(math.pi * 2 * i / 1024)) for i in range(257)]
uint16_t sintab[257] = {
0, 402, 804, 1206, 1608, 2010, 2412, 2813, 3215, 3617, 4018, 4419, 4821, 5221, 5622, 6023, 6423, 6823, 7223, 7622, 8022, 8421, 8819, 9218, 9615, 10013, 10410, 10807, 11203, 11599, 11995, 12390, 12785, 13179, 13573, 13966, 14358, 14750, 15142, 15533, 15923, 16313, 16702, 17091, 17479, 17866, 18252, 18638, 19023, 19408, 19791, 20174, 20557, 20938, 21319, 21699, 22078, 22456, 22833, 23210, 23585, 23960, 24334, 24707, 25079, 25450, 25820, 26189, 26557, 26924, 27290, 27655, 28019, 28382, 28744, 29105, 29465, 29823, 30181, 30537, 30892, 31247, 31599, 31951, 32302, 32651, 32999, 33346, 33691, 34035, 34378, 34720, 35061, 35400, 35737, 36074, 36409, 36742, 37075, 37406, 37735, 38063, 38390, 38715, 39039, 39361, 39682, 40001, 40319, 40635, 40950, 41263, 41574, 41885, 42193, 42500, 42805, 43109, 43411, 43711, 44010, 44307, 44603, 44896, 45189, 45479, 45768, 46055, 46340, 46623, 46905, 47185, 47463, 47739, 48014, 48287, 48558, 48827, 49094, 49360, 49623, 49885, 50145, 50403, 50659, 50913, 51165, 51415, 51664, 51910, 52155, 52397, 52638, 52876, 53113, 53347, 53580, 53810, 54039, 54265, 54490, 54712, 54933, 55151, 55367, 55581, 55793, 56003, 56211, 56416, 56620, 56821, 57021, 57218, 57413, 57606, 57796, 57985, 58171, 58355, 58537, 58717, 58894, 59069, 59242, 59413, 59582, 59748, 59912, 60074, 60234, 60391, 60546, 60699, 60849, 60997, 61143, 61287, 61428, 61567, 61704, 61838, 61970, 62100, 62227, 62352, 62474, 62595, 62713, 62828, 62941, 63052, 63161, 63267, 63370, 63472, 63570, 63667, 63761, 63853, 63942, 64029, 64114, 64196, 64275, 64353, 64427, 64500, 64570, 64637, 64702, 64765, 64825, 64883, 64938, 64991, 65042, 65090, 65135, 65178, 65219, 65257, 65293, 65326, 65357, 65385, 65411, 65435, 65456, 65474, 65490, 65504, 65515, 65523, 65530, 65533, 65535
};

int16_t rsin(int16_t r, uint16_t th) {
    th >>= 6; // angle 0-1023
    // return int(r * sin((2 * M_PI) * th / 1024.));
    int th4 = th & 511;
    if (th4 & 256)
        th4 = 512 - th4; // 256->256 257->255, etc
    uint16_t s = (uint16_t) *(sintab + th4);
    int16_t p = ((uint32_t)s * r) >> 16;
    if (th & 512)
        p = -p;
    return p;
}

int16_t rcos(int16_t r, uint16_t th) {
    return rsin(r, th + 0x4000);
}

uint32_t millis(void)
{
    return _getms();
}

uint32_t micros(void)
{
    return _getus();
}

void SaveContext(void) {
    Send_CMD((34UL << 24));
}

void ScissorSize(uint16_t width, uint16_t height) {
    //if (ft8xx_model == 0)
    //    cI((28UL << 24) | ((width & 1023L) << 10) | ((height & 1023L) << 0));
    //else
    Send_CMD((28UL << 24) | ((width & 4095L) << 12) | ((height & 4095L) << 0));
}

void ScissorXY(uint16_t x, uint16_t y) {
    //if (ft8xx_model == 0)
    //    Send_CMD((27UL << 24) | ((x & 511L) << 9) | ((y & 511L) << 0));
    //else
        Send_CMD((27UL << 24) | ((x & 2047L) << 11) | ((y & 2047L) << 0));
}
void StencilFunc(byte func, byte ref, byte mask) {
    Send_CMD((10UL << 24) | ((func & 7L) << 16) | ((ref & 255L) << 8) | ((mask & 255L) << 0));
}
void StencilMask(byte mask) {
    Send_CMD((19UL << 24) | ((mask & 255L) << 0));
}
void StencilOp(byte sfail, byte spass) {
    Send_CMD((12UL << 24) | ((sfail & 7L) << 3) | ((spass & 7L) << 0));
}

void cmd32(uint32_t b) {
    Send_CMD(b);
}

void cmd_number(uint16_t x, uint16_t y, uint16_t font, uint16_t options, uint32_t num)
{
    Cmd_Number(x, y, font, options, num);
}

void cFFFFFF(uint8_t c)
{
    Send_CMD(+ 0xFFFFFF00+c&0xFF);
}

void Cmd_SetBase(uint32_t b) {
    Send_CMD(0xFFFFFF38);// cFFFFFF(0x38);
    Send_CMD(b);// cI(b);
}


void cmd_dial(uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t val)
{
    Cmd_Dial(x, y, r, options, val);
}

void cmd_track(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t tag)
{
    Cmd_Track(x, y, w, h, tag);
}

void cmd_slider(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t options, uint16_t val, uint16_t range)
{
    Cmd_Slider(x, y, w, h, options, val, range);
}

void cmd_gauge(uint16_t x, uint16_t y, uint16_t r, uint16_t options, uint16_t major, uint16_t minor, uint16_t val, uint16_t range)
{
    Cmd_Gauge(x, y, r, options, major, minor, val, range);
}

void cmd_button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t font, uint16_t options, const char* str)
{
    Cmd_Button(x, y, w, h, font, options, str);
}

void Send_Byte(uint8_t data) //RJA Adapted from Send_CMD
{
    wr8(FifoWriteLocation + RAM_CMD, data);                         // write the command at the globally tracked "write pointer" for the FIFO

    FifoWriteLocation += 1;                                  // Increment the Write Address by the size of a command - which we just sent
    FifoWriteLocation %= FT_CMD_FIFO_SIZE;                           // Wrap the address to the FIFO space
}


void cmd_toggle(int16_t x, int16_t y, int16_t w, byte font, uint16_t options, uint16_t state, const char* s) 
{
    if (state > 0) state = 65535;//RJA fully turn on if on
    Send_CMD(CMD_TOGGLE);
    Send_CMD(((uint32_t)y << 16) | x);
    Send_CMD(((uint32_t)font << 16) | w);
    Send_CMD(((uint32_t)state << 16) | options);
    //send string in longs
    int b = strlen(s)+1; //#bytes
    int l = (b + 3) / 4;//#longs
    uint32_t* p = (uint32_t*)s;
    for (int i = 0; i < l; i++)
    {
        Send_CMD(*p++);   
    }
    cprim = 0xff;

}

void cmd_clock(int16_t x, int16_t y, int16_t r, uint16_t options, uint16_t h, uint16_t m, uint16_t s, uint16_t ms) {
    Send_CMD(CMD_CLOCK);
    Send_CMD(((uint32_t)y << 16) | x);
    Send_CMD(((uint32_t)options << 16) | r);
    Send_CMD(((uint32_t)m << 16) | h);
    Send_CMD(((uint32_t)ms << 16) | s);
    cprim = 0xff;
}

void cmd_progress(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t range) {
    Send_CMD(CMD_PROGRESS);
    Send_CMD(((uint32_t)y << 16) | x);
    Send_CMD(((uint32_t)h << 16) | w);
    Send_CMD(((uint32_t)val << 16) | options);
    Send_CMD(range);
    cprim = 0xff;
}

void cmd_scrollbar(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t options, uint16_t val, uint16_t size, uint16_t range) {
    Send_CMD(CMD_SCROLLBAR);
    Send_CMD(((uint32_t)y << 16) | x);
    Send_CMD(((uint32_t)h << 16) | w);
    Send_CMD(((uint32_t)val << 16) | options);
    Send_CMD(((uint32_t)range << 16) | size);
    cprim = 0xff;

}

void cmd_keys(int16_t x, int16_t y, int16_t w, int16_t h, byte font, uint16_t options, const char* s) {
    Send_CMD(CMD_KEYS);
    Send_CMD(((uint32_t)y << 16) | x);
    Send_CMD(((uint32_t)h << 16) | w);
    Send_CMD(((uint32_t)options << 16) | font);
    //send string in longs
    int b = strlen(s) + 1; //#bytes
    int l = (b + 3) / 4;//#longs
    uint32_t* p = (uint32_t*)s;
    for (int i = 0; i < l; i++)
    {
        Send_CMD(*p++);
    }
    cprim = 0xff;
}

void cmd_loadidentity()
{
    Send_CMD(CMD_LOADIDENTITY);
}

void Cell(x)
{
    Send_CMD(CELL(x));
}

void AlphaFunc(byte func, byte ref) {
    Send_CMD((9UL << 24) | ((func & 7L) << 8) | ((ref & 255L) << 0));
}

void TagMask(byte mask) {
    Send_CMD((20UL << 24) | ((mask & 1L) << 0));
}

uint32_t rd(uint32_t address)
{
    rd32(address);
}



typedef struct MoviePlayerStruct
{//This does'n work yet.  FILE reading doesn't work inside this structure due to current FlexSpin limitation
    uint32_t mf_size, mf_base, wp;
    //Reader r;
    FILE* f;
    bool bEof;//RJA
    void loadsector() {
        int n;//rja
        byte buf[512];
        __end();

        //r.readsector(buf);
        n = fread(buf, 1, 512, f);
        if (n < 512)
            bEof = true;
        resume();
        wr_n(mf_base + wp, buf, 512);
        wp = (wp + 512) & (mf_size - 1);
    }

    int begin(const char* filename) {
        bEof = false;
        mf_size = 0x40000UL;
        mf_base = 0x100000UL - mf_size;
        __end();
        FILE* fs = fopen(filename, "rb");
        if (!fs) {
            printf("Open movie file (%s) failed, returned %d\n",filename,fs);
            return 0;
        }
        f = fs;
        resume();

        wp = 0;
        while (wp < (mf_size - 512)) {
            loadsector();
        }

        cmd_mediafifo(mf_base, mf_size);
        cmd_regwrite(REG_MEDIAFIFO_WRITE, wp);
        finish();

        return 1;
    }
    int service() {
        if (bEof){//(r.eof()) {
            return 0;
        }
        else {
            uint32_t fullness = (wp - rd32(REG_MEDIAFIFO_READ)) & (mf_size - 1);
            while (fullness < (mf_size - 512)) {
                loadsector();
                fullness += 512;
                wr32(REG_MEDIAFIFO_WRITE, wp);
            }
            return 1;
        }
    }
    void play() {
        cmd_playvideo(OPT_MEDIAFIFO | OPT_FULLSCREEN);
        flush();
        while (service())
            ;
        cmd_memcpy(0, 0, 4);
        finish();
    }
}MoviePlayer;

void cmd_memcpy(uint32_t dest, uint32_t src, uint32_t num) {
    Send_CMD(CMD_MEMCPY); 
    Send_CMD(dest);
    Send_CMD(src);
    Send_CMD(num);
}

void cmd_playvideo(int32_t options) {
    Send_CMD(CMD_PLAYVIDEO);
    Send_CMD(options);
}

void cmd_mediafifo(uint32_t ptr, uint32_t size) {
    Send_CMD(CMD_MEDIAFIFO);
    Send_CMD(ptr);
    Send_CMD(size);
}

void cmd_regwrite(uint32_t ptr, uint32_t val) {
    Send_CMD(CMD_MEMWRITE);
    Send_CMD(ptr);
    Send_CMD(4UL);
    Send_CMD(val);
}


void resume(void) {
    stream();
}


void stream(void) {
    __end();
    __wstart(RAM_CMD + (FifoWriteLocation & 0xfff));
}

void __end(void) {
    SPI_Disable();
}

void __wstart(uint32_t addr) // start an SPI write transaction to addr
{
    SPI_Enable();
    SPI_Write(0x80 | ((addr >> 16) & 0x3F));
    SPI_Write((addr >> 8) & 0xff);
    SPI_Write(addr & 0xff);
}

void wr_n(uint32_t addr, byte* src, uint16_t n)
{
    __end(); // stop streaming
    __wstart(addr);
    SPI_WriteBuffer(src, n);
    stream();
}

void finish() {
    
    FifoWriteLocation &= 0xffc;
    __end();
    wr16(REG_CMD_WRITE + RAM_REG, FifoWriteLocation);

    //int r = rd16(REG_CMD_WRITE + RAM_REG);// REG_CMD_READ + RAM_REG);
    //printf("x");
    //int r1 = rp();
    //printf("%d, %d, %x\n", r1, FifoWriteLocation, r);

    while (rp() != FifoWriteLocation)
    {
        //int r = rd16(REG_CMD_WRITE + RAM_REG);// REG_CMD_READ + RAM_REG);
        //printf("x");
        //int r1 = rp();
        //printf("%d, %d, %x\n", r1, FifoWriteLocation, r);
    }//YIELD();
    //sleep(1);
    //for (;;) {}
    stream();
}

uint16_t rp() {
    uint16_t r = rd16(REG_CMD_READ+RAM_REG);
    if (r == 0xfff)
        alert();
    return r;
}

void alert()
{
    //GDTR.coprocsssor_recovery();

    copy(__bsod_815, sizeof(__bsod_815));
    swap();
    finish();
    for (;;);
}

uint16_t freespace;

void flush() {
    //YIELD();
    getfree(0);
}

void getfree(uint16_t n)
{
    FifoWriteLocation &= 0xfff;
    __end();
    wr16(REG_CMD_WRITE + RAM_REG, FifoWriteLocation & 0xffc);
    do {
        uint16_t fullness = (FifoWriteLocation - rp()) & 4095;
        freespace = (4096 - 4) - fullness;
    } while (freespace < n);
    stream();
}

void FormatVertex(f)
{//RJA adding in way to redifine vertex format from sixteenth pixel
    Send_CMD(VERTEX_FORMAT(f));  
    vxf = f;  //RJA: you can shift vertex2f points by this value if unsure of vertex format  
    //Note:  RJA:  Defined values are VERTEX_FORMAT_ONE, VFORMAT_HALF, VFORMAT_QUARTER, VFORMAT_EIGTH, VFORMAT_SIXTEENTH 
}

void BitmapTransformA(int32_t a) {
    cI((21UL << 24) | ((a & 131071L) << 0));
}
void BitmapTransformB(int32_t b) {
    cI((22UL << 24) | ((b & 131071L) << 0));
}
void BitmapTransformC(int32_t c) {
    cI((23UL << 24) | ((c & 16777215L) << 0));
}
void BitmapTransformD(int32_t d) {
    cI((24UL << 24) | ((d & 131071L) << 0));
}
void BitmapTransformE(int32_t e) {
    cI((25UL << 24) | ((e & 131071L) << 0));
}
void BitmapTransformF(int32_t f) {
    cI((26UL << 24) | ((f & 16777215L) << 0));
}





////////////////////////////////////////////////////////////////////////////////////////////////
/* FT800 font table structure */
/* Font table address in ROM can be found by reading the address from 0xFFFFC location. */
/* 16 font tables are present at the address read from location 0xFFFFC */

#define FT_GPU_NUMCHAR_PERFONT 128


typedef struct FT_Gpu_Fonts
{
    /* All the values are in bytes */
    /* Width of each character font from 0 to 127 */
    uint8_t  FontWidth[FT_GPU_NUMCHAR_PERFONT];
    /* Bitmap format of font wrt bitmap formats supported by FT800 - L1, L4, L8 */
    uint32_t FontBitmapFormat;
    /* Font line stride in FT800 ROM */
    uint32_t FontLineStride;
    /* Font width in pixels */
    uint32_t FontWidthInPixels;
    /* Font height in pixels */
    uint32_t FontHeightInPixels;
    /* Pointer to font graphics raw data */
    uint32_t PointerToFontGraphicsData;
}FT_Gpu_Fonts_t;







#endif /*_ANTARES_H_*/



