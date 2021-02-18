int sensor = ??;

void setup(){
  pinMode (sensor,OUTPUT);
}

void loop(){
  digitalWrite (sensor, HIGH); //열림
  delay(1000);
  digitalWrite (sensor, LOW); //닫힘
  delay(1000);
}
