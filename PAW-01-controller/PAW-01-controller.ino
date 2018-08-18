#include "pindef.h"
#include "debounced_button.h"
#include "utils.h"
#include "com.h"
#define joy_deadzone 8
#define joy_xzero 520
#define joy_yzero 526
int joy_x = 0;
int joy_y = 0;

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
extern ROUTINE MonRoutines[];
extern int routine_events[];

#define EL_DUTY_MIN 0
#define EL_DUTY_MAX 399

int menu_mode = 0;
int dialroutine_idx = 0;
int joyroutine_idx = 0;
int monroutine_idx = 0;
int el_duty = 0;
char* comlink = nullptr;

LONGPRESS_RECORD lp_k1 = {0, 0};
LONGPRESS_RECORD lp_k2 = {0, 0};
LONGPRESS_RECORD lp_k3 = {0, 0};
LONGPRESS_RECORD lp_joy = {0, 0};
LONGPRESS_RECORD lp_dial = {0, 0};

enum ROUTINE_TYPE {
  // Always update menu first, as the routine
  // can be changed if a menu item is triggered.
  MENU_UPDATE_ROUTINE = 0,
  DIAL_UPDATE_ROUTINE,
  JOY_UPDATE_ROUTINE,
  MON_UPDATE_ROUTINE,
  STATUS_UPDATE_ROUTINE,
  UPDATE_ROUTINE_COUNT,
};

enum KeyEvent { K1_DOWN = 1, K2_DOWN = 2, K3_DOWN = 4, K1_UP = 8, K2_UP = 16, K3_UP = 32};
enum DialEvent { DE_UP = 1, DE_DOWN = 2, DE_PUSH = 4, DE_RELEASE = 8, };
enum JoyEvent { JE_POS = 1, JE_PUSH = 2, JE_RELEASE = 4, };

void post_event(int recepient, int event)
{
  int v = routine_events[recepient];
  if(v < 0) v = 0;
  routine_events[recepient] = v | event;
}

void set_menu_mode(int mode)
{
  menu_mode = mode;
  routines[MENU_UPDATE_ROUTINE] = MenuRoutines[mode];
}

