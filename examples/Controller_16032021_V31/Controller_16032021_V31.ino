/* This sketch acts as an interface for class Controller.
 * All objects of subclasses will be created in this sketch.
 * 
 * 
 */


#include <OLED_Display.h>
#include <Joystick.h>
#include <Switch.h>
#include <Potentiometer.h>
#include <Motor.h>
#include <CutterMotor.h>
#include <ChassisMotor.h>
#include <LED.h>
#include <Mower.h>
#include "NRF24L01_controller.h"  // 'NRF24L01_controller.h' needs to be placed inside an individual folder, otherwise an error always pops out here when we compile this sketch



// Create object and assign their port on Arduino
//LED green(3);
//LED yellow(4);

Joystick joystick1(1,0);
Switch switchcontroller(2);
Switch switchcutter(3); // Digital pin
Switch switchautoforward(4);  // Digital pin
Potentiometer potentiocutter(3);// Analog pin
LED switchcontrollerLED(5);
LED switchcutterLED(6);
LED switchautoforwardLED(7);

// ----- Set Radio communication -----
//#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
//#define TX_PLOAD_WIDTH  5   // 5 unsigned chars TX payload

unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = 
{
    0x34,0x43,0x10,0x10,0x01
}; 
unsigned char RX_ADDRESS[TX_ADR_WIDTH]  = 
{
  0x34,0x43,0x10,0x10,0x01
};
 
unsigned char rx_buf[TX_PLOAD_WIDTH] = {0}; // Initialize value
unsigned char tx_buf[TX_PLOAD_WIDTH] = {0};


// ----- Define local variable to be passed around -----
/* 
 * Assign the output from 'getjoystickPosX/-Y' to local variables 'JoystickPosX/-Y' because these variables
 * were declared as "extern" variable in the class ChassisMotor.
 * If both variables are not defined here, then setChassisMotorOperation will not work.
*/
unsigned char JoystickPosX; //Use 'unsigned char'(1byte) instead of 'float'(4byte) to reduce the lag of data transmission due to different processing time required by the CPU for different data types
unsigned char JoystickPosY; //Use 'unsigned char'(1byte) instead of 'float'(4byte) to reduce the lag of data transmission due to different processing time required by the CPU for different data types
unsigned char autoforwardswitchStatus;

// Variable for cutter switch's status
unsigned char cutterswitchStatus;
unsigned char cutterSpeed;

/**********************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NRF_Init();                        // Initialize IO port
  Serial.println("TX_Mode Start");    
  switchcontroller.setSwitchLED(&switchcontrollerLED);  //Set LED as an indicator for controller's switch
  switchcutter.setSwitchLED(&switchcutterLED);  //Set LED as an indicator for cutter's switch
  switchautoforward.setSwitchLED(&switchautoforwardLED);  //Set LED as an indicator for autoforward's switch
}

void loop() {
  // put your main code here, to run repeatedly:
/*
// Turn both LEDs on
Serial.println("Green LED: On");
green.setLEDStatus(MOWER::ON);
Serial.print("Green LED Status: ");
Serial.println(green.getLEDStatus());
delay(500);

Serial.println("Yellow LED: On");
yellow.setLEDStatus(MOWER::ON);
Serial.print("Yellow LED Status: ");
Serial.println(yellow.getLEDStatus());
delay(500);


// Turn both LEDs off
Serial.println("Green LED: Off");
green.setLEDStatus(MOWER::OFF);
Serial.print("Green LED Status: ");
Serial.println(green.getLEDStatus());;
delay(500);

Serial.println("Yellow LED: On");
yellow.setLEDStatus(MOWER::OFF);
Serial.print("Yellow LED Status: ");
Serial.println(yellow.getLEDStatus());
delay(500);
*/
if(switchcontroller.getSwitchStatus() == MOWER::ON) // The controller will only function if it's turned on
{
   NRF_SeTxMode();
  
  //+++ Input objects +++
  // ------ Joystick -----
  // Both variables need to be called at the beginning of loop, so their value will be updated before they are being passed around
  JoystickPosX = joystick1.getjoystickPosX(); //<-- To be transmitted over radio communication to chassis!!!
  JoystickPosY = joystick1.getjoystickPosY(); //<-- To be transmitted over radio communication to chassis!!!
  //tx_buf[0] = joystick1.getjoystickPosX(); <-- NO reduction of processing time can be proven if the array's element is assigned directly here instead of using the Zwischenvariable(JoystickPosX)
  //tx_buf[1] = joystick1.getjoystickPosY(); <-- NO reduction of processing time can be proven if the array's element is assigned directly here instead of using the Zwischenvariable(JoystickPosY)
  //JoystickPosX = map(analogRead(joystick1.getjoystickPosX()),0,1023,0,255); <-- NO reduction of processing time can be proven if this mapping process takes place here instead in the class Joystick
  //JoystickPosY = map(analogRead(joystick1.getjoystickPosY()),0,1023,0,255); <-- NO reduction of processing time can be proven if this mapping process takes place here instead in the class Joystick
  
  Serial.print("JoystickPos-> X: ");
  Serial.print(JoystickPosX);
  Serial.print("    Y:  ");
  Serial.println(JoystickPosY);
  
  switchautoforward.setSwitchStatus();
  autoforwardswitchStatus = switchautoforward.getSwitchStatus();
  Serial.print("Autoforward status: ");
  Serial.println(autoforwardswitchStatus);
  
  // ----- CutterMotor -----
  switchcutter.setSwitchStatus();
  cutterswitchStatus = switchcutter.getSwitchStatus();  //<-- To be transmitted over radio communication to chassis!!!
  Serial.print("Cutter_Switch Status: ");
  Serial.println(cutterswitchStatus);
  cutterSpeed = potentiocutter.getPotentioValue(); 
  Serial.print("Potentimeter value: ");
  Serial.println(cutterSpeed);
  Serial.print("Switch cutter's LED status: ");
  Serial.println(switchcutter.getSwitchLEDStatus());
  /*
  //Test for passing pointer object as input argument
  cutterSwitchLED.setSwitchIndicator(&switchcutter);
  Serial.println("Switch LED:" );
  //Serial.println(cutterSwitchLED.setSwitchIndicator(&switchcutter));
  */
  //+++ Output objects +++
  // Data to be transmitted over the radio communication 
    tx_buf[0] = JoystickPosX;//map(analogRead(JoyStick_X_PIN), 0, 1023, 0, 255);
    tx_buf[1] = JoystickPosY;//map(analogRead(JoyStick_Y_PIN), 0, 1023, 0, 255);
    tx_buf[2] = autoforwardswitchStatus;
    tx_buf[3] = cutterswitchStatus;
    tx_buf[4] = cutterSpeed;//potentiocutter.getPotentioValue();
    /*Serial.println("-----------");
    Serial.print("x:");
    Serial.println(tx_buf[0]);
    Serial.print("y:");
    Serial.println(tx_buf[1]);
    */
      do{
          NRF_Send(tx_buf);
          //Serial.println("Information sent");
          
      }
   while(!NRF_CheckAck());
}
}
