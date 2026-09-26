#include <LiquidCrystal.h>

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile boolean newDistanceAvailable = false;

#define ECHO_PIN 3
#define TRIGGER_PIN 4

#define LCD_RS A5
#define LCD_E A4
#define LCD_D4 6
#define LCD_D5 5
#define LCD_D6 8
#define LCD_D7 11


LiquidCrystal lcd (LCD_RS, LCD_E, LCD_D4, 
                   LCD_D5, LCD_D6, LCD_D7);


void triggerUltrasonicSensor(){

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
}


void echoPinInterrupt(){

  if (digitalRead(ECHO_PIN) == HIGH){
    pulseInTimeBegin = micros();
  }
  else{
    pulseInTimeEnd = micros();
    newDistanceAvailable = true;
  }
  
}


float getUltrasonicSensorDistance(){

  float durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  float distance = durationMicros / 148.0;

  return distance;
  
}


void setup() {

  lcd.begin(16, 2);
  
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);

}


void loop() {

  unsigned long timeNow = millis();
  
  if (timeNow - lastTimeUltrasonicTrigger >= ultrasonicTriggerDelay){

    lastTimeUltrasonicTrigger = timeNow;
    triggerUltrasonicSensor();
    
  }

  if (newDistanceAvailable){

    newDistanceAvailable = false;
    double distance = getUltrasonicSensorDistance();

    lcd.print("Rate: ");
    lcd.print(ultrasonicTriggerDelay);
    lcd.print(" MS");

    lcd.setCursor(0, 1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print("IN");
    
  }
}
