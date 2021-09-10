//Use GPIO0 and GPIO1 as inputs and display status on screen
#include "Antares.h"  

//Note:  The GPIOs have weak pullups that will make them read 1 if nothing is connected
//       The default drive strength is 5 mA for these GPIO, but this can be increased via REG_GPIO

void setup()
{
  begin();

  //Write GPIO direction register to make GPIO0&1 inputs
  //This is the reset value so don't actually have to do this
  wr32(REG_GPIOX_DIR + RAM_REG, 0x8000); //One could use the lower two bits to make GPIO0 and/or GPIO1 outputs
}

char c[128];

void loop()
{
  ClearColorRGB(10,20,100); //set background color
  Clear();  //clear screen to background color

  
  //Read GPIO status
  uint32_t i=rd32(REG_GPIOX + RAM_REG);
  int gpio0 = 0;
  int gpio1= 0;
  if (i & 0b01)
      gpio0 = 1;
  if (i & 0b10)
      gpio1 = 1;
  sprintf(c, "GPIO0= %d, GPIO1= %d", gpio0, gpio1);
  cmd_text(w / 2, h / 2, 31, OPT_CENTER, c);
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
