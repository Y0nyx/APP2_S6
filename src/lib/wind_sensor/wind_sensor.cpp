#include "wind_sensor.h"

volatile unsigned long Wind_sensor::speed_counter = 0;

void compute_interrupt() {
    Wind_sensor::speed_counter++;
}

Wind_sensor::Wind_sensor() {}

Wind_sensor::~Wind_sensor() {}

void Wind_sensor::setup() {
    pinMode(SPEED_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(SPEED_PIN), compute_interrupt, RISING);
}

float Wind_sensor::get_wind_direction() {
    int value = analogRead(DIRECTION_PIN);
    float voltage = (value*3.3)/4096;

    if (3750 <= voltage && voltage < 3800) {
        return 0;
    } else if (3290 <= voltage && voltage < 3340) {
        return 45;
    } else if (3520 <= voltage && voltage < 3570) {
        return 67.5;
    } else if (2790 <= voltage && voltage < 2840) {
        return 80;
    } else if (3130 <= voltage && voltage < 3180) {
        return 90;
    } else if (1600 <= voltage && voltage < 1650) {
        return 112.5;
    } else if (1830 <= voltage && voltage < 1880) {
        return 135;
    } else if (300 <= voltage && voltage < 350) {
        return 157.5;
    } else if (350 <= voltage && voltage < 400) {
        return 180;
    } else if (230 <= voltage && voltage < 280) {
        return 202.5;
    } else if (700 <= voltage && voltage < 750) {
        return 225;
    } else if (480 <= voltage && voltage < 530) {
        return 247.5;
    } else if (1130 <= voltage && voltage <= 1180) {
        return 270;
    } else if (950 <= voltage && voltage <= 1000) {
        return 292.5;
    } else if (2500 <= voltage && voltage <= 2550) {
        return 315;
    } else if (2370 <= voltage && voltage <= 2420) {
        return 337.5;
    }
}

float Wind_sensor::get_wind_speed() {
    float wind_speed = speed_counter * MULTIPLIER_FACTOR;
    speed_counter = 0;

    return wind_speed; 
}

String Wind_sensor::get_wind_direction_string(){
    int val = analogRead(DIRECTION_PIN);
    float voltage = (val*3.3)/4096;

    if(voltage >= 2.09 && voltage <= 2.39){
        return "NORD";
    }
    else if(voltage >= 1.15 && voltage <= 1.34){
        return "NORD-EST";
    }
    else if(voltage >= 0.08 && voltage <= 0.17){
        return "EST";
    }
    else if(voltage >= 0.44 && voltage <= 0.47){
        return "SUD-EST";
    }
    else if(voltage >= 0.27 && voltage <= 0.78){
        return "SUD";
    }
    else if(voltage >= 1.76 && voltage <= 1.87){
        return "SUD-OUEST";
    }
    else if(voltage >= 3.09 && voltage <= 3.12){
        return "OUEST";
    }
    else if(voltage >= 2.52 && voltage <= 2.81){
        return "NORD-OUEST";
    }
    else {
        return "direction inconnu";
    }
}
