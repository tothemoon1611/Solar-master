


//---------------------------------CAC HAM THUC THI (FLAG) VA NHAP LIEU----------------------------------------------//
//--NHAP LIEU----------//

void Energy_Alert()
{
  lcd.clear() ;

  while (1)
  {
    lcd.setCursor(0, 0) ;
    lcd.print("Set Alert Energy :") ;
    lcd.setCursor(0, 2) ;
    lcd.print("Alert Lever = ") ;
    lcd.setCursor(14, 2) ;
    lcd.print(Value) ;
    if (digitalRead(OK) == 0)
    {
      Wait_Task() ;
      EnerAlert = Value ;
    }
    if (digitalRead(BACK) == 0)
    {
      Wait_Task() ;
      break ;
    }
    lcd.setCursor(0, 3) ;
    lcd.print("-->Selected:") ;
    lcd.setCursor(13, 3) ;
    lcd.print(EnerAlert) ;
    Wait_Task();
  }
}


void Set_PID()
{
  lcd.clear() ;
  pointer = 0;
  while (1)
  {
    char* SetPID[3] = { "Set Kp:", "Set Ki:", "SetKd :" } ;
    lcd.clear() ;
    for ( int i = 0; i < 3; i++ )
    {
      lcd.setCursor(1, i);
      lcd.print(SetPID[i]) ;
      lcd.setCursor(0, pointer);
      lcd.print(">") ;
      if (i == 0)
      {
        if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 0) ) {
          lcd.setCursor(9, 0);
          lcd.print(PIDKpMovSpd) ;
        }
        if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 1) ) {
          lcd.setCursor(9, 1);
          lcd.print(PIDKpCleSpd) ;
        }
      }
      if (i == 1)
      {
        if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 0) ) {
          lcd.setCursor(9, 0);
          lcd.print(PIDKiMovSpd) ;
        }
        if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 1) ) {
          lcd.setCursor(9, 1);
          lcd.print(PIDKiCleSpd) ;
        }
      }
      if (i == 2)
      {
        if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 0) ) {
          lcd.setCursor(9, 0);
          lcd.print(PIDKdMovSpd) ;
        }
        if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 1) ) {
          lcd.setCursor(9, 1);
          lcd.print(PIDKdCleSpd) ;
        }
      }
    }
    Keypad_Option() ;
    if ( OkPage == 1 && pointer == 0)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Enter your Kp Param:") ;
      lcd.setCursor(7, 1); lcd.print("Kp = ") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 0) ) {
        PIDKpMovSpd = TempData ;
      }
      if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 1) ) {
        PIDKpCleSpd = TempData ;
      }
      TempData = "" ;
    }
    if ( OkPage == 1 && pointer == 1)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Enter your Ki Param:") ;
      lcd.setCursor(7, 1); lcd.print("Ki = ") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 0) ) {
        PIDKiMovSpd = TempData ;
      }
      if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 1) ) {
        PIDKiCleSpd = TempData ;
      }
      TempData = "" ;
    }
    if ( OkPage == 1 && pointer == 2)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Enter your Kd Param:") ;
      lcd.setCursor(7, 1); lcd.print("Kd = ") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 0) ) {
        PIDKdMovSpd = TempData ;
      }
      if ( (Page_Pointer[1] == 0) && (Page_Pointer[2] == 1) && (Page_Pointer[3] == 1) ) {
        PIDKdCleSpd = TempData ;
      }
      TempData = "" ;
    }
    if ( BreakPage == 1 ) {
      BreakPage = 0;
      break ;
    }
    Wait_Task() ;
  }

}



