#include "Arduino.h"
#include "pindef.h"
#include "debounced_button.h"
#include "com.h"

#define GROUP_CNT 5
#define CV_OUT_CNT 2
#define CV_IN_CNT 4
#define CVMUX_IN_CNT 16
#define CVMUX_IN_GROUP 4
#define CVMUX_IN_GROUP_CNT 4

#define DAC0832ADDR0 13
#define DAC0832ADDR1 14
#define DAC0832ADDRXFER 15

struct KEY{
  unsigned long TriggerTime;
  bool On;
};

DEBOUNCED_BUTTON KEYS_1[37];
DEBOUNCED_BUTTON KEYS_2[37];
KEY KEYS_RECORDS[37];
byte CV_OUT[CV_OUT_CNT];
int CV_IN[CV_IN_CNT];
int CVMUX_IN[CVMUX_IN_CNT];

void DATA_IN()
{
  pinMode(DATA0, INPUT);
  pinMode(DATA1, INPUT);
  pinMode(DATA2, INPUT);
  pinMode(DATA3, INPUT);
  pinMode(DATA4, INPUT);
  pinMode(DATA5, INPUT);
  pinMode(DATA6, INPUT);
  pinMode(DATA7, INPUT);
  delayMicroseconds(50);
}

void DATA_OUT()
{
  pinMode(DATA0, OUTPUT);
  pinMode(DATA1, OUTPUT);
  pinMode(DATA2, OUTPUT);
  pinMode(DATA3, OUTPUT);
  pinMode(DATA4, OUTPUT);
  pinMode(DATA5, OUTPUT);
  pinMode(DATA6, OUTPUT);
  pinMode(DATA7, OUTPUT);
  delayMicroseconds(50);
}

void DATA_WRITE(byte value)
{
  digitalWrite(DATA0, (bool)(value & 0x1));
  digitalWrite(DATA1, (bool)(value & 0x2));
  digitalWrite(DATA2, (bool)(value & 0x4));
  digitalWrite(DATA3, (bool)(value & 0x8));
  digitalWrite(DATA4, (bool)(value & 0x10));
  digitalWrite(DATA5, (bool)(value & 0x20));
  digitalWrite(DATA6, (bool)(value & 0x40));
  digitalWrite(DATA7, (bool)(value & 0x80));
  delayMicroseconds(50);
}

void SET_ADDR(byte ADDR)
{
  digitalWrite(ADDR0, (bool)(ADDR & 0x1));
  digitalWrite(ADDR1, (bool)(ADDR & 0x2));
  digitalWrite(ADDR2, (bool)(ADDR & 0x4));
  digitalWrite(ADDR3, (bool)(ADDR & 0x8));
  // Serial.println(ADDR);
  // delay(1000);

  delayMicroseconds(50);
  // delay(1000);
}

void setup()   {                
  Serial.begin(250000);

  pinMode(ADDR0, OUTPUT);
  pinMode(ADDR1, OUTPUT);
  pinMode(ADDR2, OUTPUT);
  pinMode(ADDR3, OUTPUT);

  DATA_IN();

  for(int i=0;i<37;++i){
    KEYS_1[i].current_val=1;
    KEYS_1[i].cnt=0;
    KEYS_2[i].current_val=1;
    KEYS_2[i].cnt=0;
    KEYS_RECORDS[i].On=false;
    KEYS_RECORDS[i].TriggerTime=0;
  }

  for(int i=0;i<CV_OUT_CNT;++i){
    CV_OUT[i] = 128;
  }

  for(int i=0;i<CV_IN_CNT;++i){
    CV_IN[i] = 512;
  }

  for(int i=0;i<CVMUX_IN_CNT;++i){
    CVMUX_IN[i] = 512;
  }
}

