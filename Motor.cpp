// Evan Grissino
// 04/06/2016
// Motor object class
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <thread>

using namespace std;

class Motor {
    public:
        double power;
        int pin;
    
    Motor(int p) {
        power = 0;
        pin = p;
        startUp();
    };
    
    std::thread run() {
        for (;;) {
            update();
        };
    };
    
    void startUp() {
        softPwmCreate(pin, power, 100);
        delay(500);
    };
    
    void update() {
        softPwmWrite(pin, power);
        delay(500);
    };
    
    
};


class Motor_Control {
    public:
        double* m1;
        double* m2;
        double* m3;
        double* m4;
    
    Motor_Control(double* M1, double* M2, double* M3, double* M4) {
        m1 = M1;
        m2 = M2;
        m3 = M3;
        m4 = M4;
    };
    
    void roll(double control) {
        *m1 -= control;
        *m2 -= control;
        *m3 += control;
        *m4 += control;
        
        update();
    };
    
    void pitch(double control) {
        *m1 += control;
        *m2 -= control;
        *m3 -= control;
        *m4 += control;
        
        update();
    };
    
    void yaw(double control) {
        *m1 -= control;
        *m2 += control;
        *m3 -= control;
        *m4 += control;
        
        update();
    };
    
    void getMotorState() {
        cout << "m1 : " << *m1 << endl;
        cout << "m2 : " << *m2 << endl;
        cout << "m3 : " << *m3 << endl;
        cout << "m4 : " << *m4 << endl;
    };
    
    private:
    void update() {
        
        // ======== Postive Boundry ========
        if (*m1 > 100) {
            *m1 = 100;
        };
        if (*m2 > 100) {
            *m2 = 100;
        };
        if (*m3 > 100) {
            *m3 = 100;
        };
        if (*m4 > 100) {
            *m4 = 100;
        };
        
        // ======== Negative Boundry ========
        if (*m1 < -100) {
            *m1 = -100;
        };
        if (*m2 < -100) {
            *m2 = -100;
        };
        if (*m3 < -100) {
            *m3 = -100;
        };
        if (*m4 < -100) {
            *m4 = -100;
        };
    };
};

