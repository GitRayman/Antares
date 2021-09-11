#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

static int a[256];

#include "walk_assets.h"

void setup()
{
  begin();
  LOAD_ASSETS();
  for (int i = 0; i < 256; i++)
    a[i] = random1(512);
}

void loop()
{
  ClearColorRGB24(0x000050);  
  Clear();

  RestoreContext();
  //BitmapHandle(WALK_HANDLE);  //RJA:  Don't need to do this as asset loader does it automagically
  //Cmd_SetBitmap(0, ARGB1555, 32, 32); //RJA:  Don't need to do this as asset loader does it automagically
  FormatVertex(VERTEX_FORMAT_ONE);  //RJA:  changing from 16:1 to 1:1 pixel size
  Begin(BITMAPS);
  for (int i = 0; i < 256; i++) {
    ColorRGB(i, i, i);
    Cell((a[i] >> 2) & 7);
    Vertex2f(a[i], i);
    a[i] = (a[i] + 1) & 511;
  }
  swap();
}


void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
        usleep(100000); //RJA:  Slowing it down a bit for effect
    }
}



