#ifndef PINDEF_H
#define PINDEF_H

#define ADATA0 7
#define ADATA1 6
#define DATA0 1
#define DATA1 0
#define DATA2 2
#define DATA3 3
#define DATA4 4
#define DATA5 5
#define DATA6 6
#define DATA7 7

#define ADDR0 8
#define ADDR1 9
#define ADDR2 10
#define ADDR3 11
#define ADDR4 12 // Not connected... WHY?

#define DEXT 13

#define CVIN0 0
#define CVIN1 1
#define CVIN2 2
#define CVIN3 3

#define CVMUXIN0 4
#define CVMUXIN1 5
// #define CVMUXIN2 6
// #define CVMUXIN3 7
// unfortunately we've lost 1x4 cvmux due to a design error
// mux3 is flyover to DATA0 because 74HC138 does not have enough fanin capacity to sink current from DATA0
// resulting in D0 voltage too high. We have to use an analog pin to do it.

#endif