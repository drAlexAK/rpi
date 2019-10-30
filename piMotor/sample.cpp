#include <piMotor.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//#include <unistd.h>
#include <stdexcept>
#include <chrono>
#include <thread>

int main() {
	piMotor m(12.0, 2.0, 9.0);
	m.Init();
	m.Forward();
	for (uint i = 0; i < 101; i+=5){
		//m.getPower(i);
		m.SetSpeedLeft(i);
		m.SetSpeedRight(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	m.Stop();
	m.Release();
	return 0;
}
