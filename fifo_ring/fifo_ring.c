#include "fifo_ring.h"

void FIFO_RING_Init(FIFO_RING_t *FIFO_RING) {
    FIFO_RING->head = 0;
    FIFO_RING->tail = 0;
}

bool FIFO_RING_Push(FIFO_RING_t *FIFO_RING, uint8_t data) {
    uint16_t next_head = (FIFO_RING->head + 1) % FIFO_RING_SIZE;

    if (next_head == FIFO_RING->tail) {
        return false; // буфер заполнен
    }

    FIFO_RING->buffer[ FIFO_RING->head ] = data;
    FIFO_RING->head = next_head;
    // Если стоит задача с мультипотоком, возможны пробелмы с одновременным доступом, лечится либо mutex'ами, либо атормарниками
    return true;
}

bool FIFO_RING_Pop(FIFO_RING_t *FIFO_RING, uint8_t *data) {
    if (FIFO_RING_IsEmpty(FIFO_RING)) {
        return false; // буфер пуст
    }

    *data = FIFO_RING->buffer[FIFO_RING->tail];
    FIFO_RING->tail = (FIFO_RING->tail + 1) % FIFO_RING_SIZE;
    // Если стоит задача с мультипотоком, возможны пробелмы с одновременным доступом, лечится либо mutex'ами, либо атормарниками
    return true;
}

bool FIFO_RING_IsEmpty(FIFO_RING_t *FIFO_RING) {
    return FIFO_RING->head == FIFO_RING->tail;
}

bool FIFO_RING_IsFull(FIFO_RING_t *FIFO_RING) {
    return ((FIFO_RING->head + 1) % FIFO_RING_SIZE) == FIFO_RING->tail;
}

void FIFO_RING_Flush(FIFO_RING_t *FIFO_RING) {
    FIFO_RING_Init(FIFO_RING);
}

bool FIFO_RING_Push_rewrite(FIFO_RING_t *FIFO_RING, uint8_t data) {
    uint16_t next_head = (FIFO_RING->head + 1) % FIFO_RING_SIZE;

    #ifndef DEBUG
    __disable_irq();
    #endif

    if (next_head == FIFO_RING->tail) { 
        #ifndef DEBUG
        __enable_irq();
        #endif        
        FIFO_RING->tail = (FIFO_RING->tail + 1) % FIFO_RING_SIZE;  
    }

    FIFO_RING->buffer[FIFO_RING->head] = data;
    FIFO_RING->head = next_head;

    #ifndef DEBUG
    __enable_irq();
    #endif  
    return true;
}