////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Block Definitions


#ifndef _BLOCKS_H_
#define _BLOCKS_H_

#define MaxBlockText (1920/16) //make it width of screen in tiles
#define MaxBlockObjects 100

#include "Colors.h"

enum BlockObjectTypes { BlockType = 0, ButtonType = 1, TextType, ToggleType, SliderType, ScrollBarType, GaugeType, LedType, KeysType,
                       GraphicsAreaType, GraphicsObjectType, ProgressType, DialType, NumberType, ClockType, ImageType, 
                        RepeatType };

typedef struct
{//Common beginning of all panel objects
    char* name;             //Object Name
    int type;
    int top;
    int left;
    int width;
    int height;
    int data;
    int status;
} BlockObject;

typedef struct {
    BlockObject* p[MaxBlockObjects];
} BlockObjectList;

typedef   void (*BlockOperation)(BlockObject* pObject);

typedef struct
{//Block 
    char* name;             //Object Name
    int type;               //Object type 
    int top;                //Top 
    int left;               //Left 
    int width;              //width 
    int height;             //height
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int bordercolor;        //Border color
    int fillcolor;          //fill color
    int font;               //font #
    int fontoptions;        //font options
    char* pTitleText;           //title bar text
    int textcolor;          //color of title bar text
    int titleTop;           //y offset for title
    int titleLeft;          //x offset for title
    int titleOptions;       //options for drawing title text
    BlockObject* pParent;    //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a BlockBlock*
    BlockObjectList* pObjectList;   //pointer to NULL terminated list of form objects
    BlockOperation OnBlockOpen;  //Function to call when opening this panel
    BlockOperation OnBlockClose;  //Function to call when closing this panel
    BlockOperation OnIdle;  //Function to call when idle
    BlockOperation OnClick;  //function to call when clicked on something not handled elsewhere
} BlockBlock;


typedef struct
{//Repeat
    char* name;             //Button Name
    int type;               //Object type
    int top;                //Top
    int left;               //Left 
    int width;              //Width 
    int height;             //Height 
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int textcolor;          //Text foreground color
    int color;              //Button color 
    int font;               //font#
    int fontoptions;        //font options
    char* pText;            //Button text
    BlockOperation OnClick; //Function to call when button clicked
    bool bMouseDownOn;      //Is the mouse down on this button?
    int BmpHandleUp;        //Handle to draw when mouse up  //Replace handle with cell in future
    int BmpHandleDown;      //Handle to draw when mouse down
} BlockRepeat;



typedef struct
{//Button
    char* name;             //Button Name
    int type;               //Object type
    int top;                //Top
    int left;               //Left 
    int width;              //Width 
    int height;             //Height 
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int textcolor;          //Text foreground color
    int color;              //Button color 
    int font;               //font#
    int fontoptions;        //font options
    char* pText;            //Button text
    BlockOperation OnClick; //Function to call when button clicked
    bool bMouseDownOn;       //Is the mouse down on this button?
} BlockButton;

typedef struct
{//Slider
    char* name;             //Slider Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width   //Note: If vertical, this is width of knob
    int height;             //Height   //Note:  IF horiizontal, this is width of knob
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int leftcolor;          //left color
    int rightcolor;           //right color 
    int knobcolor;          //Knob color
    int options;            //options
    int val;                //value
    int range;              //range
    BlockOperation OnChange; //Function to call when changed
} BlockSlider;

typedef struct
{//ScrollBar
    char* name;             //Slider Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width   //Note: drawn vertical if this is less than height
    int height;             //Height   
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int outercolor;          //outer color
    int innercolor;           //inner color 
    int options;            //options
    int val;                //value
    int size;               //size
    int range;              //range
    BlockOperation OnChange; //Function to call when changed
} BlockScrollBar;

typedef struct
{//Progress
    char* name;             //Slider Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width   
    int height;             //Height   
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int color;              //background color
    int progresscolor;      //progress color 
    int options;            //options
    int val;                //value
    int range;              //range
    BlockOperation OnClick; //Function to call when clicked
} BlockProgress;

typedef struct
{//Dial
    char* name;             //Dial Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width  //sets radius
    int height;             //Height //set to same as width
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int knobcolor;          //Knob color
    int markercolor;        //marker color
    int options;            //options
    int val;                //value, max is 65535
    int minval;             //min limit
    int maxval;             //max limit
    BlockOperation OnChange; //Function to call when changed
} BlockDial;

typedef struct
{//Clock
    char* name;             //Dial Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width  //sets radius
    int height;             //Height //set to same as width
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int backcolor;          //background color
    int ticcolor;           //tic color
    int options;            //options
    int h;                  //hours
    int m;                  //minutes
    int s;                  //seconds
    int ms;                 //milliseconds
} BlockClock;

