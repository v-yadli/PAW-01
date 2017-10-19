#include "Arduino.h"
#include "pindef.h"
#include "../debounced_button.h"
#include "utils.h"
#include "../com.h"

int joy_x = 0, joy_y = 0;
int joy_xzero = 512, joy_yzero = 512;
int joy_deadzone = 50;
int transpose = 0;

DEBOUNCED_BUTTON pwr_led = {0, 0};
DEBOUNCED_BUTTON lb = {0, 0};
DEBOUNCED_BUTTON mb = {0, 0};
DEBOUNCED_BUTTON rb = {0, 0};
DEBOUNCED_BUTTON dial_sw = {0, 0};
DEBOUNCED_BUTTON joy_sw= {0, 0};
byte dial_enc1= HIGH;
byte dial_enc2 = HIGH;

typedef int (*ROUTINE) (int);
extern ROUTINE routines[];
extern ROUTINE MenuRoutines[];
extern ROUTINE DialRoutines[];
extern ROUTINE JoyRoutines[];
extern int routine_events[];

int menuroutine_idx = 0;
int dialroutine_idx = 0;
int joyroutine_idx = 0;

enum ROUTINE_TYPE {
  // Always update menu first, as the routine
  // can be changed if a menu item is triggered.
  MENU_UPDATE_ROUTINE = 0,
  STATUS_UPDATE_ROUTINE,
  DIAL_UPDATE_ROUTINE,
  JOY_UPDATE_ROUTINE,
  UPDATE_ROUTINE_COUNT,
};

enum MenuEvent { ME_UP = 1, ME_DOWN = 2, ME_ENTER = 4, };
enum DialEvent { DE_UP = 1, DE_DOWN = 2, DE_PUSH = 4, DE_RELEASE = 8, };
enum JoyEvent { JE_POS = 1, JE_PUSH = 2, JE_RELEASE = 4, };

void post_event(int recepient, int event)
{
  // Serial.print("post_event ");
  // Serial.print(event);
  // Serial.print(" to ");
  // Serial.print(recepient);
  // Serial.println();
  int v = routine_events[recepient];
  if(v < 0) v = 0;
  routine_events[recepient] = v | event;
}

void change_mode(ROUTINE_TYPE recepient)
{
  switch(recepient){
    case MENU_UPDATE_ROUTINE:
    if (NULL == MenuRoutines[++menuroutine_idx]) menuroutine_idx = 0;
    routines[MENU_UPDATE_ROUTINE] = MenuRoutines[menuroutine_idx];
    break;
    case STATUS_UPDATE_ROUTINE:
    /* ignore */
    break;
    case DIAL_UPDATE_ROUTINE:
    if (NULL == DialRoutines[++dialroutine_idx]) dialroutine_idx = 0;
    routines[DIAL_UPDATE_ROUTINE] = DialRoutines[dialroutine_idx];
    break;
    case JOY_UPDATE_ROUTINE:
    if (NULL == JoyRoutines[++joyroutine_idx]) joyroutine_idx = 0;
    routines[JOY_UPDATE_ROUTINE] = JoyRoutines[joyroutine_idx];
    break;
  }
}

// ============= Routines
int menu_idx = 0;
int menu_screenrow = 0;
enum MENU_ITEM {
  // MENU_POWER_SHORT= 0,
  // MENU_RESET,
  MENU_DIALMODE,
  MENU_JOYMODE,
  MENU_MENUMODE,
  // MENU_POWER_LONG,
  MENU_ITEM_COUNT,
};

char* MenuRoutineNames[] = {
  "Menu",
  "Oct.",
  NULL,
};
char* DialRoutineNames[] = {
  "Vol.",
  "MW.",
  "TP.",
  "Ctl.",
  NULL,
};
char* JoyRoutineNames[] = {
  "Mouse",
  "XY",
  "TP.",
  NULL,
};

