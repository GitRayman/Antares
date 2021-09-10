#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//RJA:  This gd2-lib example shows a jpg or png image on screen
//Note:  The decompresses size of the image must fit in GRAM... 

#ifdef USE_HOST
char filename[] = "streamer.png";
#elif defined USE_SD
char filename[] = "streamer.png";
#endif 



void setup()
{
  begin();
  load(filename);
}

void loop()
{  
    Clear();
    Begin(BITMAPS);  
    Vertex2f(0, 0);  //RJA: This paints the image.  Somehow it knows the image size, unless you add commands like clearcolor()
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




