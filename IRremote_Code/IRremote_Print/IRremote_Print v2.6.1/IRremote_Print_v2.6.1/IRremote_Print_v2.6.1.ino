#include <IRremote.h>
#define IR_RECEIVE_PIN 7

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results; // decode_results class is defined in IRremote.h


void setup() {
  
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  
}


void loop() {
  
  if (irrecv.decode(&results)){
    
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    
  }
  delay(100); // Small delay to prevent reading errors
}