void displayMenuItem(int item, bool current)
{
  if(current)display.print("->");
  switch(item){
    // case MENU_POWER_SHORT:
    // display.println("PWR.");
    // break;
    // case MENU_RESET:
    // display.println("RESET.");
    // break;
    case MENU_DIALMODE:
    display.print("DIAL: ");
    display.println(DialRoutineNames[dialroutine_idx]);
    break;
    case MENU_JOYMODE:
    display.print("JOY: ");
    display.println(JoyRoutineNames[joyroutine_idx]);
    break;
    case MENU_MENUMODE:
    display.println("OCT Mode");
    break;
    // case MENU_POWER_LONG:
    // display.println("PANIC.");
    // break;
  }
}

void executeMenuItem(int item)
{
  switch(item){
    // case MENU_POWER_SHORT:
    // shortPullSwitch(DMOBO_PWRSW);
    // break;
    // case MENU_RESET:
    // shortPullSwitch(DMOBO_RSTSW);
    // break;
    case MENU_MENUMODE:
    change_mode(MENU_UPDATE_ROUTINE);
    break;
    case MENU_DIALMODE:
    change_mode(DIAL_UPDATE_ROUTINE);
    break;
    case MENU_JOYMODE:
    change_mode(JOY_UPDATE_ROUTINE);
    break;
    // case MENU_POWER_LONG:
    // longPullSwitch(DMOBO_PWRSW);
    // break;
  }
}

int UpdateMenu(int event)
{
  display.fillRect(0, 16, 64, 48, BLACK);
  for(int i=0;i<MENU_ITEM_COUNT;++i){
    display.setCursor(0, 16 + i * 8);
    displayMenuItem(i, i == menu_idx);
  }
  display.fillRect(0, 16 + 8 * menu_idx, 64, 8, INVERSE);

  if (event & ME_UP){
    menu_idx = (menu_idx + MENU_ITEM_COUNT - 1) % MENU_ITEM_COUNT;
    return 0;
  }
  if (event & ME_DOWN){
    menu_idx = (menu_idx + 1) % MENU_ITEM_COUNT;
    return 0;
  }
  if (event & ME_ENTER){
    ui_blink(0, 16 + menu_idx * 8, 64, 8, 3);
    executeMenuItem(menu_idx);
    return 0;
  }
  return -1;
}

int OctaveMode(int event)
{
  if ((lb.current_val == LOW) && 
      (mb.current_val == LOW) && 
      (rb.current_val == LOW))
  {
    change_mode(MENU_UPDATE_ROUTINE);
    return 0;
  }

  display.fillRect(0, 16, 64, 48, BLACK);
  display.setCursor(0, 16);
  display.println(">== OCT MODE ==<");

  if (event & ME_UP){
    Serial.println("OCU");
  }
  if (event & ME_DOWN){
    Serial.println("OCD");
  }
  if (event & ME_ENTER){
    Serial.println("OCR");
  }
  return -1;
}

int UpdateStatusIndicators(int event)
{
  (void)event;
  return -1;
}

int DialVolume(int event)
{
  if (event & DE_UP){
    Serial.println("VLD");
  }
  if (event & DE_DOWN){
    Serial.println("VLU");
  }
  if (event & DE_PUSH){
    Serial.println("VLM");
  }
  // if (event & DE_RELEASE){
  // }
  return -1;
}

int DialMouseWheel(int event)
{
  if (event & DE_UP){
    MouseMove(0, -1, 1);
  }
  if (event & DE_DOWN){
    MouseMove(0, 1, 1);
  }
  if (event & DE_PUSH){
    MousePush(MOUSE_MIDDLE);
  }
  if (event & DE_RELEASE){
    MouseRelease(MOUSE_MIDDLE);
  }
  return -1;
}

int DialTransport(int event)
{
  if (event & DE_UP){
    Serial.println("DTU");
  }
  if (event & DE_DOWN){
    Serial.println("DTD");
  }
  if (event & DE_PUSH){
    Serial.println("DTP");
  }
  if (event & DE_RELEASE){
    Serial.println("DTR");
  }
  return -1;
}

