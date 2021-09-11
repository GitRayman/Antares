#include "Antares.h"  //Test, adapted from Matrix Orbital's test program


void MakeScreen_MatrixOrbital(uint8_t DotSize)
{
    ClearColorRGB(255, 0, 0);    // Determine the clear screen color
    Clear();               // Clear the screen and the current display list
    ColorRGB(26, 26, 192);      // change colour to blue
    PointSize(DotSize * 16);    // set point size to DotSize pixels. Points = (pixels x 16)
    Begin(POINTS);                // start drawing point
    Tag(1);                       // Tag the blue dot with a touch ID
    Send_CMD(VERTEX_TRANSLATE_X((HSIZE / 2) << 4));  //RJA: need to translate when desired x position>511
    Vertex2ii(0, (VSIZE / 2) - 60); // place blue point
    Send_CMD(VERTEX_TRANSLATE_X(0));  //RJA: set translate back to zero
    End();                         // end drawing point
    ColorRGB(255, 255, 255);   // Change color to white for text
    cmd_text(HSIZE / 2, (VSIZE / 2) - 60, 30, OPT_CENTER, " MATRIX         ORBITAL"); //Write text in the center of the screen
    cmd_text(HSIZE / 2, (VSIZE / 2), 28, OPT_CENTER, "Connecting to WIFI"); //Write text in the center of the screen
    //cmd_number(200, 100, 31, OPT_RIGHTX, 534);
    Cmd_Spinner(HSIZE / 2, 80 + (VSIZE / 2), 0, 0);  //show spinner

    swap();  // End the display list and start another
}

void setup()
{
    //check clock freq
    int cf = _clockfreq();
    printf("clock freq= %d\n", cf);

    begin(); //start EVE


}

void main()
{
    setup();
    printf("Showing Matrix Orbital Screen\n");
    MakeScreen_MatrixOrbital(16);
    printf("Done.\n");
    for (;;) {}
}
