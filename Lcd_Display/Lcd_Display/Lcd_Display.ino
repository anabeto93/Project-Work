    #include <LiquidCrystal.h>
    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
    const int analogIn = A0;
    int mVperAmp = 66;//for 30A ACS712
    int RawValue = 0;
    int ACSoffset = 2500;
    double Voltage = 0;
    double Amps = 0;
    int time = 0;
    
    void setup()
    {
      Serial.begin(9600);
      lcd.begin(16, 2);
    }
    void loop()
    {
      lcd.clear();
      time+=250;
      lcd.setCursor(1,2);
      lcd.print("Time ");
      lcd.print((float)time/1000);
      lcd.print("s");
      RawValue = analogRead(analogIn);
      Voltage = (RawValue / 1023.0) *5000;//5V
      Serial.print("Raw Value= ");
      Serial.print(RawValue);
      Serial.print(" mV = ");
      Serial.print(Voltage,3);//3 decimal places
      Serial.print(" Amps = ");
      Serial.println(Amps,3);//3 decimal places
      lcd.print(Amps,3);
      lcd.print(" A");
      delay(2500);//2.5 seconds
    }
