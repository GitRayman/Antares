#define LOAD_ASSETS()  safeload((char *) "BlockAssets.ant");

#define Arrow_HANDLE 0
#define Arrow_WIDTH 16
#define Arrow_HEIGHT 24
#define Arrow_CELLS 1
#define Arrow_Location 0

#define RepeatForever_HANDLE 1
#define RepeatForever_WIDTH 165
#define RepeatForever_HEIGHT 82
#define RepeatForever_CELLS 1
#define RepeatForever_Location 768

#define RepeatForeverHighlighted_HANDLE 2
#define RepeatForeverHighlighted_WIDTH 166
#define RepeatForeverHighlighted_HEIGHT 84
#define RepeatForeverHighlighted_CELLS 1
#define RepeatForeverHighlighted_Location 27828

#define BlockMenu_HANDLE 3
#define BlockMenu_WIDTH 192
#define BlockMenu_HEIGHT 779
#define BlockMenu_CELLS 1
#define BlockMenu_Location 55716

#define ASSETS_END 354852UL

static const shape_t Arrow_SHAPE = { 0, 16, 24, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t RepeatForever_SHAPE = { 1, 165, 82, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t RepeatForeverHighlighted_SHAPE = { 2, 166, 84, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t BlockMenu_SHAPE = { 3, 192, 779, 1 };  //RJA thinks size element is #cells in image, if non-zero

