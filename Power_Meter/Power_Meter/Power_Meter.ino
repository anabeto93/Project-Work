/*******************************************************
* Author: Richard Opoku Anabeto						   *
* Student ID: 10413353								   *
* Purpose: To simulate the power meter to be designed  *
*	for our level 400 final year undergraduate project * 
*	department of computer engineering, University of  *
* 	Ghana - Legon. Partnered with Michael Tetteh to    *
*	an energy management system for a smart home	   *
*******************************************************/
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int currentSensor = A0;
const int voltageSensor = A2;

long previousMillisec = 0;

unsigned long interval=1000;//1 second
long times;//convert to seconds

float voltage,current,power,energy,ampHour,totalAmp,totalPower;

float sampleVolt,sampleAmp;
int sampleNum = 150;

void setup()
{
	Serial.begin(9600);//baud rate
	lcd.begin(16,2);
  //init();
	energy = 0.0;//initialized once
	ampHour=0.0;
	totalAmp=0.0;
	totalPower=0.0;
}
void loop()
{
	//init();
	long currentMillisec = millis();
	if(currentMillisec-previousMillisec>interval)
	{
		previousMillisec = currentMillisec;
	}
	times = previousMillisec/interval;

	Serial.println(times);
	delay(100);
	sensorValues();//approximately 300ms
	delay(500);
	displayValues();
  	voltage = 0.0;
  	current = 0.0;
  	power = 0.0;
  	sampleVolt=0.0;
  	sampleAmp=0.0;
  	delay(1500);
  	
}

void sensorValues()
{
	for(int i=0; i<sampleNum; ++i){
		sampleAmp += analogRead(currentSensor);
		delay(1);
		sampleVolt += analogRead(voltageSensor);
		delay(1);
	}
	//average the samples obtained
	sampleAmp /=sampleNum;
	sampleVolt /=sampleNum;
	current = calCurrent(sampleAmp);
	voltage = calVoltage(sampleVolt);
	power = calPower();
	energy = calEnergy();
	ampHour = calAmpHour();
}

void displayValues()
{
	//Serial.println("Hello Function");
	//lcd.print("P ");
	lcd.clear();//clear screen first
	Serial.print("Power ");
	Serial.print(power);
	lcd.print(power);
	Serial.print("W \t Volt ");
	lcd.print("W \t ");
	Serial.print(voltage);
	lcd.print(voltage);
	Serial.println("V");
	lcd.print("V");
	lcd.setCursor(1,2);//second row
	Serial.print("Energy ");
	//lcd.print("E ");
	Serial.print(energy);
	lcd.print(energy);
	Serial.print("kWh \t ");
	lcd.print("kWh \t");
	Serial.print("Current ");
	//lcd.print("I ");
	Serial.print(current);
	lcd.print(current);
	Serial.println("A");
	lcd.println("A");
}
float calCurrent(float amp)
{
	float val = (4.88*amp)/1000.0;
	float actualVolt = val-2.5;//offset value
	actualVolt*=actualVolt;//square the values
	actualVolt = sqrt(actualVolt);
	float actualAmp = (actualVolt*1000)/66.0;
	totalAmp+=actualAmp;//increment total amps
	//That is the 66mV per Amp from datasheet
	return actualAmp;
}
float calVoltage(float volt )
{
	float val=(5.45*7*volt)/1000.0;
	return val;
}
float calPower()
{
	float val = voltage*current;
	totalPower+=val;
	return val;
}
float calEnergy()
{
	float val=(totalPower*times)/3600;//work in hours
	val/=1;//for kW
	return val;
}
float calAmpHour()
{
	float avgAmp = totalAmp/times;
	float val = (avgAmp*times)/3600;
	return val;//total amp hour
}
