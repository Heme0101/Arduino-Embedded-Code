#define ECHO_PIN 3
#define TRIGGER_PIN 8

#define WARNING_LED 5 // Warning LED Pin or Yellow LED
#define ERROR_LED 12 // RED LED

#define PUSHBUTTON_PIN 6

#define LOCK_DISTANCE 5.0 // 5 inches

// ultrasonic
unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;

float previousDistance = 157.48;

// warning LED
unsigned long lastTimeWarningLEDBlinked = millis();
unsigned long warningLEDCounter = 500;
byte warningLEDState = LOW;

// error LED
unsigned long lastTimeErrorLEDBlinked = millis();
unsigned long errorLEDCounter = 300;
byte errorLEDState = LOW;

// push button
unsigned long lastTimeButtonChanged = millis();
unsigned long buttonDebounceDelay = 50;
byte buttonState;


boolean isLocked = false;

byte OUTPUT_ARRAY[3] = {WARNING_LED, ERROR_LED, TRIGGER_PIN};


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


float getUltrasonicDistance(){

  float durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  float distance = durationMicros / 148.0;

  if (distance > 157.48){
    return previousDistance;
  }
  distance = previousDistance * 0.6 + distance * 0.4;
  previousDistance = distance;

  return distance;
}


void toggleWarningLED(){

  warningLEDState = (warningLEDState == HIGH) ? LOW : HIGH; 
  digitalWrite(WARNING_LED, warningLEDState);
  
}


void toggleErrorLED(){

  errorLEDState = (errorLEDState == HIGH) ? LOW : HIGH;
  digitalWrite(ERROR_LED, errorLEDState);
  
}


void setWarningLEDBlinkRateFromDistance(float distance){
  
  // 0 ... 157.48 -> 0 ... 629.92
  warningLEDCounter = distance * 4;
  
}


void lock(){

  if (!isLocked){
    Serial.println("Locking...");
    isLocked = true;
    warningLEDState = LOW;
    errorLEDState = LOW;
  }
  
}


void unlock(){

  if (isLocked){
    Serial.println("Unlocking...");
    isLocked = false;
    errorLEDState = LOW;
    digitalWrite(ERROR_LED, errorLEDState);
  }
  
}



void setup(){

  Serial.begin(115200);
   
  pinMode(ECHO_PIN, INPUT);
  pinMode(PUSHBUTTON_PIN, INPUT);

  for (int i = 0; i <= 3; i++){
    pinMode(OUTPUT_ARRAY[i], OUTPUT);
  }

  buttonState = digitalRead(PUSHBUTTON_PIN);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
}


void loop(){

  unsigned long timeNow = millis();

  if (isLocked){
    if (timeNow - lastTimeErrorLEDBlinked > errorLEDCounter){
      lastTimeErrorLEDBlinked += errorLEDCounter;
      toggleErrorLED();
      toggleWarningLED();
    }

    if (timeNow - lastTimeButtonChanged > buttonDebounceDelay){
       byte newButtonState = digitalRead(PUSHBUTTON_PIN);
       if (newButtonState != buttonState){
        lastTimeButtonChanged = timeNow;
        buttonState = newButtonState;
        if (buttonState == LOW){
          unlock();
        }
       }
    }
    
  }
  else{
    if (timeNow - lastTimeWarningLEDBlinked > warningLEDCounter){
      lastTimeWarningLEDBlinked += warningLEDCounter;
      toggleWarningLED();
    }
  }


  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay){
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  
  if (newDistanceAvailable){
    newDistanceAvailable = false;
    float distance = getUltrasonicDistance();
    setWarningLEDBlinkRateFromDistance(distance);

    if (distance <= LOCK_DISTANCE){
      lock();
    }
  }
  
}
