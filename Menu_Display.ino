
//---------------------------------------HIEN THI, NHAP LIEU---------------------------------------------------------------//
void LCD_Page_1_Display()
{
  lcd.clear() ;
  pointer = 0;
  PointerMax =  sizeof(LCDSettingMode)/ sizeof(int) ;
  while (1)
  {
    lcd.clear() ;
    for ( int i = 0; i < PointerMax ; i++ )
    {
      lcd.setCursor(0, i);
      lcd.print(LCDSettingMode[i]) ;
      lcd.setCursor(19, pointer) ;
      lcd.print("<") ;
    }
    Keypad_Option() ;
    if (BreakPage == 1) { BreakPage = 0 ; break ; }
    if (OkPage == 1) { OkPage = 0 ; Page_Pointer[1] = pointer ; break ; }
    Wait_Task();
  }
  
}



void LCD_Page_2_Display()
{
  lcd.clear() ;
  pointer = 0;
  while (1)
  {
    lcd.clear() ;
    switch (Page_Pointer[1])
    {
      case 0: { LCD_ParametersSetup() ; break ; }
      case 1: { LCD_TestingMode() ; break ; }
      case 2: { LCD_SetWorkingMode() ; break ; }
      case 3: { LCD_Automatic() ; break ; }
    }
    Keypad_Option() ;
    if (BreakPage == 1) { BreakPage = 0 ; break ; }
    if (OkPage == 1) { OkPage = 0 ; Page_Pointer[2] = pointer ; break ; }
    Wait_Task();
  }
   
}


void LCD_Page_3_Display()
{
  lcd.clear() ;
  pointer = 0;
  while (1)
  {
    lcd.clear() ;
    if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 0) ) { LCD_RobotID() ; } 
    if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) ) { LCD_MotorSetup() ; } 
    if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 2) ) { LCD_ChargingSetup() ;  } 
    
    if ( (Page_Pointer[1] == 1) && (Page_Pointer[2] == 0) ) { LCD_HandControl() ;  } 
    if ( (Page_Pointer[1] == 1) && (Page_Pointer[2] == 1) ) { LCD_CameraTest() ;  } 
    if ( (Page_Pointer[1] == 1) && (Page_Pointer[2] == 2) ) { Connect_Wifi() ;  } 
    if ( (Page_Pointer[1] == 1) && (Page_Pointer[2] == 3) ) { LCD_WorkTest() ; } 

    if ( (Page_Pointer[1] == 2) && (Page_Pointer[2] == 2) ) { Server_SetMode() ; }
    
    Keypad_Option() ;
    if (BreakPage == 1) { BreakPage = 0 ; break ; }
    if (OkPage == 1) { OkPage = 0 ; Page_Pointer[3] = pointer ; break ; }
    Wait_Task();
  }
   
}




void LCD_Page_4_Display()
{
  lcd.clear() ;
  pointer = 0 ;
  while (1)
  {
    lcd.clear() ;
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 0 ) && ( Page_Pointer[3] == 0 )) { Get_ID() ;  }
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 0 ) && ( Page_Pointer[3] == 2 )) { Network_Config() ; break ; }
    
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 1 ) && ( Page_Pointer[3] == 0 )) { Set_PID() ;  }
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 1 ) && ( Page_Pointer[3] == 1 )) { Set_PID() ;  }
    
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 2 ) && ( Page_Pointer[3] == 0 )) { Energy_Alert() ;  }

    if (( Page_Pointer[1] == 1 ) && ( Page_Pointer[2] == 2 ) && ( Page_Pointer[3] == 2 )) {  }

    if (( Page_Pointer[1] == 1 ) && ( Page_Pointer[2] == 3 ) && ( Page_Pointer[3] == 0 )) { Code_Run_V1() ;  }
    if (( Page_Pointer[1] == 1 ) && ( Page_Pointer[2] == 3 ) && ( Page_Pointer[3] == 1 )) {  }
    if (( Page_Pointer[1] == 1 ) && ( Page_Pointer[2] == 3 ) && ( Page_Pointer[3] == 2 )) {  }
    if (( Page_Pointer[1] == 1 ) && ( Page_Pointer[2] == 3 ) && ( Page_Pointer[3] == 3 )) {  }
   
    Keypad_Option() ;
    if (BreakPage == 1) { BreakPage = 0 ; break ; }
    if (OkPage == 1) { OkPage = 0 ; Page_Pointer[4] = pointer ; break ; }
    Wait_Task();
  }
  
}

