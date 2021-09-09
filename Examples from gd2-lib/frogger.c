#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver
//RJA May be working, but don't have input mechanism yet...
//RJA having some fake input to make frog jump

#include "frogger_assets.h"

#define CONTROL_LEFT  1
#define CONTROL_RIGHT 2
#define CONTROL_UP    4
#define CONTROL_DOWN  8

typedef struct ControllerClass {
    void begin() {
      prev = 0;
    }
    byte read() {
        byte r = 0;//RJA needs to fix input inputs.tag& (CONTROL_LEFT | CONTROL_RIGHT | CONTROL_UP | CONTROL_DOWN);
      byte edge = r & ~prev;
      prev = r;
      return edge;
    }
    byte prev;
} Controller;

static Controller Control;

static void draw_score(byte x, byte y, long n)
{
  cmd_number(8 * x, 8 * y, FONT_HANDLE, 5, n);
}

// Game variables
static unsigned int t;
static int frogx, frogy;    // screen position
static int leaping;         // 0 means not leaping, 1-8 animates the leap
static int frogdir;         // while leaping, which direction is the leap?
static int frogface;        // which way is the frog facing, in furmans for CMD_ROTATE
static int dying;           // 0 means not dying, 1-64 animation counter
static long score;
static long hiscore;
static byte lives;
static byte done[5];
static byte homes[5] = { 24, 72, 120, 168, 216 };
static int ti;

void frog_start()
{
  frogx = 120;
  frogy = 232;
  leaping = 0;
  frogdir = 0;
  frogface = 0x0000;
  dying = 0;
  ti = 120 << 7;
}

void level_start()
{
  for (byte i = 0; i < 5; i++)
    done[i] = 0;
}

void game_start()
{
  lives = 4;
  score = 0;
}

void game_setup()
{
  Control.begin();
  game_start();
  level_start();
  frog_start();
}


static void sprite(byte x, byte y, byte anim, uint16_t rot = 0xffff)
{
  x -= 16;
  y -= 8;
  if (rot != 0xffff) {
    cmd_loadidentity();
    cmd_translate(F16(8),F16(8));
    cmd_rotate(rot);
    cmd_translate(F16(-8),F16(-8));
    cmd_setmatrix();
  }
  if (x > 224) {
    Cell(anim);
    Vertex2f(16 * (x - 256), 16 * y);
  } else {
    Vertex2ii(x, y, SPRITES_HANDLE, anim);
  }
}

static void turtle3(byte x, byte y)
{
  byte anim = 50 + ((t / 32) % 3);
  sprite(x, y, anim);
  sprite(x + 16, y, anim);
  sprite(x + 32, y, anim);
}

static void turtle2(byte x, byte y)
{
  byte anim = 50 + ((t / 32) % 3);
  sprite(x, y, anim);
  sprite(x + 16, y, anim);
}

void log1(byte x, byte y)
{
  sprite(x, y,      86);
  sprite(x + 16, y, 87);
  sprite(x + 32, y, 88);
}

void log(byte length, byte x, byte y)
{
  sprite(x, y,      86);
  while (length--) {
    x += 16;
    sprite(x, y, 87);
  }
  sprite(x + 16, y, 88);
}

static int riverat(byte y, uint16_t tt)
{
  switch (y) {
  case 120: return -tt;
  case 104: return tt;
  case 88:  return 5 * tt / 4;
  case 72:  return -tt / 2;
  case 56:  return tt / 2;
  }
}

static void squarewave(uint16_t freq, byte amp)
{
  wr(REG_VOL_SOUND, amp);
  wr16(REG_SOUND, (freq << 8) | 0x01);
  wr(REG_PLAY, 1);
}

static void sound()
{
  byte note;

  if (dying) {
    note = 84 - (dying / 2);
    squarewave(note, 100);
  } else if (leaping) {
    if (leaping & 1)
      note = 60 + leaping;
    else
      note = 72 + leaping;
    squarewave(note, 100);
  } else {
    squarewave(0, 0);  // silence
  }
}

