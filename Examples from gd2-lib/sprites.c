#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver
//RJA:  Had to add a FIFO update trigger to get to 2001 sprites

#include "sprites_assets.h"

void setup()
{
  begin();
  LOAD_ASSETS();
}

static byte t;

void loop()
{
  Clear();
  Begin(BITMAPS);
  byte j = t;
  uint32_t v, r;

  int nspr = min(2001, max(256, 19 * t)); //min(2001, max(256, 19 * t));  //RJA getting overflow of display list at 1197

  uint32_t *pv = sprites;
  for (int i = 0; i < nspr; i++) {
    v = (uint32_t)*(pv++);
    r = (uint32_t)*(circle + j++);
    cmd32(v + r);
    if (i == 500)  //RJA added this to get to EVE to start working on display list, to free up space for more sprites
        UpdateFIFO();  
  }

  ColorRGB24(0x000000);
  ColorA(140);
  LineWidth(28 * 16);
  Begin(LINES);
  Vertex2ii(240 - 110, 136, 0, 0);
  Vertex2ii(240 + 110, 136, 0, 0);

  RestoreContext();

  cmd_number(215, 110, 31, OPT_RIGHTX, nspr);
  cmd_text(  229, 110, 31, 0, "sprites");

  swap();
  
  t++;
}


void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
        //usleep(100000); //RJA:  Slowing it down a bit for effect
        //for (;;) {}
    }
}

