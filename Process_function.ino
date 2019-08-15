void Get_Wifi_Command() {

  int MovingSpeed = 0;
  int ChargingThreshold = 0;
  int SpinnerSpeed = 0;
  int MaxPower = 0;
  int MinPower = 0;
  String ContentIDError = "";
  String ContentACKSERVER = "";
  for (;;)
  {
    
    Serial4.print(123456789);
    Serial.print(123456789);
    vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    Get_Serial_Wifi();

    if (StringComplete) {
#ifdef DEBUGER
      Serial.print("Recv Wifi Slave: ");
      Serial.println(InputString);
#endif
      if ( xSemaphoreTake( sem_ProcessWifi, ( TickType_t ) 0 ) )
      {
        switch (cmd) {
          case setMovingSpeed:
            MovingSpeed = InputString.toInt();
#ifdef DEBUGER
            Serial.print("Set Moving Speed: ");
            Serial.println(MovingSpeed);
#endif
            break;
          case setSpinnerSpeed:
#ifdef DEBUGER
            Serial.print("Set Moving Speed: ");
            Serial.println(SpinnerSpeed);
#endif
            break;
          case setChargeThreshold:
#ifdef DEBUGER
            Serial.print("Set Moving Speed: ");
            Serial.println(ChargingThreshold);
#endif
            break;
          case setMaxPower:
#ifdef DEBUGER
            Serial.print("Set Moving Speed: ");
            Serial.println(MaxPower);
#endif
            break;
          case setMinPower:
#ifdef DEBUGER
            Serial.print("Set Moving Speed: ");
            Serial.println(MinPower);
#endif
            break;
          case IDError:
            ContentIDError = InputString;
#ifdef DEBUGER
            Serial.print("Server Error: ");
            Serial.println(ContentIDError);
#endif
            break;
          case ACKSERVERCmd:
            ContentACKSERVER = InputString;
            wifiPayload.ACK_SERVER = true;
#ifdef DEBUGER
            Serial.print("Server connect: ");
            Serial.println(ContentACKSERVER);
#endif
            break;
          case setMode:
            wifiPayload.Mode = InputString.toInt();
#ifdef DEBUGER
            Serial.print("Set Mode: ");
            Serial.println(wifiPayload.Mode);
#endif
            break;
          case setStop:
            wifiPayload.Stop = InputString.toInt();
#ifdef DEBUGER
            Serial.print("Set Stop: ");
            Serial.println(wifiPayload.Stop);
#endif
            break;
          case setContinue:
            wifiPayload.Continue = InputString.toInt();
#ifdef DEBUGER
            Serial.print("Set Continue: ");
            Serial.println(wifiPayload.Continue);
#endif
            break;
          case NetworkError: {
              wifiPayload.NetworkError = 1;
              Serial.println(InputString);
              break;
            }
          default:
            Serial.println("Unknown cmd!!!");
        }
      }
      InputString = "";
      StringComplete = false;

      xSemaphoreGive(sem_ReadWifi);
    }
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
  }
}

void Get_Encoder_Command() {
  for (;;)
  {
    Get_Serial_Encoder();
    if (StringComplete_EncoderSerial) {
#ifdef DEBUGER
      Serial.print("Recv Wifi Slave: ");
      Serial.println(InputString_EncoderSerial);
#endif
      switch (cmd_EncoderSerial) {
        case setEncoder:
#ifdef DEBUGER
          Serial.print("Set Encoder: ");
          Serial.println(InputString_EncoderSerial);
#endif
          break;
        default:
          Serial.println("Unknown cmd!!!");
      }
    }
    InputString_EncoderSerial = "";
    StringComplete_EncoderSerial = false;
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
  }
}


void Get_Serial_Wifi() {
  if (WIFI.available())
  {
    char inChar = (char)WIFI.read();
    if (inChar == Start) SerialRecv = true;
    if (inChar == End)
    {
      SerialRecv = false;
      serial_counter = 0;
      StringComplete = true;
    }
    if (SerialRecv)  serial_counter++;
    if (serial_counter == 2) cmd = inChar;
    if (serial_counter > 2) InputString += inChar;
  }
}

void Get_Serial_Encoder() {
  if (EncoderSerial.available())
  {
    char inChar_EncoderSerial = (char)EncoderSerial.read();
    if (inChar_EncoderSerial == Start) SerialRecv_EncoderSerial = true;
    if (inChar_EncoderSerial == End)
    {
      SerialRecv_EncoderSerial = false;
      serial_counter_EncoderSerial = 0;
      StringComplete_EncoderSerial = true;
    }
    if (SerialRecv_EncoderSerial)  serial_counter_EncoderSerial++;
    if (serial_counter_EncoderSerial == 2) cmd_EncoderSerial = inChar_EncoderSerial;
    if (serial_counter_EncoderSerial > 2) InputString_EncoderSerial += inChar_EncoderSerial;
  }
}

void RTC_Init() {
  rtc.begin();
#ifdef SETTIME
  rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(15, 31, 0);    // Set the time to 00:00:00 (24hr format)
  rtc.setDate(5, 8, 2019);   // Set the date to January 1st, 2014
#endif
  t = rtc.getTime();
#ifdef DEBUGER
  Serial.println("TIME: " + String(t.hour) + ":" + String(t.min));
#endif
}

void readVolt()
{
  float    Vbat   = float(analogRead(A0)) * (5.0 / 4095.0) * (10 / 2 + 1);
}
void readCurrent()
{
  float  instantCurrent = float(analogRead(A1) - 2048) * (3.3 / 4095.0) / (66.0 / 1000); //ACS712 Measuring Current of Battery
}
void UpdatetoESP(String Command, String data) {
  WIFI.print(String(Start) + Command + data + String(End));
}
