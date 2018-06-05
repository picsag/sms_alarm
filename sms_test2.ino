#define TINY_GSM_MODEM_SIM800

// Set serial for debug console (to the Serial Monitor, speed 115200)
#define SerialMon Serial
#define SMS_TARGET  "+407*******"
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(11, 10); // RX, TX

#define TINY_GSM_DEBUG SerialMon

#include <TinyGsmClient.h>

TinyGsm modem(SerialAT);

// Module baud rate
uint32_t rate = 0; // Set to 0 for Auto-Detect

int ledPin = 13;                // choose the pin for the LED
int PIRPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
bool res = 0;                   // variable for initalizing once the SIM800L
void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(2000);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(PIRPin, INPUT);     // declare sensor as input
}

void loop() {

  if (!rate) {
    //negociate baud rate with the SIM800L
    rate = TinyGsmAutoBaud(SerialAT);
  }

  if (!rate) {
    SerialMon.println(F("***********************************************************"));
    SerialMon.println(F(" Module does not respond!"));
    SerialMon.println(F("   Check your Serial wiring"));
    SerialMon.println(F("   Check the module is correctly powered and turned on"));
    SerialMon.println(F("***********************************************************"));
    delay(30000L);
    return;
  }

  
  delay(3000);
  if (res == 0){
    SerialAT.begin(rate);
    delay(3000);
  
    modem.simUnlock("0000");

    SerialMon.println("Waiting for network...");
    if (!modem.waitForNetwork()) {
      delay(10000);
      return;
    }

    if (modem.isNetworkConnected()) {
      SerialMon.println("Network connected");
      res = 1;
    }
  
    // Access AT commands from Serial Monitor
    SerialMon.println(F("***********************************************************"));
    SerialMon.println(F(" SIM800L chip ready"));
    SerialMon.println(F(" If SIM800L output not visible, select \"Both NL & CR\" in Serial Monitor"));
    SerialMon.println(F("***********************************************************"));

  }

  val = digitalRead(PIRPin);  // read input value
  if (val == HIGH) {            // check if the PIR input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    //playTone(300, 160);
    delay(150);

    
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      delay(150);
      res = modem.sendSMS(SMS_TARGET, String("Buna"));
    }
  }
  if (pirState == HIGH){
    while(true) {
      if (SerialAT.available()) {
        SerialMon.write(SerialAT.read());
      }
      if (SerialMon.available()) {
        SerialAT.write(SerialMon.read());
      }
      delay(0);
    }
  }
}