void change_mode(ROUTINE_TYPE recepient)
{
  switch(recepient){
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
    case MON_UPDATE_ROUTINE:
    if (NULL == MonRoutines[++monroutine_idx]) monroutine_idx = 0;
    routines[MON_UPDATE_ROUTINE] = MonRoutines[monroutine_idx];
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
  MENU_OCTMODE,
  MENU_MEDIAMODE,
  MENU_KEYMODE,
  MENU_MONITORMODE,
  // MENU_POWER_LONG,
  MENU_ITEM_COUNT,
};

const char DRN_0[] PROGMEM = "VL.";
const char DRN_1[] PROGMEM = "MW.";
const char DRN_2[] PROGMEM = "TP.";
const char DRN_3[] PROGMEM = "CT.";

const char* const DialRoutineNames[] PROGMEM = {
  DRN_0, DRN_1, DRN_2, DRN_3, NULL,
};

const char JRN_0[] PROGMEM = "MS.";
const char JRN_1[] PROGMEM = "XY.";
const char JRN_2[] PROGMEM = "TP.";

const char* const JoyRoutineNames[] PROGMEM = {
  JRN_0, JRN_1, JRN_2, NULL,
};

const char MRN_0[] PROGMEM = "J-XY.";
const char MRN_1[] PROGMEM = "M-XY.";
const char MRN_2[] PROGMEM = "M-DU.";

const char* const MonitorRoutineNames[] PROGMEM = {
  MRN_0, MRN_1, MRN_2, NULL,
};

void displayMenuItem(int item, bool current)
{
  char strbuf[20];
  switch(item){
    case MENU_DIALMODE:
    display.print(F("DIAL  "));
    strcpy_P(strbuf, (char*)pgm_read_word(&(DialRoutineNames[dialroutine_idx])));
    display.println(strbuf);
    break;
    case MENU_JOYMODE:
    display.print(F("JOY   "));
    strcpy_P(strbuf, (char*)pgm_read_word(&(JoyRoutineNames[joyroutine_idx])));
    display.println(strbuf);
    break;
    case MENU_OCTMODE:
    display.println(F("OCT Mode"));
    break;
    case MENU_MEDIAMODE:
    display.println(F("MEDIA Mode"));
    break;
    case MENU_KEYMODE:
    display.println(F("KEY Mode"));
    break;
    case MENU_MONITORMODE:
    display.print(F("MON   "));
    strcpy_P(strbuf, (char*)pgm_read_word(&(MonitorRoutineNames[monroutine_idx])));
    display.println(strbuf);
    break;
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
    case MENU_OCTMODE:
    set_menu_mode(1);
    break;
    case MENU_MEDIAMODE:
    set_menu_mode(2);
    break;
    case MENU_KEYMODE:
    set_menu_mode(3);
    break;
    case MENU_DIALMODE:
    change_mode(DIAL_UPDATE_ROUTINE);
    break;
    case MENU_JOYMODE:
    change_mode(JOY_UPDATE_ROUTINE);
    break;
    case MENU_MONITORMODE:
    change_mode(MON_UPDATE_ROUTINE);
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

  if (event & K1_DOWN){
    menu_idx = (menu_idx + MENU_ITEM_COUNT - 1) % MENU_ITEM_COUNT;
    return 0;
  }
  if (event & K2_DOWN){
    menu_idx = (menu_idx + 1) % MENU_ITEM_COUNT;
    return 0;
  }
  if (event & K3_DOWN){
    ui_blink(0, 16 + menu_idx * 8, 64, 8, 3);
    executeMenuItem(menu_idx);
    return 0;
  }
  return -1;
}

int MediaMode(int event)
{
  if ((lb.current_val == LOW) && 
      (mb.current_val == LOW) && 
      (rb.current_val == LOW))
  {
    set_menu_mode(0);
    return 0;
  }

  display.fillRect(0, 16, 64, 48, BLACK);
  display.setCursor(0, 16);
  display.println(F("MEDIA MODE"));
  display.println(F("<< ||> >>"));

  if (event & K1_DOWN){
    Serial.println(F("MEDIA_PREV"));
  }
  if (event & K2_DOWN){
    Serial.println(F("MEDIA_PLAY"));
  }
  if (event & K3_DOWN){
    Serial.println(F("MEDIA_NEXT"));
  }
  return -1;
}

int BrowseKeyMode(int event)
{
  if ((lb.current_val == LOW) && 
      (mb.current_val == LOW) && 
      (rb.current_val == LOW))
  {
    set_menu_mode(0);
    return 0;
  }

  display.fillRect(0, 16, 64, 48, BLACK);
  display.setCursor(0, 16);
  display.println(F("KEY MODE"));

  if (event & K1_DOWN){
    LONGPRESS_DOWN(lp_k1);
  }
  if (event & K2_DOWN){
    LONGPRESS_DOWN(lp_k2);
  }
  if (event & K3_DOWN){
    LONGPRESS_DOWN(lp_k3);
  }

  if (event & K1_UP){
    LONGPRESS_UP(lp_k1);
  }
  if (event & K2_UP){

    LONGPRESS_UP(lp_k2);
  }
  if (event & K3_UP){
    LONGPRESS_UP(lp_k3);
  }

  LONGPRESS_STATUS k1 = LONGPRESS_CHECK(lp_k1);
  LONGPRESS_STATUS k2 = LONGPRESS_CHECK(lp_k2);
  LONGPRESS_STATUS k3 = LONGPRESS_CHECK(lp_k3);

  if(k1 == LP_SHORT){
    Serial.println(F("KEY_K1"));
  }
  if (k2 == LP_SHORT){
    Serial.println(F("KEY_K2"));
  }
  if (k3 == LP_SHORT){
    Serial.println(F("KEY_K3"));
  }

  if(k1 == LP_LONG){
    Serial.println(F("KEY_K4"));
  }
  if (k2 == LP_LONG){
    Serial.println(F("KEY_K5"));
  }
  if (k3 == LP_LONG){
    Serial.println(F("KEY_K6"));
  }

  return -1;
}


int OctaveMode(int event)
{
  if ((lb.current_val == LOW) && 
      (mb.current_val == LOW) && 
      (rb.current_val == LOW))
  {
    set_menu_mode(0);
    return 0;
  }

  display.fillRect(0, 16, 64, 63, BLACK);
  display.setCursor(0, 16);
  display.println(F("OCT MODE"));
  display.println(F("-  |  +"));

  if (event & K1_DOWN){
    Serial.println(F("OCD"));
  }
  if (event & K2_DOWN){
    Serial.println(F("OCU"));
  }
  if (event & K3_DOWN){
    Serial.println(F("OCR"));
  }
  return -1;
}

#define EL_INDICATOR_X1 18
#define EL_INDICATOR_Y1 6
#define EL_INDICATOR_X2 62
#define EL_INDICATOR_Y2 10

int UpdateStatusIndicators(int event)
{
  //TODO update event handling
  (void)event;

  display.fillRect(0, 0, 128, 15, BLACK);
  display.setCursor(0, 6);
  display.print(F("EL:"));
  int x = map(el_duty, EL_DUTY_MIN, EL_DUTY_MAX, EL_INDICATOR_X1 + 4 , EL_INDICATOR_X2 - 4);
  int y = (EL_INDICATOR_Y1 + EL_INDICATOR_Y2) / 2;
  display.drawRect(EL_INDICATOR_X1, EL_INDICATOR_Y1, EL_INDICATOR_X2 - EL_INDICATOR_X1 + 1, EL_INDICATOR_Y2 - EL_INDICATOR_Y1 + 1, WHITE);
  display.drawLine(EL_INDICATOR_X1 + 2, y, x, y, WHITE);

  return 0;
}

int DialVolume(int event)
{
  if (event & DE_UP){
    Serial.println(F("VLD"));
  }
  if (event & DE_DOWN){
    Serial.println(F("VLU"));
  }
  if (event & DE_PUSH){
    Serial.println(F("VLM"));
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
    LONGPRESS_DOWN(lp_dial);
  }
  if (event & DE_RELEASE){
    LONGPRESS_UP(lp_dial);
  }

  LONGPRESS_STATUS dial = LONGPRESS_CHECK(lp_dial);
  if(dial == LP_SHORT){
    Serial.println(F("DMP"));
  }
  if (dial == LP_LONG){
    Serial.println(F("DML"));
  }
  return -1;
}

int DialTransport(int event)
{
  if (event & DE_UP){
    Serial.println(F("DTU"));
  }
  if (event & DE_DOWN){
    Serial.println(F("DTD"));
  }
  if (event & DE_PUSH){
    Serial.println(F("DTP"));
  }
  if (event & DE_RELEASE){
    Serial.println(F("DTR"));
  }
  return -1;
}

int DialController(int event)
{
  if (event & DE_UP){
    Serial.println(F("DCU"));
  }
  if (event & DE_DOWN){
    Serial.println(F("DCD"));
  }
  if (event & DE_PUSH){
    Serial.println(F("DCP"));
  }
  if (event & DE_RELEASE){
    Serial.println(F("DCR"));
  }
  return -1;
}

int JoyMouse(int event)
{
  if (event & JE_POS){
    MouseMove(joy_x, joy_y, 0);
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
    Serial.print(F("XY,"));
    Serial.print(joy_x);
    Serial.print(F(","));
    Serial.println(joy_y);
  }
  if (event & JE_PUSH){
    Serial.println(F("XY_PUSH"));
  }
  if (event & JE_RELEASE){
    Serial.println(F("XY_RELEASE"));
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

#define MON_X1 66
#define MON_Y1 16
#define MON_X2 127
#define MON_Y2 63

#define MON_CENTER_X 96
#define MON_CENTER_Y 39

void Monitor_cls()
{
  display.fillRect(MON_X1, MON_Y1, MON_X2 - MON_X1 + 1, MON_Y2 - MON_Y1 + 1, BLACK);
  for(int x = MON_X1; x <= MON_X2; x += 10)
  {
    display.drawPixel(x, MON_CENTER_Y, WHITE);
  }
  for(int y = MON_Y1 + 3; y <= MON_Y2; y += 10)
  {
    display.drawPixel(MON_CENTER_X, y, WHITE);
  }
}

int MonitorJoyXY(int event)
{
  Monitor_cls();
  int x = map(joy_x, -512, 512, MON_X1, MON_X2);
  int y = map(joy_y, -512, 512, MON_Y1, MON_Y2);

  // display.drawFastHLine(MON_X1, y, MON_X2, y);
  // display.drawFastVLine(x, MON_Y1, x, MON_Y2);
  if(!joy_sw.current_val) {
    display.fillCircle(x, y, 5, WHITE);
  }else{
    display.drawCircle(x, y, 5, WHITE);
  }

  return 0;
}

int MonitorMidiDual(int event)
{

}

int MonitorMidiXY(int event)
{

}

ROUTINE routines[UPDATE_ROUTINE_COUNT] = {
  UpdateMenu,
  DialVolume,
  JoyMouse,
  MonitorJoyXY,
  UpdateStatusIndicators,
};
int routine_events[UPDATE_ROUTINE_COUNT];

ROUTINE MenuRoutines[] = {
  UpdateMenu,
  OctaveMode,
  MediaMode,
  BrowseKeyMode,
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

ROUTINE MonRoutines[] = {
  MonitorJoyXY,
  MonitorMidiXY,
  MonitorMidiDual,
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

  //
  pinMode(PWM_EL, OUTPUT);
  TCCR1A = _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(WGM13) /* | _BV(WGM12) */ | _BV(CS11);
  OCR1A = 789;

  memset(routine_events, 0, sizeof(routine_events));

  delay(500);
  ui_cls();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.drawLine(0, 15, 127, 15, 1);
  display.drawLine(64, 15, 64, 63, 1);

  display.display();

  Serial.println(F("START"));
}

void read()
{
  if (DEBOUNCE_READ(DCNT_LB, lb))
  {
    if(lb.current_val == LOW) post_event(MENU_UPDATE_ROUTINE, K1_DOWN);
    else post_event(MENU_UPDATE_ROUTINE, K1_UP);
  }
  if (DEBOUNCE_READ(DCNT_MB, mb))
  {
    if(mb.current_val == LOW) post_event(MENU_UPDATE_ROUTINE, K2_DOWN);
    else post_event(MENU_UPDATE_ROUTINE, K2_UP);
  }
  if (DEBOUNCE_READ(DCNT_RB, rb))
  {
    if(rb.current_val == LOW) post_event(MENU_UPDATE_ROUTINE, K3_DOWN);
    else post_event(MENU_UPDATE_ROUTINE, K3_UP);
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

  if(abs(jx) < joy_deadzone) jx = 0;
  if(abs(jy) < joy_deadzone) jy = 0;

  if(jx != joy_x || jy != joy_y)
  {
    post_event(JOY_UPDATE_ROUTINE, JE_POS);
  }

  joy_x = jx;
  joy_y = jy;

  comlink = ReadCOM();

  if(comlink != NULL){

    // =============== EL_DUTY CMD 0x01 ===============
    if(comlink[0] == 0x01)
    {
      int value = map((int)comlink[2], 0, 127, EL_DUTY_MIN, EL_DUTY_MAX);
      switch(comlink[1])
      {
        case 102:
        el_duty = value;
        break;
      }
    }
    // =============== GET_SETTINGS CMD 0x02 ===============
    else if (comlink[0] == 0x02)
    {
      char settings[64];
      static const char psettings[] PROGMEM = "SETTING,%d,%d,%d,%d";
      sprintf_P(settings, psettings, menu_mode, dialroutine_idx, joyroutine_idx, monroutine_idx);

      Serial.println(settings);
    }
    // =============== SET_SETTINGS CMD 0x0e ===============
    else if (comlink[0] == 0x03)
    {
      menu_mode = comlink[1];
      dialroutine_idx = comlink[2];
      joyroutine_idx = comlink[3];
      monroutine_idx = comlink[4];

      post_event(MENU_UPDATE_ROUTINE, 0);
    }
  }
}

void run()
{
  for(int i=0;i<UPDATE_ROUTINE_COUNT; ++i){
    if (routine_events[i] >= 0){
      routine_events[i] = routines[i](routine_events[i]);
    }
  }

  if(el_duty < EL_DUTY_MIN) { el_duty = EL_DUTY_MIN;}
  if(el_duty > EL_DUTY_MAX) { el_duty = EL_DUTY_MAX; }
  OCR1B = el_duty;

}

void loop() {
  read();
  run();
  display.display();
}