void SSID_Config()
{
  lcd.clear() ;
  pointer = 0;
  while (1)
  {
    char* SetID[4] = { "SSID:", "PASS:", "IP  :", "PORT:" } ;
    lcd.clear() ;
    for ( int i = 0; i < 4; i++ )
    {
      lcd.setCursor(1, i);
      lcd.print(SetID[i]) ;
      lcd.setCursor(0, pointer);
      lcd.print(">") ;
      if (i == 0) {
        SDreadData(FileSSIDData) ;
        lcd.setCursor(6, 0);
        lcd.print(TempData) ;
        TempData = "" ;
      }
      if (i == 1) {
        SDreadData(FilePASSData) ;
        lcd.setCursor(6, 1);
        lcd.print(TempData) ;
        TempData = "" ;
      }
      if (i == 2) {
        SDreadData(FileIPAddData) ;
        lcd.setCursor(6, 2);
        lcd.print(TempData) ;
        TempData = "" ;
      }
      if (i == 3) {
        SDreadData(FilePORTData) ;
        lcd.setCursor(6, 3);
        lcd.print(TempData) ;
        TempData = "" ;
      }
    }
    Keypad_Option() ;
    if ( OkPage == 1 && pointer == 0)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Enter your SSID :") ;
      lcd.setCursor(6, 1); lcd.print("SSID :") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      SSIDData = TempData ;
      SDsaveData(SSIDData, FileSSIDData) ;
      TempData = "" ;
    }
    if ( OkPage == 1 && pointer == 1)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Enter your PASS :") ;
      lcd.setCursor(4, 1); lcd.print("PASSWORD :") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      PASSData = TempData ;
      SDsaveData(PASSData, FilePASSData) ;
      TempData = "" ;
    }
    if ( OkPage == 1 && pointer == 2)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Enter IP Address :") ;
      lcd.setCursor(3, 1); lcd.print("IP Address :") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      IPAddData = TempData ;
      SDsaveData(IPAddData, FileIPAddData) ;
      TempData = "" ;
    }
    if ( OkPage == 1 && pointer == 3)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Select PORT :") ;
      lcd.setCursor(6, 1); lcd.print("PORT :") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      PORTData = TempData ;
      SDsaveData(PORTData, FilePORTData) ;
      TempData = "" ;
    }
    if ( BreakPage == 1 ) {
      BreakPage = 0;
      break ;
    }
    Wait_Task() ;
  }

}


void Network_Config()
{
  lcd.clear() ;
  pointer = 1 ;

  while (1)
  {
    PointerMax =  3 ;
    Page = 4 ;
    if ( pointer == 0 ) {
      pointer = 1 ;
    }
    lcd.clear()  ;
    lcd.setCursor(4, 1) ; lcd.print("[ Config  ]") ;
    lcd.setCursor(4, 2) ; lcd.print("[ SIGN IN ]") ;
    lcd.setCursor(2, pointer) ; lcd.print(">") ;
    lcd.setCursor(17, pointer) ; lcd.print("<") ;
    Keypad_Option() ;
    if (BreakPage == 1) {
      BreakPage = 0 ;
      break ;
    }
    if (OkPage == 1)
    {
      OkPage = 0 ;
      if ( pointer == 1 ) {
        PointerMax =  4 ;
        SSID_Config() ;
      }
      if ( pointer == 2 )
      {
        lcd.clear() ;
        lcd.setCursor(4, 1) ; lcd.print("Are you OK ?")  ;
        lcd.setCursor(0, 3) ; lcd.print("<Cancel>") ;
        lcd.setCursor(16, 3) ; lcd.print("<Ok>") ;
        Keypad_Option() ;
        if (BreakPage == 1) {
          BreakPage = 0 ;
        }
        if (OkPage == 1) {
          OkPage = 0 ;
          Send_NetworkData() ;
        } //  Get_ID() ; }
      }
    }
    Wait_Task();
  }
}


void Send_NetworkData()
{
  lcd.clear() ; lcd.setCursor(3, 2) ; lcd.print("Sending...") ;
  SDreadData(FileSSIDData) ;
  Serial.println(String(Start) + String(WifiSSID) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiSSID) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FilePASSData) ;
  Serial.println(String(Start) + String(WifiPass) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiPass) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FileIPAddData) ;
  Serial.println(String(Start) + String(WifiIP) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiIP) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FilePORTData) ;
  Serial.println(String(Start) + String(WifiPort) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiPort) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;
  lcd.clear() ;
  int i = 5;
  while (1)
  {
    //if( (String)Timeout) { lcd.clear() ; lcd.setCursor(2,2); lcd.print("Connected Fail !") ; break ; }
    lcd.setCursor(3, 1) ; lcd.print("Please wait ...") ; lcd.setCursor(i, 2) ; lcd.print(".") ; if ( i == 12) {
      i = 5;
      lcd.clear() ;
    }
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
    {
      vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
      if ( Key == BACK )
      {
        break ;
      }
    }
    i++ ;
    Wait_Task() ;
  }
}


