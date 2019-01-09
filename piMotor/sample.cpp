#include <piMotor.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdexcept>

int main() {

	piMotor m(80) ;
	m.Init();
	m.Forward();
	for (int i=0; i<101; i++){
		m.SetSpeedLeft(i);
		m.SetSpeedRight(i);
		sleep(1);
	}
	m.Stop();
	m.Release();
	return 0;
}
