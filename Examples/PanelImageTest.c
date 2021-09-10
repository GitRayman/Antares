#include "Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//RJA:  This example explores the effects of the A..F Bitmap Transform functions
//     The sliders adjust the value of these bitmap transform values over a small range to see what they do
//     Note:  Fortunately, EVE3 has CoPro commands like scale and rotate that let you not have to learn this!


#include "Panels.h"  //The panels interface code
#include "PanelImageTest.h"  //Test panel





void setup()
{
  begin();

  InitPanels(&Panel1);  //Start up panels interface with Panel1 showing


}

void loop()
{  
    PanelLoop();  //show panel and interact with mouse
}

PanelSlider* psA = &Panel1Slider1;
PanelSlider* psB = &Panel1Slider2;
PanelSlider* psC = &Panel1Slider3;
PanelSlider* psD = &Panel1Slider4;
PanelSlider* psE = &Panel1Slider5;
PanelSlider* psF = &Panel1Slider6;

PanelNumber* pnA = &Panel1Number1;
PanelNumber* pnB = &Panel1Number2;
PanelNumber* pnC = &Panel1Number3;
PanelNumber* pnD = &Panel1Number4;
PanelNumber* pnE = &Panel1Number5;
PanelNumber* pnF = &Panel1Number6;

PanelImage* pi = &Panel1Image1;

void DrawTransformedImage()
{
    //update numbers from sliders
    pnA->n = psA->val - 512;
    pnB->n = psB->val - 512;
    pnC->n = psC->val - 512 * 32;
    pnD->n = psD->val - 512;
    pnE->n = psE->val - 512;
    pnF->n = psF->val - 512 * 32;

    //draw image with transforms
    ColorRGB24(0xFFFFFF);
    BitmapHandle(pi->handle);
    Begin(BITMAPS);
    BitmapTransformA(pnA->n);
    BitmapTransformB(pnB->n);
    BitmapTransformC(pnC->n);
    BitmapTransformD(pnD->n);
    BitmapTransformE(pnE->n);
    BitmapTransformF(pnF->n);
    Vertex2f(400, 200);

    //restore things so cursor gets drawn correctly
    RestoreContext();
    FormatVertex(VERTEX_FORMAT_ONE);
}

void main()
{//RJA added this main function to act like Arduino
    setup();
    printf("Setup complete.\n");


    for (;;)
    {  



        loop();
        
        
    }
}




