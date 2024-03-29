// cau hinh giao tiep vs ras, cho ras khoi dong ( them goi tin khoi dong OK ), toi uu phan control motor, 4 sensor, them limit switch cho tay gamepad

bool Sensor_Temp;
int PanPosTemp = 0 ;
unsigned int PanPosMax = 0 ;

int Accelerate = 255 ;
int AccelerateCLE = 255 ;
int DelaySpeed = 1 ;

unsigned int TimeOutStr = 0 ;
void Exit_Mode_Online()
{
  Key = keypad.getKey();
  if ( ((int)keypad.getState() ==  PRESSED) )
  {
    if ( Key == BACK )
    {
      out = true ;
      Motor_Run_Stop() ;
      Motor_Cleaning_Stop() ;
      PanPos = 0 ;
    }
  }
  if ( MenuWifi.Stop)
  {
    out = true ;
    MenuWifi.Mode = 0;
    wifiPayload.Mode = 0 ;
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
  }
  if ( digitalRead(StopPin) == 0 )
  {
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
    lcd.clear() ;
    lcd.setCursor(4, 2) ; lcd.print("Resume... ?") ;
    while (digitalRead(StartPin) != 0) {
      Wait_Task() ;
    }
    Menu_ReadSensor();
    lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  }
}

void Exit_Mode_Offline()
{
  Key = keypad.getKey();
  if ( ((int)keypad.getState() ==  PRESSED) )
  {
    if ( Key == BACK )
    {
      out = true ;
      Motor_Run_Stop() ;
      Motor_Cleaning_Stop() ;
      PanPos = 0 ;
    }
  }
  if ( digitalRead(StopPin) == 0 )
  {
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
    lcd.clear() ;
    lcd.setCursor(4, 2) ; lcd.print("Resume... ?") ;
    while (digitalRead(StartPin) != 0) {
      Wait_Task() ;
    }
    Menu_ReadSensor();
    lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  }
}


void Code_Run_Offline()
{
    EncoderSerial.print(String(Start) + String(ResetEncoder) + String(End)) ; // yeu cau reset encoder
    MenuSensor.Encoder = 0 ;
    Menu_ReadSensor();
    SDreadData(FilePWMMovData) ;
    PWMMovSpd = TempData ;
    TempData = "" ;
    SDreadData(FilePWMCleData) ;
    PWMCleSpd = TempData ;
    TempData = "" ;
    out = false ;
    Input_String() ;
    TimeOutStr = 0 ;
    lcd.clear();
    lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
    while ( MenuSensor.LimitSW_2 != 0 )
    {
      Motor_Right_Start() ;
      Motor_CleaningR_Start() ;
      Menu_incPanelPos() ;
      Menu_ReadSensor();
      vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
      Exit_Mode_Offline() ;
      if ( out == true) { break ; } 
    }
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
    TimeOutStr = 0 ;
    while ( MenuSensor.LimitSW_1 != 0 )
    {
      Exit_Mode_Offline() ;
      if ( out == true) { break ; } 
      Motor_Left_Start() ;
      Motor_CleaningL_Start() ;
      Menu_decPanelPos() ;
      Menu_ReadSensor() ;
      vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
    }
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ; 
    TimeOutStr = 0 ;
}

//-------------------------------------WORK MODE 2-------------------------------//

