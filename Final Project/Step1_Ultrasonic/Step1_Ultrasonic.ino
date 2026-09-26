#define ECHO_PIN 3
#define TRIGGER_PIN 8

unsigned long lastTimeUltrasonicTrigger = millis();
unsigned long ultrasonicTriggerDelay = 60;

volatile unsigned long pulseInTimeBegin;
volatile unsigned long pulseInTimeEnd;
volatile bool newDistanceAvailable = false;

float previousDistance = 157.48;


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


void setup(){

  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
}


void loop(){

  unsigned long timeNow = millis();

  if (timeNow - lastTimeUltrasonicTrigger > ultrasonicTriggerDelay){
    lastTimeUltrasonicTrigger += ultrasonicTriggerDelay;
    triggerUltrasonicSensor();
  }

  if (newDistanceAvailable){
    newDistanceAvailable = false;
    float distance = getUltrasonicDistance();
    Serial.println(distance);
  }
  
}
