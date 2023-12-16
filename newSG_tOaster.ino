// Group 01 Smart_gardening system

// libraries

#include "DFRobot_LCD.h"

DFRobot_LCD lcd(16,2);

// initializing pin modes

int pinMoistureSensor = A3;
int pinWaterSensor = A0;
int pinLED = 10;
int pinPumpSoil = 13;
int pinPumpTank = 12;


// initializing variables

int sensorMoisture;
int sensorWater;
int wet = 500;
int dry = 750;
int empty = 480;
int full = 705;
float hum;
float temp;

// boolean methods for moisture sensor

bool isWet(){
  sensorMoisture = analogRead(pinMoistureSensor);
  if ( sensorMoisture<wet){
    return true;
  }
  return false;
}

bool isDry(){
  sensorMoisture = analogRead(pinMoistureSensor);
  if ( sensorMoisture>dry){
    return true;
  }
  return false;
}

// boolean methods for water sensor

bool isTankEmpty(){
  sensorWater = analogRead(pinWaterSensor);
  if ( sensorWater<=empty){
    return true;
  }
  return false;
}

bool isTankFull(){
  sensorWater = analogRead(pinWaterSensor);
  if ( sensorWater>=full){
    return true;
  }
  return false;
}

// SetUp

void setup() {
  Serial.begin(9600);
  lcd.init(); // initializing the display
  lcd.setCursor(0,0); // setting cursor position to 2nd column 0 row 
  //lcd.print(16,2);
  lcd.print("Smart Gardening ");
  delay(1000);
  lcd.clear();
  lcd.print("Let's Make It    ");
  delay(1000);
  pinMode(pinLED, OUTPUT);
  pinMode(pinPumpSoil, OUTPUT);
  pinMode(pinPumpTank, OUTPUT);
  
}

// Loop MAIN

void loop() {
  // conditions for Soil water pump to operate
   Serial.begin(9600);
  if ((isDry()==true) || isWet()==false){
    digitalWrite(pinPumpSoil, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Moisture Low");
    Serial.print(sensorMoisture);
    lcd.clear();
    lcd.print("Soil pump ON");
    delay(500);
    lcd.clear();
  } else if ((isDry()==false || isWet()==true)) {
    digitalWrite(pinPumpSoil, LOW);
    lcd.print("Moisture High");
    delay(500);
    Serial.print(sensorMoisture);
    lcd.clear();
    lcd.print("Soil pump OFF");
    delay(500);
    lcd.clear();
  } else {
    Serial.print(sensorMoisture);
  }
  
 // conditions for Tank water pump to operate
  
  if (isTankEmpty()==true){
    digitalWrite(pinPumpTank, HIGH);
    lcd.print("Tank Empty");
    Serial.print(sensorWater);
    delay(500);
    lcd.clear();
    lcd.print("Tank pump ON");
    delay(500);
    lcd.clear();
    digitalWrite(pinLED, HIGH);
  } else if (isTankFull()==true){
    digitalWrite(pinPumpTank, LOW);
    lcd.print("Tank Full");
    Serial.print(sensorWater);
    delay(500);
    lcd.clear();
    lcd.print("Tank pump OFF");
    digitalWrite(pinLED, LOW);
    delay(500);
    lcd.clear();
  } else {
    Serial.print(sensorWater);
  }

}
