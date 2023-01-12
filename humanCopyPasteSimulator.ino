#include <BleKeyboard.h>
#include <string.h>

BleKeyboard bleKeyboard;
int pushDelay= 2000; // zwischen eingabe & ausgabe

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
  Serial.print("\tGib Ihm\n");
}

void loop() {
    int n= pushDelay;
    String s= getUserSerialInput();
    checkInput(s);
    if (pushDelay== n) { // wird übersprungen 
        delay(pushDelay); // wenn Delay neu
        pushKeystroke(s); // gesetzt wurde
    }
}

String getUserSerialInput() {
    String input;
    Serial.print("\nPaste Keystroke to push over");
    while(!Serial.available()){Serial.print(".");delay(3000);}
    input = Serial.readStringUntil('\n');
    input = input.substring(0,input.length());
    return input;
}

void pushKeystroke(String pushMessage) {
    Serial.println("\npush:\t" + pushMessage);
    while(!bleKeyboard.isConnected()) {Serial.print(".");delay(3000);}
    int str_len = pushMessage.length(); 
    for (int i= 0; i < str_len; i++) {
        bleKeyboard.write(pushMessage[i]);
        Serial.print((char) pushMessage[i]);
        delay(50);
    }
    Serial.println("\nKEYSTROKE EXECUTED\n");
    return;
}

void checkInput(String s) {
    if (s.equals("setDelay")) {
        Serial.print("setDelay");
        while(!Serial.available()){Serial.print(".");delay(3000);}
        String input = Serial.readStringUntil('\n');
        input = input.substring(0,input.length());
        pushDelay= input.toInt();
        Serial.print("\tsetDelay to: " + pushDelay);
        return;
    }
}