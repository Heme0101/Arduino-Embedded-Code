#define ECHO_PIN 3
#define TRIGGER_PIN 4

#define LED_PIN_RED 12
#define LED_PIN_YELLOW 11
#define LED_PIN_GREEN 10

#define pinModeArraySize 4


unsigned long lastTimeUltrasonicTriggered = millis();
unsigned long ultrasonicTriggerDelay = 60;


volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile boolean newDistanceAvailable = false;


byte pinModeArray[pinModeArraySize] = 
     {LED_PIN_RED, LED_PIN_YELLOW, LED_PIN_GREEN, TRIGGER_PIN};

     
int previousDistance = 157.48;


void triggerUltrasonicSensor(){

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
}


float getUltrasonicDistance(){

  float durationMicros = pulseInTimeEnd - pulseInTimeBegin;
  float distance = durationMicros / 148.0; // Distance In Inches For Cm Divide By 58.0

  if (distance > 157.48){ // Lines 44 - 50 Help The Ultrasonic Sensor Function Smoother
    return previousDistance;
  }

  distance = previousDistance * 0.7 + distance * 0.3;
  previousDistance = distance;
  return distance;
  
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



void setup() {

  for (int i = 0; i < pinModeArraySize; i++){

    pinMode(pinModeArray[i], OUTPUT);
    
  }

  pinMode(ECHO_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
  
}



void loop() {

  unsigned long timeNow = millis();

  if (timeNow - lastTimeUltrasonicTriggered >= ultrasonicTriggerDelay){

    lastTimeUltrasonicTriggered = timeNow;

    triggerUltrasonicSensor();
    
  }


  if (newDistanceAvailable){

    newDistanceAvailable = false;
    double distance = getUltrasonicDistance();
    
    if (distance > 39.3701){

      digitalWrite(LED_PIN_GREEN, HIGH);
      digitalWrite(LED_PIN_YELLOW, LOW);
      digitalWrite(LED_PIN_RED, LOW);
      
    }
    else if (distance > 5.51181 && distance < 39.7638){

      digitalWrite(LED_PIN_YELLOW, HIGH);
      digitalWrite(LED_PIN_RED, LOW);
      digitalWrite(LED_PIN_GREEN, LOW);
      
    }
    else if (distance < 5.90551){

      digitalWrite(LED_PIN_RED, HIGH);
      digitalWrite(LED_PIN_YELLOW, LOW);
      digitalWrite(LED_PIN_GREEN, LOW);
      
    }
    
  }
  
}
