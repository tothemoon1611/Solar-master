#define SIM Serial1
#define SIM_RESET 7
#define DTR 6
#define CSpin  38

#define FullMode  1
#define BuildMap  2
#define CleanMode  3
#define MonitorMode  4

struct Status
{
  volatile bool NetworkOn ;
  volatile bool StatusLed;
  volatile bool Sleep;
  bool SDCard ;
  bool StatusSendData;

};

struct DataMachine
{
  bool MetalSensor;
  bool LimitSW_1;
  bool LimitSW_2;
  float VoltageBattery;
  float CurrentBattery;
};

struct WifiPayload
{ 
  bool ACK_SERVER = false ;
  bool ACK_NETWORK = false ;
  int Mode=0;
  bool Stop = false;
  bool Continue = false;
  bool NetworkError = false;
};

bool Run = 0;
int StrPanel = 0;
String SVSetMode = "" ;
//DataStr DataStr = {"", "", 0.00 , 0.00 , 0.00 , 0.00 , 0.00 , 0.00 , "" , ""};

Status Status = {true, false, false, true, true};

/*************************************************************/
LiquidCrystal_I2C lcd(0x27, 20, 4);

//-----------------------------------------------Hien thi cac Page tuong ung----------------------------------------------------------------//
//--PAGE 1--//
char* LCDSettingMode[] = {"1.Parameters Setup", "2.Testing Mode", "3.Set Working Mode", "4.Automatic "} ;        

//--PAGE 2--//
char* LCDParametersSetup[] = {"1.Robot ID", "2.Motor Setup", "3.Charging Setup", "4.Update Later..."} ;                                        // For Parameters Setup
char* LCDTestingMode[] = {"1.Hand Control", "2.Camera Test", "3.Commu... Test", "4.Work Test"} ;                                               // For Testing Mode      
char* LCDSetWorkingMode[] = {"1.Building Map", "2.Working Mode", "3.Server Control"} ;                                                         // For Build Map                                          
char* LCDAutomatic[] = {"Update Later..."} ;                                                                                                   // For Automatic 

//--PAGE 3--// 
char* LCDRobotID[] = {"ID :", "HID:", "0.Network Config"} ;                                                                                     // For Parameters Setup -> Robot Fixed ID 
char* LCDMotorSetup[] = {"1.Moving Motor", "2.Cleaning Motor"} ;                                                                               // For Parameters Setup -> Motor Speed       
char* LCDChargingSetup[] = {"1.Energy Alert" } ;            // For Parameters Setup -> Charging Setup

char* LCDHandControl[] = {"Update Later..."} ;                                                                // Ngay tai tai day ket noi voi tay dieu khien 
char* LCDCameraTest[] = {"Update Later..."} ;  
char* LCDCommuTest[] = {"Update Later..."} ;  
char* LCDWorkTest[] = {"1.W_Test 1", "2.W_Test 2", "3.W_Test 3", "4.W_Test 4"} ;                               // For Testing Mode ->Auto Testing 
                                                                    

//--PAGE 4--// 
char* LCDMovingMotor[] = {"1.PID_Kp", "2.PID_Ki", "3.PID_Kd", "4.PWM" } ;                                           // For Parameters Setup -> Motor Speed -> Moving Speed 
char* LCDCleaningMotor[] = {"1.PID_Kp", "2.PID_Ki", "3.PID_Kd", "4.PWM" } ;                                         // For Parameters Setup -> Motor Speed -> Cleaning Speed                                       // For Parameters Setup -> Motor Speed -> Rolling Speed


//------------------------------------Khai bao tat ca cac bien-------------------------------------------------------------------------------//
unsigned int Page = 1 ;                                               // Khoi tao Page ban dau mac dinh
unsigned int Page_Pointer[10] ;                                       // Luu lai vi tri con tro truoc do da chon 
bool BreakPage = 0 ;                                                  // Co tac dung khi nhan nut BACK
bool OkPage = 0 ;                                                     // Co tac dung khi nhan nut OK   
unsigned int pointer   ;                                              // Vi tri cua con tro trong menu 
unsigned int PointerMax = 4 ;

