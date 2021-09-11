#include "../Antares/Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//RJA:  This example explores the effects of the A..F Bitmap Transform functions
//     The sliders adjust the value of these bitmap transform values over a small range to see what they do
//     Note:  Fortunately, EVE3 has CoPro commands like scale and rotate that let you not have to learn this!

#include "BlockAssets.h"  //The Antares Assets Builder creates this file and the ".ant" file that goes with it

#include "Blocks.h"  //The panels interface code
#include "BlockImageTest.h"  //Test panel





void setup()
{
  begin();

  InitBlocks(&Block1);  //Start up panels interface with Block1 showing
}

void loop()
{  
    BlockLoop();  //show panel and interact with mouse
}



void main()
{//RJA added this main function to act like Arduino
    setup();
    printf("Setup complete.\n");


    for (;;)
    {  
        loop();
              
    }
}




