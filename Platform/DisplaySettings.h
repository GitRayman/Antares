//User selectable configurations.
//Define one if these in Platform.h
//RJA Note:  These first two are for VGA output using a P2 pin in NCO mode to drive the clock of EVE to get correct output frequency, the others are for Matrix Orbital displays

#ifdef EVE3_720p
//VGA output using NCO clock to drive EVE
#define DWIDTH      1280
#define DHEIGHT     720
#define PIXVOFFSET  0
#define PIXHOFFSET  0
#define HCYCLE      1650
#define HOFFSET     260//Hsync+backporch 
#define HSYNC0      0
#define HSYNC1      40//hsync pulse width
#define VCYCLE      750
#define VOFFSET     25//vsync+backporch 
#define VSYNC0      0
#define VSYNC1      5//vsync pulse width 
#define PCLK        1
#define SWIZZLE     0
#define PCLK_POL    0
#define HSIZE       1280
#define VSIZE       720
#define CSPREAD     0
#define DITHER      0
#endif

#ifdef EVE3_1080p  //doesn't seem to work with EVE3 :(
//VGA output using NCO clock to drive EVE
#define DWIDTH      1920
#define DHEIGHT     1080
#define PIXVOFFSET  0
#define PIXHOFFSET  0
#define HCYCLE      2200
#define HOFFSET     192//Hsync+backporch 
#define HSYNC0      0
#define HSYNC1      44//hsync pulse width
#define VCYCLE      1125
#define VOFFSET     41//vsync+backporch 
#define VSYNC0      0
#define VSYNC1      5//vsync pulse width 
#define PCLK        1
#define SWIZZLE     0
#define PCLK_POL    0
#define HSIZE       1920
#define VSIZE       1080
#define CSPREAD     0
#define DITHER      0
#endif


#ifdef EVE3_VGA  
//VGA output using NCO clock to drive EVE
#define DWIDTH      640L
#define DHEIGHT     480L
#define PIXVOFFSET  0
#define PIXHOFFSET  0
#define HCYCLE      800L
#define HOFFSET     144L///Hsync+backporch 
#define HSYNC0      0L //keep 0 //RJA
#define HSYNC1      96L //hsync pulse width
#define VCYCLE      525L
#define VOFFSET     35L//vsync+backporch 
#define VSYNC0      0L //keep 0//RJA 
#define VSYNC1      2L //vsync pulse width 
#define PCLK        3 //pixel clock divider
#define SWIZZLE     0
#define PCLK_POL    0//1  //either seems to work
#define HSIZE       640
#define VSIZE       480
#define CSPREAD     0
#define DITHER      0
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif





#ifdef EVE2_70
#define DWIDTH     800
#define DHEIGHT    480
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     928
#define HOFFSET     88
#define HSYNC0       0
#define HSYNC1      48
#define VCYCLE     525
#define VOFFSET     32
#define VSYNC0       0
#define VSYNC1       3
#define PCLK         2
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      800
#define VSIZE      480
#define CSPREAD      0
#define DITHER       1
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif

#ifdef EVE2_50
#define DWIDTH     800
#define DHEIGHT    480
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     928
#define HOFFSET     88
#define HSYNC0       0
#define HSYNC1      48
#define VCYCLE     525
#define VOFFSET     32
#define VSYNC0       0
#define VSYNC1       3
#define PCLK         2
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      800
#define VSIZE      480
#define CSPREAD      0
#define DITHER       1
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif

#ifdef EVE2_43
#define DWIDTH     480
#define DHEIGHT    272
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     548
#define HOFFSET     43
#define HSYNC0       0
#define HSYNC1      41
#define VCYCLE     292
#define VOFFSET     12
#define VSYNC0       0
#define VSYNC1      10
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#endif

#ifdef EVE2_43_CT
#define DWIDTH     480
#define DHEIGHT    272
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     548
#define HOFFSET     43
#define HSYNC0       0
#define HSYNC1      41
#define VCYCLE     292
#define VOFFSET     12
#define VSYNC0       0
#define VSYNC1      10
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#define CAPACITIVE_TOUCH  //Use capacitive touchscreen
#endif

#ifdef EVE2_43_RT
#define DWIDTH     480
#define DHEIGHT    272
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     548
#define HOFFSET     43
#define HSYNC0       0
#define HSYNC1      41
#define VCYCLE     292
#define VOFFSET     12
#define VSYNC0       0
#define VSYNC1      10
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#define RESISTIVE_TOUCH  //Use resistive touchscreen
#define STORE_RESISTIVE_CAL  //store and load resistive touchscreen calibrations to filesystem if defined
//#define FORCE_RESISTIVE_CAL  //Always do resistive calibration if defined
#endif

#ifdef EVE2_39
#define DWIDTH     480
#define DHEIGHT    128
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     524
#define HOFFSET     16
#define HSYNC0       0
#define HSYNC1      44
#define VCYCLE     288
#define VOFFSET     12
#define VSYNC0      11
#define VSYNC1      8
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      128
#define CSPREAD      1
#define DITHER       1
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif
  
#ifdef EVE2_38
#define DWIDTH     480
#define DHEIGHT    116
#define PIXVOFFSET  10
#define PIXHOFFSET   0
#define HCYCLE     524
#define HOFFSET     43
#define HSYNC0       0
#define HSYNC1      41
#define VCYCLE     292
#define VOFFSET     12
#define VSYNC0     152
#define VSYNC1      10
#define PCLK         5
#define SWIZZLE      0
#define PCLK_POL     1
#define HSIZE      480
#define VSIZE      272
#define CSPREAD      1
#define DITHER       1
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif

#ifdef EVE2_35
#define DWIDTH     320
#define DHEIGHT    240
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     408
#define HOFFSET     68
#define HSYNC0       0
#define HSYNC1      10
#define VCYCLE     262
#define VOFFSET     18
#define VSYNC0       0
#define VSYNC1       2
#define PCLK         8
#define SWIZZLE      0
#define PCLK_POL     0
#define HSIZE      320
#define VSIZE      240
#define CSPREAD      1
#define DITHER       1
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif

#ifdef EVE2_29
#define DWIDTH     320
#define DHEIGHT    102
#define PIXVOFFSET   0
#define PIXHOFFSET   0
#define HCYCLE     408
#define HOFFSET     70
#define HSYNC0       0
#define HSYNC1      10
#define VCYCLE     262
#define VOFFSET    156
#define VSYNC0       0
#define VSYNC1       2
#define PCLK         8
#define SWIZZLE      0
#define PCLK_POL     0
#define HSIZE      320
#define VSIZE      102
#define CSPREAD      1
#define DITHER       1
#define USE_TOUCHSCREEN true
#define RESISTIVE_TOUCH false
#endif
