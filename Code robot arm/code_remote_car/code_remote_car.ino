#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 

RF24 radio(10, 8);  
const byte address[6] = "00001"; 

char receivedData[32] = ""; 

// L298N 1 - Bánh trước 
#define ENA_F 3    
#define IN1_F 2 
#define IN2_F 4 
#define ENB_F 5    
#define IN3_F A4 
#define IN4_F 7 

// L298N 2 - Bánh sau 
#define ENA_R 9    
#define IN1_R A0 
#define IN2_R A1 
#define ENB_R 6    
#define IN3_R A2 
#define IN4_R A3 
 
void setup() { 
  Serial.begin(9600); 
 
  if (!radio.begin()) { 
    Serial.println("NRF24L01 không khởi động được!"); 
    while (1); 
  } 
  radio.setPALevel(RF24_PA_LOW); 
  radio.setChannel(108); 
  radio.openReadingPipe(0, address); 
  radio.startListening(); 
  Serial.println("Đang chờ lệnh từ ESP32..."); 
 
  int motorPins[] = { 
    ENA_F, IN1_F, IN2_F, ENB_F, IN3_F, IN4_F, 
    ENA_R, IN1_R, IN2_R, ENB_R, IN3_R, IN4_R 
  }; 
  for (int i = 0; i < 12; i++) { 
    pinMode(motorPins[i], OUTPUT); 
  } 
} 
 
void loop() { 
  if (radio.available()) { 
    radio.read(&receivedData, sizeof(receivedData)); 
    Serial.print("Nhận lệnh: "); 
    Serial.println(receivedData); 
 
    if (strcmp(receivedData, "FWD") == 0) { 
      forward(); 
    } else if (strcmp(receivedData, "REV") == 0) { 
      reverse(); 
    } else if (strcmp(receivedData, "LEFT") == 0) { 
      moveLeft(); 
    } else if (strcmp(receivedData, "RIGHT") == 0) { 
      moveRight(); 
    } else if (strcmp(receivedData, "STOP") == 0) { 
      stopMotors(); 
    } 
  } 
} 
 
void setMotor(int in1, int in2, int ena, int speed) { 
  if (speed > 0) { 
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
  } else if (speed < 0) { 
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 
    speed = -speed;  
  } else { 
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
  } 
  analogWrite(ena, speed); 
} 
void forward() { 
  Serial.println("Tiến"); 
  setMotor(IN1_F, IN2_F, ENA_F, 100);  
  setMotor(IN3_F, IN4_F, ENB_F, 100);  
  setMotor(IN1_R, IN2_R, ENA_R, 100);  
  setMotor(IN3_R, IN4_R, ENB_R, 100);  
} 
void reverse() { 
  Serial.println("Lùi"); 
  setMotor(IN1_F, IN2_F, ENA_F, -100);  
  setMotor(IN3_F, IN4_F, ENB_F, -100);  
  setMotor(IN1_R, IN2_R, ENA_R, -100);  
  setMotor(IN3_R, IN4_R, ENB_R, -100);  
} 
void moveLeft() { 
  Serial.println("Sang trái"); 
  setMotor(IN1_F, IN2_F, ENA_F, -100);  
  setMotor(IN3_F, IN4_F, ENB_F, 100);   
  setMotor(IN1_R, IN2_R, ENA_R, 100);   
  setMotor(IN3_R, IN4_R, ENB_R, -100);  
} 
void moveRight() { 
  Serial.println("Sang phải"); 
  setMotor(IN1_F, IN2_F, ENA_F, 100);   
  setMotor(IN3_F, IN4_F, ENB_F, -100);  
  setMotor(IN1_R, IN2_R, ENA_R, -100);  
  setMotor(IN3_R, IN4_R, ENB_R, 100);   
} 
void stopMotors() { 
  Serial.println("Dừng"); 
  setMotor(IN1_F, IN2_F, ENA_F, 0); 
  setMotor(IN3_F, IN4_F, ENB_F, 0); 
  setMotor(IN1_R, IN2_R, ENA_R, 0); 
  setMotor(IN3_R, IN4_R, ENB_R, 0); 
}