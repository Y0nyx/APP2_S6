#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

#define RAIN_PIN 23

class Rain_sensor {
    private:
    float multiplier_factor = 0.2729;

    public:
    Rain_sensor();
    ~Rain_sensor();
    void setup();
    float get_rain_mm();
};

#endif