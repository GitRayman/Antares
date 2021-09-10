////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Definitions


#ifndef _PANELS_H_
#define _PANELS_H_

#define MaxPanelText (1920/16) //make it width of screen in tiles
#define MaxPanelObjects 100

#include "Colors.h"

enum PanelObjectTypes { PanelType = 0, ButtonType = 1, TextType, ToggleType, SliderType, ScrollBarType, GaugeType, LedType, KeysType,
                       GraphicsAreaType, GraphicsObjectType, ProgressType, DialType, NumberType, ClockType, ImageType };

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
} PanelObject;

typedef struct {
    PanelObject* p[MaxPanelObjects];
} PanelObjectList;

typedef   void (*PanelOperation)(PanelObject* pObject);

typedef struct
{//Panel 
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
    PanelObject* pParent;    //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a PanelPanel*
    PanelObjectList* pObjectList;   //pointer to NULL terminated list of form objects
    PanelOperation OnPanelOpen;  //Function to call when opening this panel
    PanelOperation OnPanelClose;  //Function to call when closing this panel
    PanelOperation OnIdle;  //Function to call when idle
    PanelOperation OnClick;  //function to call when clicked on something not handled elsewhere
} PanelPanel;


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
    PanelOperation OnClick; //Function to call when button clicked
    bool bMouseDownOn;       //Is the mouse down on this button?
} PanelButton;

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
    PanelOperation OnChange; //Function to call when changed
} PanelSlider;

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
    PanelOperation OnChange; //Function to call when changed
} PanelScrollBar;

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
    PanelOperation OnClick; //Function to call when clicked
} PanelProgress;

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
    PanelOperation OnChange; //Function to call when changed
} PanelDial;

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
} PanelClock;

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
    PanelOperation OnClick; //Function to call when clicked
} PanelGauge;

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
    PanelOperation OnClick; //Function to call when button clicked
} PanelToggle;

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
} PanelText;

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
} PanelLed;

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
    PanelOperation OnClick;  //function to call when key clicked
} PanelKeys;

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
} PanelNumber;

typedef struct
{//Image -  a RGB565 image in RAM_G - handle of the bitmap (source/layout/size) must be configured before use
    char* name;             //Object Name - filename for files to load from filesystem
    int type;
    int top;
    int left;
    int width;
    int height;
    int data;    //pointer to image data for embedded in P2 images or images in flash
    int status;
    int source;  //one of {0=already in RAM_G, 1=load from filesystem, 2=load from flash, 3=load from P2 RAM}
    int address;  //address of image in RAM_G
    int handle;  //handle of this image
    PanelOperation OnClick;  //function to call when key clicked
} PanelImage;


//enum PanelColors {
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
//Begining of Panel Interface Code


//GarryJ's one cog USB Keyboard/Mouse driver
struct __using("1CogKbM_rja3a.spin2") kbm; //RJA:  Visual Studio will show an error here, but it's OK

void InitPanels(PanelPanel* p)
{
    SaveContext();
    //load up cursor into handle #0
    Load_RAW(0xF0000, (char*)"arrow01.raw"); 
    Configure_Bitmap_Handle(0,0xF0000,0,0,0,16,24,16*2,ARGB4); //    //Cmd_SetBitmap(0xF0000, ARGB4, 16, 24);
    //start USB mouse
    StartMouse();  
    InitPanel(p);
    //set current panel to the one provided
    pCurrentPanel = p;
}

void PanelLoop()
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
PanelObject* pMouseOverObject;
PanelPanel* pMouseOverParent;  //parent of mouseoverobject()
PanelObject* pClickedOnObject;
PanelPanel* pClickedOnParent;  //parent of object clicked on 
PanelPanel* pCurrentPanel;

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

void GetObject(PanelObject* p)
{//get absolute object position on screen (and some other things)
    bInvisible = p->status & 0b01;//Lowest bit of status is invisible flag
    bDisabled = p->status & 0b10;//Second lowest bit is disabled flag
    oTop = p->top + pCurrentPanel->top;
    oLeft = p->left + pCurrentPanel->left;
}

void SetVisible(PanelObject* p, bool bVisible)
{
    if (bVisible)
        p->status |= 1;
    else
        p->status &= (!1);
}

void EnableObject(PanelObject* p, bool bEnabled)
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





