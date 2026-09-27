#include <IRremote.h> // Including the IRremote library
#include <LiquidCrystal.h> // Including the LiquidCrystal library

#define LED_PIN_1 12 // Lines 4 - 7: Defining LED pins and array size
#define LED_PIN_2 11
#define LED_PIN_3 10
#define LED_ARRAY_SIZE 3

#define IR_RECEIVE_PIN 3 // Lines 9 - 14: Mapping the ir remote buttons and defining the ir receiver
#define IR_BUTTON_0 25
#define IR_BUTTON_1 69
#define IR_BUTTON_2 70
#define IR_BUTTON_3 71
#define IR_BUTTON_STOP 28

#define LCD_RS_PIN A5 // Lines 16 - 21: Defining crucial lcd screen pins
#define LCD_E_PIN A4
#define LCD_D4_PIN 6
#define LCD_D5_PIN 7
#define LCD_D6_PIN 8
#define LCD_D7_PIN 9

LiquidCrystal lcd (LCD_RS_PIN, LCD_E_PIN, LCD_D4_PIN,  // Creating an object and hosting all of the lcd screen pins in it
                   LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);
                   

byte LED_ARRAY[LED_ARRAY_SIZE] = {LED_PIN_1, LED_PIN_2, LED_PIN_3}; // Creating an array of LEDs so we can loop through them when necessary

String LEDsOffText = "LEDs toggled off"; // Lines 30 - 34: These strings will be used to print text on the lcd screen, and as an argument
String LED_1_On = "LED 1 Toggled";
String LED_2_On = "LED 2 Toggled";
String LED_3_On = "LED 3 Toggled";
String invalidText = "Invalid Data";


void switchStructureRepetition(int command, String textToReveal){ // This function helps avoid repetitions in code later on
  
  lcd.setCursor(7, 0);
  lcd.print(command);
  lcd.print("       ");
  lcd.setCursor(0, 1);
  lcd.print(textToReveal);

  for (int i = 0; i <= 16; i++){ // This for loop will help eliminate unnecessary letters in the lcd screen

    if (i >= textToReveal.length()){

      lcd.setCursor(i, 1);
      lcd.print(" ");
      
    }
  }
}


void toggleLED(int pinNumber){ // This function, toggleLED, will help turn LEDs on/off in the ir remote switch structure
  
  if (digitalRead(pinNumber) == LOW){
    digitalWrite(pinNumber, HIGH);
  }
  else {
    digitalWrite(pinNumber, LOW);
  }
}


void turnOffLEDs(){ // This function turns off all the LEDs when called

  for (int i = 0; i < LED_ARRAY_SIZE; i++){
    digitalWrite(LED_ARRAY[i], LOW);
  }
}


void LEDsLoopTinkering(){
  
  for (int i = 0; i < LED_ARRAY_SIZE; i++){ // For loop in order to turn off all LEDs at the start and place a mode
    
    pinMode(LED_ARRAY[i], OUTPUT);
    digitalWrite(LED_ARRAY[i], LOW);
    
  }
}



void setup() {

  lcd.begin(16, 2); // Lines 89 - 90: Initializing LCD display and ir receiver
  IrReceiver.begin(IR_RECEIVE_PIN);
  LEDsLoopTinkering();
  
}


void loop() {

  if (IrReceiver.decode()){ // If something is pressed...

    IrReceiver.resume(); // Continue searching buttons pressed
    int command = IrReceiver.decodedIRData.command; // Every button has a command, or a unique integer in order to map the keys

    switch (command) { // Beginning of the switch case

      case IR_BUTTON_0: { // If the button 0 is pressed...
        
        turnOffLEDs();
        switchStructureRepetition(command, LEDsOffText);
        break;
        
      }
      case IR_BUTTON_1: { // If the button 1 is pressed...

        toggleLED(LED_PIN_1); // This turns LED 1 on/off
        switchStructureRepetition(command, LED_1_On);
        break;
        
      }
      case IR_BUTTON_2: { // If the button 2 is pressed...

        toggleLED(LED_PIN_2); // This turns LED 2 on/off
        switchStructureRepetition(command, LED_2_On);
        break;
        
      }
      case IR_BUTTON_3: { // If the button 3 is pressed...

        toggleLED(LED_PIN_3); // This turns LED 3 on/off
        switchStructureRepetition(command, LED_3_On);
        break;
        
      }
      case IR_BUTTON_STOP: { // If the button "ok" is pressed...

        lcd.clear(); // LCD display clears
        break;
        
      }
      default: {
        switchStructureRepetition(command, invalidText);
      }
    }
  }
}