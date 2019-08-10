bool Sensor_Temp;
void Code_Run_V1()
{
  bool out = 0 ;
  lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
  lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  while (!out)
  {
    Motor_Right_Start() ;
    Motor_Cleaning_Start() ;
    Menu_ReadSensor();
    Menu_WifiPayload();
    Menu_incPanelPos();

    if ( MenuSensor.LimitSW_2 == 0)
    {
      while ( MenuSensor.LimitSW_1 == 1)
      {
        Motor_Cleaning_Stop() ;
        Motor_Left_Start() ;
        Menu_ReadSensor();
        Menu_WifiPayload();
        Menu_decPanelPos();

        if (MenuSensor.LimitSW_1 == 0 ) {
          out = 1 ;
          Motor_Run_Stop() ;
          break ;
        }
        Key = keypad.getKey();
        if ( ((int)keypad.getState() ==  PRESSED) )
        {
          if ( Key == BACK )
          {
            out = 1 ;
            Wait_Task();
            Motor_Run_Stop() ;
            Motor_Cleaning_Stop() ;
            PanPos = 0 ;
            break ;
          }
        }
        if ( MenuWifi.Stop)
        {
          out = 1 ;
          Motor_Run_Stop() ;
          Motor_Cleaning_Stop() ;
          MenuWifi.Mode = 0;
          wifiPayload.Mode = 0 ;
          break ;
        }
      }
    }
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
    {
      if ( Key == BACK )
      {
        out = 1 ;
        Motor_Run_Stop() ;
        Motor_Cleaning_Stop() ;
        PanPos = 0 ;
        break ;
      }
    }
    if ( MenuWifi.Stop)
    {
      out = 1 ;
      MenuWifi.Mode = 0;
      wifiPayload.Mode = 0 ;
      Motor_Run_Stop() ;
      Motor_Cleaning_Stop() ;
      break ;
    }

    Wait_Task() ;
  }
}
//-------------------------------------WORK MODE 2-------------------------------//

void Code_Run_V2()
{
  bool out = 0 ;
  lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
  lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  while (!out)
  {
    Motor_Right_Start() ;
    Motor_Cleaning_Start() ;
    Menu_ReadSensor();
    Menu_WifiPayload();
    Menu_incPanelPos();
    Run_Mode();

    if ( MenuSensor.LimitSW_2 == 0)
    {
      while ( MenuSensor.LimitSW_1 == 1)
      {
        Motor_Cleaning_Stop() ;
        Motor_Left_Start() ;
        Menu_ReadSensor();
        Menu_WifiPayload();
        Menu_decPanelPos();
        Run_Mode();

        if (MenuSensor.LimitSW_1 == 0 ) {
          out = 1 ;
          Motor_Run_Stop() ;
          break ;
        }
        Key = keypad.getKey();
        if ( ((int)keypad.getState() ==  PRESSED) )
        {
          if ( Key == BACK )
          {
            out = 1 ;
            Wait_Task();
            Motor_Run_Stop() ;
            Motor_Cleaning_Stop() ;
            PanPos = 0 ;
            break ;
          }
        }
        if ( MenuWifi.Stop)
        {
          out = 1 ;
          Motor_Run_Stop() ;
          Motor_Cleaning_Stop() ;
          MenuWifi.Mode = 0;
          wifiPayload.Mode = 0 ;
          break ;
        }
      }
    }
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
    {
      if ( Key == BACK )
      {
        out = 1 ;
        Motor_Run_Stop() ;
        Motor_Cleaning_Stop() ;
        PanPos = 0 ;
        break ;
      }
    }
    if ( MenuWifi.Stop)
    {
      out = 1 ;
      MenuWifi.Mode = 0;
      wifiPayload.Mode = 0 ;
      Motor_Run_Stop() ;
      Motor_Cleaning_Stop() ;
      break ;
    }

    Wait_Task() ;
  }
}
void Run_Mode() {
  while (Run) {
    Menu_WifiPayload();
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
    Wait_Task();
  }
}

