#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver


#include "reflection_assets.h"

void setup()
{
  begin();
  LOAD_ASSETS();
}

static void showit()
{
  ColorMask(1,1,1,1);
  BlendFunc(DST_ALPHA, ZERO);
  Begin(RECTS);
  Vertex2ii(0, 0);
  Vertex2ii(480, 272);
  swap();
}

#define MASK_ALPHA()   BlendFunc(ZERO, SRC_ALPHA)

void loop()
{
  int x = 240 - GAMEDUINO_WIDTH / 2;

  BitmapHandle(GRADIENT_HANDLE);
  BitmapSize(NEAREST, REPEAT, BORDER, 480, 272);

  Clear();
  ColorMask(1, 1, 1, 0);            // don't touch A yet
  cmd_gradient(0, 40, 0x505060,
                  0, 272, 0xc0c080);

  Begin(BITMAPS);                   // top bitmap
  Vertex2ii(x, 80, GAMEDUINO_HANDLE);

  ColorMask(0, 0, 0, 1);
  BlendFunc(ONE, ZERO);
  Vertex2ii(0, 180, GRADIENT_HANDLE);

                                       // invert the image
  cmd_translate(0, F16(GAMEDUINO_HEIGHT / 2));
  cmd_scale(F16(1), F16(-1));
  cmd_translate(0, -F16(GAMEDUINO_HEIGHT / 2));
  cmd_setmatrix();

  MASK_ALPHA();                        // mask with gradient
  Vertex2ii(x, 190, GAMEDUINO_HANDLE);

  ColorMask(1, 1, 1, 0);            // draw the reflection
  BlendFunc(DST_ALPHA, ONE_MINUS_DST_ALPHA);
  Vertex2ii(x, 190, GAMEDUINO_HANDLE);
  swap();
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
        sleep(1); //RJA:  The program seems to flip the reflection on every loop, slowing down here for effect
    }
}


