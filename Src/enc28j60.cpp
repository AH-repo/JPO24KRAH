#include "enc28j60.hpp"
namespace KRAH{
// Constructor
ENC28J60::ENC28J60():   m_spiDriver(), m_spi(SPI1),
                        m_currentBank(0), m_buffer_bsy(false), 
                        m_EIE(0), m_ESTAT(0), m_ECON2(0), m_ECON1(0), 
                        m_INT_Port(GPIOA), m_INT_Pin (12),
                        m_mac_address{0x00, 0x04, 0xA3, 0x41, 0x51, 0x1a},
                        m_rx_filter(ERXFCON_BCEN_Msk|ERXFCON_CRCEN_Msk|ERXFCON_UCEN_Msk),
                        m_rx_start(0x0000), m_rx_end(0x0BFF), m_tx_start(0x0C00), m_tx_end(0x11FF){};

ENC28J60::ENC28J60(const enc28j60config& enc_conf ,const spiconfig& spiconfig): m_spiDriver(spiconfig), m_currentBank(0), m_buffer_bsy(false), m_EIE(0), m_ESTAT(0), m_ECON2(0), m_ECON1(0) {
    
    //GPIO VALIDATION
    bool GPIO_cond = (spiconfig.MISO_Pin != enc_conf.INT_Pin || spiconfig.MISO_Port != enc_conf.INT_Port) &&
                     (spiconfig.MOSI_Pin != enc_conf.INT_Pin || spiconfig.MOSI_Port != enc_conf.INT_Port) &&
                     (spiconfig.SCK_Pin != enc_conf.INT_Pin  || spiconfig.SCK_Port != enc_conf.INT_Port)  &&
                     (spiconfig.CS_Pin != enc_conf.INT_Pin   || spiconfig.CS_Port != enc_conf.INT_Port)   &&
                     ((enc_conf.INT_Pin < 16) && (enc_conf.INT_Port == GPIOA || enc_conf.INT_Port == GPIOB || 
                                                  enc_conf.INT_Port == GPIOC || enc_conf.INT_Port == GPIOD ));

    if(GPIO_cond){
        m_INT_Port = enc_conf.INT_Port;
        m_INT_Pin = enc_conf.INT_Pin;
    }

    //MAC ADDR VALIDATION
    bool err = 1;
    for(int i = 0; i < 6; i++){
        if(enc_conf.mac_address[i] != 0xff) err = 0;
        if(err == 1 && i == 5) return;   
    }
        err = 1;
    for(int i = 0; i < 6; i++){
        if(enc_conf.mac_address[i] != 0x00) err = 0;
        if(err == 1 && i == 5) return;   
    }
        if(enc_conf.mac_address[0] % 2 == 0) err = 0; 
    if(err){
        return;
    }else{
       for(int i = 0; i < 6; i++){  
        m_mac_address[i] = enc_conf.mac_address[i];
        }
    }


    // FILTERS
    m_rx_filter = enc_conf.rx_filter;
    
    //RX TX BUFFERS VALIDATION
    if((enc_conf.rx_start < enc_conf.rx_end) && (enc_conf.rx_end < enc_conf.tx_start) 
    && (enc_conf.tx_start < enc_conf.tx_end) && (enc_conf.tx_end <= 0x1FFF)){
       m_rx_start = enc_conf.rx_start;
       m_rx_end = enc_conf.rx_end;
       m_tx_start = enc_conf.tx_start;
       m_tx_end = enc_conf.tx_end;
    };
    
    m_spi = spiconfig.spi;

};

void ENC28J60::init() {
    // SPI Initialization
    m_spiDriver.init();

    // Soft reset ENC28J60
    m_spiDriver.setCS(true);
    m_spiDriver.send(0xFF);
    while ((m_spi->SR & SPI_SR_TXE) == 0);  // Wait until soft reset command send
    
    //CLK READY wait 10.24us Rev.B4 Silicon Errata pt. 2.
    volatile uint16_t time = 130; 
    while(time>0){
        time --; 
    } 
    m_spiDriver.setCS(false);
    time = 130;
    while(time>0){
        time --; 
    } 
    

    // GPIO INIT
    gpioInit();
    
    // RX/TX BUFFERS INIT
    setBank(0);
    writeLongReg(ERXSTL, ERXSTH, m_rx_start);       // Set start of RX buffer
    writeLongReg(ERXRDPTL, ERXRDPTH, m_rx_start);   // Set RX buffer pointer on start
    writeLongReg(ERXNDL, ERXNDH, m_rx_end);         // Set end of RX buffer
    writeLongReg(ETXSTL, ETXSTH, m_tx_start);       // Set start of TX buffer
    writeLongReg(ETXNDL, ETXNDH, m_tx_end);         // Set end of TX buffer
    writeLongReg(ERDPTL, ERDPTH, m_rx_start);       // Set RX buffer start position
    writeLongReg(EWRPTL, EWRPTH, m_tx_start);       // Set TX buffer start position
    setBank(1);
    writeReg(ERXFCON, m_rx_filter);                 // Set MacAddress Filters
    

    // PHY/MAC INIT
    setBank(2);
    writeReg(MACON1, MACON1_TXPAUS_Msk | MACON1_RXPAUS_Msk | MACON1_MARXEN_Msk);    // Set RX/TX pause control frames and enable MAC packets
    writeReg(MACON3, MACON3_TXCRCEN_Msk | MACON3_FULDPX_Msk);                       // Turn on CRC and FullDuplex option
    writeReg(MAIPGL, 0x12);                                                         // Non-back-to-back interpacket gap
    writeReg(MAIPGH, 0x0C);                                                         // Non-back-to-back interpacket gap
    writeReg(MABBIPG, 0x15);                                                        // Back-to-back interpacket gap

    // MacAddress assign
    setBank(3);
    writeReg(MAADR6, m_mac_address[5]);
    writeReg(MAADR5, m_mac_address[4]);
    writeReg(MAADR4, m_mac_address[3]);
    writeReg(MAADR3, m_mac_address[2]);
    writeReg(MAADR2, m_mac_address[1]);
    writeReg(MAADR1, m_mac_address[0]);

    // PHY Register configuration
    writePHY(PHCON1, PHCON1_PDPXMD_Msk);    //FullDuplex mode
    
    // Enable interrupts for transmit and receive packets
    enableInterrupt(EIE_INTIE_Msk | EIE_PKTIE_Msk | EIE_TXIE_Msk);
    enableReceive(true);
}


// Single byte functions
void ENC28J60::sendPacket(const uint8_t* data, uint16_t length){
    
    //Validation
    if (data == nullptr) return;
    if (length > (m_tx_end - m_tx_start)) return;
    m_buffer_bsy = true;
    
    enableAutoIncrement(false);
    setBank(0);
    
    uint16_t pnt = m_tx_start;

    for (uint16_t i = 0; i < length; i++) {
        writeLongReg(EWRPTL, EWRPTH, pnt); 
        m_spiDriver.send(0x7A);          
        m_spiDriver.send(data[i]);    
        pnt++;               
    }
   
    writeLongReg(ETXNDL, ETXNDH, pnt - 1);
    writeRegBit(ECON1, ECON1_TXRTS_Pos, 1);
    m_buffer_bsy = false;
};

uint16_t ENC28J60::receivePacket(uint8_t* data, uint16_t length, uint16_t pointer){
    //Validation
    if ((data == nullptr) || (length == 0)) return m_rx_end + 1;
    m_buffer_bsy = true;

    enableAutoIncrement(false);
    setBank(0); 
    uint16_t pnt = pointer;

    for (uint16_t i = 0; i < length; i++) {
        writeLongReg(ERDPTL, ERDPTH, pnt); 
        m_spiDriver.setCS(true);
        m_spiDriver.send(0x3A);          
        data[i] = m_spiDriver.read();
        m_spiDriver.setCS(false);    
        pnt++;
        if (pnt > m_rx_end) pnt = m_rx_start;               
    }
    m_buffer_bsy = false;
    return pnt;

};

// Multi-byte functions
void ENC28J60::sendDMAPacket(const uint8_t* data, uint16_t length){
    //Validation
    if (data == nullptr) return;
    if(length > (m_tx_end - m_tx_start)) return;
    m_buffer_bsy = true;
    enableAutoIncrement(true);
    setBank(0);
    m_spiDriver.setCS(true);
    m_spiDriver.send(0x7a);
    m_spiDriver.transmit(data, length);
};

void ENC28J60::receiveDMAPacket(uint8_t* data, uint16_t length, uint16_t pointer){
    //Validation
    if ((data == nullptr) || (length == 0)) return;
    m_buffer_bsy = true;

    //AutoIncrementation ON
    enableAutoIncrement(true);
    setBank(0);
    writeLongReg(ERDPTL, ERDPTH, pointer);

    m_spiDriver.setCS(true);
    m_spiDriver.send(0x3A);
    m_spiDriver.receive(data, length);
};

// Register configuration functions
void ENC28J60::writeReg(uint8_t reg, uint8_t value) {
    m_spiDriver.setCS(true);
    uint8_t opcode = reg | 0x40;              // Write opcode with register number
    m_spiDriver.send(opcode);                 // Send command
    m_spiDriver.send(value);                  // Send value
    while (!m_spiDriver.isTXE());             // Wait until transfer finish
    m_spiDriver.setCS(false);                 // Deactive CS
}

void ENC28J60::writeLongReg(uint8_t regl, uint8_t regh, uint16_t value){
    uint8_t temp = (uint8_t)(value & 0xFF);
    writeReg(regl, temp);
    temp = (uint8_t)((value >> 8) & 0xFF);
    writeReg(regh, temp);
};

void ENC28J60::writeRegBit(uint8_t reg, uint8_t pos, bool state){
    uint8_t temp = readReg(reg);
    temp &= ~(1 << pos);
    temp |= (state << pos);
    writeReg(reg, temp);
};

uint8_t ENC28J60::readReg(uint8_t reg) {
    m_spiDriver.setCS(true);
    uint8_t opcode = (0x00 | (reg & 0x1F)); // Write opcode with register number
    m_spiDriver.send(opcode);               // Send command
    uint8_t temp = m_spiDriver.read();      // Read value
    m_spiDriver.setCS(false);               // Deactive CS
    return temp;
}

uint16_t ENC28J60::readLongReg(uint8_t regl, uint8_t regh){
    uint16_t temp = (uint16_t)(readReg(regh) << 8);
    temp |= readReg(regl);
    return temp;
};

//Misc function
void ENC28J60::setBank(uint8_t bank){
    if ((bank < 4) && (bank != (m_ECON1 & ECON1_BSEL_Msk))){
        m_ECON1 &= ~(ECON1_BSEL_Msk);
        m_ECON1 |= bank << ECON1_BSEL_Pos;
        writeReg(ECON1, m_ECON1);
    }
};

uint8_t ENC28J60::checkIntStatus(){
    return readReg(EIR);
};

//Interrupts functions
    //Setting Bit EIE
void ENC28J60::enableInterrupt(uint8_t bit_pos, bool state){
    if((m_EIE & (1 << bit_pos)) != (state << bit_pos)){
        m_EIE &= ~(state << bit_pos);
        m_EIE |= (state << bit_pos);
        writeReg(EIE, m_EIE);
    }
};