void Code_Run_Online()
{
  EncoderSerial.print(String(Start) + String(ResetEncoder) + String(End)) ; // yeu cau reset encoder
  MenuSensor.Encoder = 0  ;
  Menu_ReadSensor();
  SDreadData(FilePWMMovData) ;
  PWMMovSpd = TempData ;
  TempData = "" ;
  SDreadData(FilePWMCleData) ;
  PWMCleSpd = TempData ;
  TempData = "" ;
  out = false ;
  UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
  UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
  UpdatetoESP(String(updateStatusParameter), String(1));
  UpdatetoESP(String(updateDirectionParameter), String(1));
  lcd.clear();
  lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
  lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  TimeOutStr = 0 ;
  while ( MenuSensor.LimitSW_2 != 0 )
    {
      Motor_Right_Start() ;
      Motor_CleaningR_Start() ;
      UpdatetoESP(String(updateStatusParameter), String(1));
      Menu_ReadSensor();
      Menu_WifiPayload();
      Menu_incPanelPos();
      Run_Mode();
      vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
      Exit_Mode_Online() ;
      if ( out == true) { break ; } 
    }
    TimeOutStr = 0 ;
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
    UpdatetoESP(String(updateStatusParameter), String(0));
    while ( MenuSensor.LimitSW_1 != 0 )
      {
        Exit_Mode_Online() ;
        if ( out == true) { break ; } 
        Motor_Left_Start() ;
        Motor_CleaningL_Start() ;
        UpdatetoESP(String(updateStatusParameter), String(1));
        Menu_ReadSensor();
        Menu_WifiPayload();
        Menu_incPanelPos();
        Run_Mode();
        vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
      }
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ; 
    UpdatetoESP(String(updateStatusParameter), String(0));
    TimeOutStr = 0 ;
}


void Building_Map()
{
  SDreadData(FilePWMMovData) ;
  PWMMovSpd = TempData ;
  TempData = "" ;
  Accelerate = 255 ;
  EncoderSerial.print(String(Start) + String(ResetEncoder) + String(End)) ; // yeu cau reset encoder
  MenuSensor.Encoder = 0  ;
  Menu_ReadSensor();
  PanPosMax = 0 ;
  out = false ;
  TimeOutStr = 0 ;
  UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
  UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
  UpdatetoESP(String(updateDirectionParameter), String(1));
  lcd.clear();
  lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
  lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  while ( MenuSensor.LimitSW_2 != 0 )
  {
    Motor_Right_Start() ;
    Menu_incPanelPos() ;
    Menu_ReadSensor();
    Menu_WifiPayload();
    Run_Mode();
    PanPosMax = PanPos ;
    //    WIFI.print(PanPosMax) ;
    //    lcd.setCursor(16, 2) ; lcd.print(PanPosMax) ;
    //    Serial.println(PanPosMax) ;
    Exit_Mode_Online() ;
    if ( out == true) { break ; } 
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
  }
  Motor_Run_Stop() ;
  UpdatetoESP(String(updateStatusParameter), String(0));
  Accelerate = 255 ;
  TimeOutStr = 0 ;
  bool Direct = false ;
  while ( MenuSensor.LimitSW_1 != 0 )
  {
    Motor_Left_Start() ;
    Menu_decPanelPos() ;
    Menu_ReadSensor() ;
    Menu_WifiPayload();
    Run_Mode();
    //    if (PanPos == 0 ) { Direct = true ; }
    //    if( Direct == true && PanPos != PanPosMax ) {
    //      PanPosMax = PanPosMax + PanPos ;
    //      WIFI.print(PanPosMax) ;
    //      lcd.setCursor(16, 2) ; lcd.print(PanPosMax) ;
    //      Serial.println(PanPosMax) ;
    //    }
    Exit_Mode_Online() ;
    if ( out == true) { break ; } 
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
  }
  Motor_Run_Stop() ;
  UpdatetoESP(String(updateStatusParameter), String(0));
  Direct = false ;
  TimeOutStr = 0 ;
}

