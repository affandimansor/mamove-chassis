/* 
 * This is the .h file of of numspace MOWER.
 * This numspace holds various enumerator that define states/infos of various components used in this project
 * Creator: Muhammad Affandi Bin Mansor, 24 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */

 #ifndef Mower_h
 #define Mower_h

 #include <Arduino.h>
 
 namespace MOWER {

 enum MotorStatus{
  STOP = 0,
  RUN = 1
  };

 enum MotorDirection{
  NEUTRAL = 0,		// To be used when motor stops turning
  FORWARD = 1,
  REVERSE = 2
 };

 enum ONOFF_Status{
  OFF = 0,
  ON = 1
 };

 enum Transceiver{
	CONTROLLER = 0,
	CHASSIS = 1
 };

  
 }

#endif
