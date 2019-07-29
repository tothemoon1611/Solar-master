void SIM_reset()
{
  Serial.println("---------JUST RESET THE SIM MODULE------------");
  pinMode(SIM_RESET, OUTPUT);
  delay(500);
  pinMode(SIM_RESET, INPUT);
  delay(500);
}

void ResetNetwork() {
#ifdef DEBUGER
  Serial.print("RESET SIM");
#endif
  SIM_sendCommand("AT+CFUN=0", 2);
  delay(1000);
  SIM_sendCommand("AT+CFUN=1,1", 2);
  delay(8000);
#ifdef DEBUGER
  Serial.print("RESET DONE");
#endif
}


bool SIM_begin(byte Retry)
{
  SIM.begin(38400);
  delay(1000);
  SimSleepOff();
  delay(1000);
#ifdef DEBUGER
  Serial.print("Begin SIM");
#endif
  SIM_sendCommand("AT", 1000);
  SIM_sendCommand("AT+CPIN?", "ERROR", 1000);
  for ( byte i = 0; i <= Retry; i++)
  {
    if (SIM_sendCommand("AT+CREG?", "0,1", 2000)) return true;
    delay(3000);
  }
  return false;
}

bool SIM_begin() {
  SIM.begin(9600);
  delay(1000);
#ifdef DEBUGER
  Serial.print("Begin SIM");
#endif
  SIM_sendCommand("AT", 1000);
  SIM_sendCommand("AT+CPIN?", 1000);
  for ( byte i = 0; i <= 20; i++)
  {
    if (SIM_sendCommand("AT+CREG?", "0,1", 3000)) return true;
    delay(1000);
  }
  return false;
}

void SIM_sendCommand(String cmd) {
  //SIM_buffer_flush();
  SIM.print(cmd);
  SIM.print("\r\n");
#ifdef DEBUGER
  Serial.print("\n> ");
  Serial.println(cmd);
#endif

  delay(100);
}

void SIM_sendCommand(String cmd, int TIMEOUT) {
  SIM_buffer_flush();
#ifdef DEBUGER
  Serial.print("\n> ");
  Serial.println(cmd);
#endif
  SIM.print(cmd);
  SIM.print("\r\n");
  delay(50);
  show(TIMEOUT);
}


bool SIM_sendCommand(String cmd, String Reply, int TIMEOUT) {
  SIM_buffer_flush();
#ifdef DEBUGER
  Serial.print("\n> ");
  Serial.println(cmd);
#endif
  SIM.print(cmd);
  SIM.print("\r\n");
  delay(50);
  return show(Reply, TIMEOUT);
}

bool SIM_sendCommand(String cmd, String Reply1, String Reply2, int TIMEOUT) {
  SIM_buffer_flush();
#ifdef DEBUGER
  Serial.print("\n> ");
  Serial.println(cmd);
#endif
  SIM.print(cmd);
  SIM.print("\r\n");
  delay(50);
  return show(Reply1, Reply2, TIMEOUT);
}

String show(int TIMEOUT) {
  uint32_t entry = millis();
  String dat = "";
  do
  {
    dat = dat + readReply(200);
  }
  while ( dat.indexOf("ok") < 0  && dat.indexOf("error") < 0 && dat.indexOf("10.") < 0 && millis() - entry < TIMEOUT);
#ifdef DEBUGER
  Serial.print("show: ");
  Serial.println(dat);
#endif
  return dat;
}

bool show(String Reply , int TIMEOUT) {
  uint32_t entry = millis();
  String dat = "";
  Reply.toLowerCase();
  do
  {
    dat = dat + readReply(200);
  }
  while (dat.indexOf(Reply) < 0 && dat.indexOf("error") < 0 && millis() - entry < TIMEOUT);
#ifdef DEBUGER
  Serial.print("show: ");
  Serial.println(dat);
#endif
  return (dat.indexOf(Reply) >= 0) ? true : false;
}

bool show(String Reply1, String Reply2, int TIMEOUT) {
  uint32_t entry = millis();
  String dat = "";
  do
  {
    dat = readReply(200);
  }
  while (dat.indexOf(Reply1) < 0 && dat.indexOf(Reply2) < 0 && dat.indexOf("error") < 0 && millis() - entry < TIMEOUT);
#ifdef DEBUGER
  Serial.print("show: ");
  Serial.println(dat);
#endif
  return (dat.indexOf(Reply1) >= 0 || dat.indexOf(Reply2) >= 0) ? true : false;
}

String readReply(int Delay)
{
  String dat = "";
  char c;
  delay(Delay);
  if (SIM.available()) {
    while (SIM.available()) {
      c = SIM.read();
      dat += c;
      delay(3);
    }
  }
  dat.toLowerCase();
  return dat;
}

void SIM_buffer_flush() {
  delay(1000);
  while (SIM.available() > 0) {
    SIM.read();
  }
}

bool SimSleepOff()
{
  digitalWrite(DTR, 1);
  SIM_sendCommand("AT");
  SIM_sendCommand("AT+CSCLK=0", "OK", 2000);
  digitalWrite(DTR, 0);
  return true;
}

bool SimDeepSleep()
{
  digitalWrite(DTR, 1);
  SIM_sendCommand("AT+CSCLK=2", "OK", 2000);
  SIM_sendCommand("AT+CSCLK?", "OK", 2000);
  digitalWrite(DTR, 0);
  return true;
}
bool SimSleep()
{
  digitalWrite(DTR, 1);
  SIM_sendCommand("AT+CSCLK=1", "OK", 2000);
  SIM_sendCommand("AT+CSCLK?", "OK", 2000);
  digitalWrite(DTR, 0);
  return true;
}

void requestTime() {
  SIM_sendCommand("AT+CCLK?", 1000);
}
