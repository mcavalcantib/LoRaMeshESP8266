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


MeshStatus_Typedef WriteConfig(uint16_t id, uint16_t net, uint32_t uniqueId) {
    uint8_t crc = 0;
    uint8_t bufferPayload[31];
    uint8_t payloadSize;
    uint8_t i = 0;
    uint8_t command;
    uint16_t id = 0;

    /* Asserts parameters */
    if (net == NULL) return MESH_ERROR;
    if (uniqueId == 0) return MESH_ERROR;
    if (hSerialCommands == NULL) return MESH_ERROR;

    /* Loads dummy bytes */
    for (i = 0; i < 3; i++) bufferPayload[i] = 0x00;

    PrepareFrameCommand(idIn, CMD_REMOTEREAD, &bufferPayload[0], i);

    /* Sends packet */
    SendPacket();

    /* Flush serial input buffer */
    SerialFlush(hSerialCommand);

    /* Waits for response */
    if (ReceivePacketCommand(&id, &command, &bufferPayload[0], &payloadSize,
                             5000) != MESH_OK)
        return MESH_ERROR;

    /* Checks command */
    if ((command != CMD_REMOTEREAD) && (command != CMD_LOCALREAD))
        return MESH_ERROR;

    /* Stores the received data */
    if (idOut != NULL) /* Local read */
    {
        deviceId = id;
        *idOut = id;
    }
    *net = (uint16_t)bufferPayload[0] | ((uint16_t)(bufferPayload[1]) << 8);
    *uniqueId = (uint32_t)bufferPayload[2] |
                ((uint32_t)(bufferPayload[3]) << 8) |
                ((uint32_t)(bufferPayload[4]) << 16) |
                ((uint32_t)(bufferPayload[5]) << 24);

    return MESH_OK;
}

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
  Serial.println("Sending ID and NET Configurations......");
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