int DialController(int event)
{
  if (event & DE_UP){
    Serial.println("DCU");
  }
  if (event & DE_DOWN){
    Serial.println("DCD");
  }
  if (event & DE_PUSH){
    Serial.println("DCP");
  }
  if (event & DE_RELEASE){
    Serial.println("DCR");
  }
  return -1;
}

int JoyMouse(int event)
{
  if (event & JE_POS){
    MouseMove(joy_x / 5, joy_y / 5, 0);
  }
  if (event & JE_PUSH){
    MousePush(MOUSE_LEFT);
  }
  if (event & JE_RELEASE){
    MouseRelease(MOUSE_LEFT);
  }
  return -1;
}

int JoyXY(int event)
{
  if (event & JE_POS){

  }
  if (event & JE_PUSH){

  }
  if (event & JE_RELEASE){

  }
  return -1;
}

int JoyTransport(int event)
{
  if (event & JE_POS){

  }
  if (event & JE_PUSH){

  }
  if (event & JE_RELEASE){

  }
  return -1;
}

ROUTINE routines[UPDATE_ROUTINE_COUNT] = {
  UpdateMenu,
  UpdateStatusIndicators,
  DialVolume,
  JoyMouse,
};
int routine_events[UPDATE_ROUTINE_COUNT];

ROUTINE MenuRoutines[] = {
  UpdateMenu,
  OctaveMode,
  NULL,
};

ROUTINE DialRoutines[] = {
  DialVolume,
  DialMouseWheel,
  DialTransport,
  DialController,
  NULL,
};

ROUTINE JoyRoutines[] = {
  JoyMouse,
  JoyXY,
  JoyTransport,
  NULL,
};


// ============== End of routines

void setup()   {                
  Serial.begin(250000);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();

  // PWRLED offline
  pinMode(DMOBO_PWRLED, INPUT);
  pinMode(DCNT_DIALENC1, INPUT);
  pinMode(DCNT_DIALENC2, INPUT);
  pinMode(DCNT_DIALSW, INPUT);
  pinMode(DCNT_JOYSW, INPUT_PULLUP);
  pinMode(DCNT_LB, INPUT_PULLUP);
  pinMode(DCNT_MB, INPUT_PULLUP);
  pinMode(DCNT_RB, INPUT_PULLUP);

  // PWRSW offline
  pinMode(DMOBO_PWRSW, INPUT_PULLUP);
  // RSTSW offline
  pinMode(DMOBO_RSTSW, INPUT_PULLUP);
  // DIALMUX offline
  pinMode(DCNT_DIALMUX, INPUT_PULLUP);

  // digitalWrite(DMOBO_PWRSW, HIGH);
  // digitalWrite(DMOBO_RSTSW, HIGH);
  // digitalWrite(DCNT_DIALMUX, HIGH);

  memset(routine_events, 0, sizeof(routine_events));

  delay(500);
  ui_cls();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.drawLine(0, 15, 127, 15, 1);
  display.drawLine(64, 15, 64, 63, 1);

  display.display();
}

// byte dial_stat = LOW;
// int hdd_led;
// bool hdd_active = false;
// int hl_base = 800;

// DialMux offline
// void toggleDial()
// {
//   dial_stat = !dial_stat;
//   digitalWrite(DCNT_DIALMUX, dial_stat);
//   delay(200);
// }


