#include <Servo.h>
#include <ArduinoJson.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int base1 = 0;
int base2 = 0;
int base3 = 0;
int base4 = 0;

int arm11 = 0;
int arm12 = 0;
int arm13 = 0;
int arm14 = 0;

int i = 0;

char json[] = "{'action': 3, 'baseDegrees': '71', 'arm1Degrees': '20', 'speed': '0'}";

DynamicJsonDocument doc(300);

void setup()
{
  servo1.attach(3); //base
  servo2.attach(5); //Arm one (Range 0 - 80 (MAX 90))

  servo2.write(85);
  servo2.write(0);
  servo1.write(180);
  servo1.write(0);

  delay(1000);

  Serial.begin(115200);
  Serial.setTimeout(100);

  doc["action"];
  doc["baseDegrees"];
  doc["arm1Degrees"];
  doc["speed"];
}

void moveBase(int x, int v)
{
  if (x > servo1.read())
  {
    for (i = servo1.read(); i < x; i++)
    {
      servo1.write(i);
      delay(v);
    }
  }
  else if (x < servo1.read())
  {
    for (i = servo1.read(); i > x; i--)
    {
      servo1.write(i);
      delay(v);
    }
  }
}

void moveArm1(int x, int v)
{
  if (x > servo2.read())
  {
    for (i = servo2.read(); i < x; i++)
    {
      servo2.write(i);
      delay(v);
    }
  }
  else if (x < servo2.read())
  {
    for (i = servo2.read(); i > x; i--)
    {
      servo2.write(i);
      delay(v);
    }
  }
}

void loop()
{
  if (Serial.available() == 0)
  {

    return;
  }

  doc.clear();
  String serialContent = Serial.readString();
  deserializeJson(doc, serialContent);
  Serial.print(serialContent);

  int commandNum = doc["action"];
  String basePos = doc["baseDegrees"];
  String arm1Pos = doc["arm1Degrees"];
  String delayStr = doc["speed"];

  int basePosInt = basePos.toInt();
  int arm1PosInt = arm1Pos.toInt();
  int delayInt = delayStr.toInt();

  if (commandNum == 1)
  {

    for (i = 0; i < 180; i++)
    {
      servo1.write(i);
      delay(10);
    }

    for (i = 0; i < 80; i++)
    {
      servo2.write(i);
      delay(10);
    }
    for (i = 80; i > 0; i--)
    {
      servo2.write(i);
      delay(10);
    }

    for (i = 180; i > 0; i--)
    {
      servo1.write(i);
      delay(10);
    }
  }
  else if (commandNum == 2)
  {
    moveBase(0, delayInt);
    moveArm1(0, delayInt);
  }
  else if (commandNum == 3)
  {
    moveBase(basePosInt, delayInt);
    moveArm1(arm1PosInt, delayInt);
  }
  else if (commandNum == 11) //Save pos 1
  {
    base1 = servo1.read();
    arm11 = servo2.read();
  }
  else if (commandNum == 21) //Go to pos 1
  {
    moveBase(base1, delayInt);
    moveArm1(arm11, delayInt);
  }
  else if (commandNum == 12) //Save pos 2
  {
    base2 = servo1.read();
    arm12 = servo2.read();
  }
  else if (commandNum == 22) //Go to pos 2
  {
    moveBase(base2, delayInt);
    moveArm1(arm12, delayInt);
  }
  else if (commandNum == 13) //Save pos 3
  {
    base3 = servo1.read();
    arm13 = servo2.read();
  }
  else if (commandNum == 23) //Go to pos 3
  {
    moveBase(base3, delayInt);
    moveArm1(arm13, delayInt);
  }
  else if (commandNum == 14) //Save pos 4
  {
    base4 = servo1.read();
    arm14 = servo2.read();
  }
  else if (commandNum == 24) //Go to pos 4
  {
    moveBase(base4, delayInt);
    moveArm1(arm14, delayInt);
  }
  else if (commandNum == 19)
  {
    int base1 = 0;
    int base2 = 0;
    int base3 = 0;
    int base4 = 0;

    int arm11 = 0;
    int arm12 = 0;
    int arm13 = 0;
    int arm14 = 0;
  }
}
