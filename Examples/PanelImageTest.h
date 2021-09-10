////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel1

PanelObjectList Panel1Objects = { {
        //Zero terminated list of form objects
        (PanelObject*)&Panel1Slider1,
        (PanelObject*)&Panel1Slider2,
        (PanelObject*)&Panel1Slider3,
        (PanelObject*)&Panel1Slider4,
        (PanelObject*)&Panel1Slider5,
        (PanelObject*)&Panel1Slider6,
        (PanelObject*)&Panel1Image1,
        (PanelObject*)&Panel1Number1,
        (PanelObject*)&Panel1Number2,
        (PanelObject*)&Panel1Number3,
        (PanelObject*)&Panel1Number4,
        (PanelObject*)&Panel1Number5,
        (PanelObject*)&Panel1Number6,
        (PanelObject*)&Panel1Text1,
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
    "Image Transform Test",           //title bar text
    Yellow,          //color of title bar text
    14,           //y offset for title
    (HSIZE)/2,          //x offset for title
    OPT_CENTERX,       //options for drawing title text
    NULL,             //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a PanelPanel*
    &Panel1Objects,   //pointer to NULL terminated list of form objects
    NULL,              //OnPanelOpen function
    NULL,               //OnPanelClose function
    &DrawTransformedImage,    //Function to call when idle
    NULL //on click default
};

PanelSlider Panel1Image1 = {
    "autumn.png",             //Slider Name
    ImageType,               //Object type 
    20,                //Top
    850,               //Left
    320,              //Width
    194,             //Height
    0,    //pointer to image size/data structure for embedded images or images in flash
    0,
    1,  //one of {0=already in RAM_G, 1=load from filesystem, 2=load from flash, 3=load from P2 RAM}
    0,  //address of image in RAM_G
    2,    //handle of this image
    NULL //Function to call when button clicked
};

PanelSlider Panel1Slider1 = {
    "Slider1",             //Slider Name
    SliderType,               //Object type 
    150,                //Top
    80,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    512+256,                //value
    1024,              //range
    NULL //Function to call when button clicked
};

PanelSlider Panel1Slider2 = {
    "Slider2",             //Slider Name
    SliderType,               //Object type 
    225,                //Top
    80,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    512+0,                //value
    1024,              //range
    NULL //Function to call when button clicked
};

PanelSlider Panel1Slider3 = {
    "Slider3",             //Slider Name
    SliderType,               //Object type 
    300,                //Top
    80,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    512 * 32,                //value
    1024*32,              //range
    NULL //Function to call when button clicked
};

PanelSlider Panel1Slider4 = {
    "Slider4",             //Slider Name
    SliderType,               //Object type 
    375,                //Top
    80,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    512,                //value
    1024,              //range
    NULL //Function to call when button clicked
};

PanelSlider Panel1Slider5 = {
    "Slider5",             //Slider Name
    SliderType,               //Object type 
    450,                //Top
    80,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    512 + 256,                //value
    1024,              //range
    NULL //Function to call when button clicked
};

PanelSlider Panel1Slider6 = {
    "Slider6",             //Slider Name
    SliderType,               //Object type 
    525,                //Top
    80,               //Left
    200,              //Width
    30,             //Height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    Black,          //left color
    Yellow,           //right color
    Blue,          //Knob color
    0,           //options
    512 * 32,                //value
    1024 * 32,              //range
    NULL //Function to call when button clicked
};



PanelNumber Panel1Number1 = {//Number
    "Number 1",             //Text Name
    NumberType,               //Object type
    150,                //Top 
    300,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    OPT_SIGNED,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    0                  //number
};

PanelNumber Panel1Number2 = {//Number
    "Number 2",             //Text Name
    NumberType,               //Object type
    150+75,                //Top 
    300,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    OPT_SIGNED,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    0                  //number
};

PanelNumber Panel1Number3 = {//Number
    "Number 3",             //Text Name
    NumberType,               //Object type
    150+75*2,                //Top 
    300,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    OPT_SIGNED,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    0                  //number
};

PanelNumber Panel1Number4 = {//Number
    "Number 4",             //Text Name
    NumberType,               //Object type
    150 + 75 * 3,                //Top 
    300,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    OPT_SIGNED,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    0                  //number
};

PanelNumber Panel1Number5 = {//Number
    "Number 5",             //Text Name
    NumberType,               //Object type
    150 + 75 * 4,                //Top 
    300,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    OPT_SIGNED,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    0                  //number
};

PanelNumber Panel1Number6 = {//Number
    "Number 6",             //Text Name
    NumberType,               //Object type
    150 + 75 * 5,                //Top 
    300,               //Left 
    0,              //Width     //normally unused
    0,             //Height    //normally unused
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    LaserLemon,              //Text foreground color
    25,               //font#
    OPT_SIGNED,        //font options, including OPT_SIGNED to treat as signed
    10,               //base, one of 2..36, set to 10 for decimal
    0                  //number
};


PanelText Panel1Text1 =
{
    "Text 1",             //Text Name
    TextType,               //Object type 
    65,                //Top 
    40,               //Left 
    0,              //Width   //This is automatically calculated at run time
    0,             //Height  //This is automatically calculated at run time
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    White,              //Text foreground color
    25,               //font#
    0,        //font options
    "Transforms:\n\nA\n\nB\n\nC\n\nD\n\nE\n\nF"            //text
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Objects

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Constants and Variables




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Panel Methods

