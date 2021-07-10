/* This sketch acts as an interface for class Chassis.
 * All objects of subclasses will be created in this sketch.
 * 
 * 
 */


#include <OLED_Display.h>
#include <Joystick.h>
#include <Switch.h>
#include <Motor.h>
#include <CutterMotor.h>
#include <ChassisMotor.h>
#include <LED.h>
#include <Mower.h>
#include "NRF24L01_chassis.h"  // 'NRF24L01_chassis.h' needs to be placed inside an individual folder, otherwise an error always pops out here when we compile this sketch


// Create object and assign their port on Arduino
LED green(3);
LED yellow(4);
//Joystick joystick1(0,1);
CutterMotor cuttermotor1(6,7,8,9);
ChassisMotor chassismotor1(30,31,4,true,32);
ChassisMotor chassismotor2(40,41,13,false,42);


// ----- Set Radio communication -----
#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  3   // 3 unsigned chars TX payload

unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = 
{
    0x34,0x43,0x10,0x10,0x01
}; 
unsigned char RX_ADDRESS[TX_ADR_WIDTH]  = 
{
  0x34,0x43,0x10,0x10,0x01
};
 
unsigned char rx_buf[TX_PLOAD_WIDTH] = {0}; // initialize value
unsigned char tx_buf[TX_PLOAD_WIDTH] = {0};


// ----- Define local variable to be passed around -----
/* 
 * Assign the output from 'getjoystickPosX/-Y' to local variables 'JoystickPosX/-Y' because these variables
 * were declared as "extern" variable in the class ChassisMotor.
 * If both variables are not defined here, then setChassisMotorOperation will not work.
*/
unsigned char JoystickPosX;
unsigned char JoystickPosY;

// Same as the case above. This "CutterMotorSpeed" has been declared as "extern" variable in the class CutterMotor
unsigned char CutterMotorSpeed; 

// Variable for cutter switch's status
unsigned char cutterswitchStatus;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NRF_Init();                        // Initialize IO     
  NRF_SetRxMode();
  Serial.println("RX_Mode start...");
}

void loop() {
  // put your main code here, to run repeatedly:
  
/*
// Turn both LEDs on
Serial.println("Green LED: On");
green.setLEDStatus(MOWER::ON);
//green.setBlinkLED();
Serial.print("Green LED Status: ");
Serial.println(green.getLEDStatus());
delay(500);

Serial.println("Yellow LED: On");
yellow.setLEDStatus(MOWER::ON);
//yellow.setBlinkLED(); 
Serial.print("Yellow LED Status: ");
Serial.println(yellow.getLEDStatus());
delay(500);


// Turn both LEDs off
Serial.println("Green LED: Off");
green.setLEDStatus(MOWER::OFF);
Serial.print("Green LED Status: ");
Serial.println(green.getLEDStatus());;
//delay(500);

Serial.println("Yellow LED: On");
yellow.setLEDStatus(MOWER::OFF);
Serial.print("Yellow LED Status: ");
Serial.println(yellow.getLEDStatus());
//delay(500);
*/

//+++ Input objects +++
// Inputs that come in through the radio communication
NRF_SetRxMode();
    if(NRF_Receive(rx_buf))
    {
        JoystickPosX = rx_buf[0];
        Serial.print("RX = ");
        Serial.println(JoystickPosX);
        JoystickPosY = rx_buf[1];
        Serial.print("RY = ");
        Serial.println(JoystickPosY);
        cutterswitchStatus = rx_buf[2];
        Serial.print("Cutter Switch = ");
        Serial.println(cutterswitchStatus);
        //for(int i = 0; i < 3; i++)
        //{
           // Serial.print(rx_buf[i]);
           // Serial.print(",");
       // }
        Serial.println("hehe. TAMMAT");
        //for(int i = 0; i < 3; i++)
           // rx_buf[i] = 0;  
    }  

//+++ Output Objects +++
// ----- ChassisMotor -----
// Motor1
chassismotor1.setChassisMotorOperation();
//chassismotor1.setChassisMotorOperation(JoystickPosX, JoystickPosY);
Serial.print("Motor1 Status:  ");
Serial.println(chassismotor1.getMotorStatus());
Serial.print("Motor1 Direction:  ");
Serial.println(chassismotor1.getMotorDirection());
Serial.print("Motor1_LED Status:  ");
Serial.println(chassismotor1.getMotorLEDStatus());
// To troubleshoot the problem with the M1's motor speed
Serial.print("--->Motor1 RADIUS:  ");
Serial.println(chassismotor1.radius);
Serial.print("--->Motor1 TETA:  ");
Serial.println(chassismotor1.teta);
Serial.print("--->Motor1 a:  ");
Serial.println(chassismotor1.a);
Serial.print("--->Motor1 b:  ");
Serial.println(chassismotor1.b);
Serial.print("--->Motor1 Speed:  ");
Serial.println(chassismotor1.motorspeed);


// Motor2
chassismotor2.setChassisMotorOperation();
//chassismotor2.setChassisMotorOperation(JoystickPosX, JoystickPosY);
Serial.print("Motor2 Status:  ");
Serial.println(chassismotor2.getMotorStatus());
Serial.print("Motor2 Direction:  ");
Serial.println(chassismotor2.getMotorDirection());
Serial.print("Motor2_LED Status:  ");
Serial.println(chassismotor2.getMotorLEDStatus());
// To troubleshoot the problem with the M1's motor speed
Serial.print("--->Motor2 RADIUS:  ");
Serial.println(chassismotor2.radius);
Serial.print("--->Motor2 TETA:  ");
Serial.println(chassismotor2.teta);
Serial.print("--->Motor2 a:  ");
Serial.println(chassismotor2.a);
Serial.print("--->Motor2 b:  ");
Serial.println(chassismotor2.b);
Serial.print("--->Motor2 Speed:  ");
Serial.println(chassismotor2.motorspeed);


// ----- CutterMotor -----
//switchcutter.setSwitchStatus();
//cutterswitchStatus = switchcutter.getSwitchStatus();  //<-- Should come from the controller over radio communication
Serial.print("Cutter_Switch Status: ");
Serial.println(cutterswitchStatus);

if(cutterswitchStatus == MOWER::ON)
{
  CutterMotorSpeed = 125;
  cuttermotor1.setCutterOperation(MOWER::FORWARD);
  Serial.print("Cutter spinning direction: ");
  Serial.println(cuttermotor1.getMotorDirection());
}

else // (cutterswitchStatus == MOWER::OFF)
{
  CutterMotorSpeed = 0;
  cuttermotor1.setCutterOperation(MOWER::NEUTRAL);
  Serial.print("Cutter spinning direction: ");
  Serial.println(cuttermotor1.getMotorDirection());
}

}
