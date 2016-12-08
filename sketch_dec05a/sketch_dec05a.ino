//Programa : Sensor de umidade e temperatura DHT11
//Autor : Arduino e Cia

#include <dht.h>

#define PMTR       A0
#define dht_dpin   A1 //Pino DATA do Sensor ligado na porta Analogica A1
#define DIR_PIN    4
#define STEP_PIN   5
#define ENABLE_PIN 6

dht DHT; //Inicializa o sensor
double t;
void fan_on();
void fan_off();

void setup()
{
  Serial.begin(9600);

  pinMode(STEP_PIN, OUTPUT); // Step 
  pinMode(DIR_PIN, OUTPUT); // Dir 
  pinMode(ENABLE_PIN, OUTPUT); // ENABLE

  delay(1000);//Aguarda 1 seg antes de acessar as informações do sensor

  digitalWrite(ENABLE_PIN, HIGH);
  digitalWrite(DIR_PIN, HIGH);
}

void loop()
{
  DHT.read11(dht_dpin); //Lê as informações do sensor
  t = DHT.temperature;
  Serial.print("Temperatura = ");
  Serial.print(t); 
  Serial.print(" Celsius  ");

  int pmtrValue = analogRead(PMTR);
  int wantedTemp = map(pmtrValue, 0, 1023, 20,30); 

  Serial.print(pmtrValue); 
  Serial.print("  ");
  Serial.print(wantedTemp);
  Serial.print("  ");

  if (t > wantedTemp) {
    Serial.println("   fan is on");
    digitalWrite(ENABLE_PIN, LOW);
    fan_on(); 
  } 
  else {
    digitalWrite(ENABLE_PIN, HIGH);
    Serial.println("   fan is off");
    delay(1000);
  }


  // Não diminuir o valor abaixo. O ideal é a leitura a cada 2 segundos
  // delay(1000);  
}

void fan_on() {
  int cicle = 200;
  for(int x = 0; x < cicle * 20; x++) {
    digitalWrite(STEP_PIN,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(STEP_PIN,LOW); 
    delayMicroseconds(500); 
  }
}
