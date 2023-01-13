#include <BleKeyboard.h>
#include <string.h>

BleKeyboard bleKeyboard;
int pushDelay= 2000; // zwischen eingabe & ausgabe

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
}

void loop() {
    int n= pushDelay;
    String s= getUserSerialInput();
    Serial.println(s);
    checkInput(s);
    if (pushDelay== n) { // wird übersprungen 
        delay(pushDelay); // wenn Delay neu
        pushKeystroke(s); // gesetzt wurde
    }
}

String getUserSerialInput() {
    String input;
    while(!Serial.available()){Serial.print(".");delay(3000);}
    input = Serial.readStringUntil('\n');
    input = input.substring(0,input.length());
    return input;
}

void pushKeystroke(String pushMessage) {
    Serial.println("\npush:\t" + pushMessage);
    while(!bleKeyboard.isConnected()) {Serial.print(".");delay(3000);}
    Serial.print("\n     \t");
    for (int i= 0; i< pushMessage.length(); i++) { // z & y char swap
        if ((char) pushMessage[i] == 'y') {
            pushMessage[i]= 'z';
        } else if ((char) pushMessage[i] == 'Y') {
            pushMessage[i]= 'Z';
        } else if ((char) pushMessage[i] == 'z') {
            pushMessage[i]= 'y';
        } else if ((char) pushMessage[i] == 'Z') {
            pushMessage[i]= 'Y';
        }
    }
    for (int i= 0; i < pushMessage.length(); i++) { // schleife pusht ein char nach dem anderen
        bleKeyboard.write(pushMessage[i]);
        Serial.print(pushMessage[i]);
        delay(50);
    }
    Serial.println("\nKEYSTROKE EXECUTED\n");
    return;
}

void checkInput(String s) {
    if (s.equals("setDelay")) {
        Serial.print("\nsetDelay");
        while(!Serial.available()){Serial.print(".");delay(3000);}
        String input = Serial.readStringUntil('\n');
        input = input.substring(0,input.length());
        pushDelay= input.toInt();
        Serial.print("\tsetDelay to: " + pushDelay);
        return;
    }
}