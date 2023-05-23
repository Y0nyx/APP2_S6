#include <Arduino.h>
#include "light_sensor.h"
#include "humidity_sensor.h"
#include "barometer_sensor.h"
#include "wind_sensor.h"
#include "rain_sensor.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define THRESHOLD 0.05

Light_sensor light_sens;
Humidity_sensor humidity_sensor;
Barometer_sensor barometer_sensor;
Wind_sensor wind_sensor;
Rain_sensor rain_sensor;

String light = "";
String wind_dir = "";

float temp = 0.0;
float humi = 0.0;
float baro_temp = 0.0;
float baro_humi = 0.0;
float wind_speed = 0.0;
float rain_mm = 0.0;

// The UUID of the service and characteristic
static BLEUUID serviceUUID("912071e2-fdb5-4a2e-b420-0ffb542b0e05");

static BLEUUID baro_temp_UUID("41bcf98a-fa02-49bd-9365-9f8c3c311b1b");
static BLEUUID baro_pressure_UUID("99570e93-fa45-4bb9-a30a-d0408cf7fa37");
static BLEUUID light_UUID("b2640133-2d8d-4c19-bc4b-c493fddeed76");
static BLEUUID temp_UUID("f1949579-c2b8-4f9b-91ba-7f7257f8d84d");
static BLEUUID humi_UUID("03823d56-a16a-4551-ad7c-d96dc4d937bf");
static BLEUUID wind_speed_UUID("1c8e4ae2-87dc-4010-bcbc-291ccf23144c");
static BLEUUID wind_dir_UUID("7e54e529-dc81-4b97-8952-d50ed0cdaf50");
static BLEUUID rain_mm_UUID("e278d5b5-f233-4cb9-935c-d5d43d1f9371");

// The BLE server and characteristic
BLEServer* server;
BLECharacteristic* baro_temp_characteristic;
BLECharacteristic* baro_pressure_characteristic;
BLECharacteristic* light_characteristic;
BLECharacteristic* temp_characteristic;
BLECharacteristic* humi_characteristic;
BLECharacteristic* wind_speed_characteristic;
BLECharacteristic* wind_dir_characteristic;
BLECharacteristic* rain_mm_characteristic;

// Timer for updating the characteristic value
BLEAdvertising* advertising;
bool ConnectionEtablie = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Client Connected");
    ConnectionEtablie = true;
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Client Disconnected");
    ConnectionEtablie = false;
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Start Service BLE");

  wind_sensor.setup();
  rain_sensor.setup();
  barometer_sensor.setup();

  // Create the BLE device and server
  BLEDevice::init("ESP32 Charles et Vincent");
  
  server = BLEDevice::createServer();
  server->setCallbacks(new MyServerCallbacks());

  // Create the service and characteristic
  BLEService* service = server->createService(serviceUUID);
  baro_temp_characteristic = service->createCharacteristic(baro_temp_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  baro_pressure_characteristic = service->createCharacteristic(baro_pressure_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  light_characteristic = service->createCharacteristic(light_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  temp_characteristic = service->createCharacteristic(temp_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  humi_characteristic = service->createCharacteristic(humi_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  wind_speed_characteristic = service->createCharacteristic(wind_speed_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  wind_dir_characteristic = service->createCharacteristic(wind_dir_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
  rain_mm_characteristic = service->createCharacteristic(rain_mm_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

  // Enable notifications
  BLE2902* baro_temp_desc = new BLE2902();
  baro_temp_desc->setNotifications(true);
  baro_temp_characteristic->addDescriptor(baro_temp_desc);

  BLE2902* baro_pressure_temp = new BLE2902();
  baro_pressure_temp->setNotifications(true);
  baro_pressure_characteristic->addDescriptor(baro_pressure_temp);

  BLE2902* light_desc = new BLE2902();
  light_desc->setNotifications(true);
  light_characteristic->addDescriptor(light_desc);

  BLE2902* temp_desc = new BLE2902();
  temp_desc->setNotifications(true);
  temp_characteristic->addDescriptor(temp_desc);

  BLE2902* humi_desc = new BLE2902();
  humi_desc->setNotifications(true);
  humi_characteristic->addDescriptor(humi_desc);

  BLE2902* wind_speed_desc = new BLE2902();
  wind_speed_desc->setNotifications(true);
  wind_speed_characteristic->addDescriptor(wind_speed_desc);

  BLE2902* wind_dir_desc = new BLE2902();
  wind_dir_desc->setNotifications(true);
  wind_dir_characteristic->addDescriptor(wind_dir_desc);

  BLE2902* rain_mm_desc = new BLE2902();
  rain_mm_desc->setNotifications(true);
  rain_mm_characteristic->addDescriptor(rain_mm_desc);

  // Start the service and advertising
  service->start();
  advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(serviceUUID);
  advertising->setScanResponse(true);
  advertising->setMinPreferred(0x06); 
  advertising->setMinPreferred(0x12);  
  BLEDevice::startAdvertising();

  Serial.println("Waiting for connections...");
}

void check_notify(float value, float* last_value, String msg, BLECharacteristic* characteristic) {
    if (value > *last_value + *last_value*THRESHOLD || value < *last_value - *last_value*THRESHOLD) {
      Serial.println(msg + String(value));
      characteristic->setValue(String(value).c_str());
      characteristic->notify();
      *last_value = value;
    }
}

void check_notify_string(String value, String* last_value, String msg, BLECharacteristic* characteristic) {
  if (value != *last_value) {
      Serial.println(msg + String(value));
      characteristic->setValue(String(value).c_str());
      characteristic->notify();
      *last_value = value;
  }
}

void loop() {
  if (ConnectionEtablie) {
    // Update the value of the characteristic
    check_notify(barometer_sensor.get_temperature(), &baro_temp, "NOTIFY : baro temperature : ", baro_temp_characteristic);
    check_notify(barometer_sensor.get_pressure(), &baro_humi, "NOTIFY : baro pressure : ", baro_pressure_characteristic);
    check_notify(humidity_sensor.get_temp(), &temp, "NOTIFY : temperature : ", temp_characteristic);
    check_notify(humidity_sensor.get_humidity(), &humi, "NOTIFY : humidity : ", humi_characteristic);
    check_notify(wind_sensor.get_wind_speed(), &wind_speed, "NOTIFY : wind speed : ", wind_speed_characteristic);
    check_notify(rain_sensor.get_rain_mm(), &rain_mm, "NOTIFY : rain mm : ", rain_mm_characteristic);

    check_notify_string(light_sens.get_info(), &light, "NOTIFY : light : ", light_characteristic);
    check_notify_string(wind_sensor.get_wind_direction_string(), &wind_dir, "NOTIFY : wind direction : ", wind_dir_characteristic);
  }

  if(!ConnectionEtablie){
    BLEDevice::startAdvertising();
  }  
  
  delay(1000);  // Update the value every 1 seconds
}

