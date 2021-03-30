#include "arrayqueue.h"

#define SI_PIN 4
#define CLK_PIN 3
#define CE_PIN 2

#define USIZE sizeof(unsigned)

volatile byte nbit;
volatile unsigned buffval;
arrayqueue queue;

void addbit(volatile unsigned *value, byte b, byte pos) {
	*value |= b << (7 - pos);
}

void valtobuff(byte *buff, unsigned val) {
	int n = USIZE - 1;
	for (int i = n ; i >= 0 ; i--) {
		buff[n - i] = (val >> (8*i)) & 0xFF;
	}
}

void clkpulse(void) {
	byte si = digitalRead(SI_PIN);

	if (nbit == 8) {
		offer(&queue, buffval);
		nbit = buffval = 0;
	}

	addbit(&buffval, si, nbit);
	nbit++;
}

void cepulse(void) {
	offer(&queue, 0xFF00);
}

void setup(void) {
	Serial.begin(9600);
	//attachInterrupt(digitalPinToInterrupt(CLK_PIN), clkpulse, RISING);
	//attachInterrupt(digitalPinToInterrupt(CE_PIN), cepulse, RISING);
	queue.ptrhead = queue.ptrqueue = queue.buffer;
	nbit = buffval = 0;
  offer(&queue, 0x69);
  offer(&queue, 0x89);
  offer(&queue, 0x29);
}

void loop(void) {
	int value = poll(&queue);
	if (value != -1) {
		//byte towrite[USIZE];
		//valtobuff(towrite, value);
    Serial.println(value, HEX);
		//Serial.write(towrite, USIZE);
	}
}
