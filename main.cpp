#include "mbed.h"

// HC-SR04
DigitalOut trig(p5);
DigitalIn echo(p6);
Timer timer;

// Buzzer
PwmOut buzzer(p25);
Ticker ticker;

void updateDistance(int distance) {
    if (distance > 180) {
        buzzer.write(0.0);
    }
    else if (distance > 120) {
        buzzer.period(1.0/1000);
        buzzer.write(0.5f);
    }
    else if (distance > 60) {
        buzzer.period(1.0/2000);
        buzzer.write(0.5f);
    }
    else {
        buzzer.period(1.0/3000);
        buzzer.write(0.5f);
    }
    
}

int main()
{  
    while(1) {
        // Send trig pulse
        trig = 1;
        wait_us(10.0);
        trig = 0;
        timer.reset();
        
        // Wait for echo high
        while (echo == 0) {};
        timer.start();
        
        // Wait for echo low
        while (echo == 1) {}
        timer.stop();
        
        updateDistance(timer.read_us() / 58.0);
        
        wait(0.1);
    }
}