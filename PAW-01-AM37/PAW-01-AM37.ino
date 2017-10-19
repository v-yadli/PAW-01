#include "Arduino.h"
#include "pindef.h"
#include "../debounced_button.h"
#include "../com.h"

#define GROUP_CNT 10
#define KEYS_IN_GROUP 4
#define CV_OUT_CNT 2
#define CV_IN_CNT 4
#define CVMUX_IN_CNT 16
#define CVMUX_IN_GROUP 4
#define CVMUX_IN_GROUP_CNT 4

#define DAC0832ADDR0 13
#define DAC0832ADDR1 14
#define DAC0832ADDRXFER 15

struct KEY{
  int Velocity;
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
  pinMode(DATA0, INPUT_PULLUP);
  pinMode(DATA1, INPUT_PULLUP);
  pinMode(DATA2, INPUT_PULLUP);
  pinMode(DATA3, INPUT_PULLUP);
  pinMode(DATA4, INPUT_PULLUP);
  pinMode(DATA5, INPUT_PULLUP);
  pinMode(DATA6, INPUT_PULLUP);
  pinMode(DATA7, INPUT_PULLUP);
}

void DATA_OUT()
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

  memset(KEYS_1, 0, sizeof(KEYS_1));
  memset(KEYS_2, 0, sizeof(KEYS_2));
  memset(KEYS_RECORDS, 0, sizeof(KEYS_RECORDS));

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

void ReadKey(byte offset, byte pin1, byte pin2)
{
  bool k1, k2;
  bool kon = KEYS_RECORDS[offset].On;
  k1 = DEBOUNCE_READ(DATA0, KEYS_1[offset]);
  k2 = DEBOUNCE_READ(DATA1, KEYS_2[offset]);
  if(kon){

  }else{
    if(k1){
      Serial.print("Key1 ");
      Serial.print(offset);
      Serial.print(" triggered, state = ");
      Serial.println(KEYS_1[offset].current_val);
    }

    if(k2){
      Serial.print("Key2 ");
      Serial.print(offset);
      Serial.print(" triggered, state = ");
      Serial.println(KEYS_2[offset].current_val);
    }
  }
}

void ReadKeys()
{
  DATA_IN();
  byte grp;
  byte offset = 0;
  for(grp = 0; grp < GROUP_CNT; ++grp)
  {
    SET_ADDR(grp);
    ReadKey(offset++, DATA0, DATA1);
    ReadKey(offset++, DATA2, DATA3);
    //  The last group has only two keys
    if (grp == GROUP_CNT - 1) break;
    ReadKey(offset++, DATA4, DATA5);
    ReadKey(offset++, DATA6, DATA7);
  }
}

void ReadCVIn()
{
  DATA_IN();
  CV_IN[0] = analogRead(CVIN0);
  CV_IN[1] = analogRead(CVIN1);
  CV_IN[2] = analogRead(CVIN2);
  CV_IN[3] = analogRead(CVIN3);
}

void WriteCVOut()
{
  DATA_OUT();
  SET_ADDR(DAC0832ADDR0);
  udelay(50);
  DATA_WRITE(CV_OUT[0]);
  udelay(50);
  SET_ADDR(DAC0832ADDR1);
  udelay(50);
  DATA_WRITE(CV_OUT[1]);
  udelay(50);
  SET_ADDR(DAC0832ADDRXFER);
  udelay(50);
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
    CVMUX_IN[offset++] = analogRead(CVMUXIN2);
    CVMUX_IN[offset++] = analogRead(CVMUXIN3);
  }
}

void loop() {
  //  read 37 keys
  ReadKeys();
  ReadCVIn();
  WriteCVOut();
  ReadCVMuxIn();

  char* comlink = ReadCOM();
  if(comlink != NULL){
    //TODO MOSI commands
  }
}
