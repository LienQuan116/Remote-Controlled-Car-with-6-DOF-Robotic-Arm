#include <BluetoothSerial.h> 
#include <ESP32Servo.h> 

BluetoothSerial Bluetooth; 

Servo servos[6]; 
int currentPos[6] = {90, 150, 35, 140, 85, 80}; 
const int servoPins[6] = {13, 12, 14, 27, 26, 25}; 
String dataIn = ""; 

void setup() { 
  Serial.begin(115200); 
  Bluetooth.begin("ESP32_BT"); 
  Serial.println("Bluetooth đang khởi động..."); 
  
  for (int i = 0; i < 6; i++) { 
    servos[i].attach(servoPins[i]); 
    servos[i].write(currentPos[i]); 
  } 
} 

void moveServoSmooth(int index, int targetPos) { 
  targetPos = constrain(targetPos, 0, 180);  
  int pos = currentPos[index]; 
  int step = (targetPos > pos) ? 1 : -1; 
 
  for (int p = pos; p != targetPos; p += step) { 
    servos[index].write(p); 
    delay(15); 
  } 
  servos[index].write(targetPos);  
  currentPos[index] = targetPos; 
} 
 
void loop() { 
  if (Bluetooth.available()) { 
    dataIn = Bluetooth.readStringUntil('\n');   
 
    if (dataIn.length() >= 3 && dataIn.startsWith("s")) { 
      int servoIndex = dataIn.substring(1, 2).toInt() - 1;   
 
      if (servoIndex >= 0 && servoIndex < 6) { 
        int target = dataIn.substring(2).toInt(); 
        moveServoSmooth(servoIndex, target);   
      } 
    } 
  } 
}