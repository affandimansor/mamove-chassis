/* 
 * This is the cpp file of class Potentiometer.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 23 March 2021
 * Author: Muhammad Affandi Bin Mansor
 */
 
#ifndef Potentiometer_h
#define Potentiometer_h

#include <Arduino.h>


class Potentiometer
{
  public:
  Potentiometer (unsigned char AnalogPortPotentio);	// The argument can be like 0 to max available pins on the board.
												// The function analogRead() which will use those arguments knows that we are referring to A0, A1 etc. See 'Using "Analog Pins" as parameter in Notebook. 
												// Use 'unsigned char'(1byte) instead of 'float'(4byte) to reduce the lag of data transmission due to 
												// different processing time required by the CPU for different data types
  ~Potentiometer ();
  unsigned char getPotentioValue();	// These functions give an access to the variable mPotentioValue from outside of this class.
									// If a class that needs this variable uses an 'extern' variable to store/access the same variable, then this get() are NOT needed.
									// The 'extern' variable of other class with exactly the same name as 'mPotentioValue' can access directly to these both variable.
									// But remember to include the .h file of this class in the other class that contains those extern variables.
							
  
  private:
  int mPinPotentio;				// Variable to hold and pass the Analog-Pin for potentiometer to other member functions.
								// This variable needs to be from the type 'integer' because it holds the analog values of Potentiometer from 0 up to 1023.
  unsigned char mPotentioValue;	// Class's member variable to hold the input analog value for potentiometer after mapping.
  void setPotentioValue();		// In this function where the mapping of potentiometer's values of 10-bit into Arduino 8-bit will take place. It will then be called by getPotentioValue.
};


#endif