typedef struct
{//Gauge
    char* name;             //Dial Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width  //sets radius
    int height;             //Height //set to same as width
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int color;          //dial color
    int linecolor;          //tic and needle color
    int options;            //options
    int major;              //#major ticks
    int minor;              //#minor ticks
    int val;                //value, max is 65535
    int range;              //max value
    BlockOperation OnClick; //Function to call when clicked
} BlockGauge;

typedef struct
{//Toggle
    char* name;             //Toggle Name
    int type;               //Object type 
    int top;                //Top
    int left;               //Left 
    int width;              //Width 
    int height;             //Height 
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int state;              //0 is off, -1 is on
    int ontextcolor;          //Text foreground color when on 
    int onbarcolor;           //Bar color when on 
    int onknobcolor;          //Knob color when on 
    int offtextcolor;          //Text foreground color when off
    int offbarcolor;           //Bar color when off
    int offknobcolor;          //Knob color when off
    int font;               //font#
    int fontoptions;        //font options
    char* pText;            //Toggle text
    BlockOperation OnClick; //Function to call when button clicked
} BlockToggle;

typedef struct
{//Text
    char* name;             //Text Name
    int type;               //Object type
    int top;                //Top 
    int left;               //Left 
    int width;              //Width     //This is automatically calculated at run time
    int height;             //Height    //This is automatically calculated at run time
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int color;              //Text foreground color
    int font;               //font#
    int fontoptions;        //font options
    char* pText;            //text
} BlockText;

typedef struct
{//Led
    char* name;             //Text Name
    int type;               //Object type
    int top;                //Top 
    int left;               //Left 
    int width;              //Width     //This is automatically calculated at run time
    int height;             //Height    //This is automatically calculated at run time
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int color;              //Text foreground color
    int font;               //font#
    int fontoptions;        //font options
    char* pText;            //text
    int oncolor;            //LED on Color
    int offcolor;           //LED off Color
    bool bOn;               //is LED on? true or false 
} BlockLed;

typedef struct
{//Keys
    char* name;             //Text Name
    int type;               //Object type
    int top;                //Top 
    int left;               //Left 
    int width;              //Width     //This is automatically calculated at run time based on "keywidth" below
    int height;             //Height    //Height of keys
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int color;              //Text foreground color
    int keycolorup;           //color of keys when up
    int keycolordown;           //color of keys when down
    int font;               //font#
    int fontoptions;        //font options
    int keywidth;           //width of keys
    char* pText;            //text
    BlockOperation OnClick;  //function to call when key clicked
} BlockKeys;

typedef struct
{//Number
    char* name;             //Text Name
    int type;               //Object type
    int top;                //Top 
    int left;               //Left 
    int width;              //Width     //normally unused
    int height;             //Height    //normally unused
    int data;               //user data
    int status;             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    int color;              //Text foreground color
    int font;               //font#
    int fontoptions;        //font options, including OPT_SIGNED to treat as signed
    int base;               //base, one of 2..36, set to 10 for decimal
    int n;                  //number
} BlockNumber;

typedef struct
{//Image - from an asset
    char* name;             //Object Name - filename for files to load from filesystem
    int type;
    int top;
    int left;
    int width;
    int height;
    int data;    
    int status;
    int handle;  //handle of this image
    BlockOperation OnClick;  //function to call when key clicked
} BlockImage;


