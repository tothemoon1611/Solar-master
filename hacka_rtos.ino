#define SIM Serial1
#define WIFI Serial2
#define CAMERA Serial3
#define Monitor SerialUSB

#define DEBUGER
//#define SETTIME

#include <FreeRTOS_ARM.h>
#include "DS3231.h"
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "config.h"
#include "command.h"
#include <Keypad.h>
#include <string.h>

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);


bool ReadMetalSensor;
DS3231  rtc(SDA1, SCL1);
File myFile;
Time  t;

// The LED is attached to pin 13 on Arduino.
const uint8_t LED_PIN = 13;
// Declare a semaphore handle.
SemaphoreHandle_t sem_ReadData;
SemaphoreHandle_t sem_ProcessData;
SemaphoreHandle_t sem_ReadWifi;
SemaphoreHandle_t sem_ProcessWifi;
SemaphoreHandle_t sem2;

DataMachine dataMachine;
WifiPayload wifiPayload  ;
WifiPayload MenuWifi ;
DataMachine MenuSensor;

// wifiPayload.ACK_SERVER = false ;



//------------------------------------------------------------------------------
void setup() {
  portBASE_TYPE s1, s2;

  Serial.begin(9600); // Monitor
  WIFI.begin(9600); // cong giao tiep NodeMCU
  CAMERA.begin(9600); // cong giao tiep Raspberry
  Motor_Setup() ;

  // initialize semaphore
  sem_ReadData = xSemaphoreCreateCounting(1, 0);
  sem_ProcessData = xSemaphoreCreateCounting(1, 0);
  sem_ReadWifi = xSemaphoreCreateCounting(1, 0);
  sem_ProcessWifi= xSemaphoreCreateCounting(1, 0);
  sem2 = xSemaphoreCreateCounting(1, 0);

  s2 = xTaskCreate(BlynkLed, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  xTaskCreate(Serial_wifi, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  xTaskCreate(Robot_Init, NULL, configMINIMAL_STACK_SIZE + 200, NULL, 4, NULL);

  xTaskCreate(Menu, NULL, configMINIMAL_STACK_SIZE + 200, NULL, 2, NULL);

  xTaskCreate(Read_Sensor, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL);

  // start schedulers
  vTaskStartScheduler();
  Serial.println(F("Insufficient RAM"));
  while (1);
}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}
