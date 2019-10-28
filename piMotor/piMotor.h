#include <stdio.h>
#include <stdlib.h>

class piMotor {
private:
    uint limit = 100;
    uint speedLeft = 0;
    uint speedRight = 0;
    // sets motor direction
    void motorSet(int a1, int a2, int b1, int b2);
    uint maxMotorPowerLimit;
    uint minMotorPowerLimit;
public:
#define MAX_MOTOR_POWER_LIMIT_D 80	//-9.6- voltage out of 12
#define MIN_MOTOR_POWER_LIMIT_D 16	//-2.0- voltage out of 12
   
    piMotor() = default;
    piMotor(uint _min_limit , uint _max_limit);

    // Creates piMotor object
    // max voltage limit, percentages
    // min value = 1
    // max value 100
    //piMotor(uint _limit);
    // Initializes settings
    void Init();
    // sets directions
    void Stop();
    void Left();
    void Right();
    void Forward();
    void Backward();
    // sets/gets speed for left motor
    // min 0
    // max 100
    void SetSpeedLeft(uint v);
    uint GetSpeedLeft();
    // sets/gets speed for right motor
    // min 0
    // max 100
    void SetSpeedRight(uint v);
    uint GetSpeedRight();
    // releases settings
    void Release();
};