//enum BlockColors {
//    Black = 0, Stratos, NavyBlue, NavyBlue2, DarkBlue, Blue, DeepFir, DeepTeal,
//    MidnightBlue, Smalt, InternationalKleinBlue, BlueRibbon, Camarone, FunGreen, BlueStone,
//    BahamaBlue, ScienceBlue, BlueRibbon2, JapaneseLaurel, FunGreen2, GreenHaze, PersianGreen,
//    PacificBlue, AzureRadiance, Green, Malachite, Jade, CaribbeanGreen, RobinsEggBlue,
//    Aqua, Green2, Green3, SpringGreen, SpringGreen2, BrightTurquoise, Cyan, Temptress,
//    Barossa, Christalle, PigmentIndigo, DarkBlue2, Blue2, Madras, MineShaft, MineShaft2,
//    Sapphire, GovernorBay, Blue3, Blue4, Killarney, Casal, Azure, Azure2, DodgerBlue, Limeade,
//    Apple, Apple2, Lochinvar, CuriousBlue, DodgerBlue2, Harlequin, Apple3, Emerald, Shamrock,
//    Turquoise, DodgerBlue3, Harlequin2, Harlequin3, ScreaminGreen, SpringGreen3, BrightTurquoise2,
//    Aqua2, Lonestar, TyrianPurple, Pompadour, Purple, Purple2, ElectricViolet, NutmegWoodFinish,
//    Buccaneer, Cosmic, RoyalPurple, PurpleHeart, ElectricViolet2, VerdunGreen, CostaDelSol, DoveGray, Kimberly,
//    BlueMarguerite, CornflowerBlue, Limeade2, Apple4, Highland, Patina, Danube, Malibu, Limeade3,
//    Atlantis, Mantis, Emerald2, Downy, Malibu2, BrightGreen, BrightGreen2, ScreaminGreen2,
//    ScreaminGreen3, Aquamarine, Aquamarine2, RedBerry, Paprika, FreshEggplant, Flirt, ElectricViolet3,
//    ElectricViolet4, Oregon, Stiletto, Rouge, Plum, PurpleHeart2, ElectricViolet5, ChelseaGem, PottersClay, CopperRose,
//    Strikemaster, Amethyst, Heliotrope, Olive, Sycamore, Avocado, Avocado2, BlueBell, Melrose,
//    Pistachio, Atlantis2, WildWillow, DeYork, Sinbad, Anakiwa, Chartreuse, GreenYellow,
//    ScreaminGreen4, MintGreen, Aquamarine3, Anakiwa2, GuardsmanRed, Monza, Lipstick,
//    HollywoodCerise, PurplePizzazz, ElectricViolet6, Grenadier, Grenadier2, Hibiscus,
//    MediumRedViolet, FuchsiaPink, Heliotrope2, Tenn, Tuscany, ChestnutRose, ChestnutRose2,
//    FuchsiaPink2, Heliotrope3, BuddhaGold, HokeyPokey, AntiqueBrass, Eunry, Lilac, Mauve,
//    RioGrande, EarlsGreen, Laser, PineGlade, PineGlade2, Periwinkle, ElectricLime, GreenYellow2,
//    Canary, Reef, SnowyMint, Onahau, Red, TorchRed, Rose, HollywoodCerise2, HollywoodCerise3,
//    Magenta, Scarlet, RedOrange, RadicalRed, WildStrawberry, RazzleDazzleRose, RazzleDazzleRose2,
//    BlazeOrange, OutrageousOrange, Bittersweet, HotPink, HotPink2, HotPink3, OrangePeel,
//    NeonCarrot, AtomicTangerine, MonaLisa, CarnationPink, LavenderRose, Supernova, Sunglow,
//    GoldenTainoi, PeachOrange, PeachOrange2, PinkLace, Yellow, GoldenFizz, LaserLemon,
//    PaleCanary, Cream, White, CodGray, MineShaft3, Tundora, Boulder, Gray, SilverChalice,
//    Silver, Alto, Gallery
//};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Begining of Block Interface Code


//GarryJ's one cog USB Keyboard/Mouse driver
//struct __using("KbM_Interface_rja2f.spin2") kbm; //RJA:  Visual Studio will show an error here, but it's OK
struct __using("1CogKbM_rja3a.spin2") kbm; //RJA:  Visual Studio will show an error here, but it's OK

void InitBlocks(BlockBlock* p)
{
    SaveContext();
    LOAD_ASSETS();

    //RJA:  Cursor is now an asset
    ////load up cursor into handle #0
    ////Load_RAW(0xF0000, (char*)"arrow01.raw");
    ////Configure_Bitmap_Handle(0,0xF0000,0,0,0,16,24,16*2,ARGB4); //    //Cmd_SetBitmap(0xF0000, ARGB4, 16, 24);
    
    //start USB mouse
    StartMouse();  
    InitBlock(p);
    //set current panel to the one provided
    pCurrentBlock = p;
}

void BlockLoop()
{
    WaitMouseDown();
    HandleMouseDown();
    WaitMouseUp();
    HandleMouseUp();
}

void StartMouse()
{//Start up the USB mouse
    printf("Starting Mouse...\n");
    MouseStatus.MaxX = 1280 - 1;
    MouseStatus.MaxY = 720 - 1;
    MouseStatus.x = 100;
    MouseStatus.y = 100;
    kbm.Start(USB_BASE_PIN, USB_ENABLE_PIN, USB_DM_PIN, USB_ERR_LED_PIN, &MouseStatus);  //(base_pin, dm_pin, err_led_pin, pMouseData) : cog
}



bool bLeftButtonDown = false, bRightButtonDown = false;
bool bMouseMoved;
bool bNeedSync;



/* define a struct, and a pointer-to-struct */
BlockObject* pMouseOverObject;
BlockBlock* pMouseOverParent;  //parent of mouseoverobject()
BlockObject* pClickedOnObject;
BlockBlock* pClickedOnParent;  //parent of object clicked on 
BlockBlock* pCurrentBlock;
xy ClickPoint;

typedef struct
{
    int x;
    int y;
    int MaxX;
    int MaxY;
    int buttons;
} MouseInfo;

MouseInfo MouseStatus = { 0,0,0,0 };
MouseInfo OldMouseStatus = { 0,0,0,0 };

int DebugLong;

bool bInvisible, bDisabled;
int oLeft, oTop; //absolute position

