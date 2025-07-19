/*
  Example for receiving
  
  https://github.com/sui77/rc-switch/
  https://github.com/LSatan/SmartRC-CC1101-Driver-Lib
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
  ----------------------------------------------------------
  Mod by Little Satan. Have Fun!
  ----------------------------------------------------------
*/
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <RCSwitch.h>

int pin; // int for Receive pin.

const int maxEvents = 500;

volatile unsigned long lastChangeTime = 0;
volatile bool capturing = false;
volatile int capturedCount = 0;

unsigned long eventTime[maxEvents];
int eventLevel[maxEvents];
unsigned long lastEventMicros = 0;
void setup() {
  Serial.begin(115200);

#ifdef ESP32
pin = 4;  // for esp32! Receiver on GPIO pin 4. 
#elif ESP8266
pin = 4;  // for esp8266! Receiver on pin 4 = D2.
#else
pin = 0;  // for Arduino! Receiver on interrupt 0 => that is pin #2
#endif 
  ELECHOUSE_cc1101.addSpiPin(33, 26, 25, 32, 0);
  //ELECHOUSE_cc1101.addSpiPin(sck, miso, mosi, ss_M1, 1);
  ELECHOUSE_cc1101.addGDO0(14, 0);

  ELECHOUSE_cc1101.setModul(0);
  if (ELECHOUSE_cc1101.getCC1101()){       // Check the CC1101 Spi connection.
  Serial.println("Connection OK");
  }else{
  Serial.println("Connection Error");
  }

//CC1101 Settings:                (Settings with "//" are optional!)
  ELECHOUSE_cc1101.Init();            // must be set to initialize the cc1101!
//ELECHOUSE_cc1101.setRxBW(812.50);  // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
//ELECHOUSE_cc1101.setPA(10);       // set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12)   Default is max!
  ELECHOUSE_cc1101.setMHZ(433.92); // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
  
 // mySwitch.enableReceive(digitalPinToInterrupt(14));  

  ELECHOUSE_cc1101.SetRx();  // set Receive on

  pinMode(14, INPUT);
  attachInterrupt(digitalPinToInterrupt(14), onChange, CHANGE);  
}
void loop() {
  if (capturing) {
    
    if (capturedCount >= maxEvents || (micros() - lastEventMicros > 2000000)) {
      detachInterrupt(digitalPinToInterrupt(14));
      capturing = false;

      Serial.println("Time(us)\tLevel");

      for (int i = 0; i < capturedCount; i++) {
        Serial.print(eventTime[i]);
        Serial.print("\t");
        Serial.println(eventLevel[i]);
        delay(1); 
      }


      capturedCount = 0;
      attachInterrupt(digitalPinToInterrupt(14), onChange, CHANGE);
    }
  }
}

void onChange() {
  if (capturedCount >= maxEvents) return;

  unsigned long now1 = micros();


  if (!capturing) {
    capturing = true;
    lastChangeTime = now1;
    lastEventMicros = now1;
  }


  eventTime[capturedCount] = now1 - lastChangeTime;  
  eventLevel[capturedCount] = digitalRead(14);

  capturedCount++;

}
