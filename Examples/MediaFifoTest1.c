#include "../Antares/Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver


//RJA:  MediaFifoTest1.c  Shows how to display an image using the media fifo.
//      This example sets up a media fifo in top of RAM_G, copies a jpg or png image into the media fifo and then tells EVE to decompress the image to bottom of RAM_G, finally shows the image
//      Note:  Not really using the media fifo as a fifo here, just as a buffer to hold uncompressed image



//RJA:  This code based on an example from here: https://github.com/nutechsoftware/esp32toft81x

uint32_t mf_size, mf_base, wp; //Media Fifo Size, Base address, and write pointer

void TestLoadImage()
{
    uint32_t ImageBase;//base address for the decoded image 
    uint32_t imgptr, widthptr, heightptr;

    //Pick one of these file settings to try out
    char filename[] = "autumn.png";  //This one gives EVE STUCK messages, but seems to work anyway
    int filesize = 151058;  //Size of above image in bytes
    int image_width = 320;
    int image_height = 194;

    //char filename[] = "sunrise.jpg";
    //int filesize = 14171;
    //int image_width = 220;
    //int image_height = 147;
    

    mf_size = 0x40000UL;  //Using upper 262,144 bytes of RAM_G for media fifo
    mf_base = 0x100000UL -mf_size;  //base address of media fifo.  Note:  0x0FFFFF is the end of RAM_G, this puts the media fifo at the end of RAM_G 

    // Configure MEDIA FIFO
    cmd_mediafifo(mf_base, 0x40000UL);
    UpdateFIFO();
    Wait4CoProFIFOEmpty();  //Wait for this to process

    // stop media fifo
    wr32(REG_MEDIAFIFO_WRITE+RAM_REG, 0);

    //Want the output to go to base address 0 in RAM_G
    ImageBase = 0;

    // USE MEDIA_FIFO to load image
    //Note:  We can send this command already, even though image isn't loaded there yet
    Send_CMD(CMD_LOADIMAGE);
    Send_CMD(ImageBase);
    Send_CMD(OPT_RGB565 | OPT_NODL | OPT_MEDIAFIFO);


    // Arrange to get the decompressed image properties
    cmd_getprops(&imgptr, &widthptr, &heightptr);

    // Check the read pointer where the GPU is working currently (should be zero)
    uint32_t mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
    printf("Read pointer= %d\n", mf_rp);

    //Now, load in the image to media fifo
    Load_RAW(mf_base, filename);
    

    wp = 4*((filesize +3)/4); //14171 bytes in sunrise.jpg, rounded up to nearest 4-byte boundary
    //Once we update the fifo write pointer using the next line, the GPU will begin decoding the image and sending to RAM_G
    wr32(REG_MEDIAFIFO_WRITE + RAM_REG, wp);
    UpdateFIFO();
    Wait4CoProFIFOEmpty();

    //Now, start a display list and show the image
    ClearColorRGB(0, 0, 0);
    Clear();

    Cmd_SetBitmap(0, RGB565, image_width, image_height);  //Seems we need to provide image information when we load an image using the media fifo

    Begin(BITMAPS);
    Vertex2ii(50, 50);
    swap(); //Image should now be showing

    // Get the read pointer where the GPU is working currently and the write pointer we sent, should be equal when done
    do
    {//read the fifo pointers until done
        usleep(10000);
        mf_rp = rd32(REG_MEDIAFIFO_READ + RAM_REG);
        wp = rd32(REG_MEDIAFIFO_WRITE + RAM_REG);
        printf("Read pointer = %d, Write pointer= %d\n", mf_rp, wp);
    } while (mf_rp != wp);
    printf("Processing of media fifo complete.\n\n");

    //Now that it's done, can retrieve image dimensions from the Command Fifo
    printf("width address= %d, height address=%d\n", widthptr, heightptr);
    printf("width= %d, height=%d\n", rd32(widthptr), rd32(heightptr));



}



void loop()
{
    TestLoadImage();

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
        for (;;) {}  //just do it once...
    }
}


