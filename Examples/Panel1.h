////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel1

PanelObjectList Panel1Objects = { {
        //Zero terminated list of form objects
        (PanelObject*)&Panel2,
        (PanelObject*)&Panel3,
        (PanelObject*)0
    } };

PanelPanel Panel1 = {
    "Panel1",             //Object Name
    PanelType,               //Object type 
    0,                //Top  Note:  Top and left should be zero for main panel
    0,               //Left 
    HSIZE,              //width 
    VSIZE,             //height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    DeepFir,        //Border color
    Kimberly,          //fill color
    28,               //font #
    OPT_CENTERX,        //font options
    "This is the main Panel",           //title bar text
    Yellow,          //color of title bar text
    14,           //y offset for title
    (HSIZE)/2,          //x offset for title
    OPT_CENTERX,       //options for drawing title text
    NULL,             //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a PanelPanel*
    &Panel1Objects,   //pointer to NULL terminated list of form objects
    NULL,              //OnPanelOpen function
    NULL,               //OnPanelClose function
    NULL,    //Function to call when idle
    NULL //on click default
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel2
PanelButton Panel2Button1 = {//button1
    "Button1",     //name
    ButtonType,               //Object type 
    49,              //Top 
    50,        //Left 
    100,    //Width 
    30,              //Height
    0,              //user data
    0,              //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    White,          //Text foreground color
    Red,          //Button color
    27,               //font #
    0,        //font options
    "Click Me!", //Button text
    NULL,               //OnClick function
    false       //Is the mouse down on this button?
};

PanelToggle Panel2Toggle1={
    "Toggle1",             //Button Name
    ToggleType,               //Object type 
    100,                //Top
    50,               //Left 
    60,              //Width 
    25,             //Height 
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    0,              //0 is off, -1 is on
    White,          //Text foreground color
    Blue,           //Bar color 
    Red,          //Knob color
    Gallery,          //Text foreground color
    Silver,           //Bar color 
    BahamaBlue,          //Knob color
    27,               //font#
    0,        //font options
    "Off\xffOn",            //Toggle text
    NULL     //Function to call when toggled
};

PanelSlider Panel2Slider1 = {
    "Slider1",             //Slider Name
    SliderType,               //Object type 
    200,                //Top
    50,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    128,                //value
    255,              //range
    NULL //Function to call when button clicked
};

PanelSlider Panel2Slider2 = {
    "Slider2",             //Slider Name
    SliderType,               //Object type 
    100,                //Top
    300,               //Left
    30,              //Width
    200,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Cyan,          //left color
    Blue,           //right color
    Red,          //Knob color
    0,           //options
    128,                //value
    255,              //range
    NULL           //Function to call when changed
};

PanelSlider Panel2Dial1 = {
    "Dial #1",             //Dial Name
    DialType,               //Object type 
    300,                //Top
    80,               //Left 
    80,              //Width    //sets radius
    80,             //Height    //set to same as width
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    PeachOrange,          //Knob color
    Black,        //tic color
    0,            //options
    20000,                //value, max is 65535
    10000,             //min limit
    55535,             //max limit
    NULL //Function to call when changed
};

PanelText Panel2Text1 =
{
    "Text 1",             //Text Name
    TextType,               //Object type 
    140,                //Top 
    50,               //Left 
    0,              //Width   //This is automatically calculated at run time
    0,             //Height  //This is automatically calculated at run time
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Magenta,              //Text foreground color
    25,               //font#
    0,        //font options
    "Just Text."            //text
};

PanelLed Panel2Led1 =
{
    "Led 1",             //Text Name
    LedType,               //Object type 
    400,                //Top 
    50,               //Left 
    0,              //Width     //This is automatically calculated at run time
    0,             //Height    //This is automatically calculated at run time
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Yellow,              //Text foreground color
    25,               //font#
    0,        //font options
    "LED #1",            //text
    BlueBell,            //LED on Color
    MineShaft,           //LED off Color
    true               //is LED on? true or false 
};


PanelObjectList Panel2Objects = { {
        //Zero terminated list of form objects
        (PanelObject*)&Panel2Button1,
        (PanelObject*)&Panel2Toggle1,
        (PanelObject*)&Panel2Slider1,
        (PanelObject*)&Panel2Slider2,
        (PanelObject*)&Panel2Text1,
        (PanelObject*)&Panel2Dial1,
        (PanelObject*)&Panel2Led1,
        (PanelObject*)0  //end of list, null terminated
    } };

PanelPanel Panel2 = {
    "Panel2",             //Object Name
    PanelType,               //Object type form==0
    100,                //Top  Note:  Top and left should be zero for main panel
    100,               //Left 
    400,              //width 
    500,             //height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    DeepFir,        //Border color
    DeepFir,          //fill color
    28,               //font #
    OPT_CENTERX,        //font options
    "This is a Sub-Panel",           //title bar text
    White,          //color of title bar text
    7,           //y offset for title
    200,          //x offset for title
    OPT_CENTERX,       //options for drawing title text
    (PanelObject*) &Panel1,             //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a PanelPanel*
    &Panel2Objects,   //pointer to NULL terminated list of form objects
    NULL,              //OnPanelOpen function
    NULL,               //OnPanelClose function
    NULL,    //Function to call when idle
    NULL //on click default
};


PanelGauge Panel3Gauge1={
    "Gauge 1",             //Dial Name
    GaugeType,               //Object type 
    60,                //Top
    50,               //Left 
    100,              //Width  //sets radius
    100,             //Height //set to same as width
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    MineShaft2,          //dial color
    White,          //tic and needle color
    0,            //options
    6,              //#major ticks
    3,              //#minor ticks
    1000,                //value, max is 65535
    3000,              //max value
    NULL          //Function to call when  clicked
};

PanelProgress Panel3Progress1={
    "Progress 1",             //Slider Name
    ProgressType,               //Object type 
    200,                //Top
    50,               //Left 
    200,              //Width   
    10,             //Height   
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Christalle,              //background color
    Sunglow,      //progress color 
    0,            //options
    700,                //value
    1000,              //range
    NULL          //Function to call when clicked
};

PanelScrollBar Panel3ScrollBar1={
    "Scroll Bar 1",            //Slider Name
    ScrollBarType,               //Object type 
    50,                //Top
    350,               //Left 
    10,              //Width   //Note: drawn vertical if this is less than height
    200,             //Height   
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    ElectricLime,          //outer color
    Lipstick,           //inner color 
    0,            //options
    50,                //value
    100,               //size
    1000,              //range
    NULL //Function to call when clicked
};

PanelScrollBar Panel3ScrollBar2 = {
    "Scroll Bar 2",            //Slider Name
    ScrollBarType,               //Object type 
    250,                //Top
    50,               //Left 
    200,              //Width   //Note: drawn vertical if this is less than height
    30,             //Height   
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Apple,          //outer color
    Lilac,           //inner color 
    0,            //options
    50,                //value
    10,               //size
    1000,              //range
    NULL //Function to call when clicked
};

PanelNumber Panel3Number1= {//Number
    "Number 1",             //Text Name
    NumberType,               //Object type
    290,                //Top 
    50,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    0,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    365764109                  //number
};

PanelKeys Panel3Keys1={//Keys
    "Keys1",             //Text Name
    KeysType,               //Object type
    350,                //Top 
    50,               //Left 
    0,              //Width     //This is automatically calculated at run time based on "keywidth" below
    30,             //Height    //Height of keys
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    White,              //Text foreground color
    CostaDelSol,           //color of keys when up
    Blue,           //color of keys when down
    23,               //font#
    0,        //font options
    30,           //width of keys
    "QWERTYUIOP",            //text
    NULL        //function to call when key clicked
};

PanelClock Panel3Clock1={//Clock
    "Clock1",            //Dial Name
    ClockType,               //Object type 
    410,                //Top
    50,               //Left 
    80,              //Width  //sets radius
    80,             //Height //set to same as width
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    White,          //back color
    RedBerry,        //tic color
    0,            //options
    2,                  //hours
    31,                  //minutes
    15,                  //seconds
    3                 //milliseconds
};

PanelObjectList Panel3Objects = { {
        //Zero terminated list of form objects
        (PanelObject*)&Panel3Gauge1,
        (PanelObject*)&Panel3Progress1,
        (PanelObject*)&Panel3ScrollBar1,
        (PanelObject*)&Panel3ScrollBar2,
        (PanelObject*)&Panel3Number1,
        (PanelObject*)&Panel3Keys1,
        (PanelObject*)&Panel3Clock1,
        (PanelObject*)0  //end of list, null terminated
    } };

PanelPanel Panel3 = {
    "Panel 3",             //Object Name
    PanelType,               //Object type form==0
    100,                //Top  Note:  Top and left should be zero for main panel
    600,               //Left 
    400,              //width 
    500,             //height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    MidnightBlue,        //Border color
    MidnightBlue,          //fill color
    28,               //font #
    OPT_CENTERX,        //font options
    "This is another Sub-Panel",           //title bar text
    Cyan,          //color of title bar text
    7,           //y offset for title
    200,          //x offset for title
    OPT_CENTERX,       //options for drawing title text
    (PanelObject*)&Panel1,             //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a PanelPanel*
    &Panel3Objects,   //pointer to NULL terminated list of form objects
    NULL,              //OnPanelOpen function
    NULL,               //OnPanelClose function
    NULL,    //Function to call when idle
    NULL //on click default
};






/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Objects

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Constants and Variables




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Methods

