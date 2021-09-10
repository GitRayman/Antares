#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//This program shows how to use assets created by the Antares Assets Builder
//Alternatively, you could use the Gameduino Assets builder

//This example requires that the file "Assets.ant" is either on uSD card or in the Plan9 folder (configured by loadp2)
//All images my not show with less than 720p resolution.

//Note:  Assets are things like images and fonts that you want ready to use at launch
//       There may be a short delay as assets are loaded from uSD or Plan9

#include "TestAssets_Assets.h"  //The Antares Assets Builder creates this file and the ".ant" file that goes with it

void setup()
{
  begin(); //This activates EVE and gets it ready

  //draw text at top so you know we are busy...
  ClearColorRGB(10, 10, 50);
  Clear();
  DrawText(w / 2, h / 8, 18, OPT_CENTERX, (char*) "Loading Assets...", RGB(255, 255, 255));
  swap(); //execute display list and start a new one

  

  printf("Loading Assets, please wait...\n");
  LOAD_ASSETS(); //This loads an assets file into RAM_G
  printf("Assets loaded.\n");
}

void loop()
{
    //Set background to dark blue
    ClearColorRGB(10, 10, 50);
    Clear();


    //show some bitmaps
    Begin(BITMAPS);   
    Vertex2ii(80, 60, flowersH_HANDLE);
    Send_CMD(VERTEX_TRANSLATE_X(700 << 4));
    Vertex2ii(0, 380, springH_HANDLE);
    Send_CMD(VERTEX_TRANSLATE_X(800 << 4));
    Vertex2ii(0, 50, Pencils_HANDLE);
    Send_CMD(VERTEX_TRANSLATE_X(0 << 4));
    Vertex2ii(100, 480, Tulips_HANDLE);

    Cmd_Text(100, 380, Gameria_HANDLE, 0, "Gameria font in L4");
    Cmd_Text(100, 420, Spaceare_HANDLE, 0, "SPACEARELLA font in L4");

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
        _waitms(100);
    }
}


