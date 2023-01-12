#include <BleKeyboard.h>
#include <string.h>

BleKeyboard bleKeyboard;
int pushDelay= 2000; // between serial in & ble out

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  Serial.print("\tGib Ihm\n");
}

void loop() {
    String s= getUserSerialInput();
    checkInput(s);
    delay(pushDelay);
    pushKeystroke(s); 
}

String getUserSerialInput() {
    String input;
    Serial.print("\nPaste Keystroke to push over");
    while(!Serial.available()){Serial.print(".");delay(1000);}
    input = Serial.readStringUntil('\n');
    input = input.substring(0,input.length());
    Serial.println("\npush:\t" + input);
    return input;
}

void pushKeystroke(String pushMessage) {
    while(!bleKeyboard.isConnected()) {Serial.print(".");delay(1000);}
    int str_len = pushMessage.length(); 
    for (int i= 0; i < str_len; i++) {
        bleKeyboard.write(pushMessage[i]);
        Serial.println((char) pushMessage[i]);
        delay(50);
    }
    Serial.println("\nKEYSTROKE EXECUTED");
    return;
}

void checkInput(String s) {
    if (s.equals("setDelay")) {
        Serial.print("setDelay");
        while(!Serial.available()){Serial.print(".");delay(1000);}
        String input = Serial.readStringUntil('\n');
        input = input.substring(0,input.length());
        pushDelay= input.toInt();
        Serial.print("\tsetDelay to: " + pushDelay);
        return;
    }
}