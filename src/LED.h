/* 
 * This is the h file of class LED.
 * This class doesn't belong to any superclass. It stands on its own.
 * Creator: Muhammad Affandi Bin Mansor, 25 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef LED_h
#define LED_h

#include <Arduino.h>
#include "Mower.h"

class LED
{
  public:
  LED(uint8_t d0);   //Constructor for a LED takes digital input port as parameter
  ~LED();
  void setLEDStatus(MOWER::ONOFF_Status LEDStatus);
  int getLEDStatus();
  void setBlinkLED();		// LED needs to be blinking instead of either only ON or OFF

  private:
  MOWER::ONOFF_Status mLEDStatus;	// Variable to set/return the LED status
  uint8_t mLEDPin1;					// Variable to assign pin number
  unsigned long mpreviousMillis;	// Variable for setBlinkLED()
  const long minterval=500;			// const won't change. Interval at which to blink (milliseconds)
									// It needs to be defined here instead in .cpp file, 
									// otherwise LED will not blink according to the required interval.
};

#endif
