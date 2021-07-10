/* This is the cpp file of class Switch.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 24 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#include "Arduino.h"
#include "Switch.h"
#include "Mower.h"
#include "LED.h"    // Is required because we have an object from class LED here


Switch::Switch (uint8_t d0) : mLED1(0)  // See comments in below
{ 
  // Constructor for a object mLED1 is being initialized by using method member initialization.
  // The constructor of the object mLED1 needs to be initialized here eventhough we do not need a LED.
  // Even if an object of class LED doesn't need an input parameter, we still need to initialize this object's constructor here.
  // Otherwise an error message will pop out.
  
  mSwitchPin1 = d0;  			// Assign the digital port to a local SwitchPin1 variable
  museLED = false;				// Set variable to FALSE
  pinMode(mSwitchPin1, INPUT);	// Define mSwitchPin1 as input port
  
}


Switch::Switch (uint8_t d0, uint8_t LED_port) : mLED1(LED_port){ 

  // Constructor for object mLED1 is called by using method member initialization.
  // When calling the Switch's constructor, no need to write :mLED1,
  // instead just write everything in Switch's constructor. 
  // LED_port from the Switch's constructor will be passed automatically by the compiler into the mLED1's constructor
  
  mSwitchPin1 = d0;  			// Assign the digital port to a local SwitchPin1 variable
  museLED = true;				// Set variable to TRUE
  
  pinMode(mSwitchPin1, INPUT);	// Define mSwitchPin1 as input port
}


/*
Switch::Switch(uint8_t d0, uint8_t LED_port){ 

  // Constructor for object mLED1 is called by using method member initialization.
  // When calling the Switch's constructor, no need to write :mLED1,
  // instead just write everything in Switch's constructor. 
  // LED_port from the Switch's constructor will be passed by the compiler into the mLED1's constructor
  
  mSwitchPin1 = d0;     // Assign the digital port to a local SwitchPin1 variable
  LED mLED1(LED_port);  // Assign port to the object of class LED
  museLED = true;       // Set variable to TRUE
  
  pinMode(mSwitchPin1, INPUT);  // Define mSwitchPin1 as input port
}
*/

Switch::~Switch (){
  
}


void Switch::setSwitchStatus(){
  int switchStatus = digitalRead(mSwitchPin1);
  if (switchStatus == HIGH)
  {
	mSwitchState = MOWER::ON;				// Set the value of mSwitchState to ON, when mSwitchPin1 is HIGH
	if (museLED == true)
	{
		mLED1.setLEDStatus(mSwitchState);	// Turn on LED. This function should be defined as public in the class LED
	};
  }
	
  else										// For the case mSwitchPin1 == LOW
  {
	mSwitchState = MOWER::OFF;				// Set the value of mSwitchState to OFF, when mSwitchPin1 is LOW
	if (museLED == true)
	{
		mLED1.setLEDStatus(mSwitchState);	// Turn off LED. This function should be defined as public in the class LED
	}
  }
}

int Switch::getSwitchStatus()
{
  return mSwitchState;
}

int Switch::getSwitchLEDStatus()
{
   // Function is needed in order to get the LED status. 
   // An object of class Switch cannot directly access the functions in the class LED 
   // because the class Switch doesn't inherit from the class LED
                              
  return mLED1.getLEDStatus();
}
