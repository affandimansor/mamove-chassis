/* 
 * This is the cpp file of class Switch.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 24 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef Switch_h
#define Switch_h

#include <Arduino.h>
#include "LED.h"
#include "Mower.h"

class  Switch
{

  public:
  Switch (uint8_t d0);  // Constructor for 3 pin switch without LED
  Switch (uint8_t d0, uint8_t LED_port); 	// Constructor for 3 pin switch with a LED as status indicator
  ~Switch ();
  void setSwitchStatus();
  int getSwitchStatus();
  int getSwitchLEDStatus();   // Function is to be used in order to get the status of LED used by the switch


  private:
  int mSwitchPin1;
  MOWER::ONOFF_Status mSwitchState;
  bool museLED;		// Variable is used to indicate LED is being used along with a switch in another functions of this class
  LED mLED1;		  // Create an object from class LED in order to use a Switch with a LED as status indicator
 

};


#endif
