#ifndef UTILS_H
#define UTILS_H

#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

void shortPullSwitch(int pin)
{
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
  delay(200);
}

void longPullSwitch(int pin)
{
  digitalWrite(pin, LOW);
  delay(4000);
  digitalWrite(pin, HIGH);
  delay(200);
}

void MousePush(int button)
{
    Serial.print("MP,");
    Serial.println(button);
}

void MouseRelease(int button)
{
    Serial.print("MR,");
    Serial.println(button);
}

void MouseMove(int x, int y, int wheel)
{
    Serial.print("MM,");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(wheel);
}

float sample()
{
  return (analogRead(0) - 512) / 1024.0f;
}

#endif