#include "i2c_com.h"

#ifndef BAROMETER_SENSOR_H
#define BAROMETER_SENSOR_H

#define SENSOR_ADRESS 0x77

#define REGISTER_PSR 0x00
#define REGISTER_TMP 0x03
#define DATA_BYTES_TO_READ 3

#define REGISTER_COEF_TMP 0x10
#define REGISTER_COEF_PSR_1 0x13
#define REGISTER_COEF_PSR_2 0x1A
#define BYTES_TO_READ_TMP 3
#define BYTES_TO_READ_PSR_1 7
#define BYTES_TO_READ_PSR_2 8

#define REGISTER_PRS_CFG 0x06
#define REGISTER_TMP_CFG 0x07
#define REGISTER_BACKGROUND_CFG 0x08

#define DATA_PRS_CFG 0x00
#define DATA_TMP_CFG 0X80
#define DATA_BACKGROUND_CFG 0XF7

#define KT 524288
#define KP 524288

class Barometer_sensor {
    private:
    int c0, c1, c00, c10, c01, c11, c20, c21, c30;
    float pressure;
    float temperature;
    I2C_com i2c_com;

    void read_sensor();
    void read_coefficients();
    void calculate_pressure(float Praw_sc, float Traw_sc);
    void calculate_temperature(float Traw_sc);
    

    public:
    Barometer_sensor();
    ~Barometer_sensor();
    void setup();
    float get_temperature();
    float get_pressure();
};

#endif
