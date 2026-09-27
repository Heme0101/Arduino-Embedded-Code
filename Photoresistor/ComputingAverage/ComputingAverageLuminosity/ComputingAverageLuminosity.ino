// Dots = Progression Bar

#define PHOTORESISTOR_PIN A0
#define luminositySamplesArraySize 100

int luminositySamplesArray[luminositySamplesArraySize] = { 0 };

unsigned long previousTime = 0;
unsigned long frequentRecordingTime = 50; // Milliseconds
unsigned long totalTime = 5000;

long calculatedVar = 0;

boolean calculationCompleted = false;

long calculateAverage(long num){
  
  for (int i = 0; i < luminositySamplesArraySize; i++){
    num += luminositySamplesArray[i];
  }
  return num / luminositySamplesArraySize;
  
}


void displayResults(){

  Serial.println("");
  Serial.print("Luminosity Average For 100 Samples, Each Taken Every 50 Milliseconds: ");
  Serial.println(calculateAverage(calculatedVar));
  
}


void setup() {
  Serial.begin(115200);
}


void loop() {

  if (calculationCompleted){

    unsigned long currentTime = millis();
    if (currentTime - previousTime >= totalTime){

      calculatedVar = 0;
      displayResults();
      previousTime = currentTime;
      calculationCompleted = false;
    }
  }
  else{
  
    for (int i = 0; i < luminositySamplesArraySize; i++){
      delay(frequentRecordingTime);
      luminositySamplesArray[i] = analogRead(PHOTORESISTOR_PIN);
      Serial.print(".");
    }
    calculationCompleted = true;
  }
}
