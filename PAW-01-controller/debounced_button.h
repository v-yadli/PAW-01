#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#define LONGPRESS_TIME 500
#define DEBOUNCE_TIME 4
struct DEBOUNCED_BUTTON
{
  byte cnt;
  byte current_val; 
};

struct LONGPRESS_RECORD
{
  unsigned long down_time;
  unsigned long up_time;
};

enum LONGPRESS_STATUS
{
  LP_NOTHING,
  LP_SHORT,
  LP_LONG,
};

void LONGPRESS_DOWN(LONGPRESS_RECORD& status)
{
  status.down_time = millis();
}

void LONGPRESS_UP(LONGPRESS_RECORD& status)
{
  status.up_time = millis();
}

LONGPRESS_STATUS LONGPRESS_CHECK(LONGPRESS_RECORD& status)
{
  LONGPRESS_STATUS lpres = LP_NOTHING;
  if(status.down_time != 0 && millis() - status.down_time > LONGPRESS_TIME){
    lpres = LP_LONG;
  }else if (status.up_time != 0){
    lpres = LP_SHORT;
  }
  if(lpres != LP_NOTHING){
    status.down_time = 0;
    status.up_time = 0;
  }
  return lpres;
}

bool DEBOUNCE_READ(byte pin, DEBOUNCED_BUTTON& btn)
{
  byte pinval = digitalRead(pin);
  if(pinval != btn.current_val){
      btn.cnt++;
      if(btn.cnt > DEBOUNCE_TIME){
          btn.current_val = pinval;
          btn.cnt = 0;
          return true;
      }
      return false;
  }
  btn.cnt = 0;
  return false;
}

#endif