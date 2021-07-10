/* 
 * This is the cpp file of class Joystick.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 22 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#include "Joystick.h"
#include "Arduino.h"


Joystick::Joystick (unsigned char AnalogPortX, unsigned char AnalogPortY){
	// Pass both arguments to the local variables
	// Here is not neccessary to define both pins as input with pinMode(), since it will be used by analogRead().
	// analogRead() is defined to treat its parameters/arguments as input port.
	mPinX = AnalogPortX;	// No need to write 'A0' etc since we pass these both variable only to analogRead().
	mPinY = AnalogPortY;	// analogRead() that will use those arguments knows that we are referring to A0, A1 etc.

}

Joystick::~Joystick (){
	
}

void Joystick::setjoystickPosX(){
	// Read the input analog value for X-positon from mPinX
	// The mPinX's value is then being converted from 10bit to 8bit
	mjoystickPosX = map(analogRead(mPinX),0,1023,0,255);
}

void Joystick::setjoystickPosY(){
	// Read assign the input analog value for Y-positon from mPinY
	// The mPinY's value is then being converted from 10bit to 8bit
	mjoystickPosY = map(analogRead(mPinY),0,1023,0,255);
}


unsigned char Joystick::getjoystickPosX(){
 setjoystickPosX();
 //mjoystickPosX = map(analogRead(mPinX),0,1023,0,255);
 //mjoystickPosX = analogRead(mPinX);
 return mjoystickPosX;
}

unsigned char Joystick::getjoystickPosY(){
 setjoystickPosY();
 //mjoystickPosY = map(analogRead(mPinY),0,1023,0,255);
 //mjoystickPosY = analogRead(mPinY);
 return mjoystickPosY;
}