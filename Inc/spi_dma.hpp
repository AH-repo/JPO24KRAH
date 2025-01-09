/**
 * @file SPI_DMA.h
 * @brief SPI Communication Library with DMA Support
 * 
 * This library provides a class and associated functions for handling SPI 
 * communication using DMA (Direct Memory Access) for efficient data transfer. 
 * It abstracts the process of configuring and using SPI peripherals with 
 * DMA channels for transmission and reception.
 * 
 * @author Kamil Russ
 * @version 1.0
 * @date 2024-12-19
 * 
 * @copyright (c) 2024 Kamil Russ 
 * All rights reserved.
 * 
 * This file contains the definition for the `SPI_DMA` class which simplifies the process
 * of sending and receiving data over SPI with DMA. It includes configurations for SPI,
 * DMA, GPIO ports, and chip select handling.
 * 
 * Usage Example:
 * @code
 *     spiconfig spiConfig = { ... };  // Fill the configuration struct
 *     SPI_DMA spiDMA(spiConfig);      // Initialize the SPI_DMA object
 *     spiDMA.init();                  // Configure SPI and DMA
 *     spiDMA.transmit(txData, dataSize);  // Transmit data
 * @endcode
 */


#pragma once

extern "C" {
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include <stdio.h>
}



/**
 * @brief Structure containing the SPI configuration.
 * 
 * This structure contains all the settings required for configuring and
 * operating the SPI interface, including GPIO port assignments, DMA configuration,
 * and SPI peripheral parameters.
 * 
 * @param spi
 * @param dma
 * @param dma_stream_tx
 * @param dma_stream_rx
 * @param dma_channel_tx
 * @param dma_channel_rx
 * @param BRpre
 * @param CS_Port
 * @param CS_Pin
 * @param MISO_Port
 * @param MISO_Pin
 * @param MOSI_Port
 * @param MOSI_Pin
 * @param SCK_Port
 * @param SCK_Pin
 */
struct spiconfig
{
    SPI_TypeDef *spi;             /**< Pointer to the SPI register for the selected SPI interface (e.g., SPI1, SPI2). */
    DMA_TypeDef *dma;             /**< Pointer to the DMA register for configuring SPI data transfer (TX and RX). */
    uint8_t dma_stream_tx;        /**< DMA stream number for transmitting data (TX). */
    uint8_t dma_stream_rx;        /**< DMA stream number for receiving data (RX). */
    uint8_t dma_channel_tx;       /**< DMA channel number assigned for transmission (TX). */
    uint8_t dma_channel_rx;       /**< DMA channel number assigned for reception (RX). */
    uint8_t BRpre;                /**< SPI clock prescaler value, based on the APB clock frequency. */
    GPIO_TypeDef *CS_Port;        /**< Pointer to the GPIO port for the Chip Select (CS) pin in SPI. */
    uint16_t CS_Pin;              /**< GPIO pin number used for Chip Select (CS) in SPI. */
    GPIO_TypeDef *MISO_Port;      /**< Pointer to the GPIO port for the MISO (Master In Slave Out) pin in SPI. */
    uint16_t MISO_Pin;            /**< GPIO pin number used for receiving data (MISO) in SPI. */
    GPIO_TypeDef *MOSI_Port;      /**< Pointer to the GPIO port for the MOSI (Master Out Slave In) pin in SPI. */
    uint16_t MOSI_Pin;            /**< GPIO pin number used for sending data (MOSI) in SPI. */
    GPIO_TypeDef *SCK_Port;       /**< Pointer to the GPIO port for the SCK (Serial Clock) pin in SPI. */
    uint16_t SCK_Pin;             /**< GPIO pin number used for SPI clock generation (SCK). */
};

namespace KR{
/**
 * @brief Class for managing SPI communication with DMA support.
 * 
 * This class provides functionality for configuring and using the SPI interface with
 * DMA for both data transmission (TX) and reception (RX). It manages the initialization,
 * data transfer, and communication states for SPI over DMA.
 * 
 * Key features of this class:
 * - Configurable SPI interface with support for DMA.
 * - DMA-based transmission and reception of data.
 * - Configuration of SPI pins (CS, MISO, MOSI, SCK).
 * - Methods for checking transmission and reception statuses.
 * - Interrupt handling for DMA-related events.
 * - Functions to enable and disable SPI communication.
 */
class SPI_DMA {
public:
    /**
     * @brief Default constructor for SPI_DMA.
     *
     * This constructor initializes an SPI interface with DMA support using default
     * configuration settings:
     * - SPI1 interface
     * - DMA2 for data transfer
     * - TX stream 3, RX stream 2
     * - DMA channel 3 for both TX and RX
     * - Chip Select (CS) set to PA15
     * - MISO set to PA6, MOSI set to PA7, SCK set to PA5
     * - BaudRate prescaler set to 2, resulting in a clock frequency of 11.5 MHz
     */
    SPI_DMA();

    /**
     * @brief Constructs an SPI_DMA object with the specified configuration.
     *
     * This constructor initializes an SPI interface with DMA support using the provided
     * configuration parameters in the spiconfig structure.
     *
     * @param spi_conf A structure containing the SPI configuration parameters:
     * - SPI interface (spi)
     * - DMA configuration for TX and RX (dma, dma_stream_tx, dma_stream_rx, dma_channel_tx, dma_channel_rx)
     * - SPI clock prescaler (BRpre)
     * - GPIO configuration for Chip Select, MISO, MOSI, and SCK pins
     */
    SPI_DMA(const spiconfig& spi_conf); 
    /**
     * @brief Initializes the SPI peripheral and related configurations.
     *
     * This method configures the SPI, DMA, and related GPIO pins, enabling SPI communication.
     * It must be called before any SPI communication can take place.
     */
    void init();

