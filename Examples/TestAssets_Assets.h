#define LOAD_ASSETS()  safeload((char *) "Assets.ant");

#define Tulips_HANDLE 0
#define Tulips_WIDTH 320
#define Tulips_HEIGHT 194
#define Tulips_CELLS 1
#define Tulips_Location 0

#define flowersH_HANDLE 1
#define flowersH_WIDTH 512
#define flowersH_HEIGHT 308
#define flowersH_CELLS 1
#define flowersH_Location 124160

#define Pencils_HANDLE 2
#define Pencils_WIDTH 320
#define Pencils_HEIGHT 194
#define Pencils_CELLS 1
#define Pencils_Location 439552

#define springH_HANDLE 3
#define springH_WIDTH 512
#define springH_HEIGHT 308
#define springH_CELLS 1
#define springH_Location 563712

#define Gameria_HANDLE 4
#define Gameria_WIDTH 32
#define Gameria_HEIGHT 32
#define Gameria_CELLS 95
#define Gameria_Location 879104

#define Spaceare_HANDLE 5
#define Spaceare_WIDTH 36
#define Spaceare_HEIGHT 38
#define Spaceare_CELLS 95
#define Spaceare_Location 927892

#define ASSETS_END 993020UL

static const shape_t Tulips_SHAPE = { 0, 320, 194, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t flowersH_SHAPE = { 1, 512, 308, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t Pencils_SHAPE = { 2, 320, 194, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t springH_SHAPE = { 3, 512, 308, 1 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t Gameria_SHAPE = { 4, 32, 32, 95 };  //RJA thinks size element is #cells in image, if non-zero

static const shape_t Spaceare_SHAPE = { 5, 36, 38, 95 };  //RJA thinks size element is #cells in image, if non-zero

