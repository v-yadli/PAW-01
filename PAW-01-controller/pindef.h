#ifndef PINDEF_H
#define PINDEF_H
//  CS on my OLED is not exposed, and in the SSD1306
//  driver code, I've disabled all IO ops on that pin.
//  Thus we can reuse this pin for other purposes
//  SDA & SCL are hardware SPI pins at D11 and D13.
//  The code will set OLED_CS to OUTPUT, so we point
//  the pin to one that we will use for output.

#define OLED_CS -1
// PWRLED, PWRSW, RSTSW offline
#define DMOBO_PWRLED 0
#define DMOBO_PWRSW  1
#define DMOBO_RSTSW  2
#define DCNT_LB 3
#define DCNT_MB 4
#define DCNT_RB 5
#define OLED_DC 6
#define OLED_RESET 7
#define DCNT_DIALSW 8
#define DCNT_JOYSW 9
#define PWM_EL 10
#define OLED_SDA 11
// volume board is damaged. DIALMUX offline
#define DCNT_DIALMUX  12
#define OLED_SCL 13
#define DCNT_DIALENC1 14
#define DCNT_DIALENC2 15

#define ACONFLICT_0 0
#define ACONFLICT_1 1
#define ARESERVED_0 2
#define ACNT_JOYX 3
#define ACNT_JOYY 4
#define AMOBO_HDDLED 5
#define ASND_LVLLED 6
#define ASND_CLPLED 7

#endif