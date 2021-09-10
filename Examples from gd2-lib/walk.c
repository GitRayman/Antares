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
  Begin(BITMAPS);
  for (int i = 0; i < 256; i++) {
    ColorRGB(i, i, i);
    Vertex2ii(a[i], i, WALK_HANDLE, (a[i] >> 2) & 7);
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