void DrawObject(PanelObject* pFO)
{//Draw or redraw given object
    int type = pFO->type;

    //printf("type of object = %d\n", pFO->type);
    switch (type)
    {
    case PanelType:  //draw sub-panel
        DrawPanel((PanelPanel*)pFO);
        break;
    case ButtonType:
        DrawButton((PanelButton*)pFO);
        break;
    case ToggleType:
        DrawToggle((PanelToggle*)pFO);
        break;
    case SliderType:
        DrawSlider((PanelSlider*)pFO);
        break;
    case TextType:
        DrawPanelText((PanelText*)pFO);
        break;
    case DialType:
        DrawDial((PanelDial*)pFO);
        break;
    case GaugeType:
        DrawGauge((PanelGauge*)pFO);
        break;
    case ProgressType:
        DrawProgress((PanelProgress*)pFO);
        break;
    case ScrollBarType:
        DrawScrollBar((PanelScrollBar*)pFO);
        break;
    case NumberType:
        DrawNumber((PanelNumber*)pFO);
        break;
    case KeysType:
        DrawKeys((PanelKeys*)pFO);
        break;
    case LedType:
        DrawLed((PanelLed*)pFO);
        break;
    case ClockType:
        DrawClock((PanelClock*)pFO);
        break;
    case ImageType:
        DrawImage((PanelImage*)pFO);
        break;
    default:
        break;
    }
}

void DrawPanelText(PanelText* p)  //Note:  DrawText() already defined in Antares
{//use the function from Antares
    DrawText(p->left, p->top, p->font, p->fontoptions, p->pText, p->color);
}

void DrawLed(PanelLed* p)  //Note:  DrawText() already defined in Antares
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

void DrawNumber(PanelNumber* p)
{//use the function from Antares
    Cmd_SetBase(p->base);
    Cmd_Color_RGB(p->color);
    Cmd_Number(p->left, p->top, p->font, p->fontoptions, p->n);
}



void DrawButton(PanelButton* p)
{
    Cmd_FGcolor(p->color);
    Cmd_Color_RGB(p->textcolor);
    if (p->bMouseDownOn==false)  //draw regular
        Cmd_Button(p->left, p->top, p->width, p->height, p->font, p->fontoptions, p->pText);
    else //draw flat
        Cmd_Button(p->left, p->top, p->width, p->height, p->font, OPT_FLAT, p->pText);
}

void DrawDial(PanelDial* p)
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

void DrawClock(PanelClock* p)
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

void DrawKeys(PanelKeys* p)
{
    Cmd_FGcolor(p->keycolorup);
    Cmd_BGcolor(p->keycolordown);
    Cmd_Color_RGB(p->color);
    cmd_keys(p->left, p->top, p->width,p->height,p->font, p->fontoptions, p->pText);
}

void DrawGauge(PanelGauge* p)
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

void DrawToggle(PanelToggle* p)
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

void DrawSlider(PanelSlider* p)
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

void DrawProgress(PanelProgress* p)
{
    Cmd_BGcolor(p->color);
    Cmd_Color_RGB(p->progresscolor);
    cmd_progress(p->left, p->top , p->width, p->height, p->options, p->val, p->range);
}

void DrawScrollBar(PanelScrollBar* p)
{
    Cmd_BGcolor(p->innercolor);
    Cmd_FGcolor(p->outercolor);
    cmd_scrollbar(p->left, p->top, p->width, p->height, p->options, p->val, p->size, p->range);
}

void DrawImage(PanelImage* p)
{
    ColorRGB24(0xFFFFFF);
    BitmapHandle(p->handle);
    Begin(BITMAPS);
    Vertex2f(p->left, p->top);

}

void InitPanel(PanelPanel* pPanel)
{//Initialize a panel (do things like set size of text)
    if (pPanel == NULL)
        return;
    PanelObjectList* pFOL = pPanel->pObjectList;
    //Init all objects on form
    for (int i = 0; i < MaxPanelObjects; i++)
    {
        PanelObject* pFO = pFOL->p[i];
        if (pFO == 0)
        {//end of list
            break;
        }
        InitObject(pFO);
    }
}

