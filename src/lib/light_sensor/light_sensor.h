#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

class Light_sensor {
    private:
    int pin;

    public:
    Light_sensor(int pin);
    int getRaw();
};

#endif
