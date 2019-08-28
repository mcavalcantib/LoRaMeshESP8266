#include <Arduino.h>
#include <LoRaMesh.h>

/* Local device ID */
uint16_t localId;

/* Remote device ID */
uint16_t remoteId;

/* Local device Unique ID */
uint32_t localUniqueId;

/* Local device Net */
uint16_t localNet;

/* Remote device ID to communicate with */
uint16_t ID = 10;

/* Payload buffer */
uint8_t bufferPayload[MAX_PAYLOAD_SIZE] = {0};

/* Values read on each analog inputs */
uint16_t AdcIn[2];

/* SoftwareSerial handles */
SoftwareSerial* hSerialCommands = NULL;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
  //Configurando o módulo LoRaMesh
  delay(1000);
  Serial.begin(9600); /* Initialize monitor serial */
  
  /* Initialize SoftwareSerial */
  //Pinos:
  // D6(12)->Lora TX
  // D5(14)-> Lora RX
  hSerialCommands = SerialCommandsInit(12, 14, 9600);
  
  /* Gets the local device ID */
  if(LocalRead(&localId, &localNet, &localUniqueId) != MESH_OK)
    Serial.print("Couldn't read local ID\n\n");
  else
  {
    Serial.print("Local ID: ");
    Serial.println(localId);
    Serial.print("Local NET: ");
    Serial.println(localNet);
    Serial.print("Local Unique ID: ");
    Serial.println(localUniqueId, HEX);
    Serial.print("\n");
  }
  
  delay(500);
}

void loop() {
  digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}