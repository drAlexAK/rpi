#include <cstdlib>
#include <libconfig.h++>
#include <libconfig.h>
#include <iostream>
#include "piConfigLoader.h"
#include "piConfigCamera.h"
#include "piConfigBase.h"

using namespace libconfig;

void piConfigCamera::PrintValue() {
    std::cout << GetSectionName() << ":\n";
    std::cout << "  color_black :   " << this->color_black << "\n";
    std::cout << "  do_morphological : " << this->do_morphological << "\n";
}

void  piConfigCamera::LoadValues() {
    this->color_black = loader->GetValue<int>(this->sectionName, "color_black");
    this->do_morphological = loader->GetValue<bool>(this->sectionName, "do_morphological");
}