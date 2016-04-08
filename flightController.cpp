// Evan Grissino
// 04/04/16
// speed Test

#include <iostream>
#include <thread>
#include <wiringPi.h>
#include <softPwm.h>

#include "PID.h"
#include "Motor.cpp"
#include "Sensor.h"

using namespace std;

int main() {
    // =========== Variables =============
    int m1_pin = 12,
        m2_pin = 13,
        m3_pin = 14,
        m4_pin = 15;
    
    // ======= Initalize Objects =========
    
    // The Sensor chip
    Sensor sensor;
    
    // 3 PID - roll, pitch, yaw
    PID r_pid(0, sensor.ypr[2]);
    PID p_pid(0, sensor.ypr[1]);
    PID y_pid(0, sensor.ypr[0]);
    
    // 4 Motors and Motor Control
    
    Motor M1(m1_pin), M2(m2_pin), M3(m3_pin), M4(m4_pin);
    
    //Motor *M1_p = &M1, *M2_p = &M2, *M3_p = &M3, *M4_p = &M4;
    
    Motor_Control MC(&M1.power, &M2.power, &M3.power, &M4.power);

    
    // ====== Start the threads =========
    
    // Sensor thread
    thread sensor_thread = sensor.run();
    
    // Motor threads
    thread m1_thread = M1.run();
    thread m2_thread = M2.run();
    thread m3_thread = M3.run();
    thread m4_thread = M4.run();
        
    for (int i = 0; i < 30; i++) {
        MC.roll  ( r_pid.update( ( sensor.ypr[2] ) ) );
        MC.pitch ( p_pid.update( ( sensor.ypr[1] ) ) );
        MC.yaw   ( y_pid.update( ( sensor.ypr[0] ) ) );
    };

    
    return 0;
};