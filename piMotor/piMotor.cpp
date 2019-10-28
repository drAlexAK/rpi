#include <piMotor.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
/*//// const BCM
int PWMA1 =  6;
int PWMA2 = 13;
int PWMB1 = 20;
int PWMB2 = 21;
int D1    = 12;
int D2    = 26;
//// const wiringPi
int PWMA1 = 22;
int PWMA2 = 23;
int PWMB1 = 28;
int PWMB2 = 29;
int D1    = 26;
int D2    = 25;
*/
// physical pins
#define PWMR1  31
#define PWMR2  33
#define PWML1  38
#define PWML2  40
#define PWMR  32
#define PWML  37
// const
#define PWMLimit 100

// sets motor direction
void piMotor::motorSet(int a1, int a2, int b1, int b2){
digitalWrite(PWMR1, a1);
digitalWrite(PWMR2, a2);
digitalWrite(PWML1, b1);
digitalWrite(PWML2, b2);
}
// Creates piMotor object
// max voltage limit, percentages
// min value = 1
// max value = 100
#define BORDERS_POWER MAX_MOTOR_POWER_LIMIT - MIN_MOTOR_POWER_LIMIT

// Initializes settings
void piMotor::Init(){
if (wiringPiSetupPhys() == -1) throw std::runtime_error("Cannot initilize wiringPi.");

	pinMode(PWMR1, OUTPUT);
	pinMode(PWMR2, OUTPUT);
	pinMode(PWML1, OUTPUT);
	pinMode(PWML2, OUTPUT);

	pinMode(PWMR, PWM_OUTPUT);
	pinMode(PWML, PWM_OUTPUT);

	softPwmCreate(PWMR, 0, PWMLimit);
	softPwmCreate(PWML, 0, PWMLimit);
}

piMotor::piMotor(uint _min_limit , uint _max_limit ){
	 minMotorPowerLimit = _min_limit;
	 maxMotorPowerLimit = _max_limit;
}
// sets directions
void piMotor::Left(){
	motorSet(0, 1, 1, 0);
}
void piMotor::Right(){
	motorSet(1, 0, 0, 1);
}
void piMotor::Stop() {
	motorSet(0, 0, 0, 0);
}
void piMotor::Forward(){
	motorSet(1, 0, 1, 0);
}
void piMotor::Backward(){
	motorSet(0, 1, 0, 1);
}

// sets speed for left motor
// min 0%
// max 100%
void piMotor::SetSpeedLeft(uint v){ // percent speed
	if (v > 100) v = 100;
	if (v < 0) v = 0;
	
	if (v == speedLeft) return;
	
	if(v < minMotorPowerLimit && v != 0) v = minMotorPowerLimit;
	
	uint voltage = ((maxMotorPowerLimit / 100) * v); // normalize voltage
	softPwmWrite(PWML, voltage);
	speedLeft = v;
}
uint piMotor::GetSpeedLeft(){
	return speedLeft;
}
// sets speed for right motor
// min 0%
// max 100%
void piMotor::SetSpeedRight(uint v){ // percent speed
	if (v > 100) v = 100;
	if (v < 0) v = 0;

	if (v == speedRight) return;

	if(v < minMotorPowerLimit && v != 0) v = minMotorPowerLimit;
	uint voltage =  ((maxMotorPowerLimit / 100) * v); // normalize voltage
	std::cout << voltage << "\n";
	softPwmWrite(PWMR, voltage);
	speedRight= v;
}
uint piMotor::GetSpeedRight(){
	return speedRight;
}
// releases settings
void piMotor::Release(){
	pwmWrite (PWMR, 0) ;
	pwmWrite (PWML, 0) ;

	pinMode(PWMR, OUTPUT);
	pinMode(PWML, OUTPUT);
}
