#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

#include "Panels.h"  //for mouse things

//RJA:  This example draws a mouse cursor controlled by USB mouse on top of bird image (image takes a while to load)

#ifdef USE_HOST
char filename[] = "streamer.png";
#elif defined USE_SD
char filename[] = "streamer.png";
#endif 



void setup()
{
  begin();
  //load up cursor
  Load_RAW(0xF0000, (char*)"arrow01.raw");
  int pBird=load(filename);
  printf("Bird at %0X\n", pBird);

  StartMouse();  //start USB mouse

  

}

void loop()
{  
    FormatVertex(VERTEX_FORMAT_ONE);  //change Vertex2f scale to 1:1
    ClearScreen(RGB(25, 25, 255));
    Cmd_SetBitmap(256 * 2, PALETTED565, 1280, 720);  //RGB565 palette takes up bottom of memory
    Begin(BITMAPS);  
    Vertex2f(0, 0);  //RJA: This paints the image.  Somehow it knows the image size, unless you add commands like clearcolor()

    Cmd_SetBitmap(0xF0000, ARGB4, 16, 24);  
    Begin(BITMAPS);
    Vertex2f(MouseStatus.x, MouseStatus.y);
    //printf("Mouse at %d, %d\n", MouseStatus.x, MouseStatus.y);
    swap(); //Image should now be showing

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