void Building_Map_Offline()    // Toan code them luc 19h35 30/8
{
  SDreadData(FilePWMMovData) ;
  PWMMovSpd = TempData ;
  TempData = "" ;
  Accelerate = 255 ;
  EncoderSerial.print(String(Start) + String(ResetEncoder) + String(End)) ; // yeu cau reset encoder
  MenuSensor.Encoder = 0  ;
  Menu_ReadSensor();
  PanPosMax = 0 ;
  out = false ;
  Input_String() ;
  UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
  UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
  UpdatetoESP(String(updateDirectionParameter), String(1));
  lcd.clear();
  lcd.setCursor(0, 2) ; lcd.print("Panel Position:") ;
  lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
  TimeOutStr = 0 ;
  while ( MenuSensor.LimitSW_2 != 0 )
  {
    Exit_Mode_Offline() ;
    if ( out == true) { break ; } 
    Motor_Right_Start() ;
    Menu_incPanelPos() ;
    Menu_ReadSensor();
    PanPosMax = PanPos ;
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
  }
  Motor_Run_Stop() ;
  Accelerate = 255 ;
  bool Direct = false ;
  TimeOutStr = 0 ;
  while ( MenuSensor.LimitSW_1 != 0 )
  {
    Exit_Mode_Offline() ;
    if ( out == true) { break ; } 
    Motor_Left_Start() ;
    Menu_decPanelPos() ;
    Menu_ReadSensor() ;
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
  }
  Motor_Run_Stop() ;
  Accelerate = 255 ;
  Direct = false ;
  TimeOutStr = 0 ;
}

