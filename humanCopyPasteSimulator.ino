#include <BleKeyboard.h>
#include <string.h>

BleKeyboard bleKeyboard("HumanTrashSim", "419", 100);
int pushDelay= 1500, typeDelayy= 20;
String data;
bool changeParameters= false;

void setup() {
    Serial.begin(115200);
    while(!Serial);
    bleKeyboard.begin();
}

void loop() {
    checkBluetoothConnection();
    data= getUserSerialInput();
    // Entwerfe Methode zum modifizieren der 
    // Parameter zur Laufzeit
    if (!changeParameters) { 
        delay(pushDelay); 
        charSwap(); 
        for (int i= 0; i < data.length(); i++) {
            bleKeyboard.write(data[i]);
            delay(typeDelayy);
        }
        data= "";
    }
    Serial.print("\nready for next execute");
}

String getUserSerialInput() {
    String s;
    while(!Serial.available()){Serial.print(".");delay(3000);}
    s = Serial.readStringUntil('\n');
    s = s.substring(0,s.length());
    return s;
}

void charSwap() { // y & z upper/lower case
    for (int i= 0; i< data.length(); i++) { 
        if (data[i] == 'y') {data[i]= 'z';
        } else if (data[i] == 'Y') {data[i]= 'Z';
        } else if (data[i] == 'z') {data[i]= 'y';
        } else if (data[i] == 'Z') {data[i]= 'Y';}
    }
}

void checkBluetoothConnection() {
    if(!bleKeyboard.isConnected()){
        Serial.print("wait for connection");
    }
    while(!bleKeyboard.isConnected()) {
        Serial.print(".");delay(3000);
    }
}