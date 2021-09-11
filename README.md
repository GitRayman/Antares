# Antares
API for using the FTDI EVE 2/3/4 GPU with Parallax P2 MCU and FlexProp C

- Antares is an API to interface with the FTDI EVE series of GPUs (Mostly EVE2 and EVE3, but also works with EVE4).
- It is essentially a port of the excellent Gameduino library to the Propeller 2 MCU.
  > Since the P2 currently has no C++ compiler finished, the Gameduino library was ported back to C to be compiled with the FlexProp C compiler.
- The Matrix Orbital library was used for the low level interface.

This library has been tested with Matrix Orbital and Newhaven EVE displays.

## Usage
- 

## Offshoots
Some offshoots of Antares are:
- Antares-Assets:  A port of the Gameduino asset builder that runs natively on the P2.
- Antares-B:  EVE to 720p adapter board (VGA and HDMI versions in development).  Let's you connect EVE to TV or monitor for HD graphics.
- Antares-Panels:  A helper API for more easily generating and interfacing with GUI elements.


