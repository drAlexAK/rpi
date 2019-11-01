#include <stdio.h>
#include <stdlib.h>

class piMotor {
private:
	// sets motor direction
	void motorSet(int a1, int a2, int b1, int b2);
	
	uint speedLeft = 0;
	uint speedRight = 0;
//	uint maxMotorPowerLimit;
//	uint minMotorPowerLimit;
	double battery_volt;
	double min_motor_volt;
	double max_motor_volt;
	double rate_b;
	double rate_a;
	uint getPower(uint v);
	void calcRate(); // (v * 1%(small area) + min_bar) * 1%(big area)
public:

	//piMotor() = default;
	
	// _battary_volt    - the current input voltage of the battery
	// _min_motor_volt  - minimal output voltage at the motors 
	// _max_motor_volt  - maximum output voltage at the motors 
	piMotor(double _battery_volt, double _min_motor_volt , double _max_motor_volt);

	// Initializes settings
	void Init();
	// sets directions
	void Stop();
	void Left();
	void Right();
	void Forward();
	void Backward();
	// sets/gets speed for left motor percents from 0% up to 100%
	// min 0
	// max 100
	void SetSpeedLeft(uint v);
	uint GetSpeedLeft();
	// sets/gets speed for left motor percents from 0% up to 100%
	// min 0
	// max 100
	void SetSpeedRight(uint v);
	uint GetSpeedRight();
	// releases settings
	void Release();
};
