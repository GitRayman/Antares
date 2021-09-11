#include "../Antares/Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

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
    int linewidth;
    int o;
    int s; //scale for offset
    if (h > 512) 
    {//large screen
        s = 5;
        linewidth = 2;
    }
    else
    {//small screen
        s = 2; 
        linewidth = 1;
    }
    o = s*3;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(10, 10, 10), linewidth);
    //printf("Line from %d,%d to %d,%d\n", AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o);
    o = s;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(10, 10, 10), linewidth);
    o = -s;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(10, 10, 10), linewidth);
    o = -s*3;
    DrawLine(AntA.x + o, AntA.y - o, AntB.x + o, AntB.y - o, RGB(10, 10, 10), linewidth);

    //draw stars on top of lines
    DrawFilledCircle(AntA.x, AntA.y, RGB(250, 40, 40), w / 12);
    DrawFilledCircle(AntB.x, AntB.y, RGB(40, 40, 250), w / 24);

    //draw text at top
    if (w>512)
        DrawText(w/2, h/8, 34, OPT_CENTERX, (char *) "Antares", RGB(0,0,0));
    else
        DrawText(w / 2, h / 8, 31, OPT_CENTERX, (char*)"Antares", RGB(0, 0, 0));

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