int nKey; //key# over
int nKeyClicked;  //key# clicked on 

void GetObject(BlockObject* p)
{//get absolute object position on screen (and some other things)
    bInvisible = p->status & 0b01;//Lowest bit of status is invisible flag
    bDisabled = p->status & 0b10;//Second lowest bit is disabled flag
    oTop = p->top + pCurrentBlock->top;
    oLeft = p->left + pCurrentBlock->left;
}

void SetVisible(BlockObject* p, bool bVisible)
{
    if (bVisible)
        p->status |= 1;
    else
        p->status &= (!1);
}

void EnableObject(BlockObject* p, bool bEnabled)
{
    if (bEnabled)
    {//clear the bDisabled bit
        p->status = p->status & (~0b10);//Second lowest bit is disabled flag
    }
    else
    {//set the bDisabled bit
        p->status = p->status | 0b10;//Second lowest bit is disabled flag
    }
}





void DrawObject(BlockObject* pFO)
{//Draw or redraw given object
    int type = pFO->type;

    //printf("type of object = %d\n", pFO->type);
    switch (type)
    {
    case BlockType:  //draw sub-panel
        DrawBlock((BlockBlock*)pFO);
        break;
    case ButtonType:
        DrawButton((BlockButton*)pFO);
        break;
    case ToggleType:
        DrawToggle((BlockToggle*)pFO);
        break;
    case SliderType:
        DrawSlider((BlockSlider*)pFO);
        break;
    case TextType:
        DrawBlockText((BlockText*)pFO);
        break;
    case DialType:
        DrawDial((BlockDial*)pFO);
        break;
    case GaugeType:
        DrawGauge((BlockGauge*)pFO);
        break;
    case ProgressType:
        DrawProgress((BlockProgress*)pFO);
        break;
    case ScrollBarType:
        DrawScrollBar((BlockScrollBar*)pFO);
        break;
    case NumberType:
        DrawNumber((BlockNumber*)pFO);
        break;
    case KeysType:
        DrawKeys((BlockKeys*)pFO);
        break;
    case LedType:
        DrawLed((BlockLed*)pFO);
        break;
    case ClockType:
        DrawClock((BlockClock*)pFO);
        break;
    case ImageType:
        DrawImage((BlockImage*)pFO);
        break;
    case RepeatType:
        DrawRepeat((BlockRepeat*)pFO);
        break;
    default:
        break;
    }
}

void DrawBlockText(BlockText* p)  //Note:  DrawText() already defined in Antares
{//use the function from Antares
    DrawText(p->left, p->top, p->font, p->fontoptions, p->pText, p->color);
}

void DrawLed(BlockLed* p)  //Note:  DrawText() already defined in Antares
{//use the function from Antares
    //draw LED
    int h2 = p->height / 2;
    COLORREF c = p->bOn ? p->oncolor : p->offcolor;
    DrawFilledCircle(p->left + h2, p->top + h2, Black, h2);
    DrawFilledCircle(p->left + h2, p->top + h2, c, h2-3);
    //draw Text
    int xoff = p->height + p->height / 5;
    DrawText(p->left+xoff, p->top, p->font, p->fontoptions, p->pText, p->color);
}

void DrawNumber(BlockNumber* p)
{//use the function from Antares
    Cmd_SetBase(p->base);
    Cmd_Color_RGB(p->color);
    Cmd_Number(p->left, p->top, p->font, p->fontoptions, p->n);
}



void DrawButton(BlockButton* p)
{
    Cmd_FGcolor(p->color);
    Cmd_Color_RGB(p->textcolor);
    if (p->bMouseDownOn==false)  //draw regular
        Cmd_Button(p->left, p->top, p->width, p->height, p->font, p->fontoptions, p->pText);
    else //draw flat
        Cmd_Button(p->left, p->top, p->width, p->height, p->font, OPT_FLAT, p->pText);
}

void DrawDial(BlockDial* p)
{
    Cmd_FGcolor(p->knobcolor);
    Cmd_Color_RGB(p->markercolor);
    //calculate center of dial
    int x, y,r;
    r= p->width / 2;
    x = p->left + r;
    y = p->top + r;
    //draw dial
    Cmd_Dial(x,y , r, p->options,p->val);    
}

void DrawClock(BlockClock* p)
{
    Cmd_BGcolor(p->backcolor);
    Cmd_Color_RGB(p->ticcolor);
    //calculate center of dial
    int x, y, r;
    r = p->width / 2;
    x = p->left + r;
    y = p->top + r;
    //draw clock
    cmd_clock(x, y, r, p->options, p->h, p->m, p->s, p->ms);
}

void DrawKeys(BlockKeys* p)
{
    Cmd_FGcolor(p->keycolorup);
    Cmd_BGcolor(p->keycolordown);
    Cmd_Color_RGB(p->color);
    cmd_keys(p->left, p->top, p->width,p->height,p->font, p->fontoptions, p->pText);
}

