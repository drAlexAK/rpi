#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <libconfig.h++>

using namespace libconfig;


class piConfigLoader{
private:
    std::string fileName;
    std::string section;
    Config cfg;
    Setting *setConfDefault;
    Setting *setConfCustom;
    Setting *setConfigurations;

    std::map<std::string, std::pair<Setting*, Setting*>> mapSettings;

    // get child section by section name from specified parent section
    Setting* getSetting(const Setting* _parent, const std::string &sectionName);
    // get value by value name from the specified section
    template<typename T>
    T GetValue(const Setting *_setting, const std::string &_valueName);

public:
    // fileName - configuration file name
    piConfigLoader() = default;
    piConfigLoader(std::string _fileName);
    // load parameters from the configuration file
    void LoadSection();
    void LoadSection(std::string _section);
    void LoadFile(std::string _fileName);
    void LoadFile();

    // get value by value name from the specified section, by section name
    template <typename T>
    T GetValue(const std::string &_settingName, const std::string &_valueName);
};

template <typename T>
T piConfigLoader::GetValue(const std::string &_settingName, const std::string &_valueName) {
    if (mapSettings.count(_settingName) == 0) {
        auto setDef = getSetting(setConfDefault, _settingName);
        auto setCust = setConfCustom == NULL ? NULL : getSetting(setConfCustom, _settingName);
        mapSettings.insert(std::make_pair(_settingName, std::make_pair(setDef, setCust)));
    }
    auto pairSettings = mapSettings[_settingName];
    T value = GetValue<T>(pairSettings.first, _valueName);
    if (pairSettings.second != NULL) {
        if (pairSettings.second->lookupValue(_valueName.c_str(), value)){
            std::cout << " Value '" << _valueName << "' has been replaced from section '" << pairSettings.second->getParent().getName() << "." << pairSettings.second->getName() << "'\n";
            std::cout << "  " << pairSettings.second->getName() << "." << _valueName << " = " << value << "\n";
        }
    }
    return value;
}

template <typename T>
T piConfigLoader::GetValue(const Setting *_setting, const std::string &_valueName) {
    T result;
    if (_setting->lookupValue(_valueName.c_str(), result)) {
        std::cout << "  " << _setting->getName() << "." << _valueName << " = " << result << "\n";
        return result;
    } else {
        std::cout << " Cannot read the value '" << _valueName << "' from the section '" << _setting->getName() << "'\n";
        throw SettingNotFoundException(*_setting, _valueName.c_str());
    }
}
