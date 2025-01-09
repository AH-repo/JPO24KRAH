#include "spi_dma.hpp"
namespace KR{
//Constructors
SPI_DMA::SPI_DMA(): m_TX_busy(false),m_RX_busy(false), 
                    m_spi(SPI1),m_dma(DMA2), m_BRpre(2),
                    m_dma_stream_tx(DMA2_Stream3), m_dma_stream_rx(DMA2_Stream2), 
                    m_dma_channel_tx(3), m_dma_channel_rx(3), 
                    m_CS_Port(GPIOA), m_CS_Pin(15),
                    m_MISO_Port(GPIOA), m_MISO_Pin(6),
                    m_MOSI_Port(GPIOA), m_MOSI_Pin(7),
                    m_SCK_Port(GPIOA), m_SCK_Pin(5) {}

SPI_DMA::SPI_DMA(const spiconfig& s_conf) : m_TX_busy(false),m_RX_busy(false) {
        //SPI VALIDATION
        if (s_conf.spi == SPI1 || s_conf.spi == SPI2 || s_conf.spi == SPI3){
            m_spi = s_conf.spi;
        }else{
            printf("Wrong SPI");
            __disable_irq();
            while(1);
        }
        //DMA VALIDATION
        if(s_conf.dma == DMA1 || s_conf.dma == DMA2){
            m_dma = s_conf.dma;
        }else{
            printf("Wrong DMA");
            __disable_irq();
            while(1); 
        }

        //DMA CHANNELS/STREAMS VALIDATION
        bool cond_s1 = (s_conf.spi == SPI1 && s_conf.dma == DMA2 && (s_conf.dma_stream_rx == 0 || s_conf.dma_stream_rx == 2) 
        && (s_conf.dma_stream_tx == 3 || s_conf.dma_stream_tx == 7) && s_conf.dma_channel_tx == 3 && s_conf.dma_channel_rx == 3);
        
        bool cond_s2 = (s_conf.spi == SPI2 && s_conf.dma == DMA1 && s_conf.dma_stream_rx == 3 
        && s_conf.dma_stream_tx == 5 && s_conf.dma_channel_tx == 0 && s_conf.dma_channel_rx == 0);
        
        bool cond_s3 = (s_conf.spi == SPI3 && s_conf.dma == DMA1 && (s_conf.dma_stream_rx == 0 || s_conf.dma_stream_rx == 2) 
        && (s_conf.dma_stream_tx == 5 || s_conf.dma_stream_tx == 6) && s_conf.dma_channel_tx == 0 && s_conf.dma_channel_rx == 0);
        
        if (cond_s1||cond_s2||cond_s3){
            m_dma_stream_tx =  (DMA_Stream_TypeDef *)((uint32_t)s_conf.dma + 0x10 + (0x18 * s_conf.dma_stream_tx));
            m_dma_stream_rx = (DMA_Stream_TypeDef *)((uint32_t)s_conf.dma + 0x10 + (0x18 * s_conf.dma_stream_rx));
            m_dma_channel_tx = s_conf.dma_channel_tx;
            m_dma_channel_rx = s_conf.dma_channel_rx;
        }else{
            printf("Wrong DMA channel/streams");
            __disable_irq();
            while(1); 
        }

        //PRESCALER VALIDATION
        if (s_conf.spi == SPI1 && s_conf.BRpre > 0 && s_conf.BRpre < 8){
            m_BRpre = s_conf.BRpre;
        }else if ((s_conf.spi == SPI2 || s_conf.spi == SPI3) && s_conf.BRpre < 8){
            m_BRpre = s_conf.BRpre;
        }else{
            printf("Wrong BoudRatePrescaler Value");
            __disable_irq();
            while(1);
        }

        //GPIO VALIDATION
        if(s_conf.CS_Port == GPIOA || s_conf.CS_Port == GPIOB || s_conf.CS_Port == GPIOC || s_conf.CS_Port == GPIOD){
            m_CS_Port = s_conf.CS_Port;
        }else{
            printf("Wrong GPIO port");
            __disable_irq();
            while(1); 
        }

        if(s_conf.CS_Pin < 16){
            m_CS_Pin = s_conf.CS_Pin;
        }else{
            printf("Wrong GPIO pin");
            __disable_irq();
            while(1); 
        }

        bool miso_condition_1 = (s_conf.spi == SPI1 && ((s_conf.MISO_Port == GPIOA && s_conf.MISO_Pin == 6) || (s_conf.MISO_Port == GPIOB && s_conf.MISO_Pin == 4)));
        bool miso_condition_2 = (s_conf.spi == SPI2 && ((s_conf.MISO_Port == GPIOC && s_conf.MISO_Pin == 2) || (s_conf.MISO_Port == GPIOB && s_conf.MISO_Pin == 14)));
        bool miso_condition_3 = (s_conf.spi == SPI3 && ((s_conf.MISO_Port == GPIOD && s_conf.MISO_Pin == 6) || (s_conf.MISO_Port == GPIOB && s_conf.MISO_Pin == 4)
                                                                                                            || (s_conf.MISO_Port == GPIOC && s_conf.MISO_Pin == 11)));

        if(miso_condition_1||miso_condition_2||miso_condition_3){
           m_MISO_Port = s_conf.MISO_Port;
           m_MISO_Pin = s_conf.MISO_Pin;
        }else{
            printf("Wrong MISO port");
            __disable_irq();
            while(1); 
        }


        bool mosi_condition_1 = (s_conf.spi == SPI1 && ((s_conf.MOSI_Port == GPIOA && s_conf.MOSI_Pin == 7) || (s_conf.MOSI_Port == GPIOB && s_conf.MOSI_Pin == 5)));
        bool mosi_condition_2 = (s_conf.spi == SPI2 && ((s_conf.MOSI_Port == GPIOC && s_conf.MOSI_Pin == 1) || (s_conf.MOSI_Port == GPIOB && s_conf.MOSI_Pin == 15)
                                                                                                            || (s_conf.MOSI_Port == GPIOC && s_conf.MOSI_Pin == 3)));
        bool mosi_condition_3 = (s_conf.spi == SPI3 && ((s_conf.MOSI_Port == GPIOD && s_conf.MOSI_Pin == 0) || (s_conf.MOSI_Port == GPIOB && s_conf.MOSI_Pin == 5)
                                                     ||(s_conf.MOSI_Port == GPIOC && s_conf.MOSI_Pin == 12) || (s_conf.MOSI_Port == GPIOC && s_conf.MOSI_Pin == 1)));


        if(mosi_condition_1||mosi_condition_2||mosi_condition_3){
           m_MOSI_Port = s_conf.MOSI_Port;
           m_MOSI_Pin = s_conf.MOSI_Pin;
        }else{
            printf("Wrong MOSI port");
            __disable_irq();
            while(1); 
        }

        bool sck_condition_1 = (s_conf.spi == SPI1 && ((s_conf.SCK_Port == GPIOA && s_conf.SCK_Pin == 5)  || (s_conf.SCK_Port == GPIOB && s_conf.SCK_Pin == 3)));
        bool sck_condition_2 = (s_conf.spi == SPI2 && ((s_conf.SCK_Port == GPIOB && s_conf.SCK_Pin == 10) || (s_conf.SCK_Port == GPIOB && s_conf.SCK_Pin == 13)
                                                    || (s_conf.SCK_Port== GPIOC && s_conf.SCK_Pin == 7)   || (s_conf.SCK_Port == GPIOD && s_conf.SCK_Pin == 3)));
        bool sck_condition_3 = (s_conf.spi == SPI3 && ((s_conf.SCK_Port== GPIOB && s_conf.SCK_Pin == 3)   || (s_conf.SCK_Port == GPIOC && s_conf.SCK_Pin == 10)));


        if(sck_condition_1||sck_condition_2||sck_condition_3){
           m_SCK_Port = s_conf.SCK_Port;
           m_SCK_Pin = s_conf.SCK_Pin;
        }else{
            printf("Wrong SCK port");
            __disable_irq();
            while(1); 
        }
      }

//Initialization
void SPI_DMA::init(){
   
    // GPIO INIT
    if(m_CS_Port == GPIOA || m_MISO_Port == GPIOA || m_MOSI_Port == GPIOA || m_SCK_Port == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    if(m_CS_Port == GPIOB || m_MISO_Port == GPIOB || m_MOSI_Port == GPIOB || m_SCK_Port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    if(m_CS_Port == GPIOC || m_MISO_Port == GPIOC || m_MOSI_Port == GPIOC || m_SCK_Port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    if(m_CS_Port == GPIOD || m_MISO_Port == GPIOD || m_MOSI_Port == GPIOD || m_SCK_Port == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // CS Default Value
    m_CS_Port->BSRR = (1 << m_CS_Pin);                          // Default CS on high

    // CS
    m_CS_Port->MODER    &=      ~(0x3 << (m_CS_Pin*2));         // Clear MODE setting
    m_CS_Port->MODER    |=      (0x1 << (m_CS_Pin*2));          // Output MODE
    m_CS_Port->OTYPER   &=      ~(0x1 << (m_CS_Pin));           // Push-Pull MODE
    m_CS_Port->OSPEEDR  |=      (0x3 << (m_CS_Pin*2));          // Fast Speed Mode
    m_CS_Port->PUPDR    &=      ~(0x3 << (m_CS_Pin*2));         // No pull-up
    
    // MISO
    m_MISO_Port->MODER    &=      ~(0x3 << (m_MISO_Pin*2));     // Clear MODE setting
    m_MISO_Port->MODER    |=      (0x2  << (m_MISO_Pin*2));     // Output Alternate MODE
    m_MISO_Port->OSPEEDR  |=      (0x3 << (m_MISO_Pin*2));      // Fast Speed Mode
    m_MISO_Port->PUPDR    &=      ~(0x3 << (m_MISO_Pin*2));     // No pull-up
    m_MISO_Port->OTYPER   &=      ~(0x1 << (m_MISO_Pin));       // Push-Pull MODE
    
    if(m_MISO_Pin < 8){
        m_MISO_Port->AFR[0]    &=      ~(0xf << (m_MISO_Pin*4));    
        m_MISO_Port->AFR[0]    |=      (0x5 << (m_MISO_Pin*4)); //
    }else{
        m_MISO_Port->AFR[1]     &=     ~(0xf << ((m_MISO_Pin-8)*4));
        m_MISO_Port->AFR[1]     |=     (0x5 << ((m_MISO_Pin-8)*4));
    }
    
    // MOSI
    m_MOSI_Port->MODER    &=      ~(0x3 << (m_MOSI_Pin*2));   // Clear MODE setting
    m_MOSI_Port->MODER    |=      (0x2  << (m_MOSI_Pin*2));    // Output Alternate MODE
    m_MOSI_Port->OSPEEDR  |=      (0x3 << (m_MOSI_Pin*2));  // Fast Speed Mode
    m_MOSI_Port->PUPDR    &=      ~(0x3 << (m_MOSI_Pin*2));   // No pull-up
    m_MOSI_Port->OTYPER   &=      ~(0x1 << (m_MOSI_Pin));     // Push-Pull MODE
    if(m_MOSI_Pin < 8){
        m_MOSI_Port->AFR[0]    &=      ~(0xf << (m_MOSI_Pin*4));
        m_MOSI_Port->AFR[0]    |=      (0x5 << (m_MOSI_Pin*4));
    }else{
        m_MOSI_Port->AFR[1]     &=     ~(0xf << ((m_MOSI_Pin-8)*4));
        m_MOSI_Port->AFR[1]     |=     (0x5 << ((m_MOSI_Pin-8)*4));
    }
    
    // SCK
    m_SCK_Port->MODER    &=      ~(0x3 << (m_SCK_Pin*2));   // Clear MODE setting
    m_SCK_Port->MODER    |=      (0x2 << (m_SCK_Pin*2));    // Output Alternate MODE
    m_SCK_Port->OSPEEDR  |=      (0x3 << (m_SCK_Pin*2));  // Fast Speed Mode
    m_SCK_Port->PUPDR    &=      ~(0x3 << (m_SCK_Pin*2));   // No pull-up
    m_SCK_Port->OTYPER   &=      ~(0x1 << (m_SCK_Pin));     // Push-Pull MODE
    if(m_SCK_Pin < 8){
        m_SCK_Port->AFR[0]    &=      ~(0xf << (m_SCK_Pin*4));
        m_SCK_Port->AFR[0]    |=      (0x5 << (m_SCK_Pin*4));
    }else{
        m_SCK_Port->AFR[1]     &=     ~(0xf << ((m_SCK_Pin-8)*4));
        m_SCK_Port->AFR[1]     |=     (0x5 << ((m_SCK_Pin-8)*4));
    }    

    // SPI INIT
    if      (m_spi == SPI1) RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    else if (m_spi == SPI2) RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    else if (m_spi == SPI3) RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

    m_spi->CR1 = SPI_CR1_MSTR   // Master
               | SPI_CR1_SSM    // Software NSS
               | SPI_CR1_SSI;   // Wewnętrzny poziom NSS = High
    m_spi->CR1 |=  (m_BRpre << SPI_CR1_BR_Pos);    // Prescaler set
    m_spi->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);  // Clock Polarity/Phase
    m_spi->CR1 |= SPI_CR1_SPE;                     // Włączenie SPI

    // DMA INIT
    if      (m_dma == DMA1) RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN ;
    else if (m_dma == DMA2) RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN ;


    // RX TX CHANNELS
    m_dma_stream_tx->CR &= ~DMA_SxCR_EN;
    m_dma_stream_tx->CR &= ~(DMA_SxCR_CHSEL);
    m_dma_stream_tx->CR |= m_dma_channel_tx << DMA_SxCR_CHSEL_Pos;
    m_dma_stream_rx->CR &= ~(DMA_SxCR_CHSEL);
    m_dma_stream_rx->CR |= m_dma_channel_rx << DMA_SxCR_CHSEL_Pos;


    // INTERRUPTS
    m_dma_stream_tx->CR |= DMA_SxCR_TCIE; 
    m_dma_stream_rx->CR |= DMA_SxCR_TCIE;
    IRQn_Type txIRQ = IRQnStreamType(m_dma_stream_tx);
    IRQn_Type rxIRQ = IRQnStreamType(m_dma_stream_rx);
    NVIC_EnableIRQ(txIRQ);
    NVIC_SetPriority(txIRQ, 2);
    NVIC_EnableIRQ(rxIRQ);
    NVIC_SetPriority(rxIRQ, 2);
    dma_clr_ifcr(m_dma_stream_tx);
    dma_clr_ifcr(m_dma_stream_rx);
}

// Single byte functions
void SPI_DMA::send(uint8_t data) {
    while ((m_spi->SR & SPI_SR_TXE) == 0);      // Wait until previous transfer finish
    *(volatile uint8_t *)&m_spi->DR = data;     // Send data

    while ((m_spi->SR & SPI_SR_RXNE) == 0);     
    while((SPI1->SR & SPI_SR_BSY_Msk) != 0);    // Wait until transfer finish

    (void)*(volatile uint8_t *)&m_spi->DR;      // Dumping recived data buffer (junk)
}

uint8_t SPI_DMA::read() {
    m_spi->DR = 0x00;                           // Send dummy byte
    while ((m_spi->SR & SPI_SR_TXE) == 0);      
    while ((m_spi->SR & SPI_SR_RXNE) == 0);     
    while((SPI1->SR & SPI_SR_BSY_Msk) != 0);    // Wait until transfer finish
    return *(volatile uint8_t *)&(m_spi->DR);   // Return recieved byte
}

// Multi-byte functions
void SPI_DMA::transmit(const uint8_t* txData, uint16_t size) {

    while (m_TX_busy);  // Wait until previous transmission done
    m_TX_busy = true;   // Set busy flag

    m_dma_stream_tx->CR &= ~DMA_SxCR_EN;
    while (m_dma_stream_tx->CR & DMA_SxCR_EN); // Turn off DMA Stream

    // DMA TX configuration
    m_dma_stream_tx->M0AR = reinterpret_cast<uint32_t>(txData);     // Memory address
    m_dma_stream_tx->PAR = reinterpret_cast<uint32_t>(&m_spi->DR);  // Peripherial address
    m_dma_stream_tx->NDTR = size;                                   // Data length

    m_dma_stream_tx->CR &= ~DMA_SxCR_DIR;
    m_dma_stream_tx->CR |= DMA_SxCR_DIR_0;  // Direction: memory -> peripherial
    m_dma_stream_tx->CR |= DMA_SxCR_MINC;   // Memory address incrementation
    m_dma_stream_tx->CR &= ~DMA_SxCR_PINC;  // Peripheral address without incrementation
    m_dma_stream_tx->CR |= DMA_SxCR_TCIE;   // Enable end-of-transfer interrupt

    m_dma_stream_tx->CR |= DMA_SxCR_EN;     // Enable DMA TX again

    setCS(true);                            // Chip-Select Active (low value)
    m_spi->CR2 |= SPI_CR2_TXDMAEN;          // Assign SPI to DMA
}

void SPI_DMA::receive(uint8_t* rxData, uint16_t size) {
    
    while (m_RX_busy);  // Wait until previous transmission done
    m_RX_busy = true;   // Set busy flag

    uint8_t txData[1] = {0x00}; // Dummy byte value

    m_dma_stream_rx->CR &= ~DMA_SxCR_EN;
    while (m_dma_stream_rx->CR & DMA_SxCR_EN); // Turn off DMA RX Stream

    m_dma_stream_tx->CR &= ~DMA_SxCR_EN;
    while (m_dma_stream_tx->CR & DMA_SxCR_EN); // Turn off DMA TX Stream

   // DMA RX configuration
    m_dma_stream_rx->M0AR = reinterpret_cast<uint32_t>(rxData);     // Memory address
    m_dma_stream_rx->PAR = reinterpret_cast<uint32_t>(&m_spi->DR);  // Peripherial address
    m_dma_stream_rx->NDTR = size;                                   // Data length

    m_dma_stream_rx->CR &= ~DMA_SxCR_DIR;                           // Direction: peripherial -> memory
    m_dma_stream_rx->CR |= DMA_SxCR_MINC;                           // Inkrementacja adresu pamięci RX
    m_dma_stream_rx->CR &= ~DMA_SxCR_PINC;                          // Peripheral address without incrementation

    // DMA TX configuration (dummy bytes)
    m_dma_stream_tx->M0AR = reinterpret_cast<uint32_t>(&txData);    // Memory address
    m_dma_stream_tx->PAR = reinterpret_cast<uint32_t>(&m_spi->DR);  // Peripherial address
    m_dma_stream_tx->NDTR = size;                                   // Data length

    m_dma_stream_tx->CR |= DMA_SxCR_DIR_0;                          // Direction: memory -> peripherial
    m_dma_stream_tx->CR &= ~DMA_SxCR_MINC;                          // Memory address without incrementation
    m_dma_stream_tx->CR &= ~DMA_SxCR_PINC;                          // Peripheral address without incrementation

    m_dma_stream_tx->CR &= ~DMA_SxCR_TCIE;                          // Disable DMA TX interrupts

    m_dma_stream_tx->CR |= DMA_SxCR_EN;                             // Enable DMA TX again         
    m_dma_stream_rx->CR |= DMA_SxCR_EN;                             // Enable DMA RX again      

    m_spi->CR2 |= (SPI_CR2_RXDMAEN | SPI_CR2_TXDMAEN);              // Assign SPI to DMA

    setCS(true);                                                    // Chip-Select Active (low value)
}

// Interrupts
void SPI_DMA::enSPIint(uint8_t mode) { 
    switch (mode){
    case 0:
        m_spi->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE);
        break;
    case 1:
        m_spi->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE);
        m_spi->CR2 |= SPI_CR2_TXEIE;
        break;
    case 2:
        m_spi->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE);
        m_spi->CR2 |= SPI_CR2_RXNEIE;
        break;
    case 3:
        m_spi->CR2 |= (SPI_CR2_TXEIE | SPI_CR2_RXNEIE);
        break;
    default:
        break;
    }
    
    if(mode < 4){
        IRQn_Type spiIRQ = NonMaskableInt_IRQn;
        if      (m_spi == SPI1) spiIRQ = SPI1_IRQn;
        else if (m_spi == SPI2) spiIRQ = SPI2_IRQn;
        else if (m_spi == SPI3) spiIRQ = SPI3_IRQn;
        if(mode != 0){
            NVIC_SetPriority(spiIRQ, 1);
            NVIC_EnableIRQ(spiIRQ);
        }else{
            NVIC_DisableIRQ(spiIRQ);
        }
    }
}

void SPI_DMA::dma_clr_ifcr(DMA_Stream_TypeDef* stream){
    uint8_t stream_index = 0;
    DMA_TypeDef* dma;

    if ((stream == DMA1_Stream0)||(stream == DMA1_Stream1)||(stream == DMA1_Stream2)||(stream == DMA1_Stream3)||
        (stream == DMA1_Stream4)||(stream == DMA1_Stream5)||(stream == DMA1_Stream6)||(stream == DMA1_Stream7)) dma = DMA1;

    if ((stream == DMA2_Stream0)||(stream == DMA2_Stream1)||(stream == DMA2_Stream2)||(stream == DMA2_Stream3)||
        (stream == DMA2_Stream4)||(stream == DMA2_Stream5)||(stream == DMA2_Stream6)||(stream == DMA2_Stream7)) dma = DMA2;

     const uint32_t LIFCR_FLAGS[4] = {
        DMA_LIFCR_CTCIF0 | DMA_LIFCR_CTEIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CFEIF0, // Stream 0
        DMA_LIFCR_CTCIF1 | DMA_LIFCR_CTEIF1 | DMA_LIFCR_CHTIF1 | DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CFEIF1, // Stream 1
        DMA_LIFCR_CTCIF2 | DMA_LIFCR_CTEIF2 | DMA_LIFCR_CHTIF2 | DMA_LIFCR_CDMEIF2 | DMA_LIFCR_CFEIF2, // Stream 2
        DMA_LIFCR_CTCIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3  // Stream 3
    };

    const uint32_t HIFCR_FLAGS[4] = {
        DMA_HIFCR_CTCIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CHTIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CFEIF4, // Stream 4
        DMA_HIFCR_CTCIF5 | DMA_HIFCR_CTEIF5 | DMA_HIFCR_CHTIF5 | DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CFEIF5, // Stream 5
        DMA_HIFCR_CTCIF6 | DMA_HIFCR_CTEIF6 | DMA_HIFCR_CHTIF6 | DMA_HIFCR_CDMEIF6 | DMA_HIFCR_CFEIF6, // Stream 6
        DMA_HIFCR_CTCIF7 | DMA_HIFCR_CTEIF7 | DMA_HIFCR_CHTIF7 | DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CFEIF7  // Stream 7
    };
    
    if      (stream == DMA1_Stream0 || stream == DMA2_Stream0) stream_index = 0;
    else if (stream == DMA1_Stream1 || stream == DMA2_Stream1) stream_index = 1;
    else if (stream == DMA1_Stream2 || stream == DMA2_Stream2) stream_index = 2;
    else if (stream == DMA1_Stream3 || stream == DMA2_Stream3) stream_index = 3;
    else if (stream == DMA1_Stream4 || stream == DMA2_Stream4) stream_index = 4; 
    else if (stream == DMA1_Stream5 || stream == DMA2_Stream5) stream_index = 5;
    else if (stream == DMA1_Stream6 || stream == DMA2_Stream6) stream_index = 6;
    else if (stream == DMA1_Stream7 || stream == DMA2_Stream7) stream_index = 7;
    else return; 
    
    if (stream_index < 4) {
        dma->LIFCR |= LIFCR_FLAGS[stream_index];
    } else {
        dma->HIFCR |= HIFCR_FLAGS[stream_index - 4];
    }
}

IRQn_Type SPI_DMA::IRQnStreamType(DMA_Stream_TypeDef *dma_stream){
    //DMA1
    if      (dma_stream == DMA1_Stream0) return DMA1_Stream0_IRQn;
    else if (dma_stream == DMA1_Stream1) return DMA1_Stream1_IRQn;
    else if (dma_stream == DMA1_Stream2) return DMA1_Stream2_IRQn;
    else if (dma_stream == DMA1_Stream3) return DMA1_Stream3_IRQn;
    else if (dma_stream == DMA1_Stream4) return DMA1_Stream4_IRQn;
    else if (dma_stream == DMA1_Stream5) return DMA1_Stream5_IRQn;
    else if (dma_stream == DMA1_Stream6) return DMA1_Stream6_IRQn;
    else if (dma_stream == DMA1_Stream7) return DMA1_Stream7_IRQn;
    //DMA2
    else if (dma_stream == DMA2_Stream0) return DMA2_Stream0_IRQn;
    else if (dma_stream == DMA2_Stream1) return DMA2_Stream1_IRQn;
    else if (dma_stream == DMA2_Stream2) return DMA2_Stream2_IRQn;
    else if (dma_stream == DMA2_Stream3) return DMA2_Stream3_IRQn;
    else if (dma_stream == DMA2_Stream4) return DMA2_Stream4_IRQn;
    else if (dma_stream == DMA2_Stream5) return DMA2_Stream5_IRQn;
    else if (dma_stream == DMA2_Stream6) return DMA2_Stream6_IRQn;
    else if (dma_stream == DMA2_Stream7) return DMA2_Stream7_IRQn;
    else return NonMaskableInt_IRQn;
}

// Busy flags 
bool SPI_DMA::isDMATXbusy(){
    return m_TX_busy;
};

bool SPI_DMA::isDMARXbusy(){
    return m_RX_busy;
};

bool SPI_DMA::isTXE(){
    return ((m_spi->SR)&SPI_SR_TXE);
};

bool SPI_DMA::isRXNE(){
   return ((m_spi->SR)&SPI_SR_RXNE);
};
 
void SPI_DMA::clearDMATXbusy(){
	while (!((m_spi->SR)&SPI_SR_TXE));  // Wait until transmit done
    if(!(m_RX_busy)){
        while ((m_spi->SR)&SPI_SR_BSY); // If RX not busy then wait until transfer finish
    }
	dma_clr_ifcr(m_dma_stream_tx);      // Clear interrupts flags
    m_TX_busy = false;                      
    if (!(m_TX_busy || m_RX_busy)) m_CS_Port->BSRR |= (1 << m_CS_Pin); // If is last transmit turn off CS
    m_spi->CR2 &= ~(SPI_CR2_TXDMAEN);   // Turn off SPI DMA assign
};

void SPI_DMA::clearDMARXbusy(){
    while (((m_spi->SR)&SPI_SR_RXNE));  // Wait until transmit done
    if((!m_TX_busy)){
        while ((m_spi->SR)&SPI_SR_BSY); // If RX not busy then wait until transfer finish
    }
    dma_clr_ifcr(m_dma_stream_rx);      // Clear interrupts flags
    m_RX_busy = false;
    if (!(m_TX_busy || m_RX_busy)) m_CS_Port->BSRR |= (1 << m_CS_Pin); // If is last transmit turn off CS
    m_spi->CR2 &= ~(SPI_CR2_TXDMAEN | SPI_CR2_RXDMAEN); // Turn off SPI DMA assign
};

//Enable/disable functions
void SPI_DMA::setCS(bool state) {
    if (state) {
        m_CS_Port->BSRR = (1 << (m_CS_Pin + 16));   // Active CS (low level)
    } else {
        m_CS_Port->BSRR = (1 << (m_CS_Pin));        // Deactivation CS (high level)
    }
}

void SPI_DMA::enable(){
    m_spi->CR1 |= SPI_CR1_SPE; // Turn on SPI
};

void SPI_DMA::disable(){
    m_spi->CR1 &= ~SPI_CR1_SPE; // Turn off SPI
};
}

