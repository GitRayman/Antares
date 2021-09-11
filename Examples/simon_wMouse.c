#include "../Antares/Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

#include "Panels.h"  //RJA just using this to access mouse and cursor

void setup()
{
  begin();
  bMouseDown = false;
  InitPanels(NULL); //start mouse (but don't show any panels)
}

#define DARK_GREEN      0x007000
#define LIGHT_GREEN     0x33ff33
#define DARK_RED        0x700000
#define LIGHT_RED       0xff3333
#define DARK_YELLOW     0x707000
#define LIGHT_YELLOW    0xffff33
#define DARK_BLUE       0x007070
#define LIGHT_BLUE      0x33ffff

#define x1 (w/2-70)
#define y1 (h/2-70)
#define x2 (w/2+70)
#define y2 (h/2-70)
#define x3 (w/2-70)
#define y3 (h/2+70)
#define x4 (w/2+70)
#define y4 (h/2+70)

bool bMouseDown;

void drawscreen(int pressed)
{
  //get_inputs();  //RJA not using touchscreen

  Clear();
  FormatVertex(VERTEX_FORMAT_ONE);

  PointSize(16 * 60);  // 60-pixel radius points
  Begin(POINTS);
  Tag(1);
  if (pressed == 1)
    ColorRGB24(LIGHT_GREEN);
  else
    ColorRGB24(DARK_GREEN);
  Vertex2f(x1,y1);

  Tag(2);
  if (pressed == 2)
    ColorRGB24(LIGHT_RED);
  else
    ColorRGB24(DARK_RED);
  Vertex2f(x2, y2);

  Tag(3);
  if (pressed == 3)
    ColorRGB24(LIGHT_YELLOW);
  else
    ColorRGB24(DARK_YELLOW);
  Vertex2f(x3, y3);

  Tag(4);
  if (pressed == 4)
    ColorRGB24(LIGHT_BLUE);
  else
    ColorRGB24(DARK_BLUE);
  Vertex2f(x4, y4);

  DrawCursor();
  swap();
}

int GetMouseInputs()
{//return which button was pressed
    CheckMouse();
    if ((bMouseDown == false) && (bLeftButtonDown == true))
        bMouseDown = true;
    if ((bMouseDown == true) && (bLeftButtonDown == false))
    {//user clicked, so see if on a circle
        bMouseDown = false;
        int x = MouseStatus.x;
        int y = MouseStatus.y;
        int r;
        int r2 = 60 * 60;
        //calculate distance from center of each circle and see if inside
        r = (x - x1) * (x - x1) + (y - y1) * (y - y1);
        if (r < r2)
            return 1;
        r = (x - x2) * (x - x2) + (y - y2) * (y - y2);
        if (r < r2)
            return 2;
        r = (x - x3) * (x - x3) + (y - y3) * (y - y3);
        if (r < r2)
            return 3;
        r = (x - x4) * (x - x4) + (y - y4) * (y - y4);
        if (r < r2)
            return 4;
        return 0;
    }

}

void playNote(int pressed, bool bNoDelay=false)
{
  //                 G   R   Y   B
  //                 E3  A4  C#4 E4
  byte note[] = { 0, 52, 69, 61, 64 };
  play(BELL, note[pressed]);
  for (int i = 0; i < 30; i++)
    drawscreen(pressed);

  if (bNoDelay)  //RJA adding this so don't have to wait before pushing another button
      return;
  
  for (int i = 0; i < 15; i++)
    drawscreen(0);
}

static int get_note()
{
  byte pressed = 0;
  while (pressed == 0) {
    random();
    drawscreen(0);
    //RJA using mouse instead of touchscreen
    //if ((1 <= inputs.tag) && (inputs.tag <= 4))
    //  pressed = inputs.tag;
    pressed = GetMouseInputs();  //RJA using this instead for mouse
  }
  playNote(pressed, true);
  return pressed;
}

static int random_note()
{
  return 1 + random1(4);
}

void loop()
{
  int sequence[100];
  int length = 0;

  while (1) {
    //delay(500); //RJA:  This makes cursor freeze
    for (int i = 0; i < 50; i++)
    {//instead of delay, just draw screen
        drawscreen(0);
        delay(10);
    }

    sequence[length++] = random_note();

    for (int i = 0; i < length; i++)
      playNote(sequence[i]);

    for (int i = 0; i < length; i++) {
      int pressed = get_note();
      if (pressed != sequence[i]) {
        for (int i = 69; i > 49; i--) {
          play(BELL, i);
          delay(50);
        }
        return;
      }
    }
  }
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    delay(1500);  //wait a second
    for (;;)
    {
        loop();
    }
}
