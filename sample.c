#include "fifo_ring.h"
#include <stdio.h>
#include <stdbool.h>

FIFO_RING_t uart_FIFO_RING;

void UART_Init(void) {
    FIFO_RING_Init(&uart_FIFO_RING);
    // Инициализация UART 
}

void USART_RX_IRQHandler(void) {
    uint8_t received_byte = 0;
    
    // received_byte = UART_ReadDataRegister();
    
    FIFO_RING_Push(&uart_FIFO_RING, received_byte);
}

int main(void) {
    UART_Init();

    while (true) {
        uint8_t data;
        if (FIFO_RING_Pop(&uart_FIFO_RING, &data)) {
            printf("Received: %c\n", data);
        }
    }

    return 0;
}