float Value = 0 ;                                                     // Gia tri ban dau cua Encoder 
int State ;                                                           // Co tac dung cho Encoder
int LastState ;                                                       // Co tac dung cho Encoder

//////////////////////////////////// LCD ////////////////////////////////////////////////////
const byte rows = 4; 
const byte columns = 4; 
 
int holdDelay = 700; 
int n = 3; // 
int state = 0; 

#define PageMAX 4
#define UP 'A' 
#define DOWN 'B' 
#define OK 'C'
#define BACK 'D' 
#define BACKSPACE '*' 
#define HOME '#'  

char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
 
byte rowPins[rows] = {23, 25, 27, 29}; 
byte columnPins[columns] = {31, 33, 35, 37};
 



char ButONE[7] = { '1', '.', ',', '+', '-', '*', '@' } ;
char ButTWO[7] = { '2', 'a', 'b', 'c', 'A', 'B', 'C' } ;
char ButTHREE[7] = { '3', 'd', 'e', 'f', 'D', 'E', 'F' } ;
char ButFOUR[7] = { '4', 'g', 'h', 'i', 'G', 'H', 'I' } ;
char ButFIVE[7] = { '5', 'j', 'k', 'l', 'J', 'K', 'L' } ;
char ButSIX[7] = { '6', 'm', 'n', 'o', 'M', 'N', 'O' } ;
char ButSEVEN[9] = { '7', 'p', 'q', 'r', 's', 'P', 'Q', 'R', 'S' } ;
char ButEIGHT[7] = { '8', 't', 'u', 'v', 'T', 'U', 'V' } ;
char ButNINE[9] = { '9', 'w', 'x', 'y', 'z', 'W', 'X', 'Y', 'Z' } ;
char ButZERO[2] = { '0', ' ' } ;

unsigned long TimeKeypad ;
char Key = 0; 
char x ;
int MAXSize ;
char ButTemp[9] ;
int ValTemp ;
int LcdTemp ;

String TempData ;
String SSIDData ;
String PASSData ;
String PORTData ;
String IPAddData ;
String EnerALert ; 


String FileSSIDData   = "SSIDData.txt" ;
String FilePASSData   = "PASSData.txt" ;
String FilePORTData   = "PORTData.txt" ;
String FileIPAddData  = "IPData.txt" ;
String FileIDData     = "IDData.txt" ;
String FileHardIDData = "HdIDData.txt"  ;
String FileEAlertData = "EAlert.txt" ;
String FilePWMMovData = "PWMMov.txt" ;
String FilePWMCleData = "PWMCle.txt" ;

String PIDKpMovSpd ;
String PIDKiMovSpd ;
String PIDKdMovSpd ;
String PWMMovSpd ;

String PIDKpCleSpd ;
String PIDKiCleSpd ;
String PIDKdCleSpd ;
String PWMCleSpd ;

//-------------------------------------Control Motor-------------------------------------//

unsigned int PanPos = 0 ;
bool  StartBut  = 0 ;

#define MetalSensorPin 45
#define CheckWheel1 47
#define CheckWheel2 49

#define DIR4 22
#define DIR3 26
#define PWM4 5 
#define PWM3 4
//-----------------------------------Serial-------------------------------------------------
  bool SerialRecv = false;
  int serial_counter = 0;
  char cmd;
  String InputString = "";
String DisplayString = "";
boolean StringComplete = false;

//----------------------------------Gamepad------------------------------------------//
//#define PS2_DAT        42  //14    mac dien tro treo len nguon tu 1k - 10k
//#define PS2_CMD        40  //15
//#define PS2_SEL        46  //16
//#define PS2_CLK        44  //17
// cac chan  cua game pad  o config truc tiep trong thu vien. luoon

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false



int error = 0;
byte type = 0;
byte vibrate = 0;
