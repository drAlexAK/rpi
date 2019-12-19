#pragma once

#include "piConfigBase.h"

class piConfigMotor: public piConfigBase {
private:
public:
    static constexpr const char* name = "motor";
     //static const std::string nameA = "motor";
    double battery_volt, min_motor_volt, max_motor_volt;
    piConfigMotor(piConfigLoader* _loader): piConfigBase(piConfigMotor::name, _loader){};

    void PrintValue() override;
    void LoadValues() override ;
};