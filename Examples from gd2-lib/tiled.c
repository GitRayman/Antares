#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver



#include "tiled_assets.h"

void setup()
{
  begin();
  LOAD_ASSETS();
}

void loop()
{
  Clear();
  Begin(BITMAPS);
  BitmapSize(BILINEAR, REPEAT, REPEAT, 480, 272);
  cmd_rotate(3333);
  cmd_setmatrix();
  Vertex2ii(0, 0);
  swap();
}



void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
        usleep(300000); //RJA:  Slowing it down a bit for effect
    }
}


