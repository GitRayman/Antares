//Simple example adapted from gd2-lib
#include "Antares.h"  


void setup()
{
  begin();
}

void loop()
{
  ClearColorRGB(10,20,100); //set background color
  Clear();  //clear screen to background color
  cmd_text(w / 2, h / 2, 31, OPT_CENTER, "Hello world");
  swap();  //show this display list and start another
}

void main()
{
    setup();
    for (;;)
    {
        loop();
    }
}
