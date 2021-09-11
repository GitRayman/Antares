#include "../Antares/Antares.h"  //RJA implementing this gd2-lib code using Matrix Orbital's driver

//RJA:  This gd2-lib example shows a jpg or png image on screen, now scaled to be larger on screen
//Note:  The decompresses size of the image must fit in GRAM... 




char filename[] = "healsky3.jpg";  //128x128 image




void setup()
{
  begin();
  load(filename);
}

void loop()
{
    ClearColorRGB(55, 55, 55);
    Clear();
    
    int scale = 3;
    cmd_loadidentity();
    Cmd_Scale(scale*65536, scale * 65536);  //scale
    cmd_setmatrix();  //make scale take affect
    BitmapSize(BILINEAR, 1, 1, 128*scale, 128 * scale);
    Begin(BITMAPS);
    Vertex2ii(100, 100);  //RJA: This paints the image.  Somehow it knows the image size.
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


