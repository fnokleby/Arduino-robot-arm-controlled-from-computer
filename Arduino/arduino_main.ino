#include <Servo.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <PS2Keyboard.h>

const int DataPin = 13;
const int IRQpin = 2;

bool computerControll;
bool keyboardControll;

const int computerSelectPin = A5;
const int keyboardSelectPin = A4;

PS2Keyboard keyboard;

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo servo1;
Servo servo2;

int base1 = 0;
int base2 = 0;
int base3 = 0;
int base4 = 0;

int arm11 = 0;
int arm12 = 0;
int arm13 = 0;
int arm14 = 0;

int waitTime1 = 20;
int waitTime2 = 20;
int waitTime3 = 20;
int waitTime4 = 20;

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

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  keyboard.begin(DataPin, IRQpin);
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

void screenPos()
{
  if (keyboard.available())
  {

    char c = keyboard.read();

    lcd.setCursor(0, 0);
    lcd.print("Starting!");
  }
  else
  {
    int screenBase = servo1.read() + 1;
    int screenArm1 = servo2.read() + 1;
    lcd.setCursor(0, 0);
    lcd.print("Starting!");
    lcd.setCursor(0, 1);
    lcd.print("Base:");
    lcd.print(screenBase);

    lcd.print(" Arm1:");
    lcd.print(screenArm1);
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

  if (digitalRead(computerSelectPin) != 1 && digitalRead(keyboardSelectPin) != 1)
  {
    computerControll = false;
    keyboardControll = false;
    lcd.setCursor(0, 0);
    lcd.print("Input: None");
  }
  else if (digitalRead(computerSelectPin) == 1)
  {
    computerControll = true;
    keyboardControll = false;
    lcd.setCursor(0, 0);
    lcd.print("Input: USB ");
  }
  else if (digitalRead(keyboardSelectPin) == 1)
  {
    computerControll = false;
    keyboardControll = true;
    lcd.setCursor(0, 0);
    lcd.print("Input: PS/2");
  }
  // if (keyboard.available())
  // {

  //   // read the next key
  //   char c = keyboard.read();

  //   // check for some of the special keys
  //   if (c == PS2_ENTER)
  //   {
  //     lcd.setCursor(0,1);
  //   }
  //   else if (c == PS2_TAB)
  //   {
  //     lcd.print("[Tab]");
  //   }
  //   else if (c == PS2_ESC)
  //   {
  //     lcd.print("[ESC]");
  //   }
  //   else if (c == PS2_PAGEDOWN)
  //   {
  //     lcd.print("[PgDn]");
  //   }
  //   else if (c == PS2_PAGEUP)
  //   {
  //     lcd.print("[PgUp]");
  //   }
  //   else if (c == PS2_LEFTARROW)
  //   {
  //     lcd.print("[Left]");
  //   }
  //   else if (c == PS2_RIGHTARROW)
  //   {
  //     lcd.print("[Right]");
  //   }
  //   else if (c == PS2_UPARROW)
  //   {
  //     lcd.print("[Up]");
  //   }
  //   else if (c == PS2_DOWNARROW)
  //   {
  //     lcd.print("[Down]");
  //   }
  //   else if (c == PS2_DELETE)
  //   {
  //     lcd.print("[Del]");
  //   }
  //   else
  //   {

  //     // otherwise, just print all normal characters
  //     lcd.print(c);
  //   }

  if (Serial.available() != 0 && computerControll == true)
  {
    doc.clear();
    String serialContent = Serial.readString();
    Serial.print(serialContent);
    deserializeJson(doc, serialContent);
    Serial.print(serialContent);

    int commandNum = doc["action"];
    String basePos = doc["baseDegrees"];
    String arm1Pos = doc["arm1Degrees"];
    String delayStr = doc["speed"];
    String saveWaitTime = doc["waitTime"];
    int waitTime = saveWaitTime.toInt();

    int basePosInt = basePos.toInt();
    int arm1PosInt = arm1Pos.toInt();
    int delayInt = delayStr.toInt();

    switch (commandNum)
    {
    case 1:
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
      break;
    case 2:
      moveBase(0, delayInt);
      moveArm1(0, delayInt);
      break;
    case 3:
      moveBase(basePosInt, delayInt);
      moveArm1(arm1PosInt, delayInt);
      break;
    case 11:
      base1 = servo1.read();
      arm11 = servo2.read();
      waitTime1 = waitTime;
      break;
    case 12:
      base2 = servo1.read();
      arm12 = servo2.read();
      waitTime2 = waitTime;
      break;
    case 13:
      base3 = servo1.read();
      arm13 = servo2.read();
      waitTime3 = waitTime;
      break;
    case 14:
      base4 = servo1.read();
      arm14 = servo2.read();
      waitTime4 = waitTime;
      break;
    case 21:
      moveBase(base1, delayInt);
      moveArm1(arm11, delayInt);
      break;
    case 22:
      moveBase(base2, delayInt);
      moveArm1(arm12, delayInt);
      break;
    case 23:
      moveBase(base3, delayInt);
      moveArm1(arm13, delayInt);
      break;
    case 24:
      moveBase(base4, delayInt);
      moveArm1(arm14, delayInt);
      break;
    case 29:
      moveBase(base1, delayInt);
      moveArm1(arm11, delayInt);
      delay(waitTime1);
      moveBase(base2, delayInt);
      moveArm1(arm12, delayInt);
      delay(waitTime2);
      moveBase(base3, delayInt);
      moveArm1(arm13, delayInt);
      delay(waitTime3);
      moveBase(base4, delayInt);
      moveArm1(arm14, delayInt);
      delay(waitTime4);
      break;
    case 35:
      base1 = 0;
      base2 = 0;
      base3 = 0;
      base4 = 0;

      arm11 = 0;
      arm12 = 0;
      arm13 = 0;
      arm14 = 0;
      break;
    default:
      // statements
      break;
    }
  }
  else if (keyboard.available() && keyboardControll == true){

  }
  else
  {
    return;
  }
}
