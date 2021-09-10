#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver


#include "mono_assets.h"

void setup()
{
  begin();
  LOAD_ASSETS();
}

void loop()
{
  ClearColorRGB24(0x375e03);
  Clear();
  Begin(BITMAPS);
  ColorRGB24(0x68b203);
  BitmapSize(NEAREST, REPEAT, REPEAT, 480, 272);
  Vertex2ii(0, 0);
  swap();
}


void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
    }
}


