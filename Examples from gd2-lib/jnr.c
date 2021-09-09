#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

typedef struct scrollerClass {
  signed short dragprev;
  int vel;      // velocity
  long base;    // screen x coordinate, in 1/16ths pixel
  long limit;
  void init(uint32_t lim) {
    dragprev = -32768;
    vel = 0;      // velocity
    base = 0;     // screen x coordinate, in 1/16ths pixel
    limit = lim;
  }
  void run(bool touching, int16_t sx) {
    if (touching & (dragprev != -32768)) {
      vel = (dragprev - sx) << 4;
    } else {
      int change = max(1, abs(vel) >> 5);
      if (vel < 0)
        vel += change;
      if (vel > 0)
        vel -= change;
    }
    dragprev = touching ? sx : -32768;
    base += vel;
    base = max(0, min(base, limit));
  }
  uint16_t getval() {
    return base >> 4;
  }
} scroller;

scroller xscroll;

#include "jnr_assets.h"

static byte level[240] = {
  0xff,
  0xe2,
  0xe2,
  0xc0,
  0x44,
  0x40,
  0x04,
  0x40,
  0x44,
  0x00,
  0x04,
  0x40,
  0x5c,
  0x08,
};

int mapxy(int x, int y)
{
  if (x < 0)
    return 0;
  if (y < 0)
    return 0;
  if (8 <= y)
    return 0;
  if (240 <= y)
    return 0;
  return 1 & (level[x] >> y);
}

static void parallax(int x, int y)
{
  x %= 400;
  Vertex2f(16 * -x, 16 * y);
  Vertex2f(16 * (-x + 400), 16 * y);
}

static void draw(int xx)
{
  Clear();
  ScissorSize(480, 240);

  ClearColorRGB24(0x2578c5);
  Clear();
  Begin(BITMAPS);

  BitmapHandle(LAYER1_HANDLE);
  ColorRGB24(0x9ae8ff);
  parallax(xx >> 4, 0);

  BitmapHandle(LAYER2_HANDLE);
  ColorRGB24(0x85d2e9);
  parallax(xx >> 3, 240 - LAYER2_HEIGHT);

  BitmapHandle(LAYER3_HANDLE);
  ColorRGB24(0x67b0c5);
  parallax(xx >> 2, 240 - LAYER3_HEIGHT);

  BitmapHandle(LAYER4_HANDLE);
  ColorRGB24(0x549faa);
  parallax(xx >> 1, 240 - LAYER4_HEIGHT);

  ColorRGB24(0xffffff);
  BitmapHandle(TILES_HANDLE);
  int bx = xx / 32;
  for (int x = 0; x < 16; x++)
    for (int y = 0; y < 8; y++) {
      byte index = 0;
      if (mapxy(bx + x, y)) {
        if (mapxy(bx + x, y - 1))
          index += 1;
        if (mapxy(bx + x + 1, y))
          index += 2;
        if (mapxy(bx + x, y + 1))
          index += 4;
        if (mapxy(bx + x - 1, y))
          index += 8;
      } else {
        index = 17;
      }
      Tag(128 + 8 * x + y);
      Cell(index);
      Vertex2f(16 * (-(xx & 31) + 32 * x), 16 * 32 * y);
    }

  RestoreContext();
  cmd_scale(F16(16), F16(16));
  cmd_setmatrix();
  BitmapHandle(CHECKER_HANDLE);
  BitmapSize(NEAREST, REPEAT, REPEAT, 512, 32);
  Cell(0);
  Vertex2f(16 * -(xx & 31), 16 * 240);
}

void setup()
{
  begin();

  LOAD_ASSETS();

  xscroll.init((240UL * 32) << 4);
}

void loop()
{
  static int prevtag;
  uint16_t bx = xscroll.base >> 4;

  get_inputs();
  int touching = (inputs.x != -32768);
  byte tag = inputs.tag;

  if (prevtag != tag && (128 <= tag)) {
    level[(bx >> 5) + (tag - 128) / 8] |= 1 << (tag & 7);
  }
  prevtag = tag;

  xscroll.run(inputs.y > 240 && touching, inputs.x);
  draw(bx);
  int t;
  swap();
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
        //usleep(100000); //RJA:  Slowing it down a bit for effect
        for (;;) {}
    }
}

