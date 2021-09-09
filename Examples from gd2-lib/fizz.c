#include "Antares.h"   //RJA implementing this gd2-lib code with help of Matrix Orbital's EVE driver

void setup()
{
  begin();
}

void loop()
{
  Clear();
  Begin(POINTS);
  for (int i = 0; i < 100; i++) {
    PointSize(random1(2 * w));
    ColorRGB(random(), random(), random());
    ColorA(random());
    Vertex2f(random1(PIXELS(w)), random1(PIXELS(h)));
  }
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

