#include <Servo.h>
#include <ArduinoJson.h>

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

int i = 0;

char json[] = "{'action': 3, 'baseDegrees': '71', 'arm1Degrees': '20', 'speed': '0'}";

DynamicJsonDocument doc(300);

void setup() {
  servo1.attach(3); //base
  servo2.attach(5); //Arm one (Range 0 - 80 (MAX 90))
  
  servo2.write(85);
  servo2.write(0);
  servo1.write(180);
  servo1.write(0);

  delay(1000);
  

  Serial.begin(115200);
  Serial.setTimeout(1);

  doc["action"];
  doc["baseDegrees"];
  doc["arm1Degrees"];
  doc["speed"];
}

void moveBase(int x, int v) {
  if (x > servo1.read()) {
    for (i = servo1.read(); i < x; i++) { 
    servo1.write(i);                        
    delay(v);                      
  }
  }
  else if (x < servo1.read()) {
    for (i = servo1.read(); i > x; i--) { 
    servo1.write(i);                       
    delay(v);                      
  }
  }
}

void moveArm1(int x, int v) {
  if (x > servo2.read()) {
    for (i = servo2.read(); i < x; i++) { 
    servo2.write(i);                        
    delay(v);                      
  }
  }
  else if (x < servo2.read()) {
    for (i = servo2.read(); i > x; i--) { 
    servo2.write(i);                       
    delay(v);                      
  }
  }
}

void loop() {
  if (Serial.available() > 0) {

    doc.clear();

    deserializeJson(doc, Serial.readString());

    int commandNum = doc["action"];
    String basePos = doc["baseDegrees"];
    String arm1Pos = doc["arm1Degrees"];
    String delayStr = doc["speed"];

    int basePosInt = basePos.toInt();
    int arm1PosInt = arm1Pos.toInt();
    int delayInt = delayStr.toInt();
    
    
    if (commandNum == 1) {
      
    for (i = 0; i < 180; i++) { 
    servo1.write(i);                        
    delay(10);                      
  }

    for (i = 0; i < 80; i++) { 
    servo2.write(i);                        
    delay(10);                      
  }
  for (i = 80; i > 0; i--) { 
    servo2.write(i);                       
    delay(10);                      
  }
  
  for (i = 180; i > 0; i--) { 
    servo1.write(i);                       
    delay(10);                      
  }
  }
  
  if (commandNum == 2) {
    moveBase(0, delayInt);
    moveArm1(0, delayInt);
  }
  if (commandNum == 3) {
    moveBase(basePosInt, delayInt);
    moveArm1(arm1PosInt, delayInt);
  }
    }


  
}