//-----------------------------------------------------------HAM XU LY PAGE & NHAP LIEU---------------------------------------//
void Page_Processing()
{
  switch (Page)
  {
    case 1: {
        LCD_Page_1_Display() ;
        break ;
      }

    case 2: {
        LCD_Page_2_Display() ;
        break ;
      }

    case 3: {
        LCD_Page_3_Display() ;
        break ;
      }

    case 4: {
        LCD_Page_4_Display() ;
        break ;
      }

//    case 5: {
//        //LCD_Page_5_Display() ;
//        break ;
//      }
  }
}


void Keypad_Set_Value() 
{
   LcdTemp = 0 ;
   while(1) 
   {
     Key = keypad.getKey();
     x = Key ;
     if ( ((int)keypad.getState() ==  PRESSED) &&  (Key != 0) )
      {
        switch(Key) 
          {
            case '1' : {  MAXSize = sizeof(ButONE) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButONE[i] ; } Keypad_Processing() ; break ; }
            case '2' : {  MAXSize = sizeof(ButTWO) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButTWO[i] ; } Keypad_Processing() ; break ; }
            case '3' : {  MAXSize = sizeof(ButTHREE) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButTHREE[i] ; } Keypad_Processing() ; break ; }
            case '4' : {  MAXSize = sizeof(ButFOUR) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButFOUR[i] ; } Keypad_Processing() ; break ; }
            case '5' : {  MAXSize = sizeof(ButFIVE) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButFIVE[i] ; } Keypad_Processing() ; break ; }
            case '6' : {  MAXSize = sizeof(ButSIX) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButSIX[i] ; } Keypad_Processing() ; break ; }
            case '7' : {  MAXSize = sizeof(ButSEVEN) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButSEVEN[i] ; } Keypad_Processing() ; break ; }
            case '8' : {  MAXSize = sizeof(ButEIGHT) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButEIGHT[i] ; } Keypad_Processing() ; break ; }
            case '9' : {  MAXSize = sizeof(ButNINE) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButNINE[i] ; } Keypad_Processing() ; break ; } 
            case '0' : {  MAXSize = sizeof(ButZERO) ; for(int i = 0; i < MAXSize ; i++) { ButTemp[i] = ButZERO[i] ; } Keypad_Processing() ; break ; }
            case OK :
              {
                Serial.println(TempData) ;
                LcdTemp = 0;
                Serial.print("Sau khi reset : ") ;
                Serial.println(TempData) ;
                lcd.setCursor(0, 2) ;
                lcd.print(TempData) ;
                Wait_Task() ;
                OkPage = 1 ;  
                break ;
              }
            case BACK :  
              {
                BreakPage = 1 ; 
                break ;
              }
            case BACKSPACE : 
              {
                LcdTemp--  ;
                lcd.setCursor(LcdTemp, 2) ;
                lcd.print(' ') ;
                TempData.remove(LcdTemp) ; /// ham remove de xoa 1 ki tu trong chuoi 
                lcd.setCursor(0, 2) ;
                lcd.print(TempData) ;
                break ;  
              }
         }
     if( OkPage == 1 ) { OkPage = 0 ; break ; } 
     if( BreakPage == 1 ) {  break ; }
        
      }
      Wait_Task() ;
   }
   
}


void Keypad_Processing() 
  {
    Serial.println(Key) ;
    ValTemp = 0 ;
    lcd.setCursor(LcdTemp, 2) ;
    lcd.print(Key) ;
    Wait_Task() ;
    TimeKeypad = millis() ;
    while(1) 
    {
      char KeyContinue = keypad.getKey();
      if ( ((int)keypad.getState() ==  PRESSED) ) 
        {
//          if( (KeyContinue != x ) )            // ngay tai day xu ly khi dang thao tac nut nay ma nhan sang nut khac.
//            { 
//              Serial.print(" Slected  : ") ;
//              Serial.println(Key) ;
//              Serial.println("") ;
//              break ;
//            }
        
          if( (KeyContinue == x ) )
            {
              if( ValTemp < MAXSize -1 ) { ValTemp++ ; } 
              else { ValTemp = 0 ; } 
              Key  = ButTemp[ValTemp] ;
              lcd.setCursor(LcdTemp, 2) ;
              lcd.print(Key) ;
              Serial.println(Key) ;
              TimeKeypad = millis() ;
            }
        } 
      if( (unsigned long)(millis() - TimeKeypad) > 500 )
        {
          lcd.setCursor(LcdTemp, 2) ;
          lcd.print(Key) ;
          TempData += ButTemp[ValTemp] ;
          Serial.print(" Slected  : ") ;
          Serial.print(ButTemp[ValTemp]) ;
          lcd.setCursor(0, 2) ;
          lcd.print(TempData) ;
          LcdTemp++;
//          Serial.println(Key) ;
          Serial.println("") ;
          break ; 
        }
        Wait_Task();
    }
}



