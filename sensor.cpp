#include <iostream>
#include "Sensor.h"
#include <thread>

using namespace std;

int main() {
	Sensor sensor;
	thread sensor_thread = sensor.run();
	sensor_thread.join();

	return 0;
};
