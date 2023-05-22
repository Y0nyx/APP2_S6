#include "light_sensor.h"
#include "Arduino.h"

Light_sensor::Light_sensor() {}

Light_sensor::~Light_sensor() {}

int Light_sensor::getRaw() {
    return analogRead(LIGHT_PIN);
}
