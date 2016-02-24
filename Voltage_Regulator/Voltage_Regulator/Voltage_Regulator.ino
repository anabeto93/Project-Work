int voltPin = A2;
int ledPin =5;
void setup() {
  // put your setup code here, to run once:
  //pinMode(voltPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(voltPin);
  Serial.println(value);
  delay(500);
  float val = (float)((value/1023.0)*5);
  Serial.print(val);
  Serial.println(" V");
  delay(500);
  /*if(voltPin>=4)
  {
    digitalWrite(ledPin,HIGH);
  }
  delay(3000);
  digitalWrite(ledPin,LOW);
  delay(3000);*/
}
