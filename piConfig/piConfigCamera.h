#pragma once

#include "piConfigBase.h"

class piConfigCamera: public piConfigBase {
private:
public:
    static constexpr const char* name = "camera";
     //static const std::string nameA = "camera";
     int color_black;
     bool do_morphological;
    piConfigCamera (piConfigLoader* _loader): piConfigBase(piConfigCamera::name, _loader){};

    void PrintValue() override;
    void LoadValues() override;
};