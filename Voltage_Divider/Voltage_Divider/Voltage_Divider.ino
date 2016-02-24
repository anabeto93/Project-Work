int sum=0;
int sensorPin=A2;
float voltage = 0.0;
float sample =0;

void setup()
{
  Serial.begin(9600);  
}

void loop()
{
  for(int i=0; i<150; ++i)
  {
    
    sample+= analogRead(sensorPin);
    delay(2);//delay by a 2 miliseconds 
  }
  //after sampling, find the average
  sample /=150;
  voltage = (5.45*7*sample)/1000;
  Serial.print("ADC = ");
  Serial.print(sample);
  Serial.print("\t Voltage =");
  Serial.print(voltage);
  Serial.println(" V");
  /*Serial.println(analogRead(sensorPin));
  delay(2000);//delay by 2 seconds*/
}
