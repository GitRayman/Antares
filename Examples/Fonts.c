#include "../Antares/Antares.h"    //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//Fonts.c - Demonstrate how to use fonts created by the Eve Asset Builder
//Long filenames uses here assuming using Plan9 to access files from host
//Make sure "#define USE_HOST" is set in Platform.h

//Note:  This is the hard way.  Easier to use an asset builder to load fonts up nearly automatically at startup...

//This font created in "Legacy" mode with "SETFONT" option (base address setting doesn't matter)
#define font1_filename "GAMERIA_36_L1_SetFont.raw"
#define font1_format L1 //This is type of bitmap, L1 is 1bpp monochrome.  The asset builder creates several format types to choose from
//The following settings can be found in the ".c" file that the Asset Builder creates, if you don't know them
#define font1_FONT_HANDLE       (1)
#define font1_FONT_FILE_ADDRESS (RAM_G + 90000)  //Address to store font in GRAM, this address doesn't have to match setting in Asset Builder
#define font1_STRIDE            (4)
#define font1_FONT_WIDTH        (32)
#define font1_FONT_HEIGHT       (32)
#define font1_FIRST_CHARACTER   (32)

//This font created in "Legacy" mode with "SETFONT2" option (base address setting doesn't matter)
//Note:  SetFont2 mode makes it easier, but you have to use the ADDRESS you used in Eve Asset Builder
#define font2_filename "SPACEARE_36_L4_SetFont2.raw"
#define font2_format L4 //This is type of bitmap, L4 is 4bpp monochrome.  The asset builder creates several format types to choose from
//The following settings can be found in the ".c" file that the Asset Builder creates, if you don't know them
#define font2_FONT_HANDLE       (2)
#define font2_FONT_FILE_ADDRESS (RAM_G + 10000)  //Address to store font in GRAM, this address doesn't have to match setting in Asset Builder
#define font2_FIRST_CHARACTER   (32)

void setup()
{
  begin();
  printf("Loading Fonts...\n");
  Load_RAW(font1_FONT_FILE_ADDRESS, (char*) font1_filename);
  Load_RAW(font2_FONT_FILE_ADDRESS, (char*) font2_filename);

}

void loop()
{
    //Set background to dark blue
    ClearColorRGB(10, 10, 50);
    Clear();

    //Setup Font1 - Tricky in SetFont1 mode
    //You can see the source for these commands in the ".c" file that the Asset Builder creates
    Send_CMD(BITMAP_HANDLE(font1_FONT_HANDLE));
    Send_CMD(BITMAP_SOURCE(font1_FONT_FILE_ADDRESS + 148- font1_STRIDE * font1_FONT_HEIGHT * font1_FIRST_CHARACTER));
    Send_CMD(BITMAP_LAYOUT(font1_format, font1_STRIDE, font1_FONT_HEIGHT));
    Send_CMD(BITMAP_SIZE(NEAREST, BORDER, BORDER, font1_FONT_WIDTH, font1_FONT_HEIGHT));
    Cmd_SetFont(font1_FONT_HANDLE, font1_FONT_FILE_ADDRESS);

    //Setup Font2  - Much easier in SetFont2 mode, but have to use address you used in Eve Asset Builder
    Cmd_SetFont2(font2_FONT_HANDLE, font2_FONT_FILE_ADDRESS, font2_FIRST_CHARACTER);
    
    //Try out the fonts
    Cmd_Text(18, 18, font1_FONT_HANDLE, 0, "Gameria font in L1 format");
    Cmd_Text(50, 80, font2_FONT_HANDLE, 0, "SPACEARE font in L4 format");

    //execute display list and start a new one
    swap();

}

void main()
{//RJA added this main function to act like Arduino
    setup();
    printf("Setup Complete.\n");
    for (;;)
    {
        loop();
    }
}