void DrawGauge(BlockGauge* p)
{
    Cmd_BGcolor(p->color);
    Cmd_Color_RGB(p->linecolor);
    //calculate center of dial
    int x, y, r;
    r = p->width / 2;
    x = p->left + r;
    y = p->top + r;
    //draw Gauge
    Cmd_Gauge(x, y, r, p->options,p->major,p->minor, p->val,p->range);
}

void DrawToggle(BlockToggle* p)
{
    if (p->state==false)
    {//draw in off colors
        Cmd_FGcolor(p->offknobcolor);
        Cmd_Color_RGB(p->offtextcolor);
        Cmd_BGcolor(p->offbarcolor);
    }
    else
    {//draw in on colors
        Cmd_FGcolor(p->onknobcolor);
        Cmd_Color_RGB(p->ontextcolor);
        Cmd_BGcolor(p->onbarcolor);
    }
    cmd_toggle(p->left, p->top,  p->width, p->font, p->fontoptions, p->state, p->pText);
}

void DrawSlider(BlockSlider* p)
{
    Cmd_FGcolor(p->knobcolor);
    Cmd_Color_RGB(p->leftcolor);
    Cmd_BGcolor(p->rightcolor);
    if (p->width > p->height)
    {//horizontal slider
        cmd_slider(p->left, p->top+ p->height/4, p->width, p->height/2, p->options, p->val, p->range);
    }
    else
    {//vertical slider
        cmd_slider(p->left + p->width / 4, p->top , p->width/2, p->height, p->options, p->val, p->range);
    }
    
}

void DrawProgress(BlockProgress* p)
{
    Cmd_BGcolor(p->color);
    Cmd_Color_RGB(p->progresscolor);
    cmd_progress(p->left, p->top , p->width, p->height, p->options, p->val, p->range);
}

void DrawScrollBar(BlockScrollBar* p)
{
    Cmd_BGcolor(p->innercolor);
    Cmd_FGcolor(p->outercolor);
    cmd_scrollbar(p->left, p->top, p->width, p->height, p->options, p->val, p->size, p->range);
}

void DrawImage(BlockImage* p)
{
    ColorRGB24(0xFFFFFF);
    BitmapHandle(p->handle);
    Begin(BITMAPS);
    Vertex2f(p->left, p->top);

}

void DrawRepeat(BlockRepeat* p)
{
    ColorRGB24(0xFFFFFF);
    if ((bLeftButtonDown)&&(pMouseOverObject==(BlockObject *)p))
        BitmapHandle(p->BmpHandleDown);
    else
        BitmapHandle(p->BmpHandleUp);
    Begin(BITMAPS);
    Vertex2f(p->left, p->top);

}

void InitBlock(BlockBlock* pBlock)
{//Initialize a panel (do things like set size of text)
    if (pBlock == NULL)
        return;
    BlockObjectList* pFOL = pBlock->pObjectList;
    //Init all objects on form
    for (int i = 0; i < MaxBlockObjects; i++)
    {
        BlockObject* pFO = pFOL->p[i];
        if (pFO == 0)
        {//end of list
            break;
        }
        InitObject(pFO);
    }
}

void InitObject(BlockObject* p)
{//Initialize an object
    //Need to calculate and set height and width of text
    if (p->type == TextType)
    {//configure width and height based on font
        BlockText* pt = (BlockText*)p;
        pt->height = GetFontHeight(pt->font);
        pt->width = GetFontTextWidth(pt->font, pt->pText);
        printf("Text %s: height=%d, width=%d\n", pt->pText, pt->height, pt->width);
    }
    else if (p->type == LedType)
    {//configure width and height based on font
        BlockText* pt = (BlockText*)p;
        pt->height = GetFontHeight(pt->font);
        pt->width = GetFontTextWidth(pt->font, pt->pText);
        //add room for LED
        pt->width += pt->height + pt->height / 5; //plus some seperation from text
        printf("Text %s: height=%d, width=%d\n", pt->pText, pt->height, pt->width);
    }
    else if (p->type == KeysType)
    {//configure width and height based on font and #keys
        BlockKeys* pk = (BlockKeys*)p;
        //Need to account for 3 pixels between keys
        pk->width = pk->keywidth*strlen(pk->pText) + ((strlen(pk->pText) - 1) * 3);
        printf("Text %s: height=%d, width=%d\n", pk->pText, pk->height, pk->width);
    }
    else if (p->type == ImageType)
    {//load image and configure handle
        //now an asset..
        //BlockImage* pi = (BlockImage*)p;
        //if (pi->source == 1)
        //{//need to load image from filesystem
        //    BitmapHandle(pi->handle);  //setting handle so Load_JPG will configure this handle for us
        //    Load_JPG(pi->address, 0, pi->name);
        //    printf("Bitmap handle=%d, add=%d, width=%d, height=%d\n", pi->handle, pi->address, pi->width, pi->height);
        //}
        //printf("Image %s: type=%d, height=%d, width=%d\n", pi->name, pi->type, pi->height, pi->width);
    }
    else if (p->type == BlockType)
    {//recursively init subpanels
        InitBlock((BlockBlock*)p);
    }
}

