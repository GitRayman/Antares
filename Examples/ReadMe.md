# These are our examples for Antares

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



# Examples for Antares-B
> These examples only really work in 720p using the Anteres-B hardware

## CursorTest1.c
- This example shows a mouse cursor on top of a large image.  The cursor can be controlled via USB mouse connected to Antares-B's USB port.

## PanelTest1.c
- This example tests the Panels API and shows several controls that interact with USB mouse

## Tetris.c
- It's Tetris!  This is a Tetris game meant for 720p and controlled via the hosts computer keyboard using WASD keys

