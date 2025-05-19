#include <esp_now.h>
#include <WiFi.h>

//Set output pins
const int ledPin1 = 19;
const int ledPin2 = 21;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int num;
}struct_message;

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;

// Create an array with all the structures
struct_message boardsStruct[2] = {board1, board2};

// callback function that will be executed when data is received
// Callback function for receiving data
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  struct_message receivedData;
  memcpy(&receivedData, incomingData, sizeof(receivedData));

  if (receivedData.id >= 1 && receivedData.id <= 2) {
    boardsStruct[receivedData.id - 1].num = receivedData.num;
  }
  
  Serial.printf("Board ID %u: Received value: %d\n", receivedData.id, receivedData.num);
}


 
void setup() {
  //Initialise GPIO2 as output
  pinMode(ledPin1, OUTPUT);

  //Initialise GPIO15 as output
  pinMode(ledPin2, OUTPUT);
  
  //Initialize Serial Monitor
  Serial.begin(115200);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}
 
void loop() {
}
