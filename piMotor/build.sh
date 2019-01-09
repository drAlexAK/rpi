# g++ -I./ -lwiringPi -c ./piMotor.cpp -o piMotor.so
g++ -I/sc/rpi/piMotor -lwiringPi  ./sample.cpp ./piMotor.cpp -o motor
