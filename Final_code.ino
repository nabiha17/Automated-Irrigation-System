// Group 01 Smart_Irrigation_System

// libraries

#include "DFRobot_LCD.h"

DFRobot_LCD lcd(16,2);

// initializing pin modes

int pinMoistureSensor = A3;
int pinWaterSensor = A0;
int pinLED = 10;
int pinPumpSoil = 13;
int pinPumpTank = 12;

int moisture_value;
int water_level;
int moist;
int level;

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.setCursor(0,0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0,1);
  lcd.print("Let's Make It    ");
  delay(1000);
  lcd.clear();
  pinMode(pinLED, OUTPUT);
  pinMode(pinPumpSoil, OUTPUT);
  pinMode(pinPumpTank, OUTPUT);
  pinMode(pinMoistureSensor, INPUT);
  pinMode(pinWaterSensor, INPUT);
    
}

void loop(){
  water_level = analogRead(pinWaterSensor);
  level = map(water_level,0,1023,0,100);
  moisture_value = analogRead(pinMoistureSensor);
  moist = map(moisture_value,0,1023,0,100);
  condition();
  condition_2();
}

void condition(){
  if (level > 65 && moist < 65){
    LCD();
    digitalWrite(pinPumpSoil,HIGH);
    digitalWrite(pinPumpTank,LOW);
    digitalWrite(pinLED,HIGH);
    //delay(500);
  } else if (level < 65 && moist >65) {
    LCD();
    digitalWrite(pinPumpSoil,LOW);
    digitalWrite(pinPumpTank,HIGH);
    digitalWrite(pinLED,LOW);
    //delay(500);
  } else if (level > 65 && moist >65) {
    LCD();
    digitalWrite(pinPumpSoil,LOW);
    digitalWrite(pinPumpTank,LOW);
    digitalWrite(pinLED,LOW);
    //delay(500);
  } else if (level < 65 && moist <65){
    LCD();
    digitalWrite(pinPumpSoil,HIGH);
    digitalWrite(pinPumpTank,HIGH);
    digitalWrite(pinLED,HIGH);
    //delay(500);
  }
  
}
void condition_2(){
  if (level > 65 && moist < 65){
    V_terminal();
    //delay(500);

  } else if (level < 65 && moist >65) {
    V_terminal();
    //delay(500);
    
  } else if (level > 65 && moist >65) {
    V_terminal();
    //delay(500);
    
  } else if (level < 65 && moist <65){
    V_terminal();
    //delay(500);
  }
  
}

void LCD(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tank Level= ");
  lcd.print(level);
  lcd.print("%");
  //////////////
  lcd.setCursor(0,1);
  lcd.print("Moisture= ");
  lcd.print(moist);
  lcd.print("%");
}

void V_terminal(){
  lcd.clear();
  Serial.println(F("Water level" ));
  Serial.println(level);

  //////////////
  Serial.println(F("Moisture level" ));
  Serial.println(moist);

}
