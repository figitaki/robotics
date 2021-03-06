#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     seeker,         sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C2_1,     motorL,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorR,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorC,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorD,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 Autonomous ir test.c
 by: Gavin & Edward

 t = 0
 temp = 0

 1. Drive forward for time (t) basket
 2. Check for ir
   * If no IR then temp = t repeat to step 1
 4. drop block into the basket.
 5. Drive backwards for (temp) seconds
 6.

 **/


#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


void initializeRobot()
{
 servo[servo2] = 180;

  return;
}

task main()
{
  initializeRobot();

  int t = 250;
  int temp = 0;
  bool this = true;

  waitForStart(); // Wait for the beginning of autonomous phase

	while(this){
		motor[motorL] = 35;//Move motors forward for time (t).
		motor[motorR] = 30;
		wait1Msec(t);
		motor[motorL] = 0; //Stop motors.
		motor[motorR] = 0;
		wait1Msec(500);
		if (SensorValue[seeker] == 6 || SensorValue[seeker] == 5){
			motor[motorL] = 35;
			motor[motorR] = 30;
			if (temp > 5000)
				wait1Msec(400);
			motor[motorL] = 0;
			motor[motorR] = 0;
			servo[servo2] = 0;
			temp += t;
			this = false;
		} else {
			temp += t;
			t = 250;
		}
	}
	wait1Msec(1000);
	servo[Servo2] = 180;
	motor[motorL] = -30;
	motor[motorR] = -30;
	wait1Msec(temp - 750);
	motor[MotorL] = 0;
	motor[MotorR] = 0;
}

