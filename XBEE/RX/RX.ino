// https://github.com/andrewrapp/xbee-arduino/blob/master/examples/Series1_Rx/Series1_Rx.pde
#include <XBee.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


/*
This example is for Series 1 XBee (802.15.4)
Receives either a RX16 or RX64 packet and sets a PWM value based on packet data.
Error led is flashed if an unexpected packet is received
*/

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

int statusLed = 11;
int errorLed = 12;
int dataLed = 10;

uint8_t option = 0;
uint8_t data = 0;

void flashLed(int pin, int times, int wait) {
    
    for (int i = 0; i < times; i++) {
      digitalWrite(pin, HIGH);
      delay(wait);
      digitalWrite(pin, LOW);
      
      if (i + 1 < times) {
        delay(wait);
      }
    }
}

void setup() {
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  pinMode(dataLed,  OUTPUT);
  pinMode(2, OUTPUT);
  
  Serial.begin(9600);
  //Serial.println("Inicio codigo RX");

  digitalWrite(2, 1);
  delay(100);
  digitalWrite(2, 0);

  mySerial.begin(9600);
  xbee.setSerial(Serial);
  flashLed(statusLed, 3, 50);
}

// continuously reads packets, looking for RX16 or RX64
void loop() {
    
    xbee.readPacket(); 
    
    if (xbee.getResponse().isAvailable()) {
    digitalWrite(2, 1);
    //Serial.println("AVAILABLE");    
      
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE) {
        
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
//          Serial.println("RX_16");    
          xbee.getResponse().getRx16Response(rx16);
          option = rx16.getOption();
          data = rx16.getData(0);
        } else {
//          Serial.println("RX_64");    
          xbee.getResponse().getRx64Response(rx64);
          option = rx64.getOption();
          data = rx64.getData(0);
        }
        
        flashLed(statusLed, 1, 10);
        
        // set dataLed PWM to value of the first byte in the data
        analogWrite(dataLed, data);
      } else {
//        Serial.println("RX_??");    
        flashLed(errorLed, 1, 25);
      }
    } else if (xbee.getResponse().isError()) {
//        Serial.println("RX_ERROR");    
      //nss.print("Error reading packet.  Error code: ");  
      //nss.println(xbee.getResponse().getErrorCode());
      // or flash error led
    } 
}
