#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include <libconfig.h>
#include <map>
//#include "piConfigManager.h"
#include "piConfigLoader.h"


using namespace libconfig;
//Config cfg;

//
// Created by drAlexAK on 11/10/19.
//
// fileName - configuration file name
piConfigLoader::piConfigLoader(std::string _fileName) {
    fileName = _fileName;
}

void piConfigLoader::LoadSection() {
    return LoadSection("");
}
void piConfigLoader::LoadSection(std::string _section) {
    const std::string sectionDefaultName = "default";
    section = _section;
    auto root = &cfg.getRoot();
    std::cout << "The root of configuration has been loaded.\n";

    try {
        setConfigurations = getSetting(root, "configurations");

        setConfDefault = getSetting(setConfigurations, sectionDefaultName);
        GetValue<std::string>(setConfDefault, "description") ;// write description of Default settings
        if ((_section.length() > 0)  && (_section != sectionDefaultName)){
            setConfCustom = getSetting(setConfigurations, _section.c_str());
            GetValue<std::string>(setConfCustom, "description") ; // write description of Custom settings
        } else {
            setConfCustom = NULL;
        }
        //const Setting *motor = getSetting(conf, "motor");

        //getValueAsString(conf, "description");
        //piConfigMotor confMotor(getValueAsDouble(motor, "battery_volt"), getValueAsDouble(motor, "min_motor_volt"), getValueAsDouble(motor, "max_motor_volt"));
        //confManager.confMotor = &confMotor;
        //auto battery_volt = GetValue<double>(motor, "battery_volt");
        //auto min_motor_volt = getValueAsDouble(motor, "min_motor_volt");
        //auto max_motor_volt = getValueAsDouble(motor, "max_motor_volt");
    }
    catch (const SettingNotFoundException &nfex) {
        std::cout << "Unfortunately the configuration has not been read correctly.\n";
        throw nfex;
    }
}

Setting *piConfigLoader::getSetting(const Setting *parent, const std::string &sectionName) {
    if (parent->isRoot())
        std::cout << " Starting load the configuration section '" << sectionName << "' from root\n";
    else
        std::cout << " Starting load the configuration section '" << parent->getName() << "." << sectionName << "'\n";
    try {
        auto setting = &(*parent)[sectionName.c_str()];
        if (parent->isRoot())
            std::cout << "The configuration section '" << sectionName << "' has been loaded.\n";
        else
            std::cout << "The configuration section '" << parent->getName() << "." << sectionName
                      << "' has been loaded.\n";
        return setting;
    }
    catch (const SettingNotFoundException &nfex) {
        if (parent->isRoot())
            std::cout << "Cannot get section '" << sectionName << "' from root\n";
        else
            std::cout << "Cannot get section '" << parent->getName() << "." << sectionName << "'\n";
        throw nfex;
    }
}



void piConfigLoader::LoadFile() {
    LoadFile(fileName);
}

void piConfigLoader::LoadFile(std::string _fileName) {

    // Read the file. If there is an error, report it and exit.
    try {
        cfg.readFile(_fileName.c_str());
    }
    catch (const FileIOException &fioex) {
        throw std::invalid_argument("Cannot read the file: '" + _fileName + "'");
    }
    catch (const ParseException &pex) {
        throw std::invalid_argument(
                "Parse error at '" + _fileName + "', line: '" + std::to_string(pex.getLine()) + "', error: '" +
                std::to_string(*pex.getError()) + "'");
    }
    std::cout << "File '" << fileName << "' has been loaded.\n";

    for (auto &param: {"description", "version", "date", "time"}) {
        std::cout << "  " << param << " : " << cfg.lookup(param).c_str() << '\n';
    }
}

