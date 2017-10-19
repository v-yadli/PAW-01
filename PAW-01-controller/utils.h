#ifndef UTILS_H
#define UTILS_H
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include <gfxfont.h>

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

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

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
////  Animated clear screen
void ui_cls()
{
    for(uint8_t i = 7; i != 0xFF; i -= 1)
    {
        uint8_t x = i * 8;
        uint8_t y = i * 4;

        display.fillRect(x, y, SSD1306_LCDWIDTH - x * 2, SSD1306_LCDHEIGHT - y * 2, WHITE);
        display.display();
    }

    for(uint8_t i = 7; i != 0xFF; i -= 1)
    {
        uint8_t x = i * 8;
        uint8_t y = i * 4;

        display.drawRect(x, y, SSD1306_LCDWIDTH - x * 2, SSD1306_LCDHEIGHT - y * 2, BLACK);
        display.display();
    }

    display.clearDisplay();
    display.display();
}

void ui_blink(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t t)
{
    while(t-- != 0xFF)
    {
        display.fillRect(x, y, w, h, INVERSE);
        display.display();
        delay(30);
        display.fillRect(x, y, w, h, INVERSE);
        display.display();
        delay(30);
    }
}

float sawtooth(float x)
{
  x = x - floor(x);
  return x;
}

float sample()
{
  return (analogRead(0) - 512) / 1024.0f;
}

void oscilliscope()
{
  float t = .0f;
  while(true)
  {
    display.clearDisplay();
    display.drawLine(0, 31, 127, 31, WHITE);
    display.drawLine(63, 0, 63, 63, WHITE);

    for(int8_t x = -63; x < 63; ++x)
    {
//      float y =  sawtooth(x / 10.0f + t);
      float y = sample();
      display.drawPixel(x + 63, (int8_t) (y * 32) + 31, WHITE);
    }

    t = t + 0.1f;
    display.display();
  }
}

#endif