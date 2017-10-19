#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#define DEBOUNCE_TIME 4
struct DEBOUNCED_BUTTON
{
  byte cnt;
  byte current_val; 
};

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