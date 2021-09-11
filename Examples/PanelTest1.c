#include "../Antares/Antares.h"   //RJA implementing this gd2-lib code using Matrix Orbital's EVE driver

//RJA:  This example explores using the mouse to interact with widgets


#include "Panels.h"  //The panels interface code
#include "Panel1.h"  //Test panel





void setup()
{
  begin();

  InitPanels(&Panel1);  //Start up panels interface with Panel1 showing


}

void loop()
{  
    PanelLoop();  //show panel and interact with mouse
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




