/* 
 * This is the cpp file of class Joystick.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 22 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>

/* No need to use this define-Method to assign the Analog-Pins 
//------------------------------------------------------------------------------------------------
#define portPosX	A0		// Analog port as input for joystick's X-position
#define portPosY	A1		// Analog port as input for joystick's Y-position
//------------------------------------------------------------------------------------------------
*/

class Joystick
{
  public:
  Joystick (int AnalogPortX, int AnalogPortY);	// Both arguments can be like 0 to max available pins on the board.
												// The function analogRead() that will use those arguments knows that we are referring to A0, A1 etc.
												// See 'Using "Analog Pins" as parameter in Notebook. 
  ~Joystick ();
  float getjoystickPosX();	// These functions give an access to the variable mjoystickPosX and mjoystickPosY from outside of this class.
  float getjoystickPosY();	// If a class that needs this variable use an extern variable to store/access the same variable, then this get() are NOT needed.
							// The extern variable from other class with exactly the same name as mjoystickPosX;mjoystickPosY can access directly to these both variables.
							// But remember to include the .h file of this class in the other class that contains those extern variables.

  private:
  int mPinX;				      // Variable to hold and pass the Analog-Pin for joystick's X-position to other member functions
  int mPinY;				      // Variable to hold and pass the Analog-Pin for joystick's Y-position to other member functions
  float mjoystickPosX;		// Class's member variable to hold the input analog value for X-position
  float mjoystickPosY;		// Class's member variable to hold the input analog value for Y-position
  void setjoystickPosX();	// Function will be called by getjoystickPosX;
  void setjoystickPosY();	// Function will be called by getjoystickPosY;
};


#endif
