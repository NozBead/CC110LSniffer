#ifndef __H_ARRAYQUEUE__
#define __H_ARRAYQUEUE__

#define BUFFSIZE 512

typedef volatile struct {
	volatile unsigned buffer[BUFFSIZE];
	volatile unsigned *ptrqueue;
	volatile unsigned *ptrhead;
} arrayqueue;

void offer(arrayqueue *queue, unsigned value);
int poll(arrayqueue *queue);

#endif
