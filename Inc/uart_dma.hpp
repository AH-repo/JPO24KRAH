/**
 * @file UART_DMA.h
 * @brief UART Communication Library with DMA Support
 * 
 * This library provides a class and associated functions for handling UART 
 * communication using DMA (Direct Memory Access) for efficient data transfer. 
 * It abstracts the process of configuring and using UART peripherals with 
 * DMA channels for transmission and reception.
 * 
 * @author Adrian Homa
 * @version 1.0
 * @date 2024-12-22
 * 
 * @copyright (c) 2024 Adrian Homa 
 * All rights reserved.
 * 
 * This file contains the definition for the `UART_DMA` class which simplifies the process
 * of sending and receiving data over UART with DMA. It includes configurations for UART,
 * DMA and GPIO ports handling.
 * 
 * Usage Example:
 * @code
 *     uartconfig UARTconfig = { ... };  // Fill the configuration struct
 *     UART_DMA UARTDMA(UARTConfig);      // Initialize the UART_DMA object
 *     UARTDMA.init();                  // Configure UART and DMA
 *     UARTDMA.transmit(txData, Size);  // Transmit data
 * @endcode
 */
#pragma once
extern "C" {
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include <stdio.h>
}

/**
 * @brief Structure for UART configuration.
 * 
 * This structure holds the configuration data for setting up a UART communication
 * interface with DMA support, pin mapping, and baud rate setting.
 * 
 * @param UART        Pointer to the USART peripheral. This points to the UART/USART 
 *                    register base for communication (e.g., USART1, USART2, etc.).
 * @param dma         Pointer to the DMA peripheral. This points to the DMA register 
 *                    base used for transmitting and receiving data via DMA.
 * @param dma_stream_tx   DMA stream for TX (Transmit). This specifies the DMA stream used for 
 *                        transmitting data from the UART.
 * @param dma_stream_rx   DMA stream for RX (Receive). This specifies the DMA stream used for 
 *                        receiving data to the UART.
 * @param dma_channel_tx  DMA channel for TX (Transmit). This specifies the DMA channel used 
 *                        for transmitting data via DMA.
 * @param dma_channel_rx  DMA channel for RX (Receive). This specifies the DMA channel used 
 *                        for receiving data via DMA.
 * @param BR           Baud rate for the UART communication. This is the baud rate used for 
 *                    UART communication. This value typically ranges from a low to a high 
 *                    rate depending on the application.
 * @param RX_Port      GPIO port for RX (Receive). This is the GPIO port used for the UART 
 *                    receive pin.
 * @param RX_Pin       GPIO pin for RX (Receive). This is the GPIO pin used for the UART 
 *                    receive line.
 * @param TX_Port      GPIO port for TX (Transmit). This is the GPIO port used for the UART 
 *                    transmit pin.
 * @param TX_Pin       GPIO pin for TX (Transmit). This is the GPIO pin used for the UART 
 *                    transmit line.
 */
struct uartconfig
{
    USART_TypeDef *UART;           /**< Pointer to the USART peripheral. */
    DMA_TypeDef *dma;              /**< Pointer to the DMA peripheral. */
    uint8_t dma_stream_tx;         /**< DMA stream for TX (Transmit). */
    uint8_t dma_stream_rx;         /**< DMA stream for RX (Receive). */
    uint8_t dma_channel_tx;        /**< DMA channel for TX (Transmit). */
    uint8_t dma_channel_rx;        /**< DMA channel for RX (Receive). */
    uint32_t BR;                    /**< Baud rate for the UART communication. */
    GPIO_TypeDef *RX_Port;         /**< GPIO port for RX (Receive). */
    uint16_t RX_Pin;               /**< GPIO pin for RX (Receive). */
    GPIO_TypeDef *TX_Port;         /**< GPIO port for TX (Transmit). */
    uint16_t TX_Pin;               /**< GPIO pin for TX (Transmit). */
};

