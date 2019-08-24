//---------------------------------CAC HAM THUC THI (FLAG) VA NHAP LIEU----------------------------------------------//
//--NHAP LIEU----------//
void Init_Communication() ;

void Energy_Alert()
{
  while (1)
  {
    lcd.clear() ;
    pointer = 0;
    lcd.setCursor(0, 0) ; lcd.print(">Energy Alert:") ;
    lcd.setCursor(19, 0) ; lcd.print("%") ;
    SDreadData(FileEAlertData) ;
    Serial.print(" Energy Alert" + TempData) ;
    lcd.setCursor(15, 0) ;
    lcd.print(TempData) ; TempData = "" ;
    Keypad_Option() ;
    if (OkPage == 1)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("Energy Alert Level:") ;
      lcd.setCursor(0, 1); lcd.print("Warning at: (0-100)") ;
      lcd.setCursor(19, 2); lcd.print("%") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      EnerALert  = TempData ;
      SDsaveData(EnerALert, FileEAlertData) ;
      TempData = "" ;
      break ;
    }
    if (BreakPage == 1)
    {
      BreakPage = 0 ;
      break ;
    }
    vTaskDelay((50L * configTICK_RATE_HZ) / 1000L) ;
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

void Set_PWM()
{
  lcd.clear() ;
  pointer = 0;
  while (1)
  {
    lcd.clear() ;
    lcd.setCursor(0, 0) ; lcd.print(">Set PWM:") ;
    lcd.setCursor(19, 0) ; lcd.print("%") ;
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 1 ) && ( Page_Pointer[3] == 0 )) {
      SDreadData(FilePWMMovData) ;  // hien thi gia tri PWM cua dong co moving da luu truoc do
      lcd.setCursor(15, 0) ;
      lcd.print(TempData) ;
      TempData = "" ;
    }
    if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 1 ) && ( Page_Pointer[3] == 1 )) {
      SDreadData(FilePWMCleData) ;  // hien thi gia tri PWM cua dong co cleaning da luu truoc do
      lcd.setCursor(15, 0) ;
      lcd.print(TempData) ;
      TempData = "" ;
    }
    Keypad_Option() ;
    if (OkPage == 1)
    {
      OkPage = 0 ;
      lcd.clear() ;
      lcd.setCursor(0, 0); lcd.print("PWM Moving Motor:") ;
      lcd.setCursor(4, 1); lcd.print("Set PWM = ") ;
      lcd.setCursor(19, 2); lcd.print("%") ;
      lcd.setCursor(0, 3); lcd.print("<-") ; lcd.setCursor(18, 3); lcd.print("->") ;
      Keypad_Set_Value() ;
      if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 1 ) && ( Page_Pointer[3] == 0 )) // luu gia tri PWM cua dong co Moving vao the nho
      {
        PWMMovSpd  = TempData ;
        SDsaveData(PWMMovSpd, FilePWMMovData) ;
        TempData = "" ;
      }
      if (( Page_Pointer[1] == 0 ) && ( Page_Pointer[2] == 1 ) && ( Page_Pointer[3] == 1 )) // luu gia tri PWM cua dong co Moving vao the nho
      {
        PWMCleSpd  = TempData ;
        SDsaveData(PWMCleSpd, FilePWMCleData) ;
        TempData = "" ;
      }
    }
    if (BreakPage == 1)
    {
      BreakPage = 0 ;
      break ;
    }
    vTaskDelay((50L * configTICK_RATE_HZ) / 1000L) ;
  }

}


void Set_PID_orPWM()
{
  char* SetPID_PWM[2] = { "1.Set PWM", "2.Set PID" } ;
  PointerMax =  2 ;
  Page = 5 ;
  lcd.clear() ;
  pointer = 0 ;
  while (1)
  {
    lcd.clear() ;
    for ( int i = 0; i < 2; i++ ) {
      lcd.setCursor(0, i) ;
      lcd.print(SetPID_PWM[i]) ;
      lcd.setCursor(19, pointer) ;
      lcd.print("<") ;
    }
    Keypad_Option() ;
    if (OkPage == 1 && pointer == 0) {
      OkPage = 0 ;
      Set_PWM() ;
    }
    if (OkPage == 1 && pointer == 1) {
      OkPage = 0 ;
      Set_PID() ;
    }
    if (BreakPage == 1) {
      break ;
    }
    vTaskDelay((10L * configTICK_RATE_HZ) / 1000L) ;
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
        TempData = "" ;
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
          Connect_Wifi() ;
        }
      }
    }
    Wait_Task();
  }
}


