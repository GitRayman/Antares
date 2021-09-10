#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE drive

#include "slotgag_assets.h"

void setup()
{
  begin();
  LOAD_ASSETS();
}

void loop()
{
  Clear();
  ColorMask(1, 1, 1, 0);
  Begin(BITMAPS);
  BitmapHandle(BACKGROUND_HANDLE);
  BitmapSize(NEAREST, REPEAT, REPEAT, 480, 272);
  Vertex2ii(0, 0, BACKGROUND_HANDLE);

  ColorMask(1, 1, 1, 1);
  ColorRGB24(0xa0a0a0);
  Vertex2ii(240 - GAMEDUINO_WIDTH / 2,
               136 - GAMEDUINO_HEIGHT / 2,
               GAMEDUINO_HANDLE);

  static int x = 0;
  LineWidth(20 * 16);
  BlendFunc(DST_ALPHA, ONE);
  Begin(LINES);
  Vertex2ii(x, 0);
  Vertex2ii(x + 100, 272);
  x = (x + 20) % 480;

  swap();
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
        usleep(600); //RJA:  Slowing it down a bit for effect
    }
}


