#include "NRF24L01_mower.h"
#include "Mower.h"

#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  4   // 4 unsigned chars TX payload

// Joystick Declaration
int joyVert = A0; 
int joyHorz = A1;

// Variable fuer Schalter
int switchVal; 

// Joystick Values - Start at 512 (middle position)
 
int joyposVert = 512; 
int joyposHorz = 512;
  
unsigned char TX_ADDRESS[TX_ADR_WIDTH]  = 
{
    0x34,0x43,0x10,0x10,0x01
}; 
unsigned char rx_buf[TX_PLOAD_WIDTH] = {0}; // initialize value
unsigned char tx_buf[TX_PLOAD_WIDTH] = {0};

void setup()
{
    Serial.begin(9600);

    NRF_OperationMode(MOWER::Transceiver::CONTROLLER); 
    NRF_Init();
    Serial.println("TX_Mode Start");   

     // Set initial motor direction (static)
     // tx_buf[2] = 2; 
}

void loop()
{
  
  NRF_SeTxMode();
  // Read Joystick values and map to values of 0 - 255
  Serial.println("Reading motorcontrol values");

  // Read the Joystick X and Y positions
  joyposVert = analogRead(joyVert); 
  joyposHorz = analogRead(joyHorz);

  //switchVal = digitalRead(Schalter);

Serial.print("TX= ");
Serial.print (tx_buf[0] = 3);
Serial.print (",");
Serial.println (tx_buf[1] = 2);

  // Determine if this is a forward or backward motion
  // Do this by reading the Verticle Value
  // Apply results to MotorSpeed and to Direction
  /*
  if (switchVal == HIGH)
  {
    tx_buf[3] = 1;
  }
  else
  {
    tx_buf[3] = 0;
  }

  if (joyposVert < 460)
  {
    // This is Backward
    // Set Motors backward
    tx_buf[2] = 1;

    //Determine Motor Speeds
    // As we are going backwards we need to reverse readings
    tx_buf[0] = map(joyposVert, 460, 0, 0, 255);
    tx_buf[1] = map(joyposVert, 460, 0, 0, 255);
  }
     else if (joyposVert > 564 )
  {
    // This is Forward
    // Set Motors forward
    tx_buf[2] = 0;

    //Determine Motor Speeds
    tx_buf[0] = map(joyposVert, 564, 1023, 0, 255);
    tx_buf[1] = map(joyposVert, 564, 1023, 0, 255); 
  }
  else
  {
    // This is Stopped
    tx_buf[0] = 0;
    tx_buf[1] = 0;
    tx_buf[2] = 2; 
   }
   */
   do {
        NRF_Send(tx_buf);
      }
 while(!NRF_CheckAck());
}
