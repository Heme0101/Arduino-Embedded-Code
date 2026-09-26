#include <IRremote.h>
#define IR_RECEIVE_PIN 7

#define IR_BUTTON_0 25
#define IR_BUTTON_1 69
#define IR_BUTTON_2 70
#define IR_BUTTON_PLAY_PAUSE 28



void setup() {

  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN);

}


void loop() {

  if (IrReceiver.decode()){
    
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;

    switch (command) {
      case IR_BUTTON_0: {
        Serial.println("Button 0");
        break;
      }
      case IR_BUTTON_1: {
        Serial.println("Button 1");
        break;
      }
      case IR_BUTTON_PLAY_PAUSE: {
        Serial.println("Button play/paused");
        break;
      }
      default: {
        Serial.println("Invalid Data");
      }
    }
  }
}
