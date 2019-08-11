void Get_Command() {

  int MovingSpeed = 0;
  int ChargingThreshold = 0;
  int SpinnerSpeed = 0;
  int MaxPower = 0;
  int MinPower = 0;
  String ContentIDError = "";
  String ContentACKSERVER = "";
  for (;;)
  {
    Get_Serial_Wifi();
    if ( xSemaphoreTake( sem_ProcessWifi, ( TickType_t ) 0 ) )
    {
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
          case typeServerError:{
            ERROR_Processing() ;
            break;       }     
          default:
            Serial.println("Unknown cmd!!!");
        }
        InputString = "";
        StringComplete = false;
      }
      xSemaphoreGive(sem_ReadWifi);
    }
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


void ERROR_Processing() 
{
  Motor_Run_Stop() ; 
  Motor_Cleaning_Stop() ; 
  bool Error = 0 ;
  MenuWifi.ACK_SERVER = false ;
  wifiPayload.ACK_SERVER = false ;
  unsigned long WifiTimeout = millis() ;
  while( wifiPayload.ACK_SERVER != true ) 
    {
      lcd.setCursor(2,1) ;
      lcd.print("Disconnected to SV") ;
      lcd.setCursor(2,2) ;
      lcd.print("Retrying... ") ;
      if ( (unsigned long) (millis() - WifiTimeout) > 60000) { Error = 1 ; break ; }
    }
   if( Error == 0 ) { return Code_Run_V1() ; } 
   else{ Page_Processing() ; }  // can xu ly loi ngay tai day 
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
