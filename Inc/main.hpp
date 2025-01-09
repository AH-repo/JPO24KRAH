extern "C" {
#include "stm32f4xx.h"
#include "stm32f446xx.h"
}

#include "enc28j60.hpp"
#include "uart_dma.hpp"

extern uint8_t mac_address[6];
extern spiconfig S1;
extern enc28j60config encconf;
extern KRAH::ENC28J60 enc;
extern uartconfig u1;
extern AH::UART_DMA UARTDMA;

extern volatile uint8_t int_flag;
extern volatile uint8_t packet_left; 
extern volatile uint16_t next_pnt;
extern volatile bool buf_tx_done;
extern volatile bool buf_rx_done;
extern volatile bool debug;
extern volatile bool transfer;
extern volatile bool packet_read;
extern volatile bool uart_tx;
extern volatile bool uart_rx;
extern volatile uint8_t uart_rec;

extern const uint8_t ethernetFrame[];
extern uint16_t length_send;
extern uint8_t readPacket[1524];
