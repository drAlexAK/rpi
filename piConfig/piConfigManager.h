#pragma once
#include "piConfigLoader.h"
#include "piConfigMotor.h"
#include "piConfigCamera.h"
#include <map>

class piConfigManager{
private:
    piConfigLoader* loader;
    std::map<std::string, piConfigBase*> mapConfigs;
protected:
public:
    piConfigManager() ;

    void LoadConfigFromFile(const std::string &_fileName);
    void LoadConfigSection(const std::string &_sectionName);
    piConfigBase* GetConfiguration(const std::string &_name);
    piConfigMotor* GetConfigurationMotor();
    piConfigCamera* GetConfigurationCamera();

    //piConfigManager() = default;
    //piConfigMotor* confMotor;
    //piConfigCamera* confCamera;
};