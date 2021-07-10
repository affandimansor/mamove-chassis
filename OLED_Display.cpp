/* This is the cpp file of class OLED_Display.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 22 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */

#include "OLED_Display.h"
#include "Arduino.h"


OLED_Display::OLED_Display (){
  
};


OLED_Display::~OLED_Display (){
  
  };


float OLED_Display::getbatteryStatus()
{
  return batteryStatus;
};
