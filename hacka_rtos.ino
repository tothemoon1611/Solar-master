#define SIM Serial1
#define WIFI Serial2
#define CAMERA Serial3
#define Monitor SerialUSB

#define DEBUGER
//#define SETTIME

#include <FreeRTOS_ARM.h>
#include <SPI.h>
#include <SD.h>
#include "DS3231.h"
#include <LiquidCrystal_I2C.h>
#include "config.h"
#include <Wire.h>
#include "command.h"
#include <Keypad.h>
#include <string.h>
#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);


bool ReadMetalSensor;
DS3231  rtc(SDA1, SCL1);
File myFile;
Time  t;
String InputString = "";
String DisplayString = "";
boolean StringComplete = false;

// The LED is attached to pin 13 on Arduino.
const uint8_t LED_PIN = 13;
int initial_motor_speed = 200;
// Declare a semaphore handle.
SemaphoreHandle_t sem;
SemaphoreHandle_t sem2;

DataMachine dataMachine;
WifiPayload wifiPayload  ;


static void BlynkLed(void* arg) {

  pinMode(LED_PIN, OUTPUT);

  while (1) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);
  }
}
//------------------------------------------------------------------------------
void Robot_Init(void *pvParameters) {

  /*------SETUP SD CARD---*/
  SDformat();
  /*------SETUP RTC---*/
  RTC_Init();

  for (;;)
  {

    vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  }
}


//------------------------------------------------------------------------------
/* Sensor*/
void Read_Sensor(void *pvParameters)
{
  unsigned long last_time;
  for (;;)
  {
    float Vbat   = float(analogRead(A0)) * (3.3 / 1023.0) * (9.72 / 2.18 + 1);
    float instantCurrent = (((float)analogRead(A1) - 512)  * (3.3 / 1023.0) / (66.0 / 1000)); //ACS712 Measuring Current of Battery
    //        if(abs(Vbat)<100) {
    //          Serial.print("Voltage: ");
    //          Serial.println(analogRead(A0));
    //         WIFI.print(String(Start) + String(updateVoltageBattery) + (int)Vbat + String(End));
    //        }
    //        if(abs(instantCurrent)<100) {
    //          Serial.print("Current: ");
    //          Serial.println(instantCurrent);
    //         WIFI.print(String(Start) + String(updateCurrentBattery) +abs((int)instantCurrent) + String(End));
    //        }
    if ( (unsigned long) (millis() - last_time) > 1000)
    {

      // WIFI.print(String(Start) + String(updateVoltageBattery) + (int)Vbat + String(End));
      WIFI.print(String(Start) + String(updateVoltageBattery));
      WIFI.print(Vbat, 2);
      WIFI.print(String(End));
      Serial.print(String(Start) + String(updateVoltageBattery));
      Serial.print(Vbat, 2);
      Serial.println(String(End));
      WIFI.print(String(Start) + String(updateCurrentBattery));
      WIFI.print(instantCurrent, 2);
      WIFI.print(String(End));
      Serial.print(String(Start) + String(updateCurrentBattery));
      Serial.print(instantCurrent, 2);
      Serial.println(String(End));


      last_time = millis();
    }
    dataMachine.MetalSensor = digitalRead(MetalSensorPin);
    dataMachine.LimitSW_1 = digitalRead(CheckWheel1);
    dataMachine.LimitSW_2 = digitalRead(CheckWheel2);
    dataMachine.VoltageBattery = Vbat;
    dataMachine.CurrentBattery = instantCurrent;
    xSemaphoreGive(sem);
    vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
  }

}

//------------------------------------------------------------------------------
/* Gui du lieu den Module Wifi*/
void Serial_wifi(void *pvParameters)
{
  Wifi();
}
//------------------------------------------------------------------------------
/* Gui du lieu den Module Wifi*/
void SDCard(void *pvParameters)
{
  /*------SETUP SD CARD---*/
  SDformat();
  // SDreadData();
  // xSemaphoreGive(sem);
  for (;;)
  {
    vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  }
}
//------------------------------------------------------------------------------
/* THUC THI MENU*/

void Menu(void *pvParameters)
{
  lcd.begin() ;
  lcd.backlight() ;
  String IDmin;
  String IDhour;
  String IDdate;
  String IDmon;
  for (;;)
  {
    Page_Processing() ;
    vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
  }
}

//------------------------------------------------------------------------------
void setup() {
  portBASE_TYPE s1, s2;

  Serial.begin(9600); // Monitor
  WIFI.begin(9600); // cong giao tiep NodeMCU
  CAMERA.begin(9600); // cong giao tiep Raspberry
  Motor_Setup() ;


  // initialize semaphore
  sem = xSemaphoreCreateCounting(1, 0);
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