void InitObject(PanelObject* p)
{//Initialize an object
    //Need to calculate and set height and width of text
    if (p->type == TextType)
    {//configure width and height based on font
        PanelText* pt = (PanelText*)p;
        pt->height = GetFontHeight(pt->font);
        pt->width = GetFontTextWidth(pt->font, pt->pText);
        printf("Text %s: height=%d, width=%d\n", pt->pText, pt->height, pt->width);
    }
    else if (p->type == LedType)
    {//configure width and height based on font
        PanelText* pt = (PanelText*)p;
        pt->height = GetFontHeight(pt->font);
        pt->width = GetFontTextWidth(pt->font, pt->pText);
        //add room for LED
        pt->width += pt->height + pt->height / 5; //plus some seperation from text
        printf("Text %s: height=%d, width=%d\n", pt->pText, pt->height, pt->width);
    }
    else if (p->type == KeysType)
    {//configure width and height based on font and #keys
        PanelKeys* pk = (PanelKeys*)p;
        //Need to account for 3 pixels between keys
        pk->width = pk->keywidth*strlen(pk->pText) + ((strlen(pk->pText) - 1) * 3);
        printf("Text %s: height=%d, width=%d\n", pk->pText, pk->height, pk->width);
    }
    else if (p->type == ImageType)
    {//load image and configure handle
        PanelImage* pi = (PanelImage*)p;
        if (pi->source == 1)
        {//need to load image from filesystem
            BitmapHandle(pi->handle);  //setting handle so Load_JPG will configure this handle for us
            Load_JPG(pi->address, 0, pi->name);
            printf("Bitmap handle=%d, add=%d, width=%d, height=%d\n", pi->handle, pi->address, pi->width, pi->height);
        }
        printf("Image %s: type=%d, height=%d, width=%d\n", pi->name, pi->type, pi->height, pi->width);
    }
    else if (p->type == PanelType)
    {//recursively init subpanels
        InitPanel((PanelPanel*)p);
    }
}

void DrawPanel(PanelPanel* pPanel)
{//Draw a form
    //First draw the form title border and background
    RestoreContext();
    FormatVertex(VERTEX_FORMAT_ONE);  //change Vertex2f scale to 1:1
    
    if (pPanel->pParent!=NULL)
    {//This is a sub panel
        //translate and draw area of sub panel using a button 
        //printf("Top=%d, Left=%d\n", pPanel->top, pPanel->left);
        //
        Cmd_FGcolor(pPanel->fillcolor);
        TranslateXY(pPanel->left, pPanel->top);
        Cmd_Button(0, 0, pPanel->width, pPanel->height, 18, OPT_FLAT," ");  //draw panel as button with no text     
        
    }
    else
    {//This is the main panel, just clear screen
        ClearScreen(pPanel->fillcolor);  //background color
    }
    //draw title
    Cmd_Color_RGB(pPanel->textcolor);
    Cmd_Text(pPanel->titleLeft, pPanel->titleTop, pPanel->font, pPanel->titleOptions, pPanel->pTitleText);
    //Cmd_Button(0, 0, 100, 100, 18, 0, " ");

    PanelObjectList* pFOL = pPanel->pObjectList;
    //Then, draw all the objects on the form
    for (int i = 0; i < MaxPanelObjects; i++)
    {
        PanelObject* pFO = pFOL->p[i];
        if (pFO == 0)
        {//end of list
            break;
        }
        DrawObject(pFO);
    }
    //printf("End of Panel object list.\n");
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

PanelObject* GetMouseOverObject(PanelPanel* pPanel)
{//See if mouse is over any object and return pointer to that object or NULL
    PanelObjectList* pFOL = pPanel->pObjectList;
    int x, y;
    PanelObject* p=NULL;


    for (int i = 0; i < MaxPanelObjects; i++)
    {
        p = pFOL->p[i];
        if (p == 0)
        {//end of list
            return NULL;
        }
        if (p->type == PanelType)
        {//recursively look for object
            PanelObject* p2= GetMouseOverObject((PanelPanel*)p);
            if (p2 != NULL)
                return p2;
            continue;
        }

        int oLeft = p->left + pPanel->left;
        int oTop = p->top + pPanel->top;

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
            int kw = ((PanelKeys*)p)->keywidth + 3;
            nKey = dx / kw;
        }

        pMouseOverParent = pPanel;//save parent pointer for slider
        return p;
    }



}



void IdleProcess()
{//things to do while waiting for user input
    DrawPanel(pCurrentPanel);  //draw panel first

    //let app draw on top of panel if need by
    if (pCurrentPanel->OnIdle != NULL)
        pCurrentPanel->OnIdle(NULL);  //do the idle process

    DrawCursor();  //draw cursor last
    swap(); //Image should now be showing
}



