REM These are command lines to build the various Examples
REM Uncomment the one you want to try and then run this batch file

REM -O2,!cse  <-- Use this if -O2 doesn't work

REM This is the Matrix Orbital example using Antares
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from MatrixOrbital\EVEMO_Test.c"

REM Here are working gd2-lib examples using Antares
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\helloworld.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\blobs.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\jpeg.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\fizz.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\simon.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\logo.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\mono.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\reflection.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\slotgag.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\tiled.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\walk.c"  
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\sprites.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\widgets.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\kenney.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\jnr.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\frogger.c"
REM This one needs video file to be on uSD and correct uSD pins defined in platform.h  Also specifying to use long file names...
REM C:\FlexProp\bin\flexspin.exe -O2,!cse -2 -DFF_USE_LFN  -L C:\FlexProp\include -o Antares.binary "Examples from gd2-lib\video1.c"


REM Examples by RJA
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\png.c"
C:\FlexProp\bin\flexspin.exe -2 -DFF_USE_LFN=1 -L C:\FlexProp\include -o Antares.binary "Examples\Fonts.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\AntLogo.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\TestAssets.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\MediaFifoTest1.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\CursorTest1.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\PanelTest1.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\Tetris.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\simon_wMouse.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\GPIO_InputTest.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\PanelImageTest.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\BlockImageTest.c"
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary "Examples\jpeg_scaled.c"

REM Flash Examples by RJA
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary FlashErase.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary FlashLoad.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary FlashShowImage.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary FlashShowImageDirect.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary FlashShowVideoDirect.c

REM Board1 examples by RJA 
REM C:\FlexProp\bin\flexspin.exe -DPIN_MISO=44 -DPIN_MOSI=46 -DPIN_SS=47 -DPIN_CLK=45 -2 -L C:\FlexProp\include -o Antares.binary TestAssets.c
REM C:\FlexProp\bin\flexspin.exe -DPIN_MISO=58 -DPIN_MOSI=60 -DPIN_SS=61 -DPIN_CLK=59 -2 -L C:\FlexProp\include -o Antares.binary TestAssets.c

REM AntaresB Hardware examples by RJA 
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary WiiClassicController.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -DFF_USE_LFN -o Antares.binary GameOnDesigner.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary kenney_720p.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary kenney_game.c
REM NOTE:  Add this to command line to use different pins for uSD:  -DPIN_MISO=10 -DPIN_MOSI=12 -DPIN_SS=13 -DPIN_CLK=11
REM NOTE:  For AntaresB SD_MISO=Basepin+10, SD_CLK=Basepin+11, SD_MOSI=Basepin+12, SD_CS=Basepin+13
REM C:\FlexProp\bin\flexspin.exe -DPIN_MISO=10 -DPIN_MOSI=12 -DPIN_SS=13 -DPIN_CLK=11 -2 -L C:\FlexProp\include -o Antares.binary TestAssets.c
REM This example uses a mouse connected to the AntaresB USB port to move an onscreen cursor and interact with onscreen elements
REM C:\FlexProp\bin\flexspin.exe -DPIN_MISO=10 -DPIN_MOSI=12 -DPIN_SS=13 -DPIN_CLK=11 -2 -L C:\FlexProp\include -o Antares.binary PanelTest1.c

REM This is RJA testing...
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary Test.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary helloworld_ClassTest.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary video1_NoMediaFifo.c


REM These compile and run, but don't look right
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary radarchart.c
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary cobra.c

REM Too complex to compile for now due to C++ features, like advanced classes
REM C:\FlexProp\bin\flexspin.exe -2 -L C:\FlexProp\include -o Antares.binary nightstrike.c