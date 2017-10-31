#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#define DEBOUNCE_TIME 2
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
      if(btn.cnt > 0){
          btn.current_val = pinval;
          btn.cnt = 0;
          return true;
      }
      return false;
  }
  btn.cnt = 0;
  return false;
}

bool DEBOUNCE_READ_ANALOG(byte pin, DEBOUNCED_BUTTON& btn)
{
  int aval = analogRead(pin);
  byte pinval = (aval > 1020);
  if(pinval != btn.current_val){
      btn.cnt++;
      if(btn.cnt > 0){
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