/* 
 * This is the cpp file of class OLED_Display.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 22 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef OLED_Display_h
#define OLED_Display_h

#include "Arduino.h"

class OLED_Display
{
  private:
  OLED_Display ();
  ~OLED_Display ();
  float batteryStatus;

  public:
  float getbatteryStatus();
  
};


#endif