void Menu_incPanelPos() {

  if (  MenuSensor.MetalSensor == 0 && Sensor_Temp == 0) Sensor_Temp = 1  ;
  if (  MenuSensor.MetalSensor == 1 && Sensor_Temp == 1)
  {
    Sensor_Temp = 0;
    PanPos++ ;
    lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
    //Serial.println(PanPos) ;
    UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
    UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
  }
}

void Menu_decPanelPos() {

  if (  MenuSensor.MetalSensor == 0 && Sensor_Temp == 0) Sensor_Temp = 1 ;
  if (  MenuSensor.MetalSensor == 1 && Sensor_Temp == 1)
  {
    Sensor_Temp = 0;
    if (PanPos) PanPos-- ;
    lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
    //Serial.println(PanPos) ;
    UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
    UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
  }
}
//-------------------------------------WORK MODE 2-------------------------------//
void Server_SetMode()
{
  lcd.clear() ;
  lcd.setCursor(1, 1) ; lcd.print("Excute From Center") ;
  lcd.setCursor(0, 3) ; lcd.print("<BACK>") ;
  lcd.setCursor(13, 3) ; lcd.print("<ALLOW>") ;
  Keypad_Option() ;
  if (BreakPage == 1) {
    BreakPage = 0 ;
  }
  if (OkPage == 1)
  {
    MenuWifi.Mode = 0 ;
    wifiPayload.Mode = 0 ;
    OkPage = 0 ;
    lcd.clear() ;
    lcd.setCursor(1, 1) ; lcd.print("Waiting for Command") ;
    while (1) {
      Menu_WifiPayload();
      if ( MenuWifi.Mode == 2 ) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Building Map ...") ;
        MenuWifi.Mode = 0 ;
      }
      if ( MenuWifi.Mode == 3 ) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Cleaning Mode... ") ;
        Code_Run_V2() ;
        MenuWifi.Mode = 0;
        wifiPayload.Mode = 0 ;
      }
      if ( MenuWifi.Mode == 1) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Full Mode...") ;
        MenuWifi.Mode = 0 ;
      }
      if ( MenuWifi.Mode == 4 ) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Monitor Mode...") ;

        MenuWifi.Mode = 0 ;
      }
      Key = keypad.getKey();
      if ( ((int)keypad.getState() ==  PRESSED) )
      {
        if ( Key == BACK )
        {
          break ;
        }
      }
      Wait_Task() ;
    }
  }
}



//-------------------------Thiet Lap Ban Dau Cho Dong Co------------------------------------------------//

void Motor_Setup()
{
  pinMode(MetalSensorPin, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(CheckWheel2, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(CheckWheel1, INPUT_PULLUP) ;   // duong-nau, am-xanh

  pinMode(DIR4, OUTPUT) ;               
  pinMode(DIR3, OUTPUT) ;
  pinMode(PWM4, OUTPUT) ;
  pinMode(PWM3, OUTPUT) ;
//  pinMode(ENA, OUTPUT) ;
//  pinMode(ENB, OUTPUT) ;
  digitalWrite(PWM4, HIGH) ;
  digitalWrite(PWM3, HIGH) ;
}


//--------------------------------------------Dieu Khien Dong Co------------------------------------------------//
void Motor_Right_Start()
{
  digitalWrite(DIR4, HIGH) ;
  analogWrite(PWM4, 0) ;
}


void Motor_Left_Start()
{
  digitalWrite(DIR4, LOW) ;
  analogWrite(PWM4, 0) ;
}


void Motor_Run_Stop()
{
  //digitalWrite(22, HIGH) ;
  analogWrite(PWM4, 255) ;
}


void Motor_Cleaning_Start()
{
  digitalWrite(DIR3, HIGH) ;
  analogWrite(PWM3, 0) ;
}


void Motor_Cleaning_Stop()
{
  digitalWrite(DIR3, HIGH) ;
  analogWrite(PWM3, 255) ;
}