void DrawBlock(BlockBlock* pBlock)
{//Draw a form
    //First draw the form title border and background
    RestoreContext();
    FormatVertex(VERTEX_FORMAT_ONE);  //change Vertex2f scale to 1:1
    
    if (pBlock->pParent!=NULL)
    {//This is a sub panel
        //translate and draw area of sub panel using a button 
        //printf("Top=%d, Left=%d\n", pBlock->top, pBlock->left);
        //
        Cmd_FGcolor(pBlock->fillcolor);
        TranslateXY(pBlock->left, pBlock->top);
        Cmd_Button(0, 0, pBlock->width, pBlock->height, 18, OPT_FLAT," ");  //draw panel as button with no text     
        
    }
    else
    {//This is the main panel, just clear screen
        ClearScreen(pBlock->fillcolor);  //background color
    }
    //draw title
    Cmd_Color_RGB(pBlock->textcolor);
    Cmd_Text(pBlock->titleLeft, pBlock->titleTop, pBlock->font, pBlock->titleOptions, pBlock->pTitleText);
    //Cmd_Button(0, 0, 100, 100, 18, 0, " ");

    BlockObjectList* pFOL = pBlock->pObjectList;
    //Then, draw all the objects on the form
    for (int i = 0; i < MaxBlockObjects; i++)
    {
        BlockObject* pFO = pFOL->p[i];
        if (pFO == 0)
        {//end of list
            break;
        }
        DrawObject(pFO);
    }
    //printf("End of Block object list.\n");
}

void DrawCursor()
{//draw mouse on top of panels
    TranslateXY(0, 0);  //undo translate
    Cmd_Color_RGB(White);  //color is affected by earlier calls to Cmd_Color_RGB if not set to white
    //Cmd_SetBitmap(0xF0000, ARGB4, 16, 24);
    BitmapHandle(0);  //cursor has handle #0
    Begin(BITMAPS);
    Vertex2f(MouseStatus.x, MouseStatus.y);
    //printf("Mouse at %d, %d\n", MouseStatus.x, MouseStatus.y);
}

void CheckMouse()
{
    if ((MouseStatus.x != OldMouseStatus.x) || (MouseStatus.y != OldMouseStatus.y))
    {
        bMouseMoved = true;
        //Original didn't do this, but maybe we should?
        memcpy(&OldMouseStatus, &MouseStatus, sizeof(MouseInfo));
    }
    else //adding this too
        bMouseMoved = false;

    int b = MouseStatus.buttons;

    if (b & 1)
        bLeftButtonDown = true;
    else
        bLeftButtonDown = false;

    if (b & 0b10)
        bRightButtonDown = true;
    else
        bRightButtonDown = false;


}

BlockObject* GetMouseOverObject(BlockBlock* pBlock)
{//See if mouse is over any object and return pointer to that object or NULL
    BlockObjectList* pFOL = pBlock->pObjectList;
    int x, y;
    BlockObject* p=NULL;


    for (int i = 0; i < MaxBlockObjects; i++)
    {
        p = pFOL->p[i];
        if (p == 0)
        {//end of list
            return NULL;
        }
        if (p->type == BlockType)
        {//recursively look for object
            BlockObject* p2= GetMouseOverObject((BlockBlock*)p);
            if (p2 != NULL)
                return p2;
            continue;
        }

        int oLeft = p->left + pBlock->left;
        int oTop = p->top + pBlock->top;

        bool bInvisible = p->status & 0b01;//Lowest bit of status is invisible flag
        if (bInvisible)
            continue;//skip if invisible
        x = MouseStatus.x; 
        y = MouseStatus.y;
        //printf("type=%d mouse=%d,%d  object=%d,%d\n", p->type,x, y, oTop, oLeft);
        if (y < oTop)
            continue; //above object
        if (y > (oTop + p->height - 1))
            continue;//below object
        if (x < oLeft)
            continue;//left of object
        if (x > (oLeft + p->width - 1))
            continue; //right of object
        //If we are still here, we must be over this object
        //printf("Over type %d\n", p->type);

        //Special handling if this is a Keys Type
        if (p->type == KeysType)
        {//want to figure out what key # this is 
            int dx = x - oLeft;
            int kw = ((BlockKeys*)p)->keywidth + 3;
            nKey = dx / kw;
        }

        pMouseOverParent = pBlock;//save parent pointer for slider
        return p;
    }



}



