#include "light_sensor.h"

Light_sensor::Light_sensor() {}

Light_sensor::~Light_sensor() {}

float Light_sensor::getRaw() {
    return analogRead(LIGHT_PIN);
}

String Light_sensor::get_info() {
    int light = analogRead(LIGHT_PIN);  

    if (light > 1500) {
        return "Ensoleiller";
    } else {
        return "couvert";
    }
}
