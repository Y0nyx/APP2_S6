#include "barometer_sensor.h"

Barometer_sensor::Barometer_sensor() {}

Barometer_sensor::~Barometer_sensor() {}

void Barometer_sensor::read_coefficients() {
    // Lire les coefficients de calibration
    uint64_t tmp_coeff = 0;
    uint64_t psr_coeff_1 = 0;
    uint64_t psr_coeff_2 = 0;

    i2c_com.read_nbr_bytes(tmp_coeff, REGISTER_COEF_TMP, BYTES_TO_READ_TMP, SENSOR_ADRESS);
    i2c_com.read_nbr_bytes(psr_coeff_1, REGISTER_COEF_PSR_1, BYTES_TO_READ_PSR_1, SENSOR_ADRESS);
    i2c_com.read_nbr_bytes(psr_coeff_2, REGISTER_COEF_PSR_2, BYTES_TO_READ_PSR_2, SENSOR_ADRESS);

    c0 = tmp_coeff >> 12 & 0xFFF;
    c1 = tmp_coeff & 0xFFF;
    c00 = psr_coeff_1 >> 36 & 0xFFFFF;
    c10 = psr_coeff_1 >> 16 & 0xFFFFF;
    c01 = psr_coeff_1 & 0xFFFF;
    c11 = psr_coeff_2 >> 48 & 0xFFFF;
    c20 = psr_coeff_2 >> 32 & 0xFFFF;
    c21 = psr_coeff_2 >> 16 & 0xFFFF;
    c30 = psr_coeff_2 & 0xFFFF;

    i2c_com.complement_2_binary(c0, 12);
    i2c_com.complement_2_binary(c1, 12);
    i2c_com.complement_2_binary(c00, 20);
    i2c_com.complement_2_binary(c10, 20);
    i2c_com.complement_2_binary(c01, 16);
    i2c_com.complement_2_binary(c11, 16);
    i2c_com.complement_2_binary(c20, 16);
    i2c_com.complement_2_binary(c21, 16);
    i2c_com.complement_2_binary(c30, 16);
}

void Barometer_sensor::calculate_pressure(float Praw_sc, float Traw_sc) {
    pressure = c00 + Praw_sc * (c10 + Praw_sc * (c20 + Praw_sc * c30)) + Traw_sc * c01 + Traw_sc * Praw_sc * (c11 + Praw_sc * c21);
}

void Barometer_sensor::calculate_temperature(float Traw_sc) {
    temperature = c0 * 0.5 + c1 * Traw_sc;
}

void Barometer_sensor::read_sensor() {
    // read temperature
    i2c_com.write_register(0x08, 0x02, SENSOR_ADRESS);
    byte tempData[3];
    i2c_com.read_register(0x03, tempData, 3, SENSOR_ADRESS); // read three bytes from register 0x03
    // calculate temperature
    int Traw = tempData[0] << 16 | tempData[1] << 8 | tempData[2];
    i2c_com.complement_2_binary(Traw, 24);
    float Traw_sc = Traw / (float)KT;
    calculate_temperature(Traw_sc);

    // read pressure
    i2c_com.write_register(0x08, 0x01, SENSOR_ADRESS);
    byte pressureData[3];
    i2c_com.read_register(0x00, pressureData, 3, SENSOR_ADRESS); // read three bytes from register 0x00
    // calculate pressure
    int Praw = pressureData[0] << 16 | pressureData[1] << 8 | pressureData[2];
    i2c_com.complement_2_binary(Praw, 24);
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
    i2c_com.setup();
    i2c_com.write_register(REGISTER_PRS_CFG, DATA_PRS_CFG, SENSOR_ADRESS);
    i2c_com.write_register(REGISTER_TMP_CFG, DATA_TMP_CFG, SENSOR_ADRESS);
    i2c_com.write_register(REGISTER_BACKGROUND_CFG, DATA_BACKGROUND_CFG, SENSOR_ADRESS);
    read_coefficients();
}