void IdleProcess()
{//things to do while waiting for user input
    DrawBlock(pCurrentBlock);  //draw panel first

    //let app draw on top of panel if need by
    if (pCurrentBlock->OnIdle != NULL)
        pCurrentBlock->OnIdle(NULL);  //do the idle process

    DrawCursor();  //draw cursor last
    swap(); //Image should now be showing
}



void WaitMouseDown()
{//wait for user to push mouse down
    BlockObject* pOldObject = NULL;
    bMouseMoved = false;
    while (true)
    {
        CheckMouse();
        if (bLeftButtonDown)
        {//button is down, so done waiting
            pClickedOnObject= GetMouseOverObject(pCurrentBlock);
            pClickedOnParent = pMouseOverParent;
            if (pClickedOnObject == NULL)
                printf("NULL\n");
            else
                printf("Clicked on %s\n", pClickedOnObject->name);
            //special handling for keys type
            if (pClickedOnObject->type == KeysType)
            {//note the key that was clicked on
                nKeyClicked = nKey;
            }
            ClickPoint.x = MouseStatus.x;
            ClickPoint.y = MouseStatus.y;
            return;
           
        }

        if (bMouseMoved)
        {
            pMouseOverObject = GetMouseOverObject(pCurrentBlock);
            if (pOldObject != NULL)
            {
                if (pOldObject != pMouseOverObject) //Over something else?  Need to redraw if old was a button
                {
                    ////printf("Now over object %s\n", pMouseOverObject->name);
                    //if (pOldObject->type == ButtonType)
                    //{
                    //    ((BlockButton*)pMouseOverObject)->bMouseDownOn = false;
                    //}
                }
            }
            if (pMouseOverObject != NULL)
            {//Over an object                
                ////printf("Over object %s\n", pMouseOverObject->name);
                //if (pMouseOverObject->type == ButtonType)
                //{
                //    ((BlockButton*)pMouseOverObject)->bMouseDownOn = true;
                //}
            }
        }
        IdleProcess();//do background things            
    }
}



int GetAngle(int x, int y)
{//turn x,y into an angle
    int a;
    int a360 = 65535;
    __asm{
        qvector x, y
        //getqx   l
        getqy   a
        qmul    a, a360
        getqy   a
    }
    //printf("x=%d, y=%d, a=%d\n", x, y, a);
    return a;

}


void WaitMouseUp()
{//wait for user to let mouse up
    BlockObject* p;
    while (true)
    {
        CheckMouse();
        if (true)//bMouseMoved)
        {
            p = GetMouseOverObject(pCurrentBlock);

            //printf("Mouse over %s\n", p->name);
            if ((p != pClickedOnObject) && (pClickedOnObject != NULL))
            {//mouse is still down, but over something else
                if (pClickedOnObject->type == ButtonType)
                {//return button to 3D look to show back up
                    ((BlockButton*)pClickedOnObject)->bMouseDownOn = 0;
                        
                }
            }
            if ((p == pClickedOnObject) && (pClickedOnObject != NULL))
            {//mouse is still down on same thing clicked on 
                if (pClickedOnObject->type == ButtonType)
                {//show button as 2D to show down
                    ((BlockButton*)pClickedOnObject)->bMouseDownOn = -1;
                }
                if (pClickedOnObject->type == KeysType)
                {//show selected key as 2D to show down
                    ((BlockKeys*)pClickedOnObject)->fontoptions &= (~0x3F);
                    ((BlockKeys*)pClickedOnObject)->fontoptions |= ((BlockKeys*)pClickedOnObject)->pText[nKeyClicked]; //need to fix this
                }
            }

            if ((pClickedOnObject->type == RepeatType))
            {//drag repeat by mouse position
                pClickedOnObject->top = pClickedOnObject->top + MouseStatus.y - ClickPoint.y;
                pClickedOnObject->left = pClickedOnObject->left + MouseStatus.x - ClickPoint.x;
                ClickPoint.y = MouseStatus.y;
                ClickPoint.x = MouseStatus.x;
            }


            if ((pClickedOnObject->type == SliderType))
            {//drag slider by mouse position
                BlockSlider* pS = (BlockSlider*)pClickedOnObject;
                if (pS->width > pS->height)
                {//horizontal slider
                    int x = MouseStatus.x - pClickedOnParent->left;
                    pS->val = (pS->range * (x - pS->left)) / pS->width;
                }
                else
                {//vertical slider
                    int y = MouseStatus.y - pClickedOnParent->top;
                    pS->val = (pS->range * (y - pS->top)) / pS->height;
                }
                //enforce limits
                if (pS->val < 0)
                    pS->val = 0;
                if (pS->val > pS->range)
                    pS->val = pS->range;
            }

            if ((pClickedOnObject->type == ScrollBarType))
            {//drag scrollbar by mouse position
                BlockScrollBar* pS = (BlockScrollBar*)pClickedOnObject;
                if (pS->width > pS->height)
                {//horizontal slider
                    int x = MouseStatus.x - pClickedOnParent->left;
                    pS->val = (pS->range * (x - pS->left)) / pS->width;
                }
                else
                {//vertical slider
                    int y = MouseStatus.y - pClickedOnParent->top;
                    pS->val = (pS->range * (y - pS->top)) / pS->height;
                }
                //enforce limits
                if (pS->val < 0)
                    pS->val = 0;
                if (pS->val > (pS->range-pS->size))
                    pS->val = (pS->range - pS->size);
            }


            if ((pClickedOnObject->type == DialType))
            {//drag dial by mouse position
                BlockDial* pD = (BlockDial*)pClickedOnObject;
                int r = pD->width / 2;
                int x = MouseStatus.x - (pClickedOnParent->left+r+pD->left);
                int y = MouseStatus.y - (pClickedOnParent->top+r+pD->top);
                pD->val = GetAngle(y,-x);
                //enforce limits
                if (pD->val < pD->minval)
                    pD->val = pD->minval;
                if (pD->val > pD->maxval)
                    pD->val = pD->maxval;
            }

        }
        if (!bLeftButtonDown)
            return;

        IdleProcess();
    }

}

