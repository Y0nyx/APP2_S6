#include <Wire.h>
#include "Arduino.h"

#ifndef I2C_COM_H
#define I2C_COM_H

class I2C_com {
    private:

    public:
    I2C_com();
    ~I2C_com();
    void setup();
    void write_register(uint8_t reg, uint8_t data, int sensor_adress);
    void read_register(uint8_t reg, byte* buffer, uint8_t length, int sensor_adress);
    void read_nbr_bytes(u_int64_t  &data, int registerData, int nbBytes, int sensor_adress);
    void complement_2_binary(int &cx, int nbBits);
};

#endif
