/* This sketch acts as an interface for class Chassis.
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
#include <CombineMotor.h>
#include "NRF24L01_chassis.h"  // 'NRF24L01_chassis.h' needs to be placed inside an individual folder, otherwise an error always pops out here when we compile this sketch


// Create object and assign their port on Arduino
LED green(3);
LED yellow(4);
//Joystick joystick1(0,1);
//+++++ Initiate objects when LED was not defined as a pointer object in each respective class +++++
//CutterMotor cuttermotor1(6,7,8,9);
//ChassisMotor chassismotor1(30,31,4,true,32);
//ChassisMotor chassismotor2(40,41,13,false,42);

//+++++ Initiate objects when LED has been defined as a pointer object in each respectice class +++++
//CutterMotor cuttermotor1(6,7,8);
//ChassisMotor chassismotor1(30,31,4,true);
//ChassisMotor chassismotor2(40,41,13,false);
//LED cutterLED(9);
//LED chassisLED1(32);
//LED chassisLED2(42);

//+++++ Initiate objects when LED has been defined as a pointer object in each respectice class +++++
CutterMotor cuttermotor1(6,7,8);
ChassisMotor chassismotor1(30,31,4);
ChassisMotor chassismotor2(40,41,13);
CombineMotor combinemotor();  // Create an object of class combine motor
LED cutterLED(9);
LED chassisLED1(32);
LED chassisLED2(42);
LED forwardLED(28); // LED will indicate chassis moves forward
LED reverseLED(29); // LED will indicate chassis moves backward/reverse

// ----- Set Radio communication -----
#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  4   // 4 unsigned chars TX payload

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
  cuttermotor1.setMotorLED(&cutterLED);
  chassismotor1.setMotorLED(&chassisLED1);
  chassismotor2.setMotorLED(&chassisLED2);
  combinemotor.setChassisMotor(&chassismotor1, &chassismotor2);
  combinemotor.setChassisLED(
}

void loop() {
  // put your main code here, to run repeatedly:
  
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
        CutterMotorSpeed = rx_buf[3];
        Serial.print("Cutter Potentiometer = ");
        Serial.println(CutterMotorSpeed);
        //for(int i = 0; i < 3; i++)
        //{
           // Serial.print(rx_buf[i]);
           // Serial.print(",");
       // }
        Serial.println("hehe. TAMMAT");
        //for(int i = 0; i < 3; i++)
           // rx_buf[i] = 0;  
    }  
//green.setMotorIndicator(&chassismotor1);
//+++ Output Objects +++
/*
// ----- Test LEDs -----
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


/* To test if the lag to turn on repective LEDs for each motor is due to the object mLED, which is created 
 * INSIDE the class Motor instead of creating the object mLED here and 
 * assign its address to the repective motors
 * Result --> NO reduction of time lagging when turning on the LEDs can be proven if the objects of class LED
 *            is created here.
*/
/* 
//start of testing LED's time lagging test
if(JoystickPosX > 127)
{
  Serial.println("Green LED: On");
  green.setLEDStatus(MOWER::ON);
  Serial.print("Green LED Status: ");
  Serial.println(green.getLEDStatus());
  
  Serial.println("Yellow LED: Off");
  yellow.setLEDStatus(MOWER::OFF);
  Serial.print("Yellow LED Status: ");
  Serial.println(yellow.getLEDStatus());
}

else if (JoystickPosX < 125)
{
  Serial.println("Green LED: Off");
  green.setLEDStatus(MOWER::OFF);
  Serial.print("Green LED Status: ");
  Serial.println(green.getLEDStatus());
  
  Serial.println("Yellow LED: On");
  yellow.setLEDStatus(MOWER::ON);
  Serial.print("Yellow LED Status: ");
  Serial.println(yellow.getLEDStatus());
}

else // For the case when joystick is untouched
{
  Serial.println("Green LED: Off");
  green.setLEDStatus(MOWER::OFF);
  Serial.print("Green LED Status: ");
  Serial.println(green.getLEDStatus());
  
  Serial.println("Yellow LED: OFF");
  yellow.setLEDStatus(MOWER::OFF);
  Serial.print("Yellow LED Status: ");
  Serial.println(yellow.getLEDStatus());
}
//end of testing LED's time lagging test
*/


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
Serial.print("--->Motor1 joystickX:  ");
Serial.println(chassismotor1.joyX);
Serial.print("--->Motor1 joystickY:  ");
Serial.println(chassismotor1.joyY);

Serial.print("--->Motor1 RADIUS:  ");
Serial.println(chassismotor1.radius);
Serial.print("--->Motor1 TETA:  ");
Serial.println(chassismotor1.teta);
/*
Serial.print("--->Motor1 a:  ");
Serial.println(chassismotor1.a);
Serial.print("--->Motor1 b:  ");
Serial.println(chassismotor1.b);
*/
Serial.print("--->Motor1 Speed:  ");
Serial.println(chassismotor1.mMotorspeed);


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
Serial.print("--->Motor2 joystickX:  ");
Serial.println(chassismotor2.joyX);
Serial.print("--->Motor2 joystickY:  ");
Serial.println(chassismotor2.joyY);

Serial.print("--->Motor2 RADIUS:  ");
Serial.println(chassismotor2.radius);
Serial.print("--->Motor2 TETA:  ");
Serial.println(chassismotor2.teta);
/*
Serial.print("--->Motor2 a:  ");
Serial.println(chassismotor2.a);
Serial.print("--->Motor2 b:  ");
Serial.println(chassismotor2.b);
*/
Serial.print("--->Motor2 Speed:  ");
Serial.println(chassismotor2.mMotorspeed);


// ----- CutterMotor -----
//switchcutter.setSwitchStatus();
//cutterswitchStatus = switchcutter.getSwitchStatus();  //<-- Should come from the controller over radio communication
Serial.print("Cutter_Switch Status: ");
Serial.println(cutterswitchStatus);
Serial.print("Cutter motor speed: ");
Serial.println(CutterMotorSpeed);
cuttermotor1.setCutterOperation(cutterswitchStatus);
Serial.print("Cutter spinning direction: ");
Serial.println(cuttermotor1.getMotorDirection());
/*
if(cutterswitchStatus == MOWER::ON)
{
  //CutterMotorSpeed = 125;
  //cuttermotor1.setCutterOperation(MOWER::FORWARD);
  Serial.print("Cutter spinning direction: ");
  Serial.println(cuttermotor1.getMotorDirection());
}

else // (cutterswitchStatus == MOWER::OFF)
{
  //CutterMotorSpeed = 0;
  cuttermotor1.setCutterOperation(MOWER::NEUTRAL);
  Serial.print("Cutter spinning direction: ");
  Serial.println(cuttermotor1.getMotorDirection());
}
*/

}
