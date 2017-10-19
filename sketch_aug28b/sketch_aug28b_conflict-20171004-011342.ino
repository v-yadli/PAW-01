#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>

#define OLED_DC 6
#define OLED_RESET 7
//  CS is not used
//  SDA & SCL are hardware SPI pins at D11 and D13.
#define OLED_SDA 11
#define OLED_CS 12
#define OLED_SCL 13

#define MOBO_PWRLED 0
#define MOBO_HDDLED 1
#define MOBO_PWRSW  2
#define MOBO_RSTSW  3

//  Extra caution with phantom power..
//  A good idea is to always reset to
//  no-phantom-power after a power failure.
#define SND_PHASW 4
#define SND_PHALED 5
#define SND_MICMUX 8


Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


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
        delay(80);
        display.fillRect(x, y, w, h, INVERSE);
        display.display();
        delay(80);
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

void setup()   {                
  Serial.begin(2000000);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  ui_cls();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello from PAW-01 with love! (Ok now supercharged!)");
  display.display();
  delay(2000);

  Serial.println("GO!");

  //oscilliscope();

//  // Clear the buffer.
//  display.clearDisplay();

  pinMode(  
}


void loop() {
  
}

