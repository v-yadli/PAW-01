#include "pindef.h"
#include "debounced_button.h"
#include "utils.h"
#include "readline.h"

DEBOUNCED_BUTTON KEYS_1[37];
DEBOUNCED_BUTTON KEYS_2[37];

void DATA_IN()
{
  pinMode(DATA0, INPUT_PULLUP);
  pinMode(DATA1, INPUT_PULLUP);
  pinMode(DATA2, INPUT_PULLUP);
  pinMode(DATA3, INPUT_PULLUP);
  pinMode(DATA4, INPUT_PULLUP);
  pinMode(DATA5, INPUT_PULLUP);
  pinMode(DATA6, INPUT_PULLUP);
  pinMode(DATA7, INPUT_PULLUP);
}

void SET_ADDR(byte ADDR)
{
  digitalWrite(ADDR0, ADDR & 0x1);
  digitalWrite(ADDR1, ADDR & 0x2);
  digitalWrite(ADDR2, ADDR & 0x4);
  digitalWrite(ADDR3, ADDR & 0x8);
}

void setup()   {                
  Serial.begin(250000);

  pinMode(ADDR0, OUTPUT);
  pinMode(ADDR1, OUTPUT);
  pinMode(ADDR2, OUTPUT);
  pinMode(ADDR3, OUTPUT);

  DATA_IN();
}

void read()
{
}

void run()
{
}

void loop() {
  read();
  run();
}
