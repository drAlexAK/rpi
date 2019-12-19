#include <cstdlib>
#include <libconfig.h++>
#include <libconfig.h>
#include <iostream>
#include "piConfigLoader.h"
#include "piConfigMotor.h"
#include "piConfigBase.h"

using namespace libconfig;

void piConfigMotor::PrintValue() {
    std::cout << GetSectionName() << ":\n";
    std::cout << "  battery_volt   : " << this->battery_volt << "\n";
    std::cout << "  max_motor_volt : " << this->max_motor_volt << "\n";
    std::cout << "  min_motor_volt : " << this->min_motor_volt << "\n";
}

void  piConfigMotor::LoadValues() {
    //battery_volt = 13; //this->loader->GetValue<double>(this->sectionName, "battery_volt");
    this->battery_volt = loader->GetValue<double>(this->sectionName, "battery_volt");
    this->max_motor_volt = loader->GetValue<double>(this->sectionName, "max_motor_volt");
    this->min_motor_volt = loader->GetValue<double>(this->sectionName, "min_motor_volt");
}