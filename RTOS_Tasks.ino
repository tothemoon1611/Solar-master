static void BlynkLed(void* arg) {

  pinMode(StaLedYELLOW, OUTPUT);

  while (1) {
    // Turn LED on.
//    digitalWrite(LED_PIN, HIGH);
//    vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);
//    digitalWrite(LED_PIN, LOW);
//    vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);
    digitalWrite(StaLedYELLOW, HIGH);
    vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);
    digitalWrite(StaLedYELLOW, LOW);
    vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);
  }
}
//------------------------------------------------------------------------------
void Robot_Init(void *pvParameters) {

  /*------SETUP SD CARD---*/
  SDformat();
  /*------SETUP RTC---*/
  RTC_Init();
  xSemaphoreGive( sem_ProcessData);
  xSemaphoreGive( sem_ProcessWifi);
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  Init_Communication();

  for (;;)
  {
    vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  }
}


//------------------------------------------------------------------------------
/* Sensor*/
void Read_Sensor(void *pvParameters)
{
  analogReadResolution(10);
  unsigned long last_time;
  for (;;)
  {
    analogReadResolution(10);
    float Vbat   = float(analogRead(A6)) * (3.3 / 1023.0) * (11.2 / 1.2);
    float instantCurrent = (((float)analogRead(A7)*5.3 - 512*5)  /1023 / (66.0 / 1000)); //ACS712 Measuring Current of Battery
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
      WIFI.print(String(Start) + String(updateCurrentBattery));
      WIFI.print(instantCurrent, 2);
      WIFI.print(String(End));


      last_time = millis();
    }
    if ( xSemaphoreTake( sem_ProcessData, ( TickType_t ) 0 ) )
    {
      dataMachine.MetalSensor = digitalRead(IRSensor);
      dataMachine.LimitSW_1 = digitalRead(CheckWheel1);
      dataMachine.LimitSW_2 = digitalRead(CheckWheel2);
//      Serial.println(dataMachine.LimitSW_1);
//      Serial.println(dataMachine.LimitSW_2);
      dataMachine.VoltageBattery = Vbat;
      dataMachine.CurrentBattery = instantCurrent;
      xSemaphoreGive(sem_ReadData);
    }
    vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
  }

}

//------------------------------------------------------------------------------
/* Gui du lieu den Module Wifi*/
void Serial_wifi(void *pvParameters)
{
  Get_Wifi_Command();
  if ( Net_SocStatus == true )  digitalWrite(StaLedGREEN, HIGH) ;
  else digitalWrite(StaLedGREEN, LOW) ;
}
void Serial_Encoder(void *pvParameters)
{
  Get_Encoder_Command();
}

void Serial_CAMERA(void *pvParameters)
{
  Get_CAMERA_Command();
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
