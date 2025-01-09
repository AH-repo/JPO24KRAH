/**
 * @file enc28j60.hpp
 * @brief ENC28J60 Ethernet Controller Driver Library
 * 
 * This library provides a class and associated functions for handling the ENC28J60 
 * Ethernet controller using SPI communication with DMA support. It abstracts the process 
 * of configuring and using the ENC28J60 peripheral for network communication.
 * 
 * @author Kamil Russ, Adrian Homa
 * @version 1.0
 * @date 2024-01-07
 * 
 * This file contains the definition for the `ENC28J60` class which simplifies the process
 * of sending and receiving Ethernet packets using the ENC28J60 controller. It includes 
 * configurations for SPI, DMA, buffer management, and GPIO handling.
 * 
 * Usage Example:
 * @code
 *     enc28j60config config = { ... };  // Fill the configuration struct
 *     spiconfig spi_config = { ... };   // Fill the SPI configuration
 *     ENC28J60 eth(config, spi_config); // Initialize the ENC28J60 object
 *     eth.init();                       // Configure the controller
 *     eth.sendPacket(data, length);     // Send an Ethernet packet
 * @endcode
 */
#pragma once
extern "C" {
#include "stm32f4xx.h"
#include "stm32f446xx.h"
#include <stdio.h>
}

#include "spi_dma.hpp"
#include "enc28j60_reg.hpp"
/**
 * @brief Configuration structure for the ENC28J60 controller.
 * 
 * This structure holds all the necessary configuration parameters for initializing
 * and operating the ENC28J60 Ethernet controller, including GPIO settings, MAC address,
 * and buffer configurations.
 */
struct enc28j60config {
    GPIO_TypeDef *INT_Port;    /**< GPIO port INT pin. */
    uint8_t INT_Pin;           /**< GPIO pin number for INT. */
    uint8_t *mac_address;      /**< ENC28J60 MAC address. */
    uint16_t rx_start;         /**< RX buffer start. */
    uint16_t rx_end;           /**< RX buffer end. */
    uint16_t tx_start;         /**< TX buffer start. */
    uint16_t tx_end;           /**< TX buffer end. */
    uint8_t rx_filter;         /**< Packet filter masks */
};
namespace KRAH{
/**
 * @brief Driver class for the ENC28J60 Ethernet controller.
 * 
 * This class allows controlling and communicating
 * with the ENC28J60 Ethernet controller. It supports both standard and DMA-based
 * transfer operations, filtering and interrupt handling.
 */
class ENC28J60 {

public:
    /**
     * @brief Default constructor.
     * 
     * Initializes a new instance of the ENC28J60 class with default values.
     */
    ENC28J60();

    /**
     * @brief Constructs a new ENC28J60 object with specific configurations.
     * 
     * @param enc_conf Configuration structure containing ENC28J60 settings.
     * @param spiconfig Configuration structure containing SPI interface settings.
     */

    ENC28J60(const enc28j60config& enc_conf, const spiconfig& spiconfig);

    /**
     * @brief ENC28J60 initialization.
     * 
     * Configures the controller according to the provided settings, including
     * buffer setup, provided MAC address configuration, and interrupt settings.
     */
    void init();

    /**
     * @brief Initializes GPIO pins for the controller.
     * 
     * Sets up GPIO pins for SPI communication and interrupt detection.
     */
    void gpioInit();

    /**
     * @brief Sends a packet directly without using DMA.
     * 
     * @param data Pointer to the data buffer containing the packet to send.
     * @param length Length of the packet in bytes.
     */
    void sendPacket(const uint8_t* data, uint16_t length);

    /**
     * @brief Receives a packet directly without using DMA.
     * 
     * @param data Pointer to the buffer to store the received packet.
     * @param length Length of data to receive.
     * @param pointer Start position in the receive buffer.
     * @return uint16_t Number of bytes received.
     */
    uint16_t receivePacket(uint8_t* data, uint16_t length, uint16_t pointer);

    /**
     * @brief Sends a packet using DMA.
     * 
     * @param data Pointer to the data buffer containing the packet to send.
     * @param length Length of the packet in bytes.
     */
    void sendDMAPacket(const uint8_t* data, uint16_t length);

        /**
     * @brief Receives a packet using DMA transfer.
     * 
     * @param data Buffer to store the received packet.
     * @param length Length of data to receive.
     * @param pointer Start position in the receive buffer.
     */
    void receiveDMAPacket(uint8_t* data, uint16_t length, uint16_t pointer);

    /**
     * @brief Writes a value to a register.
     * 
     * @param reg Register address to write to.
     * @param value Value to write to the register.
     */
    void writeReg(uint8_t reg, uint8_t value);

    /**
     * @brief Writes a 16-bit value to a pair of registers.
     * 
     * @param regl Low byte register address.
     * @param regh High byte register address.
     * @param value 16-bit value to write.
     */
    void writeLongReg(uint8_t regl, uint8_t regh, uint16_t value);

