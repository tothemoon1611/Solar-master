
bool SDformat()
{
  pinMode(CSpin, OUTPUT);
#ifdef DEBUGER
  Serial.print("Initializing SD card...");
#endif
  if (!SD.begin(CSpin))
  {
#ifdef DEBUGER
    Serial.println("SD card failed!");
#endif
    return false;
  }
#ifdef DEBUGER
  Serial.println("SD Card OK! ");
#endif

  if (!SD.exists(FileSSIDData))
  {
    myFile = SD.open(FileSSIDData, FILE_WRITE);
    myFile.close();
  } else {}
  if (!SD.exists(FilePASSData))
  {
    myFile = SD.open(FilePASSData, FILE_WRITE);
    myFile.close();
  } else {}
  if (!SD.exists(FileIPAddData))
  {
    myFile = SD.open(FileIPAddData, FILE_WRITE);
    myFile.close();
  } else {}
  if (!SD.exists(FilePORTData))
  {
    myFile = SD.open(FilePORTData, FILE_WRITE);
    myFile.close();
  } else {}
  if (!SD.exists(FileIDData))
  {
    myFile = SD.open(FileIDData, FILE_WRITE);
    myFile.close();
  } else {}
  if (!SD.exists(FileHardIDData))
  {
    myFile = SD.open(FileHardIDData, FILE_WRITE);
    myFile.close();
  } else {}
  if (!SD.exists(FileEAlertData))
  {
    myFile = SD.open(FileEAlertData, FILE_WRITE);
    myFile.close();
  } else {}

  //  if (!SD.exists("robot.csv"))
  //  {
  //#ifdef DEBUGER
  //    Serial.println("File not exist");
  //#endif
  //    myFile = SD.open("robot.csv", FILE_WRITE);
  //    myFile.close();
  //    String dataString = "DAY,TIME,PANEL";
  //    return SDsaveData (dataString) ? true : false;
  //
  //  }
  return true;
}


bool SDsaveData(String DataStr, String FileData)
{
  if (SD.exists(FileData))
  {
    SD.remove(FileData);
    myFile = SD.open(FileData, FILE_WRITE);
    if (myFile)
    {
      myFile.print(DataStr);
      myFile.close(); // close the file
      Serial.println("Saved");
    }
  }
  else
  {
    myFile = SD.open(FileData, FILE_WRITE);
    if (myFile)
    {
      myFile.print(DataStr);
      myFile.close(); // close the file
      Serial.println("Saved");
    }
  }
}



void SDreadData(String FileData)
{
  if (SD.exists(FileData))
  {
    //TempData = "" ;
    myFile = SD.open(FileData);
    if (myFile) {
      Serial.println("Opening " + FileData);
      while (myFile.available()) {
        TempData += (char)myFile.read();
      }
      // close the file:
      myFile.close();
      Serial.println(TempData) ;
    } else {
      Serial.print("  Error opening ") ; Serial.print(FileData) ;
    }
  } else {
    Serial.println(FileData + " not exist ! ");
    myFile = SD.open(FileData, FILE_WRITE);
    myFile.close();
  }
  //return TempData ;
}