    //Setting whole EIE
void ENC28J60::enableInterrupt(uint8_t value){
    if(m_EIE != value){
        m_EIE = value;
        writeReg(EIE, m_EIE);
    }
};

void ENC28J60::clearTXInterrupt(uint8_t state){
    state = ~state;
    state &= 0x2B;
    writeReg(EIR, state);
};

void ENC28J60::clearRXInterrupt(uint8_t state){
    if(state & EIR_PKTIF_Msk){
        writeReg(ECON2, m_ECON2 | ECON2_PKTDEC_Msk);
    }
};

//Enable/disable functions
void ENC28J60::enableReceive(bool state){
    if((m_ECON1 & ECON1_RXEN_Msk) != state){
        m_ECON1 &= ~(ECON1_RXEN_Msk);
        m_ECON1 |=  (state << ECON1_RXEN_Pos);
        writeReg(ECON1, m_ECON1);
    }
};

void ENC28J60::enableTransmit(bool state){
    m_ECON1 &= ~(ECON1_TXRTS_Msk);
    m_ECON1 |=  (state << ECON1_TXRTS_Pos);   
    writeReg(ECON1, m_ECON1);
    m_ECON1 &= ~(ECON1_TXRTS_Msk);
};  

void ENC28J60::enableAutoIncrement(bool state){
    
    if((m_ECON2 & ECON2_AUTOINC_Msk) != state){
        m_ECON2 &= ~(ECON2_AUTOINC_Msk);
        m_ECON2 |=  (state << ECON2_AUTOINC_Pos);
        writeReg(ECON2, m_ECON2);
    }

};  

//PHY Misc functions
void ENC28J60::waitMIIM() {
    setBank(3);
    bool status = readReg(MISTAT) & MISTAT_BUSY_Msk;
    while (status){
        status = readReg(MISTAT) & MISTAT_BUSY_Msk; 
    }
}

void ENC28J60::writePHY(uint8_t reg, uint16_t value) {
    setBank(2);
    writeReg(MIREGADR, reg);
    writeLongReg(MIWRL, MIWRH, value);
   
    volatile uint16_t time = 130; // wait 10.24us
    while(time>0){
        time --; 
    }
    waitMIIM();
}

//GPIO Functions
void ENC28J60::gpioInit(){  
    uint8_t temp = 0;  
    if (m_INT_Port == GPIOA){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        temp = 0;
    }else if (m_INT_Port == GPIOB){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        temp = 1;
    }else if (m_INT_Port == GPIOC){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        temp = 2;
    }else if (m_INT_Port == GPIOD){
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
        temp = 3;
    }

    //GPIO PIN MODE
    m_INT_Port->MODER    &=      ~(0x3 << (m_INT_Pin*2));
    m_INT_Port->PUPDR    &=      ~(0x3 << (m_INT_Pin*2));
    m_INT_Port->PUPDR    &=      (0x1 << (m_INT_Pin*2));
    
    // GPIO INTERRUPTS
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    if (m_INT_Pin < 4){
        SYSCFG->EXTICR[0] &= ~(0xf << m_INT_Pin*4);
        SYSCFG->EXTICR[0] |= (temp << m_INT_Pin*4);
    }else if (m_INT_Pin < 8){
        SYSCFG->EXTICR[1] &= ~(0xf << (m_INT_Pin-4)*4);
        SYSCFG->EXTICR[1] |= (temp << (m_INT_Pin-4)*4);
    }else if (m_INT_Pin < 12){
        SYSCFG->EXTICR[2] &= ~(0xf << (m_INT_Pin-8)*4);
        SYSCFG->EXTICR[2] |= (temp << (m_INT_Pin-8)*4);
    }else if (m_INT_Pin < 16){
        SYSCFG->EXTICR[3] &= ~(0xf << (m_INT_Pin-12)*4);
        SYSCFG->EXTICR[3] |= (temp << (m_INT_Pin-12)*4);
    }

    EXTI->IMR   |=  (0x1 << (m_INT_Pin));
    EXTI->RTSR  |=  (0x1 << (m_INT_Pin));
    EXTI->FTSR  |=  (0x1 << (m_INT_Pin));

    if (m_INT_Pin < 5)          NVIC_EnableIRQ((IRQn_Type)(6 + m_INT_Pin)); // EXTI0-4
    else if (m_INT_Pin < 10)    NVIC_EnableIRQ(EXTI9_5_IRQn);               // EXTI5-9
    else                        NVIC_EnableIRQ(EXTI15_10_IRQn);             // EXTI10-15

}

uint8_t ENC28J60::getINTpin(){
    return m_INT_Pin;
}

GPIO_TypeDef* ENC28J60::getINTport(){
    return m_INT_Port;
}

//Flags
void ENC28J60::clearDMARXbusy(){
    m_spiDriver.clearDMARXbusy();
    m_spiDriver.setCS(false);
};

void ENC28J60::clearDMATXbusy(){
    m_spiDriver.clearDMATXbusy();
    m_spiDriver.setCS(false);
};

void ENC28J60::clearbufferbusy(){
    m_buffer_bsy = false;
};

bool ENC28J60::isDMATXbusy(){
    return m_spiDriver.isDMATXbusy();
};

bool ENC28J60::isDMARXbusy(){
    return m_spiDriver.isDMARXbusy();
};

bool ENC28J60::isbufferbusy(){
    return m_buffer_bsy;
};
}

