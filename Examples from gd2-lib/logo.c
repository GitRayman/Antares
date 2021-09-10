#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

#include "logo_assets.h"

void setup()
{

  begin();
  LOAD_ASSETS();
  printf("setup complete.\n");

}

byte clamp255(int x)
{
  if (x < 0)
    return 0;
  if (255 < x)
    return 255;
  return x;
}

#define NSTARS 256

void loop()
{
  byte fade;
  xy stars[NSTARS];
  for (int i = 0; i < NSTARS; i++)
    stars[i].set(random1(PIXELS(w)), random1(PIXELS(h)));

  for (int t = 0; t < 464; t++) {
    cmd_gradient(0, 0, 0x120000, 0, h, 0x480000);
    BlendFunc(SRC_ALPHA, ONE);
    Begin(POINTS);
    for (int i = 0; i < NSTARS; i++) {
      ColorA(64 + (i >> 2));
      PointSize(8 + (i >> 5));
      stars[i].draw(0);
      // stars drift left, then wrap around
      stars[i].x -= 1 + (i >> 5);
      if (stars[i].x < -256) {
        stars[i].x += PIXELS(w + 20);
        stars[i].y = random1(PIXELS(h));
      }
    }


    RestoreContext();
    Begin(BITMAPS);

    // Main logo fades up from black
    fade = clamp255(5 * (t - 15));
    ColorRGB(fade, fade, fade);
    Vertex2ii(240 - GAMEDUINO_WIDTH/2, 65, GAMEDUINO_HANDLE, 0);
    RestoreContext();

    // The '2' and its glow
    fade = clamp255(8 * (t - 120));
    ColorA(fade);
    Vertex2ii(270, 115, TWO_HANDLE, 0);
    fade = clamp255(5 * (t - 144));

    BlendFunc(SRC_ALPHA, ONE);
    ColorA(fade);
    ColorRGB(85,85,85);
    Vertex2ii(270, 115, TWO_HANDLE, 1);

    RestoreContext();

    // The text fades up. Its glow is a full-screen bitmap
    fade = clamp255(8 * (t - 160));
    ColorA(fade);
    cmd_text(140, 200, 29, OPT_CENTER, "This time");
    cmd_text(140, 225, 29, OPT_CENTER, "it's personal");
    fade = clamp255(5 * (t - 184));
    BlendFunc(SRC_ALPHA, ONE);
    ColorA(fade);
    ColorRGB(85,85,85);
    Vertex2ii(0, 0, PERSONAL_HANDLE, 0);

    // OSHW logo fades in
    ColorRGB(0, 153 * 160 / 255, 176 * 160 / 255);
    Vertex2ii(2, 2, OSHW_HANDLE, 0);
    RestoreContext();


    // Fade to white at the end by drawing a white rectangle on top
    fade = clamp255(5 * (t - 400));
    ColorA(fade);
    Begin(EDGE_STRIP_R);
    Vertex2f(0, 0);
    Vertex2f(0, PIXELS(h));

    swap();
  }
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;) 
    {
        loop();
    }
}