void Connect_Wifi()
{
  lcd.clear() ; lcd.setCursor(3, 2) ; lcd.print("Sending...") ;
  Init_Communication();
  lcd.clear() ; lcd.setCursor(3, 1) ; lcd.print("Sending DONE !") ;
  vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
  lcd.clear() ;
  int i = 5;
  bool Check  = 0 ;
  unsigned long TimeConnect = millis() ;
  Menu_WifiPayload();
  while ( MenuWifi.ACK_SERVER != true )
  {
    Menu_WifiPayload();
    lcd.setCursor(3, 1) ; lcd.print("Please wait ...") ; lcd.setCursor(i, 2) ; lcd.print(".") ; if ( i == 12) {
      Init_Communication();
      i = 3;
      lcd.clear() ;
    }
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
    {
      vTaskDelay((50L * configTICK_RATE_HZ) / 1000L);
      if ( Key == BACK )
      {
        Check = 1 ;
        break ;
      }
    }
    i++ ;
    vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
    if ( (unsigned long) (millis() - TimeConnect) > 30000) {
      Check = 1 ;
      break ;
    }
  }

  if (Check == 1)
  {
    Check = 0;
    lcd.clear() ;
    lcd.setCursor(4, 2) ;
    lcd.print("Connect failed !") ;
    for ( int i = 0; i < 7 ; i++ ) {
      digitalWrite(StaLedRED, HIGH);
      vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
      digitalWrite(StaLedRED, LOW);
      vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
    }
    MenuWifi.ACK_SERVER = false ;
    wifiPayload.ACK_SERVER = false ;
    xSemaphoreGive(sem_ProcessWifi);
  }
  else {
    Check = 0 ;
    lcd.clear() ;
    lcd.setCursor(4, 2) ;
    lcd.print("Connected !") ;
    for ( int i = 0; i < 7 ; i++ ) {
      digitalWrite(StaLedGREEN, HIGH);
      vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
      digitalWrite(StaLedGREEN, LOW);
      vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
    }
    digitalWrite(StaLedGREEN, HIGH);
    MenuWifi.ACK_SERVER = false ;
    wifiPayload.ACK_SERVER = false ;
    xSemaphoreGive(sem_ProcessWifi);
  }
}


void Get_ID()
{
  SDreadData(FileIDData) ;
  if(TempData)
    {
      lcd.clear() ; 
      lcd.setCursor(4,1); lcd.print("ID Was Init") ;
      lcd.setCursor(3,2); lcd.print("ReInitialize ?") ;
      lcd.setCursor(0,3); lcd.print("<BACK>          <OK>") ;
      Keypad_Option() ;
      if(OkPage == 1)
        {
          OkPage = 0 ;
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
          lcd.setCursor(0, 2) ;
          lcd.print("Getting ID Done!!!") ;
        }
       if(BreakPage == 1) { BreakPage = 0 ; }  
    }
  

}


//--CAC HAM THUC THI NHIEM VU---------//

void Init_Communication() {
  TempData = "" ;
  SDreadData(FileHardIDData) ;
  Serial.print(String(Start) + String(IDCmd) + TempData + String(End));
  WIFI.print(String(Start) + String(IDCmd) + TempData + String(End));
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FileSSIDData) ;
  Serial.println(String(Start) + String(WifiSSID) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiSSID) + TempData + String(End)) ;
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FilePASSData) ;
  Serial.println(String(Start) + String(WifiPass) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiPass) + TempData + String(End)) ;
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FileIPAddData) ;
  Serial.println(String(Start) + String(WifiIP) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiIP) + TempData + String(End)) ;
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;

  SDreadData(FilePORTData) ;
  Serial.println(String(Start) + String(WifiPort) + TempData + String(End)) ;
  WIFI.print(String(Start) + String(WifiPort) + TempData + String(End)) ;
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);
  TempData = "" ;
}


void Menu_ReadSensor() {
  if ( xSemaphoreTake( sem_ReadData, ( TickType_t ) 0 ) )
  {
    MenuSensor.MetalSensor = dataMachine.MetalSensor;
    MenuSensor.LimitSW_1 = dataMachine.LimitSW_1;
    MenuSensor.LimitSW_2 = dataMachine.LimitSW_2;
    MenuSensor.VoltageBattery = dataMachine.VoltageBattery;
    MenuSensor.CurrentBattery = dataMachine.CurrentBattery;

    xSemaphoreGive(sem_ProcessData);
  }
  if ( xSemaphoreTake( sem_ReadEncoder, ( TickType_t ) 0 ) )
  {
    MenuSensor.Encoder = dataMachine.Encoder;
  }
}

void Menu_WifiPayload()
{
  if ( xSemaphoreTake( sem_ReadWifi, ( TickType_t ) 0 ) )
  {
    MenuWifi.ACK_SERVER = wifiPayload.ACK_SERVER ;
    MenuWifi.ACK_NETWORK = wifiPayload.ACK_NETWORK ;
    MenuWifi.Mode = wifiPayload.Mode ;
    MenuWifi.Stop = wifiPayload.Stop ;
    MenuWifi.Continue = wifiPayload.Continue;
    MenuWifi.NetworkStatus = wifiPayload.NetworkStatus ;
    MenuWifi.ServerStatus = wifiPayload.ServerStatus ;
    MenuWifi.FixedIDMachine = wifiPayload.FixedIDMachine ;
    SDsaveData(wifiPayload.FixedIDMachine,FileIDData) ;
    if (MenuWifi.Continue) {
      Run = !Run;
      Serial.print("RUN: ");
      Serial.println(Run);
      MenuWifi.Continue = 0;
      wifiPayload.Continue = 0 ;
    }
    if (MenuWifi.ServerStatus == false || MenuWifi.NetworkStatus == false ) { ERROR_Processing() ; }
    xSemaphoreGive(sem_ProcessWifi);
  }
}


void Wait_Task()
{
  vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
}
