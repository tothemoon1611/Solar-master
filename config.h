#define SIM Serial1
#define SIM_RESET 7
#define DTR 6
#define CSpin  53

String msgGPRS = "GET /update?api_key=XN6MA1R9H63Q1IZX"; // chanel 1

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
  bool ACK_ID;
};

//DataStr DataStr = {"", "", 0.00 , 0.00 , 0.00 , 0.00 , 0.00 , 0.00 , "" , ""};

Status Status = {true, false, false, true, true};

/*************************************************************/
LiquidCrystal_I2C lcd(0x27, 20, 4);

//-----------------------------------------------Hien thi cac Page tuong ung----------------------------------------------------------------//
//--PAGE 1--//
char* LCDSettingMode[] = {"1.Parameters setup", "2.Testing Mode", "3.Building Map", "4.Start "} ;        

//--PAGE 2--//
char* LCDParametersSetup[] = {"1.Robot ID", "2.Motor Setup", "3.Charging Setup", "4.Update Later..."} ;     // For Parameters Setup
char* LCDTestingMode[] = {"1.Hand Control", "2.Camera Test", "3.Commu... Test", "4.Work Test"} ;                                                     // For Testing Mode      
char* LCDBuildMap[] = {"Update Later..."} ;                                                                         // For Build Map                                          
char* LCDStart[] = {"Update Later..."} ;                                                                        // For Automatic 

//--PAGE 3--// 
char* LCDRobotID[] = {"ID:", "HID:", "0.Network Config"} ;                                                                          // For Parameters Setup -> Robot Fixed ID 
char* LCDMotorSetup[] = {"1.Moving Motor", "2.Cleaning Motor"} ;                                // For Parameters Setup -> Motor Speed       
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

String PIDKpMovSpd ;
String PIDKiMovSpd ;
String PIDKdMovSpd ;
String PWMMovSpd ;

String PIDKpRolSpd ;
String PIDKiRolSpd ;
String PIDKdRolSpd ;
String PWMRolSpd ;

String PIDKpCleSpd ;
String PIDKiCleSpd ;
String PIDKdCleSpd ;
String PWMCleSpd ;

unsigned int EnerAlert = 15 ;             // muc Pin canh bao, can phai nap sac 
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
 
byte rowPins[rows] = {22, 24, 26, 28}; 
byte columnPins[columns] = {30, 32, 34, 36};
 



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

String FileSSIDData = "SSIDData.txt" ;
String FilePASSData = "PASSData.txt" ;
String FilePORTData = "PORTData.txt" ;
String FileIPAddData = "IPData.txt" ;
String FileIDData = "IDData.txt" ;
String FileHardIDData = "HdIDData.txt" ;

//-------------------------------------Control Motor-------------------------------------//
unsigned int PanPos = 0 ;
bool  StartBut  = 0 ;

#define MetalSensorPin 8 
#define CheckWheel1 9
#define CheckWheel2 10

#define ENA 2
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENB 7
