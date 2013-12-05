#include <SPI.h>
#include <Ethernet.h>
#include "plotly_ethernet.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // doesn't really matter
byte my_ip[] = { 199, 168, 222, 18 }; // google will tell you: "public ip address"

void startEthernet(){
    Serial.println("Initializing ethernet");
    if(Ethernet.begin(mac) == 0){
        Serial.println("Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, my_ip);
    }
    Serial.println("Done initializing ethernet");
    delay(1000);
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  startEthernet();    // initialize ethernet
  
  plotly plotly;
  plotly.VERBOSE = true;
  plotly.DRY_RUN = false;
  plotly.layout="{}"; //{\"title\": \"oh, how fun! arduino data streaming\", \"xaxis\": {\"type\": \"date\"}, \"yaxis\": {\"name\": \"analog values\"}}"; // JSON formatted layout object -- not for the memory constrained!
  plotly.maxStringLength = 19;

  int nTraces=2; // number of traces
  int nPoints=45; // number of points to transmit for a single trace
  char filename[] = "arduino - example 1";
  char username[] = "public_arduino";
  char api_key[] = "4z1r78yx9a";
  
  plotly.open_stream(nPoints, nTraces, filename, username, api_key);
  
  String date; int reading; float freading;
  for(int i=0; i<nPoints; i++){
    date = "2013-12-04 12:35:";
    if(i<10){ date += "0"; }
    date += i;
    reading = analogRead(2);
    freading = 1.1*reading;
    plotly.post(date,reading); // trace 1 (implicitly defined by order)
    plotly.post(date, freading); // trace 2
    delay(500);
  }
}

void loop() {
  while(true);
}