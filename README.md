# Antares
API for using the FTDI EVE 2/3/4 GPU with Parallax P2 MCU and FlexProp C

- Antares is an API to interface with the [FTDI EVE series of GPUs](https://brtchip.com/eve/) (Mostly EVE2 and EVE3, but also works with EVE4).
- Antares is essentially a port of the excellent [Gameduino library](https://github.com/jamesbowman/gd2-lib) for the [Propeller 2 MCU](https://www.parallax.com/propeller-2/).
  > Since the P2 currently has no C++ compiler finished, the Gameduino library was ported back to C to be compiled with the [FlexProp C compiler](https://github.com/totalspectrum/flexprop/).
- The [Matrix Orbital library](https://github.com/MatrixOrbital/EVE2-Library) was used for the low level interface.

This library has been tested with [Matrix Orbital](https://www.matrixorbital.com/) and [Newhaven](https://www.newhavendisplay.com/) EVE displays.  There are other companies that sell displays that are probably compatible as well.

## Usage
- There are several examples here, many adapted from Gameduino, that show how to use the library
- The easiest way to get started with coding might be to use the [FlexProp GUI](https://github.com/totalspectrum/flexprop/) to open an example .c file and then run it
- The Platform.h file contains most of the display and I/O pin settings.  There are many settings there and the display and pin settings must be correct to have it work. 
  > Getting the settings right in Platform.h is essential because there are so many display options and possible combinations of I/O pins which can be used.
  > Other settings, such as P2 frequency, serial I/O baud rate, and I/O pins for uSD card are also defined there
- The list of display options is in DisplaySettings.h, which is included in Platform.h
  - The touchscreen options are also definined here
  - Resistive touchscreens have extra options for how to handle the calibration data
- Once can also build and run these examples using the command line.  See "build.bat" for how to build this way.  Use loadp2.exe to load the built code with command line options such as "-9 D:\Propeller2\uSD_Contents -t -k -b  2000000 Antares.binary".
- Microsoft Visual Studio (even the free Community Edition) can also be used to compile and launch this code and a solution and project file is included here for that uses.
  - With the solution open, simply edit the "build.bat" file to uncomment the file you want to compile.
  - You can then Build->Build Antares with the menu or push the green play button next to "Local Windows Debugger" to launch.
  - More instructions for doing this are [given here](http://www.rayslogic.com/Propeller2/VisualStudio_P2.htm). 

## See Also
- The [Gameduino 3 page](https://excamera.com/sphinx/gameduino3/) has several resources include a book on how to use it and a description of their examples.
- The [EVE 2/3 Programming Guide](https://brtchip.com/wp-content/uploads/Support/Documentation/Programming_Guides/ICs/EVE/BRT_AN_033_BT81X_Series_Programming_Guide.pdf) is extremely useful for figuring out how to interface with EVE.
- The [EVE IC Datasheets](https://brtchip.com/datasheets/#toggle-id-1) are also very useful. 
- In addition to the [Gameduino library](https://github.com/jamesbowman/gd2-lib) and the [Matrix Orbital library](https://github.com/MatrixOrbital/EVE2-Library), there are several [FTDI (AKA Bridgetek) examples](https://brtchip.com/SoftwareExamples-eve/) that may work with some adaptation.  The FTDI API is full featured, but very complex.  The Matrix Orbital version of the lower level interfacing used by Antares is much simpler to follow.
- [Rayslogic.com](http://www.rayslogic.com/) has info on the P2 microprocessor.
- The [Eve Asset Builder](https://brtchip.com/eve-toolchains/) is essential for preparing images for use and also using a flash chip connected to EVE3.  There are also some screen designer tools there that are interesting.

## Offshoots
Some offshoots of Antares are:
- Antares-Assets:  A clone of the [Gameduino asset builder](https://github.com/jamesbowman/gd2-asset) that runs natively on the P2.
  - Assets are a .h file (and a .ant file for placement on uSD card) that automagically load images into EVE's RAM from uSD and configure bitmap handles for useage.
  - You can also use Gameduino assets, as demonstrated in several gd2-lib examples.
  - The Gameduino asset builder has more options and may be a preferred option, if you can get it to work on your system. 
- Antares-B:  EVE to 720p adapter board (VGA and HDMI versions in development).  Let's you connect EVE to TV or monitor for HD graphics.
- Antares-Panels:  A helper API for more easily generating and interfacing with GUI elements.


