g++ -w -std=c++14 -c ./piConfigManager.cpp ./piConfigLoader.cpp ./piConfigBase.h ./piConfigMotor.cpp ./piConfigCamera.cpp -lconfig++
ar rvs piConfig.a piConfigManager.o piConfigLoader.o  piConfigMotor.o piConfigCamera.o
g++ main.cpp piConfig.a -lconfig++ -o test
