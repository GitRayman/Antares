#include "../Antares/Antares.h"     //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver


//RJA:  video.c  Shows how to play a .avi video using the media fifo.
//      This example sets up a media fifo in top of RAM_G and then continuously streams data to it as EVE decodes the video

//RJA:  This code extends the MediaFifoText1.c example to play video using the media fifo to implement this gd2-lib example

void loop()
{//Play the video in a loop
    playVideo("fun-1500.avi"); //"test.avi"); //"fun-1500.avi"); //sintel.avi");// fun - 1500.avi");"test.avi");
}

void setup()
{
    begin();
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    for (;;)
    {
        loop();
    }
}


