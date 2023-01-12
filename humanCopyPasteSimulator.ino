/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>
#include <string.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  Serial.println("Serial & ble init");
}

void loop() {
    pushKeystroke(getUserSerialInput()); 
    while (true) {delay(99999);}
}

String getUserSerialInput() {
    String input;
    while(!Serial.available()){
        Serial.print("\nPaste Keystroke to push over: ");
        delay(5000);
    }
    Serial.flush();
    input = Serial.readStringUntil('\n');
    input = input.substring(0,input.length());
    Serial.println("User will push: " + input);
    Serial.println("            to: BLE Keyboard");
    return input;
}

void pushKeystroke(String pushMessage) {
    while(!bleKeyboard.isConnected()) {
        Serial.println("BLE connection waiting 5 seconds...");
        delay(5000);
    }
    int str_len = pushMessage.length() + 1; 
    for (int i= 0; i < str_len; i++) {
        bleKeyboard.write(pushMessage[i]);
        Serial.println("execute: "+ pushMessage[i]);
        delay(100);
    }
    Serial.println("\nKEYSTROKE EXECUTED");
    return;

}