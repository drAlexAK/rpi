#include "piConfigManager.h"
#include "piConfigLoader.h"
#include "piConfigBase.h"
#include "piConfigMotor.h"
#include "piConfigCamera.h"

piConfigManager::piConfigManager() {
    this->loader = new piConfigLoader();
    piConfigBase* confMotor = new piConfigMotor(loader);
    mapConfigs.insert(std::make_pair(confMotor->GetSectionName(), confMotor));

    piConfigBase* confCamera = new piConfigCamera(loader);
    mapConfigs.insert(std::make_pair(confCamera->GetSectionName(), confCamera));
}

void piConfigManager::LoadConfigFromFile(const std::string &_fileName){
    loader->LoadFile(_fileName);
}

void piConfigManager::LoadConfigSection(const std::string &_sectionName){
    loader->LoadSection(_sectionName);
    for(auto conf: mapConfigs){
        conf.second->LoadValues();
        conf.second->PrintValue();
    }
}

piConfigMotor* piConfigManager::GetConfigurationMotor(){
    return (piConfigMotor*)GetConfiguration(piConfigMotor::name);
}

piConfigCamera* piConfigManager::GetConfigurationCamera(){
    return (piConfigCamera*)GetConfiguration(piConfigCamera::name);
}

piConfigBase* piConfigManager::GetConfiguration(const std::string &_name){
    if (mapConfigs.count(_name) > 0)
        return mapConfigs[_name];
    else
        throw std::invalid_argument("The section '" + _name + "' doesn't exist.");
}
