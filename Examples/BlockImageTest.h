////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Block1

BlockObjectList Block1Objects = { {
        //Zero terminated list of form objects
        (BlockObject*)&BlockMenu,
        (BlockObject*)&BlockDrawArea,
        (BlockObject*)0
    } };

BlockBlock Block1 = {
    "Block1",             //Object Name
    BlockType,               //Object type 
    0,                //Top  Note:  Top and left should be zero for main panel
    0,               //Left 
    HSIZE,              //width 
    VSIZE,             //height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    DeepFir,        //Border color
    MidnightBlue,          //fill color
    28,               //font #
    OPT_CENTERX,        //font options
    "Blocks Test",           //title bar text
    Yellow,          //color of title bar text
    14,           //y offset for title
    (HSIZE)/2,          //x offset for title
    OPT_CENTERX,       //options for drawing title text
    NULL,             //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a BlockBlock*
    &Block1Objects,   //pointer to NULL terminated list of form objects
    NULL,              //OnBlockOpen function
    NULL,               //OnBlockClose function
    NULL,    //Function to call when idle
    NULL //on click default
};

BlockImage BlockMenu=
{//Image - from an asset
    "Menu",             //Object Name - filename for files to load from filesystem
    ImageType,
    50,
    30,
    192,
    779,
    0,
    0,
    3,  //handle of this image
    NULL  //function to call when key clicked
};


BlockBlock BlockDrawArea = {
    "Block Draw Area",             //Object Name
    BlockType,               //Object type 
    50,                //Top  Note:  Top and left should be zero for main panel
    300,               //Left 
    1279-300,              //width 
    719-50,             //height
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    DeepFir,        //Border color
    White,          //fill color
    28,               //font #
    OPT_CENTERX,        //font options
    "",           //title bar text
    Yellow,          //color of title bar text
    14,           //y offset for title
    0,          //x offset for title
    OPT_CENTERX,       //options for drawing title text
    (BlockObject*)&Block1,             //pointer to parent form (or 0 if this is top form)  //Note:  Must type cast this one as can't make it a BlockBlock*
    &BlockDrawAreaObjects,   //pointer to NULL terminated list of form objects
    NULL,              //OnBlockOpen function
    NULL,               //OnBlockClose function
    NULL,    //Function to call when idle
    NULL //on click default
};

BlockObjectList BlockDrawAreaObjects = { {
        //Zero terminated list of form objects
        (BlockObject*)&Block1Repeat1,
        (BlockObject*)0
    } };

BlockRepeat Block1Repeat1 ={//Repeat
    "Repeat1",             //Button Name
    RepeatType,               //Object type
    200,                //Top
    300,               //Left 
    165,              //Width 
    82,             //Height 
    0,               //user data
    0,             //status: Lowest bit of status is invisible flag, Second lowest bit is disabled flag
    White,          //Text foreground color
    Blue,              //Button color 
    15,               //font#
    0,        //font options
    NULL,            //Button text
    NULL, //Function to call when button clicked
    NULL,      //Is the mouse down on this button?
    1,        //Handle to draw when mouse up
    2      //Handle to draw when mouse down
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Block Objects

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Block Constants and Variables




/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Block Methods

