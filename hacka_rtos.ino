#define WIFI Serial1
#define SIM Serial2
#define EncoderSerial Serial3 
#define CAMERA Serial4

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
#include "PS2X_lib.h"

Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
PS2X ps2x; // create PS2 Controller Class

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
SemaphoreHandle_t sem_ReadEncoder;

DataMachine dataMachine;
WifiPayload wifiPayload  ;
WifiPayload MenuWifi ;
DataMachine MenuSensor;

// wifiPayload.ACK_SERVER = false ;


// Use the Arduino core to set-up the unused USART2 on Serial4
RingBuffer rx_buffer5;
RingBuffer tx_buffer5;
USARTClass Serial4(USART2, USART2_IRQn, ID_USART2, &rx_buffer5, &tx_buffer5);
//void serialEvent4() __attribute__((weak));
//void serialEvent4() { }

void USART2_Handler(void)   // Interrupt handler for UART2
{
  Serial4.IrqHandler();     // In turn calls on the Serial2 interrupt handler
}


//------------------------------------------------------------------------------
void setup() {
  portBASE_TYPE s1, s2;

  Serial.begin(9600); // Monitor
  EncoderSerial.begin(9600); // cong giao tiep NodeMCU
  WIFI.begin(9600); // cong giao tiep NodeMCU 
//  CAMERA.begin(9600); // cong giao tiep Raspberry
  SerialUSB.begin(9600); // Monitor
  PIO_Configure(PIOB, PIO_PERIPH_A, PIO_PB20A_TXD2 | PIO_PB21A_RXD2, PIO_DEFAULT);
  Serial4.begin(9600);
  Motor_Setup() ;
  pinMode(A0, OUTPUT) ;
  // pinMode(A0, OUTPUT) ;

  // initialize semaphore
  sem_ReadData = xSemaphoreCreateCounting(1, 0);
  sem_ProcessData = xSemaphoreCreateCounting(1, 0);
  sem_ReadWifi = xSemaphoreCreateCounting(1, 0);
  sem_ProcessWifi = xSemaphoreCreateCounting(1, 0);
  sem_ReadEncoder = xSemaphoreCreateCounting(1, 0);
  sem2 = xSemaphoreCreateCounting(1, 0);

  s2 = xTaskCreate(BlynkLed, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

 xTaskCreate(Serial_wifi, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  xTaskCreate(Serial_Encoder, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

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