    /**
     * @brief Sets or clears a specific bit in a register.
     * 
     * @param reg Register address.
     * @param pos Bit position to modify (0-7).
     * @param state Desired state of the bit.
     */
    void writeRegBit(uint8_t reg, uint8_t pos, bool state);

    /**
     * @brief Writes a value to a physical register.
     * 
     * @param reg PHY register address.
     * @param value Value to write to the register.
     */
    void writePHY(uint8_t reg, uint16_t value);

    /**
     * @brief Waits for MIIM register operation to complete.
     * 
     * Blocks until any ongoing MIIM (Management Interface) operation is finished.
     */
    void waitMIIM();

    /**
     * @brief Reads a value from a controller register.
     * 
     * @param reg Register address to read from.
     * @return uint8_t Value read from the register.
     */
    uint8_t readReg(uint8_t reg);

    /**
     * @brief Reads a 16-bit value from a pair of registers.
     * 
     * @param regl Low byte register address.
     * @param regh High byte register address.
     * @return uint16_t Combined 16-bit value read from the registers.
     */
    uint16_t readLongReg(uint8_t regl, uint8_t regh);

    /**
     * @brief Changes the selected bank.
     * 
     * @param bank Bank number to select (0-3).
     */
    void setBank(uint8_t bank);

    /**
     * @brief Checks the interrupt status.
     * 
     * @return uint8_t Current interrupt status flags.
     */
    uint8_t checkIntStatus();

    /**
     * @brief Enables or disables a chosen interrupt.
     * 
     * @param pos Interrupt position to modify.
     * @param state Desired state.
     */
    void enableInterrupt(uint8_t pos, bool state);

    /**
     * @brief Configure whole interrupt register.
     * 
     * @param value Value to write to the interrupt enable register.
     */
    void enableInterrupt(uint8_t value);

    /**
     * @brief Clears transmit interrupt flag.
     * 
     * @param state Active flag from the EIE register.
     */
    void clearTXInterrupt(uint8_t state);

    /**
     * @brief Decrement the value of unprocessed packets.
     * 
     * @param state Active EIE flag.
     */
    void clearRXInterrupt(uint8_t state);

    /**
     * @brief Enables or disables packet reception.
     * 
     * @param state true to enable reception, false to disable.
     */
    void enableReceive(bool state);     

    /**
     * @brief Enables or disables packet transmission.
     * 
     * @param state true to enable transmission, false to disable.
     */
    void enableTransmit(bool state); 

    /**
     * @brief Enables or disables buffer pointer auto-increment.
     * 
     * @param state true to enable auto-increment, false to disable.
     */
    void enableAutoIncrement(bool state);  // Włączenie automatycznej inkrementacji wskaźnika bufora

    /**
     * @brief Clears the DMA receive busy flag.
     */
    void clearDMARXbusy();

    /**
     * @brief Clears the DMA transmit busy flag.
     */
    void clearDMATXbusy();

    /**
     * @brief Clears the buffer busy flag.
     */
    void clearbufferbusy();

    /**
     * @brief Checks if DMA RX is busy.
     * 
     * @return true if DMA RX is in progress.
     * @return false if DMA RX is idle.
     */
    bool isDMARXbusy();

    /**
     * @brief Checks if DMA TX is busy.
     * 
     * @return true if DMA TX is in progress.
     * @return false if DMA TX is idle.
     */
    bool isDMATXbusy();

    /**
     * @brief Checks if the buffer is busy.
     * 
     * @return true if buffer operations are in progress.
     * @return false if buffer is busy.
     */
    bool isbufferbusy();
    
    /**
     * @brief Gets the configured INT pin number.
     * 
     * @return uint8_t The INT pin number.
     */
    uint8_t getINTpin();

    /**
     * @brief Gets the configured INT port.
     * 
     * @return GPIO_TypeDef* Pointer to the INT GPIO port.
     */
    GPIO_TypeDef* getINTport();


    
private:

    KR::SPI_DMA m_spiDriver;                /**< SPI driver for communication with the controller. */
    SPI_TypeDef* m_spi;                     /**< SPI peripheral. */
    uint8_t m_currentBank;                  /**< Currently selected register bank. */
    bool m_buffer_bsy;                      /**< Buffer busy status flag. */
    uint8_t m_EIE;                          /**< Status of interrupt enable register. */
    uint8_t m_ESTAT;                        /**< Status of the ethernet status register. */
    uint8_t m_ECON2;                        /**< Status of Control register 2. */
    uint8_t m_ECON1;                        /**< Status of Control register 1. */
    GPIO_TypeDef* m_INT_Port;               /**< GPIO port for interrupt pin. */
    uint8_t m_INT_Pin;                      /**< GPIO pin number for interrupt. */
    uint8_t m_mac_address[6];               /**< MAC address. */
    uint8_t m_rx_filter;                    /**< Current filter configuration. */
    uint16_t m_rx_start;                    /**< Start address of receive buffer. */
    uint16_t m_rx_end;                      /**< End address of receive buffer. */
    uint16_t m_tx_start;                    /**< Start address of transmit buffer. */
    uint16_t m_tx_end;                      /**< End address of transmit buffer. */

};
}