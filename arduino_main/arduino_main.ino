#include <Servo.h>

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

String commandNum;
String posBase;
int posBaseInt;
String posArm1;
int posArm1Int;
String speedRemote;
int speedRemoteInt;

int i = 0;

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
    
    String command = Serial.readString(); 
    
    commandNum = command;
    commandNum.remove(1);
    
    command.remove(0, 2);

    int hyphenPos = command.indexOf('-');
    int starPos = command.indexOf('*');


    posArm1 = command;
    posBase = command;
    speedRemote = command;

    posArm1.remove(0, hyphenPos + 1);
    posBase.remove(hyphenPos, 3);
    speedRemote.remove(0, starPos + 1);
    
    posBaseInt = posBase.toInt();
    posArm1Int = posArm1.toInt();
    speedRemoteInt = speedRemote.toInt();
    speedRemoteInt = map(speedRemoteInt, 1, 100, 50, 10); 
    
    int commandInt = command.toInt();

    if (commandNum.toInt() == 1) {
      
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
  if (commandNum.toInt() == 2) {
    moveBase(0, speedRemoteInt);
    moveArm1(0, speedRemoteInt);
  }
  if (commandNum.toInt() == 3) {
    moveBase(posBaseInt, speedRemoteInt);
    moveArm1(posArm1Int, speedRemoteInt);
  }
    }


  
}
