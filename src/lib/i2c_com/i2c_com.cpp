#include "i2c_com.h"

I2C_com::I2C_com() {}

I2C_com::~I2C_com() {}

void I2C_com::setup() {
    Wire.begin();
}

void I2C_com::write_register(uint8_t reg, uint8_t data, int sensor_adress) {
  Wire.beginTransmission(sensor_adress);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void I2C_com::read_register(uint8_t reg, byte* buffer, uint8_t length, int sensor_adress) {
  Wire.beginTransmission(sensor_adress);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)sensor_adress, (uint8_t)length);
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }
}

void I2C_com::read_nbr_bytes(u_int64_t &data, int registerData, int nbBytes, int sensor_adress) {
    Wire.beginTransmission(sensor_adress);
    Wire.write(registerData);
    Wire.endTransmission(false);

    Wire.requestFrom(sensor_adress, nbBytes);

    while(Wire.available()){
        char c = Wire.read();
        data = (data << 8) | c;
    }

    Wire.endTransmission();
}

void I2C_com::complement_2_binary(int &cx, int nbBits) {
    if((cx >> (nbBits - 1)) & 0x1) {
        cx = cx - (1 << nbBits); //pow(2, nbBits)
    }
}