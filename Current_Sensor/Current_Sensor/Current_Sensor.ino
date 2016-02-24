int currentSensor=A0;
float sample = 0.0;
float actualAmp = 0.0;
void setup()
{
  Serial.begin(9600);//baud rate
    
}

void loop()
{
  for(int i=0; i<150; ++i)
  {
    int temp=analogRead(currentSensor);
    //Serial.println(temp);
    sample+=temp;
    delay(2);  
  }  
  sample/=150;//average of all the samples
  float val = (4.88*sample)/1000;
  float actualVolt = val-2.5;//offset
  actualVolt *=actualVolt;//square the value
  actualVolt = sqrt(actualVolt);//to get rms value
  actualAmp = (actualVolt*1000)/66.0;//66mVperAmp
  Serial.print("ADC = ");
  Serial.print(sample);
  Serial.print("\t Current = ");
  Serial.print(actualAmp);
  Serial.println(" A");

  delay(600);//assuming 100m for calc
  sample = 0;
  actualAmp = 0;
}
