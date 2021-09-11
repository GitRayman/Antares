
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

//Add in some needed includes here
#include "propeller2.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

//EVE Display Type
//Pick one: (see more options in DisplaySettings.h)
//#define EVE2_70  //7" WVGA LCD
//#define EVE2_43  //4.3" LCD
#define EVE3_720p  //Antares-B 
//#define EVE3_VGA   //Antares-B

//I/O Pin Settings
//Pick one of these board configs or add your own
//#define Board1  //This is a generic P2 board
//#define Dazzler  //This is a special P2 based board with Arduino layout to host Dazzler 
#define AntaresB  //This is a special P2 based board that outputs VGA from EVE

//Settings for various types of displays are here, the define above selects display settings in this file
#include "DisplaySettings.h" 

//Note:  For VGA, there other frequency options, but for 720p we need 297 MHz
#ifdef EVE3_VGA
enum { _clkfreq = 200000000 }; //Note: If you change this you must also change the NCO values to maintain 12 MHz output
#elif defined EVE3_720p
enum { _clkfreq = 297000000 }; 
#elif defined EVE2_70
enum { _clkfreq = 160000000 };
#elif defined EVE3_1080p
enum { _clkfreq = 237600000 };  //24 Hz
#endif


enum { heapsize = 16000 };  //override the default heapsize to give more, if needed for malloc





//RJA's P2 Board1 with EVE2 display
#ifdef Board1
#define FT800_CS                                (30)
#define FT800_INT                               (28)
#define FT800_PD_N                              (31)
#define FT800_SEL_PIN           FT800_CS
#define FT800_MOSI								(24)
#define FT800_MISO								(25)
#define FT800_CLK								(29)
#define uSD_MISO  44 
#define uSD_MOSI  46 
#define uSD_SS  47 
#define uSD_CLK  45
#endif

//RJA's Arduino style P2 Board with Dazzler
#ifdef Dazzler
#define FT800_CS                                (50)
#define FT800_INT                               (36)
#define FT800_PD_N                              (-1)
#define FT800_SEL_PIN           FT800_CS
#define FT800_MOSI								(53)
#define FT800_MISO								(54)
#define FT800_CLK								(55)
#define Dazzler_CS								(52)
#define DazzlerSD_CS								(51)
#endif

//P2 Eval board with AntaresB 
//Antares-B uses a P2 smartpin in NCO mode to give clock to EVE3 chip in order to get TV and monitors to accept VGA/720p signals selected by the below
//Note:  Eve sometimes gets stuck when switched from VGA to 720p
#ifdef AntaresB
#define basepin (0) //This is the starting pin on which the Antares-B adapter is situated
//Using this P2 pin to supply ~12 MHz clock to eve chip
#define NCOPIN (basepin+2)

#ifdef EVE3_VGA
#define NCOYPIN $4000_0000  //wypin value for NCO oscillator
#define NCOXPIN 4
#else
#define NCOYPIN $8000_0000  //wypin value for NCO oscillator
#define NCOXPIN 12
#endif

#define FT800_CS                                (basepin+5)
#define FT800_INT                               (basepin+7) 
#define FT800_PD_N                              (basepin+6)
#define FT800_SEL_PIN           FT800_CS
//RJA adding more pins
#define FT800_MOSI								(basepin+0)
#define FT800_MISO								(basepin+1)
#define FT800_CLK								(basepin+4)

//The Eval Board's uSD pins
#define uSD_MISO  58 
#define uSD_MOSI  59 
#define uSD_SS  60 
#define uSD_CLK  61
#endif


//Pick one or none of these to say where files might come from
//#define USE_SD
#define USE_HOST

//USB pin definitions for AntaresB
#define USB_BASE_PIN 16 //(basepin+3)  //use AntaresB onboard LED for USB activity
#define USB_ENABLE_PIN -1  //not using a P2 pin to enable AntaresB USB
#define USB_DM_PIN (basepin+14)  //USB is on +14 and +15
#define USB_ERR_LED_PIN 57       //Using P2 Eval board's P57 led for error display

////USB pin definitions Parallax USB adapter board for P2 Eval Board
//#define SERIAL_HOST_BASEPIN 16
//#define USB_BASE_PIN (SERIAL_HOST_BASEPIN+0) 
//#define USB_ENABLE_PIN (SERIAL_HOST_BASEPIN+1)  
//#define USB_DM_PIN (SERIAL_HOST_BASEPIN+6)  //USB is on +6 and +7 for lower port, +2 and +3 for upper port
//#define USB_ERR_LED_PIN 57       //Using P2 Eval board's P57 led for error display



///* Threshold for resistance */
#define RESISTANCE_THRESHOLD                    (1200) //RJA:  for resistive touch panels




//typedef boolean bool_t;
#define TRUE     (1)
#define FALSE    (0)

// override baud rate for serial, requires use of "_setbaud(_BAUD);" in code
#ifndef _BAUD
#define _BAUD 2000000
#endif



//some types not yet defined in FlexSpin, or needed to translate Arduino code
typedef char  byte;
typedef unsigned char uchar;
typedef char		bool_t;
typedef char		char8_t;
typedef unsigned char	uchar8_t;
typedef unsigned char prog_uchar8_t;
typedef signed char	schar8_t;
typedef float		float_t;

//RJA:  Seem to need this...
#define min(x,y)  ((x) > (y) ? (y) : (x))
#define max(x,y)  ((x) > (y) ? (x) : (y))



#endif /*_PLATFORM_H_*/
/* Nothing beyond this*/




