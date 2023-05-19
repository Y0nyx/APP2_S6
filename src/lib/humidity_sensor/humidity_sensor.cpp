#include "humidity_sensor.h"
#include "Arduino.h"

Humidity_sensor::Humidity_sensor() {
    this->pin = 16;
    this->humidity = 0;
    this->temp = 0;
};

void Humidity_sensor::read_sensor() {
    int i, j;
    int duree[42];
    unsigned long pulse;
    byte data[5];
    
    pinMode(pin, OUTPUT_OPEN_DRAIN);
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(20);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT_PULLUP);
    
    while (digitalRead(pin) == HIGH);
    i = 0;

    do {
            pulse = pulseIn(pin, HIGH);
            duree[i] = pulse;
            i++;
    } while (pulse != 0);
    
    if (i != 42) 
        Serial.printf(" Erreur timing \n"); 

    for (i=0; i<5; i++) {
        data[i] = 0;
        for (j = ((8*i)+1); j < ((8*i)+9); j++) {
        data[i] = data[i] * 2;
        if (duree[j] > 50) {
            data[i] = data[i] + 1;
        }
        }
    }

    if ( (data[0] + data[1] + data[2] + data[3]) != data[4] ) 
        Serial.println(" Erreur checksum");

    humidity = data[0] + (data[1] / 256.0);
    temp = data[2] + (data[3] / 256.0);
};

float Humidity_sensor::get_temp() {
    read_sensor();
    return temp;
};

float Humidity_sensor::get_humidity() {
    read_sensor();
    return humidity;
};