void read()
{
  if (DEBOUNCE_READ(DCNT_LB, lb) && lb.current_val == LOW)
  {
    post_event(MENU_UPDATE_ROUTINE, ME_UP);
  }
  if (DEBOUNCE_READ(DCNT_MB, mb) && mb.current_val == LOW)
  {
    post_event(MENU_UPDATE_ROUTINE, ME_DOWN);
  }
  if (DEBOUNCE_READ(DCNT_RB, rb) && rb.current_val == LOW)
  {
    post_event(MENU_UPDATE_ROUTINE, ME_ENTER);
  }
  if (DEBOUNCE_READ(DCNT_DIALSW, dial_sw))
  {
    if(dial_sw.current_val == LOW) {
      post_event(DIAL_UPDATE_ROUTINE, DE_PUSH);
    }else{
      post_event(DIAL_UPDATE_ROUTINE, DE_RELEASE);
    }
  }
  if (DEBOUNCE_READ(DCNT_JOYSW, joy_sw))
  {
    if(joy_sw.current_val == LOW) {
      post_event(JOY_UPDATE_ROUTINE, JE_PUSH);
    }else{
      post_event(JOY_UPDATE_ROUTINE, JE_RELEASE);
    }
  }

  byte enc1 = digitalRead(DCNT_DIALENC1);
  byte enc2 = digitalRead(DCNT_DIALENC2);

  if (enc1 != dial_enc1 || enc2 != dial_enc2){

    if(dial_enc1 == HIGH && dial_enc2 == LOW && enc1 == LOW && enc2 == LOW)
    {
      post_event(DIAL_UPDATE_ROUTINE, DE_UP);
    }

    if(dial_enc1 == LOW && dial_enc2 == HIGH && enc1 == LOW && enc2 == LOW)
    {
      post_event(DIAL_UPDATE_ROUTINE, DE_DOWN);
    }

    dial_enc1 = enc1;
    dial_enc2 = enc2;
  }

  int jx = analogRead(ACNT_JOYX) - joy_xzero;
  int jy = analogRead(ACNT_JOYY) - joy_yzero;

  if((abs(jx) >= joy_deadzone && jx != joy_x) ||
     (abs(jy) >= joy_deadzone && jy != joy_y))
  {
    post_event(JOY_UPDATE_ROUTINE, JE_POS);
  }

  if((abs(jx) < joy_deadzone && abs(joy_x) >= joy_deadzone) ||
     (abs(jy) < joy_deadzone && abs(joy_y) >= joy_deadzone))
  {
    post_event(JOY_UPDATE_ROUTINE, JE_POS);
  }

  joy_x = jx;
  joy_y = jy;

  // if(DEBOUNCE_READ(DMOBO_PWRLED, pwr_led)){
  //   post_event(STATUS_UPDATE_ROUTINE, 0);
  // }
  // HDD_LED offline
  // int hl_val = (analogRead(AMOBO_HDDLED));
  // hl_base = hl_base * 0.995 + hl_val * 0.005;
  // int cur_hdd_led = hl_val  - hl_base;
  // hdd_led = max(max(cur_hdd_led, hdd_led - 1), 0);
  // bool ha = (hdd_led > 10);
  // if(ha != hdd_active){
  //   hdd_active = ha;
  //   post_event(STATUS_UPDATE_ROUTINE, 0);
  // }
  char* comlink = ReadCOM();
  if(comlink != NULL){
    //TODO MOSI commands
  }

}

void run()
{
  for(int i=0;i<UPDATE_ROUTINE_COUNT; ++i){
    if (routine_events[i] >= 0){
      // Serial.print("run ");
      // Serial.println(i);
      routine_events[i] = routines[i](routine_events[i]);
    }
  }
}

void loop() {
  read();
  run();
  // display.print("pwr_led=");
  // display.print(pwr_led);
  // display.print("dial_stat=");
  // display.println(dial_stat);
  // display.print("hdd_led=");
  // display.println(hdd_led);

  // display.print("lb=");
  // display.print(lb);
  // display.print(" mb=");
  // display.print(mb);
  // display.print(" rb=");
  // display.println(rb);

  // display.print(" js=");
  // display.print(joy_sw);
  // display.print(" jx=");
  // display.print(joy_x);
  // display.print(" jy=");
  // display.println(joy_y);

  // display.print("ds=");
  // display.print(dial_sw);
  // display.print("de1=");
  // display.print(dial_enc1);
  // display.print(" de2=");
  // display.println(dial_enc2);


  display.display();

  // if(lb == LOW){
  //   //   shortPullSwitch(DMOBO_PWRSW);
  //   toggleDial();
  // }
}
