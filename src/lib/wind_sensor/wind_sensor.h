#ifndef WIND_SENSOR_H
#define WIND_SENSOR_H

#define MULTIPLIER_FACTOR 2.4
#define SPEED_PIN 27
#define DIRECTION_PIN 35

class Wind_sensor {
    private:

    public:
    static volatile unsigned long speed_counter;
    Wind_sensor();
    ~Wind_sensor();
    void setup();
    float get_wind_direction();
    float get_wind_speed();
};

#endif