#include <piMotor.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//#include <unistd.h>
#include <stdexcept>
#include <chrono>
#include <thread>

int main() {

	piMotor m(1, 1);
	m.Init();
	m.Forward();
	for (int i = 0; i < 101; i++){
		m.SetSpeedLeft(i);
		m.SetSpeedRight(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	m.Stop();
	m.Release();
	return 0;
}
