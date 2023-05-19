#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

class Humidity_sensor {
    private:
    int pin;
    float temp;
    float humidity;
    void read_sensor();

    public:
    Humidity_sensor();
    float get_temp();
    float get_humidity();
};

#endif
