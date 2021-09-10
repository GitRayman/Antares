//RJA:  This gd2-lib example paints a bunch of expanding filled circles on the screen
//      The original version used touchsreen to set circle locations, but using random locations here as don't have touchscreen

#include "../Antares/Antares.h"  

#define NBLOBS      128

xy blobs[NBLOBS];  
const xy offscreen = {-16384, -16384};

void setup()
{
    begin();// ~GD_STORAGE);

  for (int i = 0; i < NBLOBS; i++)
    blobs[i] = offscreen;
}

void loop()
{
  static byte blob_i;
  get_inputs();  //RJA:  This would update touchscreen data if we had a touchscreen
  if (inputs.x != -32768)  //((rand() % 10)==1)//inputs.x != -32768)     //RJA don't have real touchscreen, so faking touches
  {
      //inputs.xytouch.x = (rand() % w)*16;
      //inputs.xytouch.y = (rand() % h) *16;
      //printf("Touching: %d, %d\n", inputs.xytouch.x, inputs.xytouch.y);
    blobs[blob_i] = inputs.xytouch;  
  }
  else
    blobs[blob_i] = offscreen;
  blob_i = (blob_i + 1) & (NBLOBS - 1);

  //RJA clear the screen
  ClearColorRGB24(0xe0e0e0);  //RJA appended "24" to this function since we don't have overloading in C
  Clear();

  //RJA draw some text
  ColorRGB24(0xa0a0a0);
  cmd_text(240, 136, 31, OPT_CENTER, "touch to draw");


  //RJA draw the circles
  Begin(POINTS); 
  for (int i = 0; i < NBLOBS; i++) {
    // Blobs fade away and swell as they age
    ColorA(i << 1);
    PointSize((1024 + 16) - (i << 3));

    // Random color for each blob, keyed from (blob_i + i)
    uint8_t j = (blob_i + i) & (NBLOBS - 1);
    byte r = j * 17;
    byte g = j * 23;
    byte b = j * 147;
    ColorRGB(r, g, b);

    // Draw it!
    blobs[j].draw(0);  //RJA added 0 parameter
  }
  //Finish and draw screen
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


