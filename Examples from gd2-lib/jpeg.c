#include "Antares.h"  //RJA implementing this gd2-lib code using Matrix Orbital's driver

//RJA:  This gd2-lib example shows a jpg or png image on screen
//Note:  The decompresses size of the image must fit in GRAM... 

#ifdef USE_HOST
char filename[] = "healsky3.jpg";  //"betterbird.jpg";// "healsky3.jpg";  //"tree.jpg";
#elif defined USE_SD
char filename[] = "streamer.jpg"; // "better~1.jpg";// "healsky3.jpg";  //"tree.jpg";"streamer.jpg"; //
#endif 



void setup()
{
  begin();
  load(filename);  //automagically configures bitmap handle #0 to show this image
}

void loop()
{
    Clear();
    //Cmd_SetBitmap(0, RGB565, 896, 504);  //Don't need this because works automagically when just one bitmap handle in use...
    Begin(BITMAPS);  
    Vertex2ii(0, 0);  //RJA: This paints the image.  Somehow it knows the image size.
    swap();
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




