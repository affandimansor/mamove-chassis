/* 
 * This is the cpp file of class Potentiometer.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 23 March 2021
 * Author: Muhammad Affandi Bin Mansor
 */
 
#include "Potentiometer.h"
#include "Arduino.h"


Potentiometer::Potentiometer (unsigned char AnalogPortPotentio){
	// Pass the input argument to a local variable
	// Here is not neccessary to define both pins as input with pinMode(), since it will be used by analogRead().
	// analogRead() is defined to treat its parameters/arguments as input port.
	mPinPotentio = AnalogPortPotentio;	// No need to write 'A0' etc. since we pass these both variable only to analogRead().
										// analogRead() that will use those arguments knows that we are referring to A0, A1 etc.
}

Potentiometer::~Potentiometer (){
	
}

void Potentiometer::setPotentioValue(){
	// Read the input analog value for X-positon from mPinPotentio
	// The mPinPotentio's value is then being converted from 10bit to 8bit
	mPotentioValue = map(analogRead(mPinPotentio),0,1023,0,255);
}



unsigned char Potentiometer::getPotentioValue(){
 setPotentioValue();
 //mjoystickPosX = map(analogRead(mPinX),0,1023,0,255);
 //mjoystickPosX = analogRead(mPinX);
 return mPotentioValue;
}
