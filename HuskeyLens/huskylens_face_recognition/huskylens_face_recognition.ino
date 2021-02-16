#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;

void printResult(HUSKYLENSResult result);

void setup(){
  Serial.begin(9600);

  Wire.begin();
  while(!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1. Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
    Serial.println(F("2. Please recheck the connection."));
   delay(100); 
  } 
}

void loop(){
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection"));
  else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKTLENS to learn one!"));
  else if(!huskylens.available()) 
  {Serial.println(F("No block or arrow appears on the screen!"));
   delay(1000); 
  }
  else
  {
    Serial.println(F("###########"));
    while(huskylens.available())
    {
      HUSKYLENSResult result = huskylens.read();
      printResult(result);
    }
  }
}

void printResult(HUSKYLENSResult result){
  if (result.command == COMMAND_RETURN_BLOCK){
    Serial.println(String()+F(",ID")+result.ID);
    delay(1000); 
  }
  else if (result.command == COMMAND_RETURN_ARROW){
    Serial.println(String()+F(",ID")+result.ID);
    delay(1000); 
  }
  else{
    Serial.println("Object unknown!");
  }
}
