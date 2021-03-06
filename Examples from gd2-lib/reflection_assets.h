#ifdef USE_SD
#define LOAD_ASSETS()  safeload("reflec~1.gd2");
#elif defined USE_HOST
#define LOAD_ASSETS()  safeload((char *)"reflection.gd2");
#endif // USE_SD


#define GAMEDUINO_HANDLE 0
#define GAMEDUINO_WIDTH 395
#define GAMEDUINO_HEIGHT 113
#define GAMEDUINO_CELLS 1
#define GRADIENT_HANDLE 1
#define GRADIENT_WIDTH 1
#define GRADIENT_HEIGHT 128
#define GRADIENT_CELLS 1
#define ASSETS_END 89398UL
static const shape_t GAMEDUINO_SHAPE = {0, 395, 113, 0};
static const shape_t GRADIENT_SHAPE = {1, 1, 128, 0};