static void rotate_around(int x, int y, int a)
{
    cmd_loadidentity();
    cmd_translate(F16(x),F16(y));
    cmd_rotate(a);
    cmd_translate(F16(-x),F16(-y));
    cmd_setmatrix();
}

void game_over()
{
  wr(REG_VOL_SOUND, 0);
  for (byte i = 0; i < 60; i++) {
    Clear();

    // Draw "F R O G G E R" using the sprites 90-94

    int x = 160, y = 50, space = 24;
    Begin(BITMAPS);
    Vertex2ii(x, y, SPRITES_HANDLE, 90); x += space;   // F
    Vertex2ii(x, y, SPRITES_HANDLE, 91); x += space;   // R
    Vertex2ii(x, y, SPRITES_HANDLE, 92); x += space;   // O
    Vertex2ii(x, y, SPRITES_HANDLE, 93); x += space;   // G
    Vertex2ii(x, y, SPRITES_HANDLE, 93); x += space;   // G
    Vertex2ii(x, y, SPRITES_HANDLE, 94); x += space;   // E
    Vertex2ii(x, y, SPRITES_HANDLE, 91); x += space;   // R

    cmd_text(240, 136, FONT_HANDLE, OPT_CENTER, "GAME OVER");
    if (i == 59)
      cmd_text(240, 200, FONT_HANDLE, OPT_CENTER, "PRESS TO PLAY");
    swap();
  }
  while (inputs.x == -32768)
    get_inputs();
  while (inputs.x != -32768)
    get_inputs();
}

