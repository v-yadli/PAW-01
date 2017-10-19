#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>

#define OLED_DC 6
#define OLED_RESET 7
#define OLED_CS 12
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

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

void randrect()
{
  int i=0;
  while(true)
  {
    uint8_t x = (rand() % 16) * 8;
    uint8_t y = (rand() % 8) * 8;
    display.fillRect(x, y, 8, 8, INVERSE);
    display.display();
    Serial.println(i++);
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
//  display.display();
//  delay(2000);
//
//  display.drawRect(57, 51, 60, 3, WHITE);
//
//  for (uint8_t k=0; k<60; ++k)
//  {
//    display.drawPixel(57+k, 52, WHITE);
//    display.display();
//    delay(50);
//  }
//
//  delay(2000);
//  
  ui_cls();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello from PAW-01 with love! (Ok now supercharged!)");
  display.display();
  delay(2000);

  Serial.println("GO!");

//  for (uint8_t i=0; i < 168; i++) {
//    ui_blink((i % 21) * 6, i/21 * 8, 6, 8, 5);
//  }    

  //randrect();
  oscilliscope();



//  // Clear the buffer.
//  display.clearDisplay();
//  Serial.println("hey");
//  // draw a single pixel
//  display.drawPixel(10, 10, WHITE);
//  // Show the display buffer on the hardware.
//  // NOTE: You _must_ call display after making any drawing commands
//  // to make them visible on the display hardware!
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//
//  // draw many lines
//  testdrawline();
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//
//  // draw rectangles
//  testdrawrect();
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//
//  // draw multiple rectangles
//  testfillrect();
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//
//  // draw mulitple circles
//  testdrawcircle();
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//
//  // draw a white circle, 10 pixel radius
//  display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
//  display.display();
//  delay(2000);
//  display.clearDisplay();
//
//  testdrawroundrect();
//  delay(2000);
//  display.clearDisplay();
//
//  testfillroundrect();
//  delay(2000);
//  display.clearDisplay();
//
//  testdrawtriangle();
//  delay(2000);
//  display.clearDisplay();
//   
//  testfilltriangle();
//  delay(2000);
//  display.clearDisplay();

  // draw the first ~12 characters in the font
  testdrawchar();
  display.display();
  delay(2000);
  display.clearDisplay();

  // draw scrolling text
  testscrolltext();
  delay(2000);
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
  display.clearDisplay();

  // miniature bitmap display
  display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  display.display();

  // invert the display
  display.invertDisplay(true);
  delay(1000); 
  display.invertDisplay(false);
  delay(1000); 
  display.clearDisplay();

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop() {
  
}


void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(10);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
//    if ((i > 0) && (i % 21 == 0))
//      display.println();
  }    
  display.display();
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    display.display();
  }
  delay(250);
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}
