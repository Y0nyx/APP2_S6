#include <Arduino.h>

#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#define LIGHT_PIN 34

class Light_sensor {
    private:

    public:
    Light_sensor();
    ~Light_sensor();
    float getRaw();
    String get_info();
};

#endif
