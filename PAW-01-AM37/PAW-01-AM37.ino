#include "Arduino.h"
#include "pindef.h"
#include "debounced_button.h"
#include "com.h"

#define GROUP_CNT 5
#define CV_IN_CNT 1

struct KEY{
  unsigned long TriggerTime;
  bool On;
};

DEBOUNCED_BUTTON KEYS_1[37];
DEBOUNCED_BUTTON KEYS_2[37];
KEY KEYS_RECORDS[37];
int CV_IN[CV_IN_CNT];

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

  for(int i=0;i<CV_IN_CNT;++i){
    CV_IN[i] = 512;
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
      // when primary switch is OFF, we should reset Trigger time.
      // this prevents "ghost timers" producing very weak velocities
      // note, ghost timer is due to the fact that TriggerTime is only
      // recorded on an edge trigger when TriggerTime == 0.
      if (KEYS_1[i].current_val) KEYS_RECORDS[i].TriggerTime = 0;

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
  int cv0 = analogRead(CVIN_AFTERTOUCH);
  cv0 = map(cv0, 0, 1024, 127, 0);

  if(cv0 != CV_IN[0]){
    Serial.print("CC,107,");
    Serial.println(cv0);
  }

  CV_IN[0] = cv0;
}

void loop() {
  //  read 37 keys
  ReadKeys();
  ReadCVIn();
}