// --- CHE DO NHAN LENH DIEU KHIEN TU SERVER --- //
void Server_SetMode()
{
  Input_String() ;
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
    Menu_WifiPayload() ;
    EncoderSerial.print(String(Start) + String(ResetEncoder) + String(End)) ; // yeu cau reset encoder
    MenuSensor.Encoder = 0  ;
    MenuWifi.Mode = 0 ;
    wifiPayload.Mode = 0 ;
    Menu_ReadSensor();
    OkPage = 0 ;
    lcd.clear() ;
    lcd.setCursor(1, 1) ; lcd.print("Waiting for Command") ;
    while (1) {
      Menu_WifiPayload();
      if ( MenuWifi.Mode == 1 ) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Building Map ...") ;
        Building_Map() ;
        MenuWifi.Mode = 0;
        wifiPayload.Mode = 0 ;
        MenuWifi.Stop = 0;
        wifiPayload.Stop = 0 ;
        MenuWifi.Continue = 0;
        wifiPayload.Continue = 0 ;
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Reset Mode") ;
      }
      if ( MenuWifi.Mode == 2) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Full Mode...") ;
        Code_Run_Online() ;
        MenuWifi.Mode = 0;
        wifiPayload.Mode = 0 ;
        MenuWifi.Stop = 0;
        wifiPayload.Stop = 0 ;
        MenuWifi.Continue = 0;
        wifiPayload.Continue = 0 ;
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Reset Mode") ;
      }
      if ( MenuWifi.Mode == 3 ) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Monitor Mode...") ;

        MenuWifi.Mode = 0 ;
        wifiPayload.Mode = 0 ;
      }
      if ( MenuWifi.Mode == 4 ) {
        lcd.clear() ;
        lcd.setCursor(1, 0) ;
        lcd.print("Cleaning Mode... ") ;
        MenuWifi.Mode = 0;
        wifiPayload.Mode = 0 ;
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





//-----------------DIEU KHIEN BANG GAMEPAD ----------------------//
void Gamepad_Control()
{
  EncoderSerial.print(String(Start) + String(ResetEncoder) + String(End)) ; // yeu cau reset encoder
  MenuSensor.Encoder = 0  ;
  Menu_ReadSensor();
  Motor_Setup() ;
  vTaskDelay((300L * configTICK_RATE_HZ) / 1000L)  ;   //added delay to give wireless ps2 module some time to startup, before configuring it

  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(pressures, rumble);
  lcd.setCursor(0, 1) ;
  lcd.print("Connecting to PS2...") ;
  if (error == 0) {
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  //  Serial.print(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
  }
  bool RightRun = true ;
  bool LeftRun = true ;
  bool StopCle = false ;
  bool RightCle = true ;
  bool LeftCle = true ;
  Accelerate = 255 ;
  AccelerateCLE = 255 ;
  SDreadData(FilePWMMovData) ;
  PWMMovSpd = TempData ;
  TempData = "" ;
  SDreadData(FilePWMCleData) ;
  PWMCleSpd = TempData ;
  TempData = "" ;
  while (1)
  {
    Menu_ReadSensor() ;
    if (error == 1) //skip loop if no controller found
      return;
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed

    if (ps2x.Button(PSB_START))        //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");
    if ( (ps2x.Button(PSB_PAD_RIGHT)) && (MenuSensor.LimitSW_2 != 0) ) {
      vTaskDelay((10L * configTICK_RATE_HZ) / 1000L)  ;
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      if ( LeftRun == true ) {
        while ( Accelerate < 256) {
          Accelerate++ ;  // ham lai, de dao chieu quay
          analogWrite(PWM4, Accelerate) ;
          vTaskDelay((2L * configTICK_RATE_HZ) / 1000L)  ;
        }
      }
      Accelerate = Accelerate - 20 ;  // thoi gian tang toc
      if (Accelerate < 0) {
        Accelerate = 0 ;
      }
      digitalWrite(DIR4, LOW) ;
      RightRun = true ; LeftRun = false ;
    }
    if ( (ps2x.Button(PSB_PAD_LEFT)) && (MenuSensor.LimitSW_1 != 0) ) {
      vTaskDelay((10L * configTICK_RATE_HZ) / 1000L)  ;
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      if (RightRun == true) {
        while ( Accelerate < 256) {
          Accelerate++ ;  // ham lai de dao chieu quay
          analogWrite(PWM4, Accelerate) ;
          vTaskDelay((2L * configTICK_RATE_HZ) / 1000L)  ;
        }
      }
      Accelerate = Accelerate - 20 ;   // thoi gian tang toc
      if (Accelerate < 0) {
        Accelerate = 0 ;
      }
      digitalWrite(DIR4, HIGH) ;
      RightRun = false ; LeftRun = true ;
    }

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if (ps2x.Button(PSB_L1))
        Serial.println("L3 pressed");
      if (ps2x.Button(PSB_R1))
        Serial.println("R3 pressed");
      if (ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if (ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if (ps2x.Button(PSB_TRIANGLE)) // kich hoat dong co lau chui
        Serial.println("Triangle pressed");
    }
    if (ps2x.ButtonPressed(PSB_CIRCLE))              //will be TRUE if button was JUST pressed
      {
        vTaskDelay((20L * configTICK_RATE_HZ) / 1000L)  ;
        lcd.clear() ; lcd.setCursor(0,0) ; lcd.print("Push to Right") ; 
        if( LeftCle == true || StopCle == true ) 
          {
            Motor_Cleaning_Stop() ; 
            while ( AccelerateCLE > 255 - (int)(PWMCleSpd.toInt()) ) { Motor_CleaningL_Start() ; }
            LeftCle = false ; RightCle = true ; StopCle = false ;            
          }
        else {
//            while ( AccelerateCLE > 255 - (int)(PWMCleSpd.toInt()) ) { Motor_CleaningL_Start() ; }
            LeftCle = false ; RightCle = true ; StopCle = true ;   
              Motor_Cleaning_Stop() ; 
          }
      }
  
    if (ps2x.ButtonReleased(PSB_SQUARE))             //will be TRUE if button was JUST released
      {
        vTaskDelay((20L * configTICK_RATE_HZ) / 1000L)  ;
        lcd.clear() ; lcd.setCursor(0,0) ; lcd.print("Push to Left") ; 
        if( RightCle == true || StopCle == true ) 
          {
            Motor_Cleaning_Stop() ; 
            while ( AccelerateCLE > 255 - (int)(PWMCleSpd.toInt()) ) { Motor_CleaningR_Start() ; }
            LeftCle = true ; RightCle = false ; StopCle = false ;           
          }
        else {
//            while ( AccelerateCLE > 255 - (int)(PWMCleSpd.toInt()) ) { Motor_CleaningR_Start() ; }
            LeftCle = true ; RightCle = false ; StopCle = true ;  
              Motor_Cleaning_Stop() ; 
          }
      }
    if (ps2x.NewButtonState(PSB_CROSS))              //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");  
    if (ps2x.Button(PSB_L3) || ps2x.Button(PSB_R3)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC);
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC);
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
    }
    Accelerate = Accelerate + 7 ;
    if (Accelerate > 255 ) {
      Accelerate = 255 ;
    }
    analogWrite(PWM4, Accelerate) ;
    Key = keypad.getKey();
    if ( ((int)keypad.getState() ==  PRESSED) )
    {
      if ( Key == BACK )
      {
        Motor_Run_Stop() ;
        Motor_Cleaning_Stop() ;
        break ;
      }
    }
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
  }
}


