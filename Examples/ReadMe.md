# These are our examples for Antares
> Many of these examples use files in the Assets folder that must be placed in the host's Plan9 folder or on uSD on P2 board.

## AntLogo.c
- A simple example to show a logo for Antares using built in font and some graphical primitives
## PNG.c
- This example simply loads a .png image from either PC using Plan9 or uSD (depending on setting in Platform.h) into EVE's RAM and then displays it.
- Loading a large image over Plan9 can take several seconds
## TestAssets.c
- This example shows how to use "asset" files.  The Antares Asset Builder was used to create the TestAssets.h and TestAssets.ant files.  
- The TestAssets.ant file contains several images and a couple fonts and is loaded from either PC using Plan9 or uSD (depending on setting in Platform.h) into EVE's RAM.
- Not all the images and fonts can be seen with a small screen.
## Fonts.c
- This example shows how to use fonts built with the EVE Asset Builder
- The two font files are loaded from either PC (using Plan9) or uSD into EVE's RAM
- This shows the hard way to use these kind of assets.  Either the Antares asset builder or the Gameduino asset builder can make it easier. 
## MediaFifoTest1.c  
- Shows how to display an image using the media fifo.
- This example sets up a media fifo in top of RAM_G, copies a jpg or png image into the media fifo and then tells EVE to decompress the image to bottom of RAM_G, finally shows the image
- Note:  Not really using the media fifo as a fifo here, just as a buffer to hold uncompressed image
## jpeg_scaled.c
- This gd2-lib example for showing a jpg or png image is modified to scale the image to be larger (or smaller) on the screen


# Examples for Antares-B
> These examples only really work in 720p using the Anteres-B hardware

## CursorTest1.c
- This example shows a mouse cursor on top of a large image.  The cursor can be controlled via USB mouse connected to Antares-B's USB port.

## PanelTest1.c
- This example tests the Panels API and shows several controls that interact with USB mouse

## Tetris.c
- It's Tetris!  This is a Tetris game meant for 720p and controlled via the hosts computer keyboard using WASD keys

## Simon_wMouse.c
- The GD2 example modified for use USB mouse and cursor instead of touchscreen.  Has sound.

## GPIO_InputTest.c
- Shows input from EVE's GPIO pins, GPIO0 and GPIO1.
- This may work with regular EVE lcds too, but I don't think they bring these pins out for use.
 
## PanelImageTest.c
- This example explores the effects of the A..F Bitmap Transform functions
- Uses the Panels API so that a USB mouse can interact with on screen sliders
- The sliders adjust the value of these bitmap transform values over a small range to see what they do
  > Note:  Fortunately, EVE3 has CoPro commands like scale and rotate that let you not have to learn this!

## BlockImageTest.c
- This is just a test to see if Blockly graphical programming could be implemented with EVE...
- It just shows one repeat block that you can move around the screen.
- Looks like it could work, but would take a lot more programming...
