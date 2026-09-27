#define PHOTORESISTOR_PIN A0
#define LED_PIN_1 12
#define LED_PIN_2 10

byte LED_PIN_ARRAY[2] = {LED_PIN_1, LED_PIN_2};

int threshold = 200;


void setup() {

  for (int i = 0; i < 2; i++){
    pinMode(LED_PIN_ARRAY[i], OUTPUT);
  }

}


void loop() {

  int luminosity = analogRead(PHOTORESISTOR_PIN);

  if (luminosity < threshold){
    digitalWrite(LED_PIN_1, HIGH);
  }
  else{
    digitalWrite(LED_PIN_1, LOW);
  }

  int brightness = 255 - luminosity / 4;

  analogWrite(LED_PIN_2, brightness);
  
}