//---------------------------------------------------------------------------------------------------

void Run_Mode()
{
  while (Run) {
    Menu_WifiPayload();
    Motor_Run_Stop() ;
    Motor_Cleaning_Stop() ;
    UpdatetoESP(String(updateStatusParameter), String(0));
    Serial.print("Stopping");
    
    if (MenuWifi.Stop) {
      Run = 0;
      break;
    }
    Wait_Task();
  }
}

void Menu_incPanelPos()       // a Phuong code, toan sua :)))
{
  if ( PanPos != MenuSensor.Encoder)
  {
    PanPos = MenuSensor.Encoder ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
    SDsaveData((String)PanPos, FilePanPosData);
    UpdatetoESP(String(updateDirectionParameter), String(1));
  }
//  if (  MenuSensor.IRSensorR == 0 && Sensor_Temp == 0) Sensor_Temp = 1  ;
//  if (  MenuSensor.IRSensorR == 1 && Sensor_Temp == 1)
//  {
//    Sensor_Temp = 0 ;
//    EncoderSerial.print(String(Start) + String(NextPanel) + String(End)) ; // IR phat hien tam pin moi
//        UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
//        UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
//  }
}

void Menu_decPanelPos()     // toan code
{
  if ( PanPos != MenuSensor.Encoder)
  {
    if ( PanPos == 9 ) {
      lcd.clear() ;
    }
    PanPos = MenuSensor.Encoder ;
    lcd.setCursor(16, 2) ; lcd.print(PanPos) ;
    SDsaveData((String)PanPos, FilePanPosData) ;
    UpdatetoESP(String(updateDirectionParameter), String(-1));
  }
//  if (  MenuSensor.IRSensorR == 0 && Sensor_Temp == 0) Sensor_Temp = 1  ;
//  if (  MenuSensor.IRSensorR == 1 && Sensor_Temp == 1)
//  {
//    Sensor_Temp = 0 ;
//    EncoderSerial.print(String(Start) + String(NextPanel) + String(End)) ; // IR phat hien tam pin moi
//        UpdatetoESP(String(updateCollumnPanelParameter), String(PanPos));
//        UpdatetoESP(String(updateStringPanelParameter), String(StrPanel));
//  }
}

//-------------------------Thiet Lap Ban Dau Cho Dong Co------------------------------------------------//

