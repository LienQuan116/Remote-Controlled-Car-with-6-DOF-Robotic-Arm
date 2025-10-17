#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 

RF24 radio(4, 5); 
const byte address[6] = "00001"; 

// Nút nhấn 
const int buttonFWD = 12;  
const int buttonREV = 13;   
const int buttonLEFT = 27;  
const int buttonRIGHT = 26; 

void setup() { 
  pinMode(buttonFWD, INPUT_PULLUP); 
  pinMode(buttonREV, INPUT_PULLUP); 
  pinMode(buttonLEFT, INPUT_PULLUP); 
  pinMode(buttonRIGHT, INPUT_PULLUP); 
  pinMode(buttonROTATE, INPUT_PULLUP); 
  
  Serial.begin(115200); 
  
  if (!radio.begin()) { 
    Serial.println("NRF24L01 không khởi động được."); 
    while (1); 
  } 
  radio.setPALevel(RF24_PA_LOW); 
  radio.setChannel(108); 
  radio.openWritingPipe(address); 
  radio.stopListening(); 
} 
 
void loop() { 
  const char* command = "STOP";  
 
  if (digitalRead(buttonFWD) == LOW) { 
    command = "FWD"; 
  } else if (digitalRead(buttonREV) == LOW) { 
    command = "REV"; 
  } else if (digitalRead(buttonLEFT) == LOW) { 
    command = "LEFT"; 
  } else if (digitalRead(buttonRIGHT) == LOW) { 
    command = "RIGHT"; 
  } 
 
  radio.write(command, strlen(command) + 1); 
  Serial.print("Gửi: "); Serial.println(command); 
 
  delay(200); // Chống dội 
}