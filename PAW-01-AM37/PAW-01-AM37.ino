#include "pindef.h"
#include "debounced_button.h"
#include "utils.h"
#include "readline.h"

// ============== End of routines

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

void setup()   {                
  Serial.begin(250000);

  pinMode(ADDR0, OUTPUT);
  pinMode(ADDR1, OUTPUT);
  pinMode(ADDR2, OUTPUT);
  pinMode(ADDR3, OUTPUT);
  pinMode(ADDR4, OUTPUT);

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
