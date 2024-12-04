#ifndef FIFO_RING_H
#define FIFO_RING_H

#include <stdint.h>
#include <stdbool.h>

#define FIFO_RING_SIZE 8

typedef struct {
    uint8_t buffer[FIFO_RING_SIZE];
    volatile uint16_t head; 
    volatile uint16_t tail; 
} FIFO_RING_t;

void FIFO_RING_Init(FIFO_RING_t *FIFO_RING);

bool FIFO_RING_Push(FIFO_RING_t *FIFO_RING, uint8_t data);

bool FIFO_RING_Pop(FIFO_RING_t *FIFO_RING, uint8_t *data);

bool FIFO_RING_IsEmpty(FIFO_RING_t *FIFO_RING);

bool FIFO_RING_IsFull(FIFO_RING_t *FIFO_RING);

void FIFO_RING_Flush(FIFO_RING_t *FIFO_RING);

bool FIFO_RING_Push_rewrite(FIFO_RING_t *FIFO_RING, uint8_t data);

#endif