void ReadKeys()
{
  DATA_IN();
  byte grp;
  byte offset1 = 0;
  byte offset2 = 0;
  byte updates[37];
  memset(updates, 0, sizeof(updates));
  for(grp = 0; grp < GROUP_CNT; ++grp)
  {
    SET_ADDR(grp * 2);
    updates[offset1] |= DEBOUNCE_READ_ANALOG(ADATA0, KEYS_1[offset1]);
    offset1++;
    updates[offset1] |= DEBOUNCE_READ_ANALOG(ADATA1, KEYS_1[offset1]);
    offset1++;
    updates[offset1] |= DEBOUNCE_READ(DATA2, KEYS_1[offset1]);
    offset1++;
    updates[offset1] |= DEBOUNCE_READ(DATA3, KEYS_1[offset1]);
    offset1++;
    updates[offset1] |= DEBOUNCE_READ(DATA4, KEYS_1[offset1]);
    offset1++;
    //  The last group has only 5 keys
    if (grp < GROUP_CNT - 1){
      updates[offset1] |= DEBOUNCE_READ(DATA5, KEYS_1[offset1]);
      offset1++;
      updates[offset1] |= DEBOUNCE_READ(DATA6, KEYS_1[offset1]);
      offset1++;
      updates[offset1] |= DEBOUNCE_READ(DATA7, KEYS_1[offset1]);
      offset1++;
    }
    SET_ADDR(grp * 2 + 1);
    updates[offset2] |= DEBOUNCE_READ_ANALOG(ADATA0, KEYS_2[offset2]);
    offset2++;
    updates[offset2] |= DEBOUNCE_READ_ANALOG(ADATA1, KEYS_2[offset2]);
    offset2++;
    updates[offset2] |= DEBOUNCE_READ(DATA2, KEYS_2[offset2]);
    offset2++;
    updates[offset2] |= DEBOUNCE_READ(DATA3, KEYS_2[offset2]);
    offset2++;
    updates[offset2] |= DEBOUNCE_READ(DATA4, KEYS_2[offset2]);
    offset2++;
    //  The last group has only 5 keys
    if (grp < GROUP_CNT - 1){
      updates[offset2] |= DEBOUNCE_READ(DATA5, KEYS_2[offset2]);
      offset2++;
      updates[offset2] |= DEBOUNCE_READ(DATA6, KEYS_2[offset2]);
      offset2++;
      updates[offset2] |= DEBOUNCE_READ(DATA7, KEYS_2[offset2]);
      offset2++;
    }
  }

  for(int i=0;i<37;++i){
    if(!updates[i]){
      continue;
    }
    if(!KEYS_RECORDS[i].On){
      if (!KEYS_1[i].current_val && KEYS_RECORDS[i].TriggerTime == 0){
        KEYS_RECORDS[i].TriggerTime = millis();
      }
      if(!KEYS_2[i].current_val){
        KEYS_RECORDS[i].On = true;
        long time = millis() - KEYS_RECORDS[i].TriggerTime;
        if(time < 0) {time += 2147483647;}
        Serial.print("KON,");
        Serial.print(i);
        Serial.print(",");
        Serial.print(time);
        Serial.println();
      }
    }else{
      if (KEYS_1[i].current_val || KEYS_2[i].current_val){
        KEYS_RECORDS[i].On = false;
        KEYS_RECORDS[i].TriggerTime = 0;
        Serial.print("KOFF,");
        Serial.println(i);
      }
    }
  }
}

void ReadCVIn()
{
  DATA_IN();

  int cv0= analogRead(CVIN0);
  int cv1= analogRead(CVIN1);
  int cv2= analogRead(CVIN2);
  int cv3= analogRead(CVIN3);

  if(cv0 != CV_IN[0]){
    Serial.print("CC,0,");
    Serial.println(cv0);
  }
  if(cv1 != CV_IN[1]){
    Serial.print("CC,1,");
    Serial.println(cv1);
  }
  if(cv2 != CV_IN[2]){
    Serial.print("CC,2,");
    Serial.println(cv2);
  }
  if(cv3 != CV_IN[3]){
    Serial.print("CC,3,");
    Serial.println(cv3);
  }

  CV_IN[0] = cv0;
  CV_IN[1] = cv1;
  CV_IN[2] = cv2;
  CV_IN[3] = cv3;
}

void WriteCVOut()
{
  DATA_OUT();
  SET_ADDR(DAC0832ADDR0);
  delayMicroseconds(50);
  DATA_WRITE(CV_OUT[0]);
  delayMicroseconds(50);
  SET_ADDR(DAC0832ADDR1);
  delayMicroseconds(50);
  DATA_WRITE(CV_OUT[1]);
  delayMicroseconds(50);
  SET_ADDR(DAC0832ADDRXFER);
  delayMicroseconds(50);
}

void ReadCVMuxIn()
{
  DATA_IN();
  byte grp;
  byte offset = 0;
  for(grp = 0; grp < CVMUX_IN_GROUP_CNT; ++grp)
  {
    SET_ADDR(grp);
    CVMUX_IN[offset++] = analogRead(CVMUXIN0);
    CVMUX_IN[offset++] = analogRead(CVMUXIN1);
    // CVMUX_IN[offset++] = analogRead(CVMUXIN2);
    // CVMUX_IN[offset++] = analogRead(CVMUXIN3);
  }
}

int val[80];
int oldval[80];

void testkeys()
{
  byte grp;
  byte offset = 0;
  for(grp = 0; grp < GROUP_CNT; ++grp)
  {
    SET_ADDR(grp);
    //val[offset++] = digitalRead(DATA0);
    val[offset++] = (analogRead(7) > 950);
    val[offset++] = digitalRead(DATA1);
    val[offset++] = digitalRead(DATA2);
    val[offset++] = digitalRead(DATA3);
    val[offset++] = digitalRead(DATA4);
    val[offset++] = digitalRead(DATA5);
    val[offset++] = digitalRead(DATA6);
    val[offset++] = digitalRead(DATA7);
  }
  if(memcmp(val, oldval, sizeof(val))){
    for(int i=0;i<80;++i){
      Serial.print(val[i]);
      Serial.print(' ');
    }
    Serial.println();
    delay(1);
  }
  memcpy(oldval, val, sizeof(val));
}

void loop() {
  // testkeys();
  //  read 37 keys
  ReadKeys();
  ReadCVIn();
  WriteCVOut();
  //ReadCVMuxIn();

  char* comlink = ReadCOM();
  if(comlink != NULL){
    if(comlink[0] == 0x01){
      //two bytes after this flag. "CVOUT_ID,VALUE"
      //CVOUT_ID is 0-1
      //the value should be 0-255.
      byte cvout_id = comlink[1];
      byte val = comlink[2];
      Serial.print("INFO,CVOUT-");
      Serial.print(cvout_id);
      Serial.print(" SET TO ");
      Serial.println(val);
      CV_OUT[cvout_id] = val;
    }
  }
}
