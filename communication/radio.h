#ifndef HRADIO
#define HRADIO

#include <stdio.h>

//Header masks
#define RWMSK	(1 << 7) /*1000 0000*/
#define BRSTMSK	(1 << 6) /*0100 0000*/
#define ADDRMSK	(0x3F)	 /*0011 1111*/

//Special addr
#define FIFOADDR 0x3F
#define PATADDR 0x3E

//Commands addresses
#define RESADDR 0x30
#define RXADDR 0x34
#define TXADDR 0x35
#define IDLEADDR 0x36
#define FRXADDR 0x3A
#define FTXADDR 0x3B
#define NOPADDR 0x3D
 
void setwrite(unsigned char *header);
int isread(const unsigned char *header);
void setread(unsigned char *header);

void setburst(unsigned char *header);
int isburst(const unsigned char *header);
void setnoburst(unsigned char *header);

unsigned char getaddr(const unsigned char *header);
void setaddr(unsigned char *header, unsigned char addr);

int istofifo(const unsigned char *header);
int iscmd(const unsigned char *header);
void printheader(const unsigned char *header);
#endif
