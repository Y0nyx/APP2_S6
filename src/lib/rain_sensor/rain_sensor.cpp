#include "rain_sensor.h"
#include "Arduino.h"

volatile int rain_counter = 0; 

void handleRainfall() {
    rain_counter++;
}

Rain_sensor::Rain_sensor() {}

void Rain_sensor::setup() {
   pinMode(RAIN_PIN, INPUT);
   attachInterrupt(digitalPinToInterrupt(RAIN_PIN), handleRainfall, RISING); 
}

Rain_sensor::~Rain_sensor() { }

float Rain_sensor::get_rain_mm() {
    return rain_counter * this->multiplier_factor;
}

