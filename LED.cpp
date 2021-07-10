/* 
 * This is the h file of class LED.
 * This class doesn't belong to any superclass. It stands on its own.
 * Creator: Muhammad Affandi Bin Mansor, 25 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */

#include <Arduino.h>
#include "Mower.h"
#include "LED.h"


LED::LED(uint8_t d0)
{
	mLEDPin1 = d0;
	mLEDStatus = MOWER::OFF;	// Set LED to off when an object of this class is created
	pinMode(mLEDPin1, OUTPUT);	// Assign port as output port
	
	// ----- Initialize variable to be used in setBlinkLED();
	// Generally, you should use "unsigned long" for variables that hold time
	// The value will quickly become too large for an int to store
	unsigned long mpreviousMillis = 0;        // will store last time LED was updated
	// constants won't change:
	//const long minterval = 1000;           // interval at which to blink (milliseconds)
}


LED::~LED()
{

}


void LED::setBlinkLED()	// Function is copied from https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
{
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - mpreviousMillis >= minterval) 
  {
	  // save the last time you blinked the LED
	  mpreviousMillis = currentMillis;
		  // if the LED is off turn it on and vice-versa:
		  if (mLEDStatus == MOWER::OFF) 
		  {
			 digitalWrite(mLEDPin1, HIGH);
			 mLEDStatus = MOWER::ON;
		  } 
		  else 
		  {
			digitalWrite(mLEDPin1, LOW);
			mLEDStatus = MOWER::OFF;
		  }
	}
}
  
  
void LED::setLEDStatus(MOWER::ONOFF_Status LEDStatus)
{
	mLEDStatus = LEDStatus;
	if (mLEDStatus == MOWER::ON)
	{
			digitalWrite(mLEDPin1, HIGH);
	}
	
	else	//mLEDStatus == MOWER::ONOFF_Status::OFF
	{
		digitalWrite(mLEDPin1, LOW);
	}
	
}


unsigned char LED::getLEDStatus()
{
	return mLEDStatus;
}