void WaitMouseDown()
{//wait for user to push mouse down
    PanelObject* pOldObject = NULL;
    bMouseMoved = false;
    while (true)
    {
        CheckMouse();
        if (bLeftButtonDown)
        {//button is down, so done waiting
            pClickedOnObject= GetMouseOverObject(pCurrentPanel);
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
            return;
           
        }

        if (bMouseMoved)
        {
            pMouseOverObject = GetMouseOverObject(pCurrentPanel);
            if (pOldObject != NULL)
            {
                if (pOldObject != pMouseOverObject) //Over something else?  Need to redraw if old was a button
                {
                    ////printf("Now over object %s\n", pMouseOverObject->name);
                    //if (pOldObject->type == ButtonType)
                    //{
                    //    ((PanelButton*)pMouseOverObject)->bMouseDownOn = false;
                    //}
                }
            }
            if (pMouseOverObject != NULL)
            {//Over an object                
                ////printf("Over object %s\n", pMouseOverObject->name);
                //if (pMouseOverObject->type == ButtonType)
                //{
                //    ((PanelButton*)pMouseOverObject)->bMouseDownOn = true;
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
    PanelObject* p;
    while (true)
    {
        CheckMouse();
        if (true)//bMouseMoved)
        {
            p = GetMouseOverObject(pCurrentPanel);

            //printf("Mouse over %s\n", p->name);
            if ((p != pClickedOnObject) && (pClickedOnObject != NULL))
            {//mouse is still down, but over something else
                if (pClickedOnObject->type == ButtonType)
                {//return button to 3D look to show back up
                    ((PanelButton*)pClickedOnObject)->bMouseDownOn = 0;
                        
                }
            }
            if ((p == pClickedOnObject) && (pClickedOnObject != NULL))
            {//mouse is still down on same thing clicked on 
                if (pClickedOnObject->type == ButtonType)
                {//show button as 2D to show down
                    ((PanelButton*)pClickedOnObject)->bMouseDownOn = -1;
                }
                if (pClickedOnObject->type == KeysType)
                {//show selected key as 2D to show down
                    ((PanelKeys*)pClickedOnObject)->fontoptions &= (~0x3F);
                    ((PanelKeys*)pClickedOnObject)->fontoptions |= ((PanelKeys*)pClickedOnObject)->pText[nKeyClicked]; //need to fix this
                }
            }

            if ((pClickedOnObject->type == SliderType))
            {//drag slider by mouse position
                PanelSlider* pS = (PanelSlider*)pClickedOnObject;
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
                PanelScrollBar* pS = (PanelScrollBar*)pClickedOnObject;
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
                PanelDial* pD = (PanelDial*)pClickedOnObject;
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

void HandleMouseUpToggle(PanelToggle* p)
{
    p->state = p->state ? 0 : -1;
    if ((p->OnClick) != NULL)
        p->OnClick((PanelObject*)p); //do whatever this button is supposed to do 

}

void HandleMouseUpButton(PanelButton* p)
{
    if ((p->OnClick) != NULL)
        p->OnClick((PanelObject*)p); //do whatever this button is supposed to do 
    //return button to 3D look to show back up
    p->bMouseDownOn = 0;

}

void HandleMouseUpText(PanelText* p)
{//not implementing anything yet

}

void HandleMouseUpGauge(PanelGauge* p)
{//not implementing anything yet

}

void HandleMouseUpScrollBar(PanelScrollBar* p)
{//not implementing anything yet

}

void HandleMouseUpSlider(PanelSlider* pS)
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

void HandleMouseUpDial(PanelDial* pD)
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
void HandleMouseUpKeys(PanelKeys* pD)
{//show keys back as 3d
    pD->fontoptions &= (~0x3F);
}

void DeselectOptionGroup(int group)
{//Unselect all options in this group

}


void HandleMouseDown()
{//Left button pressed, respond accordingly to object it is over
    //PanelObject* p;
    //pMouseOverObject = GetMouseOverObject(pCurrentPanel);
    //if (p == NULL)
    //    return;  //if not over an object just return

}


void HandleMouseUp()
{//Left button released, respond accordingly to object it is over
    PanelObject* p;
    p = GetMouseOverObject(pCurrentPanel);
    if (p != pClickedOnObject)
        return; //do nothing else if not released over the same object
    if (p == NULL)
        return;  //if not over an object just return

    printf("Clicked on %s\n", p->name);


    switch (p->type)
    {
    case ButtonType:
        HandleMouseUpButton((PanelButton*)p);
        break;
    case ToggleType:
        HandleMouseUpToggle((PanelToggle*)p);
        break;
    case SliderType:
        HandleMouseUpSlider((PanelSlider*)p);
        break;
    case TextType:
        HandleMouseUpText((PanelText*)p);
        break;
    case DialType:
        HandleMouseUpDial((PanelDial*)p);
        break;
    case GaugeType:
        HandleMouseUpGauge((PanelGauge*)p);
        break;
    case ScrollBarType:
        HandleMouseUpScrollBar((PanelScrollBar*)p);
        break;
    case KeysType:
        HandleMouseUpKeys((PanelKeys*)p);
        break;
    default:  //Maybe form has special code to handle clicks on objects
        printf("type=%d, top=%d, left=%d",p->type,p->top, p->left);
        if (pCurrentPanel->OnClick!=NULL)
            pCurrentPanel->OnClick(p);
        break;
    }

}


#endif //_PANELS_H_
