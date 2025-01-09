extern "C" {
#include "stm32f4xx.h"
#include "stm32f446xx.h"
}

#include "main.hpp"

// INTERRUPT INT PIN
extern "C" void EXTI15_10_IRQHandler() {
    if (EXTI->PR & (1 << enc.getINTpin())) {
        if ((enc.getINTport()->IDR & (1 << enc.getINTpin())) != 0) {
            int_flag = 0;
            EXTI->PR |= (1 << enc.getINTpin()); // clear pending exti flag 
        } else {
            int_flag = 0x80;
            EXTI->PR |= (1 << enc.getINTpin()); // clear pending exti flag
        }
        debug = true;
    }
}

// INTERRUPT SPI DMA TX
extern "C" void DMA2_Stream3_IRQHandler(void){
    enc.clearDMATXbusy();
    buf_tx_done = true;
}

// INTERRUPT SPI DMA RX
 extern "C" void DMA2_Stream2_IRQHandler(void){
    enc.clearDMARXbusy();
    enc.clearDMATXbusy();
    buf_rx_done = true;
}

// INTERRUPT UART RX
 extern "C" void USART2_IRQHandler(void){
    uart_rec = UARTDMA.read();
    uart_rx = true;
}

// INTERRUPT UART DMA TX
 extern "C" void DMA1_Stream6_IRQHandler(void){
    UARTDMA.clearTXbusy();
    packet_read = true;
}