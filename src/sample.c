#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h> 
#include <time.h>    

#include "../fifo_ring/fifo_ring.h"

#define ITERATIONS 10
#define MS_DELAY 5e5

FIFO_RING_t uart_FIFO_RING;

void USART_Init(void) {
    FIFO_RING_Init(&uart_FIFO_RING);
    // Инициализация USART 
}

void USART_RX_IRQHandler(void) {
    uint8_t received_byte = 0;
    
    // received_byte = UART_ReadDataRegister();
    
    FIFO_RING_Push(&uart_FIFO_RING, received_byte);
}
    
void timer_handler(bool (*FFRG_Push_sim)(FIFO_RING_t*, uint8_t)) { 
    static uint8_t simulated_byte = 0;
    simulated_byte = (simulated_byte + 1) % 256;

    if (FFRG_Push_sim(&uart_FIFO_RING, simulated_byte)) {
        printf("Simulated byte received FIFO: %u\n", simulated_byte);
    } else {
        printf("FIFO full, byte not added: %u\n", simulated_byte);
    }
}

void recieve_sim(bool (*FFRG_Push_sim)(FIFO_RING_t*, uint8_t)) {
    for (int i = 0; i < ITERATIONS; i++) {
        timer_handler(FFRG_Push_sim);
        usleep(MS_DELAY);
    }

    for (int i = 0; i < ITERATIONS; i++) {
        uint8_t data;
        if (FIFO_RING_Pop(&uart_FIFO_RING, &data)) {
            printf("Received from FIFO: %u\n", data);
        }
        else {
            printf("Not received from FIFO\n");
        }
        usleep(MS_DELAY);
    }
}

int main(void) {

    USART_Init();

    printf("Use FIFO_RING_Push\n");
    recieve_sim(FIFO_RING_Push);

    FIFO_RING_Flush(&uart_FIFO_RING);

    printf("Use FIFO_RING_Push_rewrite\n");
    recieve_sim(FIFO_RING_Push_rewrite);

    return 0;
}
