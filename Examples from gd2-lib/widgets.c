#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//Note:  This example is adapted from the gd2-lib code with same name here:  https://github.com/jamesbowman/gd2-lib

static uint16_t value = 15000;      // every widget is hooked to this value
static char message[41];            // 40 character text entry field
static uint16_t options = OPT_FLAT;
static byte prevkey;

void setup()
{
  memset(message, 7, 40);
  begin();
}

#define TAG_DIAL      200
#define TAG_SLIDER    201
#define TAG_TOGGLE    202
#define TAG_BUTTON1   203
#define TAG_BUTTON2   204

void loop()
{

  get_inputs();

  switch (inputs.track_tag & 0xff) {
  case TAG_DIAL:
  case TAG_SLIDER:
  case TAG_TOGGLE:
    value = inputs.track_val;
  }
  switch (inputs.tag) {
  case TAG_BUTTON1:
    options = OPT_FLAT;
    break;
  case TAG_BUTTON2:
    options = 0;
    break;
  }
  byte key = inputs.tag;
  if ((prevkey == 0x00) && (' ' <= key) && (key < 0x7f)) {
    memmove(message, message + 1, 39);
    message[39] = key;
  }
  prevkey = key;

  cmd_gradient(0, 0,   0x404044,  //RJA:  Note this also clears the screen
                  480, 480, 0x606068);
  ColorRGB24(0x707070);

  LineWidth(4 * 16);
  Begin(RECTS);

  Vertex2ii(8, 8);
  Vertex2ii(128, 128);

  Vertex2ii(8, 136 + 8);
  Vertex2ii(128, 136 + 128);

  Vertex2ii(144, 136 + 8);
  Vertex2ii(472, 136 + 128);
  ColorRGB24(0xffffff);

  Tag(TAG_DIAL);
  cmd_dial(68, 68, 50, options, value);
  cmd_track(68, 68, 1, 1, TAG_DIAL);

  Tag(TAG_SLIDER);
  cmd_slider(16, 199, 104, 10, options, value, 65535);
  cmd_track(16, 199, 104, 10, TAG_SLIDER);

  Tag(TAG_TOGGLE);
  printf("Options= %d, Value=%d\n", options, value);
  cmd_toggle(360, 62, 80, 29, options, value,"that" "\xff" "this");
  cmd_track(360, 62, 80, 20, TAG_TOGGLE);

  Tag(255);
  cmd_number(68, 136, 30, OPT_CENTER | 5, value);

  cmd_clock(184, 48, 40, options | OPT_NOSECS, 0, 0, value, 0);
  cmd_gauge(280, 48, 40, options, 4, 3, value, 65535);

  Tag(TAG_BUTTON1);
  cmd_button(352, 12, 40, 30, 28, options,  "2D");
  Tag(TAG_BUTTON2);
  cmd_button(400, 12, 40, 30, 28, options,  "3D");

  Tag(255);
  cmd_progress(144, 100, 320, 10, options, value, 65535);
  cmd_scrollbar(144, 120, 320, 10, options, value / 2, 32768, 65535);

  cmd_button(308 - 60, 172 + 74, 120, 20, 28, options, "");

  cmd_keys(144, 168,      320, 24, 28, options | OPT_CENTER | key, "qwertyuiop");
  cmd_keys(144, 168 + 26, 320, 24, 28, options | OPT_CENTER | key,   "asdfghjkl");
  cmd_keys(144, 168 + 52, 320, 24, 28, options | OPT_CENTER | key,   "zxcvbnm,.");
  Tag(' ');
  cmd_button(308 - 60, 172 + 74, 120, 20, 28, options,   "");

  BlendFunc(SRC_ALPHA, ZERO);
  cmd_text(149, 146, 18, 0, message);

  

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

