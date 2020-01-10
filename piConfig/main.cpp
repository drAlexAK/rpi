// sudo apt-get install libconfig++
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include "piConfigManager.h"

//using namespace std;
using namespace libconfig;


int main(int argc, char **argv){
    if ((argc != 2) && (argc != 3)) {
        std::cout << "Usage: config.cfg [default].\n";
        std::cout << " - config.cfg - path to the configuration file;\n";
        std::cout << " - [default] - optional parameter, section name, by default - default section will be selected;\n";
        return  7;
    }
    auto fileConfig = std::string(argv[1]);
    auto configSection = std::string(""); //std::string("default");
    if (argc == 3) configSection = std::string(argv[2]);

    //piConfigLoader cfg(fileConfig);
    //cfg.LoadFile();
    //cfg.LoadSection(configSection);

    piConfigManager confManager;
    confManager.LoadConfigFromFile(fileConfig);
    confManager.LoadConfigSection(configSection);
    confManager.LoadConfigSection("fast");

    auto cMotor = confManager.GetConfigurationMotor();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
