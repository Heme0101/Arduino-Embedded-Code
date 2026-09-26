#include <IRremote.h>
#define IR_RECEIVE_PIN 7


void setup() {
  
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN); // Start the receiver
  
}


void loop() {
  
  if (IrReceiver.decode()){
    
    IrReceiver.resume(); // Receive the next value
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    Serial.println(IrReceiver.decodedIRData.command);
    Serial.println("---");
    
  }
}
