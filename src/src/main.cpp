#include <Arduino.h>
#include "light_sensor.h"
#include "humidity_sensor.h"

// DEFINE
int light_sensor_pin = 34;

Light_sensor light_sens(34);
Humidity_sensor humidity_sensor;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.printf("light : %d\n", light_sens.getRaw());
  Serial.printf("temp : %.2f\n", humidity_sensor.get_temp());
  Serial.printf("humidity : %.2f\n", humidity_sensor.get_humidity());

  delay(2000);
}