void Get_ID()
{
  SDreadData(FileHardIDData) ;
  //  if( TempData  != "") { lcd.clear() ; lcd.setCursor(0, 2) ; lcd.print("ID Existed !") ; vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L); }
  //  else
  //    {
  lcd.clear() ;
  lcd.setCursor(0, 2) ;
  lcd.print("Start Getting ID...") ;       // bat dau ham khoi tao ID cho robot
  vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L) ;
  String IDmin;
  String IDhour;
  String IDdate;
  String IDmon;
  if (t.min < 10) IDmin = String("0") + String(t.min);
  else IDmin = String(t.min);
  if (t.hour < 10) IDhour = String("0") + String(t.hour);
  else IDhour = String(t.hour);
  if (t.date < 10) IDdate = String("0") + String(t.date);
  else IDdate = String(t.date);
  if (t.mon < 10) IDmon = String("0") + String(t.mon);
  else IDmon = String(t.mon);
  String AssignedID = IDmin + IDhour + IDdate + IDmon + String(t.year);
  Serial.println(AssignedID);
  SDsaveData(AssignedID, FileHardIDData) ;

  Serial.println(String(Start) + String(IDCmd) + AssignedID + String(End));
  WIFI.print(String(Start) + String(IDCmd) + AssignedID + String(End));

  lcd.clear() ;
  int i = 5;
  while (1)
  {
    //if( (String)Timeout) { lcd.clear() ; lcd.setCursor(2,2); lcd.print("Connected Fail !") ; break ; }
    lcd.setCursor(3, 1) ; lcd.print("Please wait ...") ; lcd.setCursor(i, 2) ; lcd.print(".") ; if ( i == 12) {
      i = 5;
      lcd.clear() ;
    }
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
    {
      vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
      if ( Key == BACK )
      {
        break ;
      }
    }
    i++ ;
    Wait_Task() ;
  }
}

//}

//--CAC HAM THUC THI NHIEM VU---------//

void Hand_Control()
{

}

void Build_Map()
{

}

void Automatic()
{
  lcd.clear() ;
  lcd.setCursor(0, 1) ;
  lcd.print("Speed: ") ;
  String DisplayLCD = "";
  while (1) {
    //  lcd.setCursor(0, 1) ;
    //  lcd.print("Current: ") ;
    DisplayLCD = DisplayString;
    lcd.setCursor(10, 1) ;
    lcd.print(DisplayLCD) ;
    DisplayLCD = "";
    if (digitalRead(UP) == 0)
    {
      Wait_Task() ;
      if (pointer == 0) {
        pointer = 0;
      }
      else {
        pointer-- ;
      }
      break ;
    }
    if (digitalRead(DOWN) == 0)
    {
      Wait_Task() ;
      if (pointer == 3) {
        pointer = 3;
      }
      else {
        pointer++ ;
      }
      break ;
    }
    if (digitalRead(OK) == 0)
    {
      Wait_Task() ;
      OkPage = 1 ;
      if (Page == PageMAX) {
        Page = PageMAX ;
      }
      else {
        Page++;
      }
      break ;
    }
    if (digitalRead(BACK) == 0)
    {
      Wait_Task() ;
      BreakPage = 1 ;
      if (Page == 1) {
        Page = 1 ;
      }
      else {
        Page--;
      } ;
      //pointer = Page_Pointer[Page] ;
      break ;
    }
    Wait_Task;
  }
}
void Connect_Wifi() {
  lcd.clear() ; lcd.setCursor(3, 2) ; lcd.print("Sending...") ;
  
//  WIFI.print(String(Start) + String(ACKIDCmd) + wifiPayload.ACK_ID + String(End));
//  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  
  SDreadData(FileHardIDData) ;
  Serial.print(String(Start) + String(IDCmd) + TempData + String(End));
  WIFI.print(String(Start) + String(IDCmd) + TempData + String(End));
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FileSSIDData) ;
  Serial.println(String(Start) + String(WifiSSID) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiSSID) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FilePASSData) ;
  Serial.println(String(Start) + String(WifiPass) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiPass) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FileIPAddData) ;
  Serial.println(String(Start) + String(WifiIP) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiIP) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FilePORTData) ;
  Serial.println(String(Start) + String(WifiPort) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiPort) + TempData + String(End)) ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;
  lcd.clear() ; lcd.setCursor(3, 2) ; lcd.print("DONE!") ;

}
DataMachine MenuSensor;

void Menu_ReadSensor() {
  if ( xSemaphoreTake( sem, ( TickType_t ) 0 ) )
  {
    MenuSensor.MetalSensor = dataMachine.MetalSensor;
    MenuSensor.LimitSW_1 = dataMachine.LimitSW_1;
    MenuSensor.LimitSW_2 = dataMachine.LimitSW_2;
    MenuSensor.VoltageBattery = dataMachine.VoltageBattery;
    MenuSensor.CurrentBattery = dataMachine.CurrentBattery;
    Serial.println( MenuSensor.VoltageBattery);
  }
}

void Wait_Task()
{
  vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
}
