#include "DHT.h"

#define DHTTYPE   DHT11
#define DHTPIN    2
#define RELAY     3
#define PMTR      A7

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(RELAY, OUTPUT);
  //digitalWrite(RELAY, LOW);
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  delay(2000);
  float t = dht.readTemperature();

  int pmtrValue = analogRead(PMTR);
  int wantedTemp = map(pmtrValue, 0, 1023, 20,30);
  bool fanOn = (t > wantedTemp);
  
  Serial.print("Desired Temp: ");
  Serial.print(wantedTemp);
  Serial.print(" *C;");
  Serial.print(" %\t");
  Serial.print("Actual Temp: ");
  Serial.print(t);
  Serial.print(" *C;");
  Serial.print(" %\t");
  if (fanOn) {
    digitalWrite(RELAY, LOW);
    Serial.println("Fan: ON");
  } else {
    digitalWrite(RELAY, HIGH);
    Serial.println("Fan: OFF");
  }
}
