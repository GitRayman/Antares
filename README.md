# Antares
API for using the FTDI EVE 2/3/4 GPU with Parallax P2 MCU and FlexProp C

- Antares is an API to interface with the [FTDI EVE series of GPUs] (https://brtchip.com/eve/) (Mostly EVE2 and EVE3, but also works with EVE4).
- Antares is essentially a port of the excellent [Gameduino library](https://github.com/jamesbowman/gd2-lib) for the [Propeller 2 MCU] (https://www.parallax.com/propeller-2/).
  > Since the P2 currently has no C++ compiler finished, the Gameduino library was ported back to C to be compiled with the [FlexProp C compiler] (https://github.com/totalspectrum/flexprop/).
- The [Matrix Orbital library] (https://github.com/MatrixOrbital/EVE2-Library) was used for the low level interface.

This library has been tested with [Matrix Orbital](https://www.matrixorbital.com/) and [Newhaven](https://www.newhavendisplay.com/) EVE displays.

## Usage
- There are several examples here, many adapted from Gameduino, that show how to use the library
- The easiest way to get started with coding might be to use the [FlexProp GUI] (https://github.com/totalspectrum/flexprop/) to open an example .c file and then run it
- The Platform.h file contains most of the display and I/O pin settings.  There are many settings there and the display and pin settings must be correct to have it work. 
  > Getting the settings right in Platform.h is essential because there are so many display options and possible combinations of I/O pins which can be used.
  > Other settings, such as P2 frequency, serial I/O baud rate, and I/O pins for uSD card are also defined there
- The list of display options is in DisplaySettings.h, which is included in Platform.h
  - The touchscreen options are also definined here
  - Resistive touchscreens have extra options for how to handle the calibration data 

## Offshoots
Some offshoots of Antares are:
- Antares-Assets:  A clone of the [Gameduino asset builder] (https://github.com/jamesbowman/gd2-asset) that runs natively on the P2.
  - Assets are a .h file (and a .ant file for placement on uSD card) that automagically load images into EVE's RAM from uSD and configure bitmap handles for useage.
  - You can also use Gameduino assets, as demonstrated in several gd2-lib examples.
  - The Gameduino asset builder has more options and may be a preferred option, if you can get it to work on your system. 
- Antares-B:  EVE to 720p adapter board (VGA and HDMI versions in development).  Let's you connect EVE to TV or monitor for HD graphics.
- Antares-Panels:  A helper API for more easily generating and interfacing with GUI elements.


