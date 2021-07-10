/* This sketch acts as an interface for class Controller.
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
#include "NRF24L01_controller.h"  // 'NRF24L01_controller.h' needs to be placed inside an individual folder, otherwise an error always pops out here when we compile this sketch



// Create object and assign their port on Arduino
//LED green(3);
//LED yellow(4);
Joystick joystick1(0,1);
CutterMotor cuttermotor1(6,7,8,9);
ChassisMotor chassismotor1(30,31,4,true,32);
ChassisMotor chassismotor2(40,41,13,false,42);
Switch switchcutter(50,51);

// Set Radio communication
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
float JoystickPosX;
float JoystickPosY;

// Same as the case above. This "CutterMotorSpeed" has been declared as "extern" variable in the class CutterMotor
float CutterMotorSpeed = 0; 

// Variable for cutter switch's status
int cutterswitchStatus;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NRF_Init();                        // Initialize IO port
  Serial.println("TX_Mode Start");    
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
 NRF_SeTxMode();

//+++ Input objects +++
// ------ Joystick -----
// Both variables need to be called at the beginning of loop, so their value will be updated before they are being passed around 
JoystickPosX = joystick1.getjoystickPosX(); //<-- To be transmitted over radio communication to chassis!!!
JoystickPosY = joystick1.getjoystickPosY(); //<-- To be transmitted over radio communication to chassis!!!
Serial.print("JoystickPos-> X: ");
Serial.print(JoystickPosX);
Serial.print("    Y:  ");
Serial.println(JoystickPosY);


//+++ Output Objects +++
/*
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
*/


// ----- CutterMotor -----
switchcutter.setSwitchStatus();
cutterswitchStatus = switchcutter.getSwitchStatus();  //<-- To be transmitted over radio communication to chassis!!!
Serial.print("Cutter_Switch Status: ");
Serial.println(cutterswitchStatus);


// Data to be transmitted over the radio communication 
  tx_buf[0] = 15;//map(analogRead(JoyStick_X_PIN), 0, 1023, 0, 255);
  tx_buf[1] = 20;//map(analogRead(JoyStick_Y_PIN), 0, 1023, 0, 255);
  tx_buf[2] = 100;
  Serial.println("-----------");
  Serial.print("x:");
  Serial.println(tx_buf[0]);
  Serial.print("y:");
  Serial.println(tx_buf[1]);
    do{
        NRF_Send(tx_buf);
    }
 while(!NRF_CheckAck());
}