void HandleMouseUpToggle(BlockToggle* p)
{
    p->state = p->state ? 0 : -1;
    if ((p->OnClick) != NULL)
        p->OnClick((BlockObject*)p); //do whatever this button is supposed to do 

}

void HandleMouseUpButton(BlockButton* p)
{
    if ((p->OnClick) != NULL)
        p->OnClick((BlockObject*)p); //do whatever this button is supposed to do 
    //return button to 3D look to show back up
    p->bMouseDownOn = 0;

}

void HandleMouseUpText(BlockText* p)
{//not implementing anything yet

}

void HandleMouseUpGauge(BlockGauge* p)
{//not implementing anything yet

}

void HandleMouseUpScrollBar(BlockScrollBar* p)
{//not implementing anything yet

}

void HandleMouseUpSlider(BlockSlider* pS)
{//Set slider by mouse position
    if (pS->width > pS->height)
    {//horizontal slider
        int x = MouseStatus.x - pClickedOnParent->left;
        pS->val = (pS->range * (x - pS->left)) / pS->width;
    }
    else
    {//vertical slider
        int y = MouseStatus.y - pClickedOnParent->top;
        pS->val = (pS->range * (y - pS->top)) / pS->height;
    }

}

void HandleMouseUpDial(BlockDial* pD)
{//set dial by mouse position
    int r = pD->width / 2;
    int x = MouseStatus.x - (pClickedOnParent->left + r + pD->left);
    int y = MouseStatus.y - (pClickedOnParent->top + r + pD->top);
    pD->val = GetAngle(y, -x);
    //enforce limits
    if (pD->val < pD->minval)
        pD->val = pD->minval;
    if (pD->val > pD->maxval)
        pD->val = pD->maxval;

}
void HandleMouseUpKeys(BlockKeys* pD)
{//show keys back as 3d
    pD->fontoptions &= (~0x3F);
}

void DeselectOptionGroup(int group)
{//Unselect all options in this group

}


void HandleMouseDown()
{//Left button pressed, respond accordingly to object it is over
    //BlockObject* p;
    //pMouseOverObject = GetMouseOverObject(pCurrentBlock);
    //if (p == NULL)
    //    return;  //if not over an object just return

}


void HandleMouseUp()
{//Left button released, respond accordingly to object it is over
    BlockObject* p;
    p = GetMouseOverObject(pCurrentBlock);
    if (p != pClickedOnObject)
        return; //do nothing else if not released over the same object
    if (p == NULL)
        return;  //if not over an object just return

    printf("Clicked on %s\n", p->name);


    switch (p->type)
    {
    case ButtonType:
        HandleMouseUpButton((BlockButton*)p);
        break;
    case ToggleType:
        HandleMouseUpToggle((BlockToggle*)p);
        break;
    case SliderType:
        HandleMouseUpSlider((BlockSlider*)p);
        break;
    case TextType:
        HandleMouseUpText((BlockText*)p);
        break;
    case DialType:
        HandleMouseUpDial((BlockDial*)p);
        break;
    case GaugeType:
        HandleMouseUpGauge((BlockGauge*)p);
        break;
    case ScrollBarType:
        HandleMouseUpScrollBar((BlockScrollBar*)p);
        break;
    case KeysType:
        HandleMouseUpKeys((BlockKeys*)p);
        break;
    default:  //Maybe form has special code to handle clicks on objects
        printf("type=%d, top=%d, left=%d",p->type,p->top, p->left);
        if (pCurrentBlock->OnClick!=NULL)
            pCurrentBlock->OnClick(p);
        break;
    }

}


#endif //_BLOCKS_H_
