#include "barometer_sensor.h"
#include "Arduino.h"
#include <Wire.h>

void writeRegister(uint8_t reg, uint8_t data) {
  Wire.beginTransmission(SENSOR_ADRESS);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void readRegister(uint8_t reg, byte* buffer, uint8_t length) {
  Wire.beginTransmission(SENSOR_ADRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)SENSOR_ADRESS, (uint8_t)length);
  for (uint8_t i = 0; i < length; i++) {
    buffer[i] = Wire.read();
  }
}

void continue_readRegister(int &data, int registerData, int nbBytes) {
    Wire.beginTransmission(SENSOR_ADRESS);
    Wire.write(registerData);
    Wire.endTransmission(false);

    Wire.requestFrom(SENSOR_ADRESS, nbBytes);

    while(Wire.available()){
        char c = Wire.read();
        data = (data << 8) | c;
    }

    Wire.endTransmission();
}

Barometer_sensor::Barometer_sensor() {}

Barometer_sensor::~Barometer_sensor() {}

void Barometer_sensor::complementTwoToBinary(int &cx, int nbBits) {
    if((cx >> (nbBits - 1)) & 0x1) {
        cx = cx - (1 << nbBits); //pow(2, nbBits)
    }
}

void Barometer_sensor::read_coefficients() {
    // Lire les coefficients de calibration
    u_int64_t tmp_coeff = 0;
    u_int64_t psr_coeff_1 = 0;
    u_int64_t psr_coeff_2 = 0;

    continue_readRegister(tmp_coeff, REGISTER_COEF_TMP, BYTES_TO_READ_TMP);
    continue_readRegister(psr_coeff_1, REGISTER_COEF_PSR_1, BYTES_TO_READ_PSR_1);
    continue_readRegister(psr_coeff_2, REGISTER_COEF_PSR_2, BYTES_TO_READ_PSR_2);

    c0 = tmp_coeff >> 12 & 0xFFF;
    c1 = tmp_coeff & 0xFFF;
    c00 = psr_coeff_1 >> 36 & 0xFFFFF;
    c10 = psr_coeff_1 >> 16 & 0xFFFFF;
    c01 = psr_coeff_1 & 0xFFFF;
    c11 = psr_coeff_2 >> 48 & 0xFFFF;
    c20 = psr_coeff_2 >> 32 & 0xFFFF;
    c21 = psr_coeff_2 >> 16 & 0xFFFF;
    c30 = psr_coeff_2 & 0xFFFF;

    complementTwoToBinary(c0, 12);
    complementTwoToBinary(c1, 12);
    complementTwoToBinary(c00, 20);
    complementTwoToBinary(c10, 20);
    complementTwoToBinary(c01, 16);
    complementTwoToBinary(c11, 16);
    complementTwoToBinary(c20, 16);
    complementTwoToBinary(c21, 16);
    complementTwoToBinary(c30, 16);
}

void Barometer_sensor::calculate_pressure(float Praw_sc, float Traw_sc) {
    pressure = c00 + Praw_sc * (c10 + Praw_sc * (c20 + Praw_sc * c30)) + Traw_sc * c01 + Traw_sc * Praw_sc * (c11 + Praw_sc * c21);
}

void Barometer_sensor::calculate_temperature(float Traw_sc) {
    temperature = c0 * 0.5 + c1 * Traw_sc;
}

void Barometer_sensor::read_sensor() {
    // read temperature
    writeRegister(0x08, 0x02);
    byte tempData[3];
    readRegister(0x03, tempData, 3); // read three bytes from register 0x03
    // calculate temperature
    int Traw = tempData[0] << 16 | tempData[1] << 8 | tempData[2];
    complementTwoToBinary(Traw, 24);
    float Traw_sc = Traw / (float)KT;
    calculate_temperature(Traw_sc);

    // read pressure
    writeRegister(0x08, 0x01);
    byte pressureData[3];
    readRegister(0x00, pressureData, 3); // read three bytes from register 0x00
    // calculate pressure
    int Praw = pressureData[0] << 16 | pressureData[1] << 8 | pressureData[2];
    complementTwoToBinary(Praw, 24);
    float Praw_sc = Praw / (float)KP;
    calculate_pressure(Praw_sc, Traw_sc);
}

float Barometer_sensor::get_pressure() {
    read_sensor();
    return pressure;
}

float Barometer_sensor::get_temperature() {
    read_sensor();
    return temperature;
}

void Barometer_sensor::setup() {
    Wire.begin();
    writeRegister(REGISTER_PRS_CFG, DATA_PRS_CFG);
    writeRegister(REGISTER_TMP_CFG, DATA_TMP_CFG);
    writeRegister(REGISTER_BACKGROUND_CFG, DATA_BACKGROUND_CFG);
    read_coefficients();
}


