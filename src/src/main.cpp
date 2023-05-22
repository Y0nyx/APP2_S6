#include <Arduino.h>
#include <Wire.h>
#include "light_sensor.h"
#include "humidity_sensor.h"
#include "barometer_sensor.h"
#include "wind_sensor.h"
#include "rain_sensor.h"

//Light_sensor light_sens;
//Humidity_sensor humidity_sensor;
Barometer_sensor barometer_sensor;
Wind_sensor wind_sensor;
Rain_sensor rain_sensor;


void setup() {
  Serial.begin(115200);

  wind_sensor.setup();
  rain_sensor.setup();
  barometer_sensor.setup();
}

void loop() {
  //Serial.printf("light : %d\n", light_sens.getRaw()); // DONE
  //Serial.printf("temp : %.2f\n", humidity_sensor.get_temp()); //DONE
  //Serial.printf("humidity : %.2f\n", humidity_sensor.get_humidity()); // DONE
  Serial.printf("temp : %.2f\n", barometer_sensor.get_temperature()); // TODO
  Serial.printf("pressure : %.2f\n", barometer_sensor.get_pressure()); // TODO

  //Serial.printf("speed : %.2f\n", wind_sensor.get_wind_speed()); // DONE
  //Serial.printf("direction : %.2f\n", wind_sensor.get_wind_direction()); // DONE
  //Serial.printf("rain : %.2f\n", rain_sensor.get_rain_mm()); // DONE
  delay(1000);
}