void loop()
{
  static uint32_t counter;
  static int prevt;

  Clear();
  Tag(1);
  BitmapHandle(SPRITES_HANDLE);
  SaveContext();
  ScissorSize(224, 256);
  Begin(BITMAPS);
  Vertex2ii(0, 0, BACKGROUND_HANDLE, 0);   // Background bitmap

  wr(REG_TAG_X, frogx - 8);
  wr(REG_TAG_Y, frogy);

  Tag(2);
  AlphaFunc(GREATER, 0); // on road, don't tag transparent pixels

  // Completed homes
  for (byte i = 0; i < 5; i++) {
    if (done[i])
      sprite(homes[i], 40, 63);
  }

  // Yellow cars
  sprite(-t,       216, 3);
  sprite(-t + 128, 216, 3);

  // Dozers
  sprite(t, 200, 4);
  sprite(t + 50, 200, 4);
  sprite(t + 150, 200, 4);

  // Purple cars
  sprite(-t,       184, 7);
  sprite(-t + 75,  184, 7);
  sprite(-t + 150, 184, 7);

  // Green and white racecars
  sprite(2 * t,    168, 8);

  // Trucks
  sprite(-t/2,       152, 5);
  sprite(-t/2 + 16,  152, 6);
  sprite(-t/2 + 100, 152, 5);
  sprite(-t/2 + 116, 152, 6);

  AlphaFunc(GREATER, 0); // on river, tag transparent pixels

  // Turtles
  for (int i = 0; i < 256; i += 64)
    turtle3(riverat(120, t) + i, 120);

  // Short logs
  for (int i = 0; i < 240; i += 80)
    log(1, riverat(104, t) + i, 104);

  // Long logs
  for (int i = 0; i < 256; i += 128)
    log(5, riverat(88, t) + i, 88);

  // Turtles again, but slower
  for (int i = 0; i < 250; i += 50)
    turtle2(riverat(72, t) + i, 72);

  // Top logs
  for (int i = 0; i < 210; i += 70)
    log(2, riverat(56, t) + i, 56);

  // The frog himself, or his death animation

  TagMask(0);

  if (!dying) {
    static byte frog_anim[] = {2, 1, 0, 0, 2};
    sprite(frogx, frogy, frog_anim[leaping / 2], frogface);
  } else {
    static byte die_anim[] = {31, 32, 33, 30};
    sprite(frogx, frogy, die_anim[dying / 16], frogface);
  }

  prevt = t;
  t++;
  ti = max(0, ti - 1);
  if ((ti == 0) && (dying == 0))
    dying = 1;

  // Draw 'time remaining' by clearing a black rectangle
  {
    byte tw = 120 - (ti >> 7);
    byte tx = 72;
    SaveContext();
    ScissorXY(tx, 248);
    ScissorSize(tw, 8);
    Clear();
    RestoreContext();
  }

  TagMask(1);

  // player control.  If button pressed, start the 'leaping' counter
  byte con = Control.read();

  if (random() < 10)
  {//RJA adding fake input
      con = CONTROL_UP;
  }

  if (!dying && (leaping == 0) && con) {
    frogdir = con;
    leaping = 1;
    score += 10;
  } else if (leaping > 0) {
    if (leaping <= 8) {
      if (frogdir == CONTROL_LEFT) {
        frogx -= 2;
        frogface = 0xc000;
      } if (frogdir == CONTROL_RIGHT) {
        frogx += 2;
        frogface = 0x4000;
      } if (frogdir == CONTROL_UP) {
        frogy -= 2;
        frogface = 0x0000;
      } if (frogdir == CONTROL_DOWN) {
        frogy += 2;
        frogface = 0x8000;
      }
      leaping++;
    } else {
      leaping = 0;
    }
  }

  RestoreContext();
  SaveContext();
  Begin(BITMAPS);

#define PADX(x) (480 + (x - 3) * 48)
#define PADY(y) (272 + (y - 3) * 48)

  Tag(CONTROL_RIGHT);
  Vertex2ii(PADX(2), PADY(1), ARROW_HANDLE, 0);
  rotate_around(24, 24, 3 * 0x4000);

  Tag(CONTROL_UP);
  Vertex2ii(PADX(1), PADY(0), ARROW_HANDLE, 0);
  rotate_around(24, 24, 2 * 0x4000);

  Tag(CONTROL_LEFT);
  Vertex2ii(PADX(0), PADY(1), ARROW_HANDLE, 0);
  rotate_around(24, 24, 1 * 0x4000);

  Tag(CONTROL_DOWN);
  Vertex2ii(PADX(1), PADY(2), ARROW_HANDLE, 0);
  RestoreContext();

  ColorRGB(255, 85, 0);
  draw_score(3, 1, score);
  draw_score(11, 1, hiscore);

  ColorRGB(255, 255, 255);
  for (byte i = 0; i < lives; i++)
    Vertex2ii(8 * i, 30 * 8, LIFE_HANDLE, 0);

  // for (byte i = 0; i < 16; i++)
  //  wr(atxy(i, 30), (i < lives) ? BG_LIFE : BG_BLACK);

  swap();

  get_inputs();
  byte tag = rd(REG_TAG);
  byte touching = (tag == 2);

  if (dying) {
      printf("Dying...\n");
    if (++dying == 64) {
      if (--lives == 0 || ti == 0) {
        game_over();
        game_start();
        level_start();
      }
      frog_start();
    }
  }
  else if (frogx < 8 || frogx > 224) {
    dying = 1;
  }
  else if (frogy >= 136) {    // road section
    // if touching something, frog dies
    if (tag == 2)
      dying = 1;
  }
  else if (frogy > 40) {      // river section
    if (!leaping) {
      // if touching something, frog is safe
      if (tag != 1) {
        // move frog according to lane speed
        int oldx = riverat(frogy, prevt);
        int newx = riverat(frogy, t);
        int river_velocity = newx - oldx;
        frogx += river_velocity;
      } else {
        dying = 1;
      }
    }
  }
  else
  {                      // riverbank section
    if (!leaping) {
      byte landed = 0;
      for (byte i = 0; i < 5; i ++) {
        if (!done[i] && abs(homes[i] - frogx) < 4) {
          done[i] = 1;
          landed = 1;
          score += 10;
        }
      }
      if (landed) {
        if (done[0] && done[1] && done[2] && done[3] && done[4])
          level_start();
        frog_start();
      } else // if frog did not land in a home, die!
        dying = 1;
    }
  }
  sound();
  hiscore = max(score, hiscore);
}

void setup()
{
  begin();
  LOAD_ASSETS();
  game_setup();
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
    }
}


