#include <Servo.h>

Servo servo1; 
Servo servo2;
Servo servo3;
Servo servo4;

int i = 0;

void setup() {
  servo1.attach(3); //base
  servo2.attach(5); //Arm one (Range 0 - 80 (MAX 90))

  servo2.write(0);
  servo1.write(0);

  delay(1000);

  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop() {
  while (!Serial.available());

  
  if (Serial.readString().toInt() == 5){
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
    
    
}
