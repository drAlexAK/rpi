# g++ -I./ -lwiringPi -c ./piMotor.cpp -o piMotor.so
g++ -std=c++14 -I/sc/rpi/piMotor -lwiringPi  ./sample.cpp ./piMotor.cpp -o motor
