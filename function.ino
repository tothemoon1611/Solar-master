void Wifi() {
  bool SerialRecv = false;
  int serial_counter = 0;
  char cmd;
  int MovingSpeed = 0;
  int ChargingThreshold = 0;
  int SpinnerSpeed = 0;
  int MaxPower = 0;
  int MinPower = 0;
  String ContentIDError = "";
  String ContentACKID = "";
  for (;;)
  {
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
    if (StringComplete) {
      //   DisplayString = InputString;
      switch (cmd) {
        case setMovingSpeed:
          MovingSpeed = InputString.toInt();
#ifdef DEBUGER
          Serial.print("Set Moving Speed: ");
          Serial.println(MovingSpeed);
#endif
          DisplayString = MovingSpeed;
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
          Serial.print("IDError: ");
          Serial.println(ContentIDError);
#endif
          break;
        case ACKIDCmd:
          ContentACKID = InputString;
          wifiPayload.ACK_ID = true;
#ifdef DEBUGER
          Serial.print("SetupID: ");
          Serial.println(ContentACKID);
#endif
          break;
        default:
          Serial.println("Unknown cmd!!!");
      }
      // xSemaphoreGive(sem2);
      InputString = "";
      StringComplete = false;
    }
    xSemaphoreGive(sem2);
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
  }
}
void RTC_Init() {
  rtc.begin();
#ifdef SETTIME
  rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(20, 21, 0);    // Set the time to 00:00:00 (24hr format)
  rtc.setDate(13, 7, 2019);   // Set the date to January 1st, 2014
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
void UpdatetoSlave(String Command, String data) {
  WIFI.print(String(Start) + Command + data + String(End));
}
