#include "arrayqueue.h"

int headisqueue(arrayqueue *queue) {
	return queue->ptrqueue == queue->ptrhead;
}

volatile unsigned *incrptr(volatile unsigned *ptr, volatile unsigned *base, unsigned maxoff) {
	return ((ptr + 1 - base) % maxoff) + base;
}

void offer(arrayqueue *queue, unsigned value) {
	*(queue->ptrqueue) = value;
	queue->ptrqueue = incrptr(queue->ptrqueue, queue->buffer, BUFFSIZE);
}

int poll(arrayqueue *queue) {
	int value = -1;
  
	if (!headisqueue(queue)) {
		value = *(queue->ptrhead);
		queue->ptrhead = incrptr(queue->ptrhead, queue->buffer, BUFFSIZE);

	}
  
	return value;
}