void Motor_Setup()
{
  pinMode(IRSensorPinR, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(IRSensorPinL, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(CheckWheel2, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(CheckWheel1, INPUT_PULLUP) ;   // duong-nau, am-xanh
  pinMode(StartPin, INPUT_PULLUP) ;
  pinMode(StopPin, INPUT_PULLUP) ;

  pinMode(DIR4, OUTPUT) ;
  pinMode(DIR3, OUTPUT) ;
  pinMode(PWM4, OUTPUT) ;
  pinMode(PWM3, OUTPUT) ;
  digitalWrite(PWM4, HIGH) ;
  digitalWrite(PWM3, HIGH) ;
}


//--------------------------------------------Dieu Khien Dong Co------------------------------------------------//
void Motor_Left_Start()
{
  digitalWrite(DIR4, HIGH) ;
  if (Accelerate > (255 - (int)(PWMMovSpd.toInt())) )
  {
    Accelerate-- ;
    if (Accelerate < 255 - (int)(PWMMovSpd.toInt()) ) {
      Accelerate = 255 - (int)(PWMMovSpd.toInt()) ;
    }
  }
  if(MenuSensor.IRSensorR == 1)
    {
      vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
      if( TimeOutStr > 80 ) analogWrite(PWM4, 175) ;        // Giam toc khi IR phat hien end string
      TimeOutStr++ ;
      if( TimeOutStr > 290 && MenuSensor.LimitSW_1 != 0)  // gioi han time hong ngoai ngay tai day :(285) 
        {
          Motor_Run_Stop() ; 
          Motor_Cleaning_Stop() ;
          lcd.setCursor(2,3) ; lcd.print("LimitSW1 Error !") ;
//          UpdatetoESP(String(), String());         // update to ESP loi limit switch tai day 
          bool Err = false ;
          while(digitalRead(StartPin) != 0) { digitalWrite(StaLedRED, Err) ; vTaskDelay((200L * configTICK_RATE_HZ) / 1000L)  ; Err = !Err ; } 
          digitalWrite(StaLedRED, LOW) ;
          Accelerate = 255 ;
          TimeOutStr = 0 ;
//          MenuSensor.LimitSW_1 = 0 ;
        }
    }
  else analogWrite(PWM4, Accelerate) ;  
  vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
}


void Motor_Right_Start()
{

  digitalWrite(DIR4, LOW) ;
  if (Accelerate > 255 - (int)(PWMMovSpd.toInt()) )
  {
    Accelerate-- ;
    if (Accelerate < 255 - (int)(PWMMovSpd.toInt()) ) {
      Accelerate = 255 - (int)(PWMMovSpd.toInt()) ;
    }
  }
  if(MenuSensor.IRSensorL == 1)
  {
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
    if( TimeOutStr > 80 ) analogWrite(PWM4, 175) ;    // Giam toc khi IR phat hien end string
    TimeOutStr++ ;
    if( TimeOutStr > 300 && MenuSensor.LimitSW_2 != 0)  // gioi han time hong ngoai ngay tai day :(270) 
      {
        Motor_Run_Stop() ; 
        Motor_Cleaning_Stop() ;
        lcd.setCursor(2,3) ; lcd.print("LimitSW2 Error !") ;
//        UpdatetoESP(String(), String());         // update to ESP loi limit switch tai day 
        bool Err = false ;
        while(digitalRead(StartPin) != 0) { digitalWrite(StaLedRED, Err) ; vTaskDelay((200L * configTICK_RATE_HZ) / 1000L)  ; Err = !Err ; } 
        digitalWrite(StaLedRED, LOW) ;
        TimeOutStr = 0 ;
        Accelerate = 255 ;
//        MenuSensor.LimitSW_2 = 0 ;
      }
  }
  else analogWrite(PWM4, Accelerate) ;  
  vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
}


void Motor_Run_Stop()
{
  while ( Accelerate < 255 )
  {
    Accelerate = Accelerate + 5 ;
    analogWrite(PWM4, Accelerate ) ;
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
  }
}


void Motor_CleaningR_Start()
{
  digitalWrite(DIR3, HIGH) ;
  if (AccelerateCLE > 255 - (int)(PWMCleSpd.toInt()) )
  {
    AccelerateCLE--;
    if (AccelerateCLE < 255 - (int)(PWMCleSpd.toInt()) ) {
      AccelerateCLE = 255 - (int)(PWMCleSpd.toInt()) ;
    }
  }
  analogWrite(PWM3, AccelerateCLE) ;
  vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
}


void Motor_CleaningL_Start()
{
  digitalWrite(DIR3, LOW) ;
  if (AccelerateCLE > 255 - (int)(PWMCleSpd.toInt()) )
  {
    AccelerateCLE--;
    if (AccelerateCLE < 255 - (int)(PWMCleSpd.toInt()) ) {
      AccelerateCLE = 255 - (int)(PWMCleSpd.toInt()) ;
    }
  }
  analogWrite(PWM3, AccelerateCLE) ;
  vTaskDelay((1L * configTICK_RATE_HZ) / 1000L)  ;
}

void Motor_Cleaning_Stop()
{
  while ( AccelerateCLE < 255 )
  {
    AccelerateCLE = AccelerateCLE + 2 ;
    analogWrite(PWM3, AccelerateCLE ) ;
    vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
  }
}
