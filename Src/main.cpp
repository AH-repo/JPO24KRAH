extern "C" {
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include "RccConfig.h"
}
#include "main.hpp"
#include "enc28j60.hpp"
#include "uart_dma.hpp"

uint8_t mac_address[6] = {0x00, 0x04, 0xA3, 0x41, 0x51, 0x1a};
spiconfig S1 = {SPI1, DMA2, 3, 2, 3, 3, 2, GPIOA, 15, GPIOA, 6, GPIOA, 7, GPIOA, 5};
//enc28j60config encconf = {GPIOA, 12, mac_address, 0x0000, 0x0BFF, 0x0C00, 0x11FF, ERXFCON_BCEN_Msk|ERXFCON_CRCEN_Msk|ERXFCON_UCEN_Msk};
enc28j60config encconf = {GPIOA, 12, mac_address, 0x0000, 0x0BFF, 0x0C00, 0x11FF, ERXFCON_CRCEN_Msk|ERXFCON_UCEN_Msk};
KRAH::ENC28J60 enc(encconf, S1);
uartconfig u1 = {USART2, DMA1, 6, 5, 4, 4, 9600, GPIOA, 3, GPIOA, 2};
AH::UART_DMA UARTDMA(u1);

volatile uint8_t int_flag = 0;
volatile uint8_t packet_left = 0; 
volatile uint16_t next_pnt = 0;
volatile bool buf_tx_done = false;
volatile bool buf_rx_done = false;
volatile bool debug = false;
volatile bool transfer = false;
volatile bool packet_read = true;
volatile bool uart_tx = false;
volatile bool uart_rx = false;
volatile uint8_t uart_rec = 0;

const uint8_t ethernetFrame[] = {
    0x00,
    // Ethernet Header
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // Destination MAC (Broadcast)
    0x00, 0x04, 0xA3, 0x41, 0x51, 0x1A, // Source MAC (Your MAC)
    0x08, 0x06,                         // EtherType (ARP)

    // ARP Payload
    0x00, 0x01,                         // Hardware Type (Ethernet)
    0x08, 0x00,                         // Protocol Type (IPv4)
    0x06,                               // Hardware Size (MAC = 6 bytes)
    0x04,                               // Protocol Size (IP = 4 bytes)
    0x00, 0x01,                         // Opcode (Request)

    0x00, 0x04, 0xA3, 0x41, 0x51, 0x1A, // Sender MAC Address
    0xC0, 0xA8, 0x00, 0x65,             // Sender IP Address (192.168.0.101)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Target MAC Address (Unknown)
    0xC0, 0xA8, 0x00, 0x13              // Target IP Address (192.168.0.19)
};

uint16_t length_send = sizeof(ethernetFrame)/sizeof(ethernetFrame[0]);
uint8_t readPacket[1524];

int main(void){
	size_t length_rec;
	SysClockConfig();
    UARTDMA.init();
    UARTDMA.enUARTint(2);
	enc.init();

	while(1){

        if(int_flag == 0 && !enc.isbufferbusy() && transfer){
           enc.sendDMAPacket(ethernetFrame, length_send);
           transfer = false;
        }

        if(!buf_rx_done && !enc.isbufferbusy() && packet_read){
            if(((int_flag & EIR_PKTIF_Msk) != 0) && packet_left != 0){                             
                uint16_t pnt = enc.receivePacket(readPacket, 2, next_pnt);
                next_pnt = (readPacket[1] << 8) + readPacket[0];
                if(pnt != 0){   
                    if (next_pnt > pnt) {
                        length_rec = next_pnt - pnt - 1;
                    } else {
                        length_rec = (0x0BFF - pnt) + next_pnt - 1;
                    }   
                    enc.receiveDMAPacket(&readPacket[0] + 2, length_rec, pnt);
                    packet_read = false;
                    packet_left --;
                }
            }
        }

        if(int_flag == 0x80 && !enc.isbufferbusy() && !buf_rx_done && !buf_tx_done){             
            int_flag = enc.readReg(EIR);
            if(int_flag & EIR_TXIF_Msk){
                enc.clearTXInterrupt(int_flag);
            }
            if(int_flag & EIR_PKTIF_Msk){
                enc.setBank(1);
                packet_left = enc.readReg(EPKTCNT);
            }
        }

        if (buf_tx_done){
            enc.writeLongReg(ETXNDL, ETXNDH, (encconf.tx_start + length_send - 1));
            enc.enableTransmit(true);
            enc.clearbufferbusy();
            buf_tx_done = false;
        }

        if (buf_rx_done){
            enc.clearRXInterrupt(int_flag);
            enc.setBank(1);
            packet_left = enc.readReg(EPKTCNT);
            enc.clearbufferbusy();
            buf_rx_done = false;
        }

        if (uart_rx && uart_rec == 0x41){
            transfer = true;
            uart_rx = false;
        }

        if (!packet_read){
            UARTDMA.transmit(readPacket, length_rec + 2);
        }
	};
}