namespace AH{
/**
 * @brief Class for UART communication with DMA support.
 * 
 * This class provides methods for initializing and handling UART communication, including data transfer, interrupt management,
 * and status checking, with customizable configurations through the uartconfig structure.
 * 
 * @param UART_DMA()                    - Default constructor which initializes UART with DMA support and default settings.
 * @param UART_DMA(const uartconfig&)   - Constructor that accepts a configuration structure for custom UART and DMA settings.
 */
class UART_DMA {
public: 
    /**
     * @brief Default constructor for UART_DMA.
     *
     * This constructor initializes a UART interface with DMA support using default
     * configuration settings:
     * - USART2 interface
     * - DMA1 for data transfer
     * - TX stream 6, RX stream 5
     * - DMA channel 4 for both TX and RX
     * - BaudRate set to 9600
     * - RX pin set to PA3
     * - TX pin set to PA2
     */
    UART_DMA();
     /**
     * @brief Constructs a new UART_DMA object.
     * 
     * @param u_conf Configuration structure containing all necessary UART and DMA settings.
     */
    UART_DMA(const uartconfig& u_conf);

    /**
     * @brief Initializes the UART and DMA peripherals.
     * 
     * Configures GPIO pins, UART parameters, and DMA streams according to the 
     * configuration provided during object construction.
     */
    void init();

    /**
     * @brief Enables UART interrupts.
     * 
     * @param mode Mode definition:
     * - mode = 0; interrupts disable
     * - mode = 1; tx interrupts only
     * - mode = 2; rx interrupts only
     * - mode = 3; rx/tx interrupts
     */    
    void enUARTint(uint8_t mode);
 
    /**
     * @brief Determines the IRQ number for a given DMA stream.
     * 
     * @param dma_stream Pointer to the DMA stream.
     * @return IRQn_Type The interrupt number corresponding to the DMA stream.
     */   
    IRQn_Type IRQnStreamType(DMA_Stream_TypeDef *dma_stream);

        /**
     * @brief Clears DMA stream interrupt flags.
     * 
     * @param stream Pointer to the DMA stream whose flags need to be cleared.
     */
    void dma_clr_ifcr(DMA_Stream_TypeDef* stream);

    /**
     * @brief Transmits data using DMA.
     * 
     * @param txData Pointer to the data buffer to transmit.
     * @param size Size of the data to transmit in bytes.
     */
    void transmit(uint8_t* txData, uint16_t size);

    
    /**
     * @brief Receives data using DMA.
     * 
     * @param rxData Pointer to the buffer where received data will be stored.
     * @param size Number of bytes to receive.
     */
    void receive(uint8_t* rxData, uint16_t size);

    /**
     * @brief Sends a single byte of data.
     * 
     * @param data The byte to send.
     */
    void send(uint8_t data);

    /**
     * @brief Reads a single byte of data.
     * 
     * @return uint8_t The received byte.
     */
    uint8_t read();

    /**
     * @brief Checks if transmission is in progress.
     * 
     * @return true if transmission is busy.
     * @return false if transmission is idle.
     */
    bool isTXbusy();

    /**
     * @brief Checks if reception is in progress.
     * 
     * @return true if reception is busy.
     * @return false if reception is idle.
     */
    bool isRXbusy();

    
    /**
     * @brief Clears the transmission busy flag.
     */
    void clearTXbusy();

    /**
     * @brief Clears the reception busy flag.
     */
    void clearRXbusy();

    /**
     * @brief Disables UART transmission.
     */
    void TXdisable();

    
    /**
     * @brief Disables UART reception.
     */
    void RXdisable();

    
    /**
     * @brief Enables both UART transmission and reception.
     */
    void enable();

    /**
     * @brief Disables both UART transmission and reception.
     */
    void disable();

private:
    volatile bool m_TX_busy;      
    volatile bool m_RX_busy;
    uint32_t m_BR;    
    USART_TypeDef *m_UART;          
    DMA_TypeDef *m_dma;          
    DMA_Stream_TypeDef *m_dma_stream_tx; 
    DMA_Stream_TypeDef *m_dma_stream_rx;
    uint8_t m_dma_channel_tx;     
    uint8_t m_dma_channel_rx;      
    GPIO_TypeDef *m_RX_Port;     
    uint16_t m_RX_Pin;            
    GPIO_TypeDef *m_TX_Port;       
    uint16_t m_TX_Pin;                               
};
}