void Keypad_Option()
{
  while (1)
  {
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
      {
        if ( Key == UP )
        {
          vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
          if (pointer == 0) {
            pointer = 0;
          }
          else {
            pointer-- ;
          }
          break ;
        }
        if ( Key == DOWN )
        {
          vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
          if (pointer == ( PointerMax - 1) ) {
            pointer = PointerMax - 1 ;
          }
          else {
              pointer++ ;
          }
          break ;
        }
         
        if ( Key == OK )
        {
          vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
          OkPage = 1 ;
          if (Page == PageMAX) {
            Page = PageMAX ;
          }
          else {
            Page++;
          }
          break ;
        }
        if ( Key == BACK )
        {
          vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
          BreakPage = 1 ;
          if (Page == 1) {
            Page = 1 ;
          }
          else {
            Page--;
          } 
          //pointer = Page_Pointer[Page] ;
          break ;
        }
      }
      Wait_Task() ;
  }
}
//-----------------------------------------------CAC HAM DUOI DAY DUNG DE HIEN THI CAC BIEN CHAR* RA LCD---------------------------------------------------//


//--PAGE 2----------//
void LCD_ParametersSetup()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDParametersSetup)/sizeof(int) ;
  for ( int i = 0; i < PointerMax ; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDParametersSetup[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_TestingMode()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDTestingMode)/sizeof(int) ;
  for ( int i = 0; i < PointerMax ; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDTestingMode[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_SetWorkingMode()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDSetWorkingMode)/sizeof(int) ;
  for ( int i = 0; i < PointerMax ; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDSetWorkingMode[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_Automatic()
{
  lcd.clear() ;
  lcd.setCursor(0, 0) ;
  lcd.print(LCDAutomatic[0]) ;    // bat dau ham lam viec tu dong
}

//--PAGE 3----------//
void LCD_FixedID()
{
//lcd.clear() ;
//lcd.setCursor(0, 0) ;
 // lcd.print(LCDFixedID[0]) ;       // bat dau ham khoi tao ID cho robot
  String AssignedID = String(t.min) + String(t.hour) + String(t.date) + String(t.mon) + String(t.year);
 Serial.println(AssignedID);
  Serial.println(String(Start) + String(IDCmd) + AssignedID + String(End));
  WIFI.print(String(Start) + String(IDCmd) + AssignedID + String(End));
  Serial.println(String(Start) + String(CapImg) + String("{'panel':1,'collumn':2}") + String(End));
//  //CAMERA.print(String(Start) + String(CapImg)  +String("{'panel':1','collumn':2}")+ String(End));
//  CAMERA.println(String(Start) + String(CapImg)  +String("{'panel':1','collumn':2}")+ String(End));
//  //0x84+0x70+"{'panel':1','collumn':2}"+0x95
}

void LCD_RobotID()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDRobotID)/sizeof(int) ;
  for ( int i = 0; i < PointerMax ; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDRobotID[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_MotorSetup()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDMotorSetup)/sizeof(int) ;
  for ( int i = 0; i < PointerMax; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDMotorSetup[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_ChargingSetup()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDChargingSetup)/sizeof(int) ;
  for ( int i = 0; i < PointerMax; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDChargingSetup[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_HandControl()
{
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print(LCDHandControl[0]) ;
}

void LCD_CameraTest()
{
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print(LCDCameraTest[0]) ;
}

void LCD_CommuTest()
{
  lcd.clear() ;
  lcd.setCursor(0, 0);
  lcd.print(LCDCommuTest[0]) ;
}

void LCD_WorkTest()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDWorkTest)/sizeof(int) ;
  for ( int i = 0; i < PointerMax; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDWorkTest[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

//--PAGE 4----------//
void LCD_MovingMotor()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDMovingMotor)/sizeof(int) ;
  for ( int i = 0; i < PointerMax; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDMovingMotor[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}

void LCD_CleaningMotor()
{
  lcd.clear() ;
  PointerMax = sizeof(LCDCleaningMotor)/sizeof(int) ;
  for ( int i = 0; i < PointerMax; i++ )
  {
    lcd.setCursor(0, i);
    lcd.print(LCDCleaningMotor[i]) ;
    lcd.setCursor(19, pointer);
    lcd.print("<") ;
  }
}
