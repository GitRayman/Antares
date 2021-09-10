#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver


void setup()
{
  begin();
}

#define DARK_GREEN      0x007000
#define LIGHT_GREEN     0x33ff33
#define DARK_RED        0x700000
#define LIGHT_RED       0xff3333
#define DARK_YELLOW     0x707000
#define LIGHT_YELLOW    0xffff33
#define DARK_BLUE       0x007070
#define LIGHT_BLUE      0x33ffff

void drawscreen(int pressed)
{
  get_inputs();
  Clear();

  PointSize(16 * 60);  // 60-pixel radius points
  Begin(POINTS);
  Tag(1);
  if (pressed == 1)
    ColorRGB24(LIGHT_GREEN);
  else
    ColorRGB24(DARK_GREEN);
  Vertex2ii(240 - 70, 136 - 70);

  Tag(2);
  if (pressed == 2)
    ColorRGB24(LIGHT_RED);
  else
    ColorRGB24(DARK_RED);
  Vertex2ii(240 + 70, 136 - 70);

  Tag(3);
  if (pressed == 3)
    ColorRGB24(LIGHT_YELLOW);
  else
    ColorRGB24(DARK_YELLOW);
  Vertex2ii(240 - 70, 136 + 70);

  Tag(4);
  if (pressed == 4)
    ColorRGB24(LIGHT_BLUE);
  else
    ColorRGB24(DARK_BLUE);
  Vertex2ii(240 + 70, 136 + 70);

  swap();
}

void playNote(int pressed)
{
  //                 G   R   Y   B
  //                 E3  A4  C#4 E4
  byte note[] = { 0, 52, 69, 61, 64 };
  play(BELL, note[pressed]);
  for (int i = 0; i < 30; i++)
    drawscreen(pressed);
  for (int i = 0; i < 15; i++)
    drawscreen(0);
}

static int get_note()
{
  byte pressed = 0;
  while (pressed == 0) {
    random();
    drawscreen(0);
    if ((1 <= inputs.tag) && (inputs.tag <= 4))
      pressed = inputs.tag;
  }
  playNote(pressed);
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
    delay(500);

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
    for (;;)
    {
        loop();
    }
}