    /**
     * @brief Enables SPI interrupt.
     *
     * @param mode Mode definition:
     * - mode = 0; interrupts disable
     * - mode = 1; tx interrupts only
     * - mode = 2; rx interrupts only
     * - mode = 3; rx/tx interrupts
     */
    void enSPIint(uint8_t mode);

    /**
     * @brief Returns the appropriate IRQ type for a given DMA stream.
     *
     * This method returns the interrupt request (IRQ) type based on the provided
     * DMA stream, which is used to configure interrupts for DMA transfers.
     *
     * @param dma_stream The DMA stream for which the IRQ type is required.
     * @return IRQn_Type The interrupt type corresponding to the given DMA stream.
     */
    IRQn_Type IRQnStreamType(DMA_Stream_TypeDef *dma_stream);

    /**
     * @brief Transmits data via SPI using DMA.
     *
     * This method sets up DMA transmission, transferring data from the provided buffer
     * to the SPI interface. It uses DMA for efficient data transfer.
     *
     * @param txBuffer Pointer to the buffer containing the data to be transmitted.
     * @param size The size of the data in the buffer to transmit.
     */
    void transmit(const uint8_t *txBuffer, uint16_t size);

    /**
     * @brief Receives data via SPI using DMA.
     *
     * This method sets up DMA reception, reading data from the SPI interface into
     * the provided buffer. It uses DMA for efficient data reception.
     *
     * @param rxBuffer Pointer to the buffer where received data will be stored.
     * @param size The size of the data to receive.
     */
    void receive(uint8_t *rxBuffer, uint16_t size);

    /**
    * @brief Sets the state of the Chip Select (CS) line.
    * 
    * Activates or deactivates the CS line based on the given state.
    * 
    * @param state `true` to activate CS, `false` to deactivate CS.
    */
    void setCS(bool state);
    
    /**
     * @brief Sends a single byte of data via SPI.
     *
     * This method sends a byte of data to the SPI interface.
     * It is typically used for single byte transmissions.
     *
     * @param data The byte of data to send.
     */
    void send(uint8_t data);

     /**
     * @brief Reads a single byte of data from SPI.
     *
     * This method reads one byte of data from the SPI interface. It is commonly used
     * in master-slave communication.
     *
     * @return uint8_t The byte of data received via SPI.
     */   
    uint8_t read();

    /**
     * @brief Checks if the SPI transmission (TX) is in progress.
     *
     * This method checks if the TX DMA stream is still active or if the transmission
     * is complete.
     *
     * @return `true` If the TX DMA stream is busy, indicating ongoing transmission.
     * @return `false` If the TX DMA stream is not busy, indicating the transmission is complete.
     */
    bool isDMATXbusy();

    /**
     * @brief Checks if the SPI reception (RX) is in progress.
     *
     * This method checks if the RX DMA stream is still active or if the reception
     * is complete.
     *
     * @return `true` If the RX DMA stream is busy, indicating ongoing reception.
     * @return `false` If the RX DMA stream is not busy, indicating the reception is complete.
     */
    bool isDMARXbusy();

    /**
     * @brief Clears the TX DMA busy flag and the interrupt flags associated with TX DMA.
     *
     * This method clears the TX DMA flags after the transmission is complete, 
     * allowing for new transmissions.
     */
    void clearDMATXbusy();

    /**
     * @brief Clears the RX DMA busy flag and the interrupt flags associated with RX DMA.
     *
     * This method clears the RX DMA flags after the reception is complete, 
     * allowing for new receptions.
     */
    void clearDMARXbusy();

    /**
     * @brief Checks if the Transmit Data Register is empty (TXE).
     * 
     * @return `true` if TXE flag is set, indicating the register is empty and ready for new data.
     */
    bool isTXE();

    /**
     * @brief Checks if the Receive Data Register is not empty (RXNE).
     * 
     * @return `true` if RXNE flag is set, indicating new data is available for reading.
     */
    bool isRXNE();

    /**
     * @brief Enables SPI communication .
     */
    void enable();

    /**
     * @brief Disables SPI communication.
     */
    void disable();

    
 
private:
    volatile bool m_TX_busy;
    volatile bool m_RX_busy;
    SPI_TypeDef* m_spi;
    DMA_TypeDef* m_dma;
    uint8_t m_BRpre;
    DMA_Stream_TypeDef *m_dma_stream_tx;
    DMA_Stream_TypeDef *m_dma_stream_rx;
    uint8_t m_dma_channel_tx;
    uint8_t m_dma_channel_rx;              
    GPIO_TypeDef *m_CS_Port;
    uint8_t m_CS_Pin;
    GPIO_TypeDef *m_MISO_Port;
    uint8_t m_MISO_Pin;
    GPIO_TypeDef *m_MOSI_Port;
    uint8_t m_MOSI_Pin;
    GPIO_TypeDef *m_SCK_Port;
    uint8_t m_SCK_Pin;
    
    void dma_clr_ifcr(DMA_Stream_TypeDef* stream);
};
}