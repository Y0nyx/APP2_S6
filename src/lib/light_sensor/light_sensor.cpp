#include "light_sensor.h"
#include "Arduino.h"

Light_sensor::Light_sensor(int pin) {
    this->pin = pin;
}

int Light_sensor::getRaw() {
    return analogRead(pin);
}
