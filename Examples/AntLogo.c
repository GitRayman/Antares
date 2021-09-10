#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//RJA:  Antares project logo


void setup()
{
  begin();
  //_pinh(basepin+3);  //Turn on AntaresB LED 
}

void loop()
{
    ClearScreen(RGB(255, 255, 255)); 
    FormatVertex(VERTEX_FORMAT_ONE);  //RJA 1:1 coordinate system

    //define points at center of stars
    xy AntA;
    AntA.x = w / 2 + w / 12;
    AntA.y = h / 2 + h / 12;
    xy AntB;
    AntB.x = w / 2 - w / 12;
    AntB.y = h / 2 - h / 12;

    //draw lines between stars
    int linewidth = 2 * h / 720;
    int o;
    o = 15 * w / 1280;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(100, 100, 100), linewidth);
    o = 5 * w / 1280;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(100, 100, 100), linewidth);
    o = -5 * w / 1280;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(100, 100, 100), linewidth);
    o = -15 * w / 1280;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(100, 100, 100), linewidth);

    //draw stars on top of lines
    DrawFilledCircle(AntA.x, AntA.y, RGB(250, 40, 40), w / 12);
    DrawFilledCircle(AntB.x, AntB.y, RGB(40, 40, 250), w / 24);

    //draw text at top
    DrawText(w/2, h/8, 34, OPT_CENTERX, (char *) "Antares", RGB(0,0,0));

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




