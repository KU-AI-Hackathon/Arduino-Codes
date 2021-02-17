String incomingString;
String analogValue;
String headerString;
int ledPin = 3;
void setup() {
 // put your setup code here, to run once
 // Baud rate of ESP13 shield set up in configuration
 Serial.begin(115200);
}
void loop() {
 // reply only when you receive data:
 if (Serial.available() > 0)
 {
   // read the incoming string and strip out four first bytes:
   incomingString = Serial.readString();
   headerString = incomingString.substring(0,4);
   // If the header string equals "12#$" then update LED brightenss and pot value
   if (headerString.equals("12#$"))
   {
     //remove the first four bytes, analogWrite function needs and integer, conversion required
     incomingString.remove(0,4);
     analogWrite(ledPin,incomingString.toInt());
     //read the A0 analog input, convert to string and send back
     analogValue = String(analogRead(A0),DEC);
     Serial.print(analogValue);
   }
   else
   {
   // say what you got:
     Serial.print("ESPRecieved: ");
     Serial.flush();
     Serial.print(incomingString);
   }
 }
 else
 {
   delay(500);    
 }
}
