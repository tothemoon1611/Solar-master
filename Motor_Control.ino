
void Code_Run_V1()
{
  bool out = 0 ;
  bool MotorTemp = 0 ;
  Motor_Right_Start() ;
  Motor_Cleaning_Start() ;
  lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
  lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  while (1)
  {
    Menu_ReadSensor();
    Menu_WifiPayload();
    if (  MenuSensor.MetalSensor == 0 && MotorTemp == 0) {
      MotorTemp = 1 ;
    }
    if (  MenuSensor.MetalSensor == 1 && MotorTemp == 1)
    {
      MotorTemp = 0;
      PanPos++ ;
      lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
      lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
      Serial.println(PanPos) ;
      Serial2.print(PanPos) ;
    } else {}

    if ( MenuSensor.LimitSW_2 == 0)
    {
      Motor_Cleaning_Stop() ;
      Motor_Left_Start() ;
      while ( MenuSensor.LimitSW_1 == 1)
      {
        Menu_ReadSensor();
        Menu_WifiPayload();
        if (  MenuSensor.MetalSensor == 0 && MotorTemp == 0) {
          MotorTemp = 1 ;
        }
        if (  MenuSensor.MetalSensor == 1 && MotorTemp == 1)
        {
          MotorTemp = 0;
          if (PanPos) PanPos-- ;
          lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ; // lcd(0,2)
          lcd.setCursor(16, 2) ; lcd.print(PanPos) ;          // lcd(16,2)
          Serial.println(PanPos) ;
          Serial2.print(PanPos) ;                      //      gui du lieu cho ESP
        } else {}

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
      //out = 1 ;
      MenuWifi.Mode = 0;
      wifiPayload.Mode = 0 ;
      Motor_Run_Stop() ; 
      Motor_Cleaning_Stop() ;
      break ;
    }
    if (out == 1 ) {
      out = 0 ;
      break ;
    }
    Wait_Task() ;
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
        Code_Run_V1() ;
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

void F_Code_Run_V2()
{

}

//-------------------------Thiet Lap Ban Dau Cho Dong Co------------------------------------------------//

void Motor_Setup()
{
  pinMode(MetalSensorPin, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(CheckWheel2, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(CheckWheel1, INPUT_PULLUP) ;   // duong-nau, am-xanh

  pinMode(IN1, OUTPUT) ;
  pinMode(IN2, OUTPUT) ;
  pinMode(IN3, OUTPUT) ;
  pinMode(IN4, OUTPUT) ;
  pinMode(ENA, OUTPUT) ;
  pinMode(ENB, OUTPUT) ;
}


//--------------------------------------------Dieu Khien Dong Co------------------------------------------------//
void Motor_Right_Start()
{
  analogWrite(ENA, 255); // Send PWM signal to motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}


void Motor_Left_Start()
{
  analogWrite(ENA, 255); // Send PWM signal to motor A
  // Set Motor RUN Left
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}


void Motor_Run_Stop()
{
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}


void Motor_Cleaning_Start()
{
  analogWrite(ENB, 255); // Send PWM signal to motor A
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void Motor_Cleaning_Stop()
{
  analogWrite(ENB, 0); // Send PWM signal to motor A
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
