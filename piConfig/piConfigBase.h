#pragma once
#include <cstdlib>
#include <libconfig.h++>
#include <libconfig.h>
#include "piConfigLoader.h"

using namespace libconfig;

class piConfigBase {
private:
protected:
    const std::string sectionName;
    piConfigLoader *loader;
    //Setting *setDefault;
    //Setting *setCustom;
public:
    piConfigBase(std::string _sectionName, piConfigLoader* _loader): sectionName(_sectionName), loader(_loader){};
    std::string GetSectionName() { return sectionName; };
    //void SetSetting(const Setting *_setDefault, const Setting *_setCustom) {*setDefault = _setDefault; *setCustom = _setCustom; };

    virtual void LoadValues() = 0;
    virtual void PrintValue() = 0;
};
