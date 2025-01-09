#include "uart_dma.hpp"
namespace AH{
// Constructors
UART_DMA::UART_DMA() :  m_TX_busy(false), m_RX_busy(false), m_BR(9600),
                        m_UART(USART2), m_dma(DMA1), 
                        m_dma_stream_tx(DMA1_Stream6), m_dma_stream_rx(DMA1_Stream5), 
                        m_dma_channel_tx(4), m_dma_channel_rx(4),
                        m_RX_Port(GPIOA), m_RX_Pin(3), 
                        m_TX_Port(GPIOA), m_TX_Pin(2){}

UART_DMA::UART_DMA(const uartconfig& u_conf) : m_TX_busy(false), m_RX_busy(false)  {
    // UART1: PA9 (TX), PA10 (RX) lub PB6 (TX), PB7 (RX)
    bool u1_gpio_cond = (u_conf.UART == USART1 && ((u_conf.TX_Port == GPIOA && u_conf.TX_Pin == 9) || (u_conf.TX_Port == GPIOB && u_conf.TX_Pin == 6)) &&
                                                  ((u_conf.RX_Port == GPIOA && u_conf.RX_Pin == 10) ||( u_conf.RX_Port == GPIOB && u_conf.RX_Pin == 7)));

    // UART2: PA2 (TX), PA3 (RX) lub PD5 (TX), PD6 (RX)        
    bool u2_gpio_cond = (u_conf.UART == USART2 && ((u_conf.TX_Port == GPIOA && u_conf.TX_Pin == 2) || (u_conf.TX_Port == GPIOD && u_conf.TX_Pin == 5)) &&
                                                  ((u_conf.RX_Port == GPIOA && u_conf.RX_Pin == 3) ||( u_conf.RX_Port == GPIOD && u_conf.RX_Pin == 6)));
     
    // UART3: PB10 (TX), PB11 (RX) lub PC10 (TX), PC11 (RX) lub PD8 (TX), PD9 (RX)
    bool u3_gpio_cond = (u_conf.UART == USART3 && (((u_conf.TX_Port == GPIOB || u_conf.TX_Port == GPIOC)&& u_conf.TX_Pin == 10) 
                                                || (u_conf.TX_Port == GPIOD && u_conf.TX_Pin == 8)) &&
                                                (((u_conf.RX_Port == GPIOB || u_conf.RX_Port == GPIOC)&& u_conf.TX_Pin == 11) 
                                                ||( u_conf.RX_Port == GPIOD && u_conf.RX_Pin == 9)));
    
    // UART4: PA0 (TX), PA1 (RX) lub PC10 (TX), PC11 (RX)
    bool u4_gpio_cond = (u_conf.UART == UART4 && ((u_conf.TX_Port == GPIOA && u_conf.TX_Pin == 0) || (u_conf.TX_Port == GPIOC && u_conf.TX_Pin == 10)) &&
                                                  ((u_conf.RX_Port == GPIOA && u_conf.RX_Pin == 1) ||( u_conf.RX_Port == GPIOC && u_conf.RX_Pin == 11)));
    
    // UART5: PC12 (TX), PD2 (RX)
    bool u5_gpio_cond = (u_conf.UART == UART5 && ((u_conf.TX_Port == GPIOC && u_conf.TX_Pin == 12) && (u_conf.RX_Port == GPIOD && u_conf.RX_Pin == 2)));

    // UART6: PC6 (TX), PC7 (RX)
    bool u6_gpio_cond = (u_conf.UART == USART6 && ((u_conf.TX_Port == GPIOC && u_conf.TX_Pin == 6) && (u_conf.RX_Port == GPIOC && u_conf.RX_Pin == 7)));

    bool u_gpio_cond = u1_gpio_cond||u2_gpio_cond||u3_gpio_cond||u4_gpio_cond||u5_gpio_cond||u6_gpio_cond;
    
    if (u_gpio_cond){

        m_RX_Pin = u_conf.RX_Pin;
        m_RX_Port = u_conf.RX_Port;
        m_TX_Pin = u_conf.TX_Pin;
        m_TX_Port = u_conf.TX_Port;
        m_UART = u_conf.UART;           // If the validation of RX and TX ports and pins is successful, assign the struct to m-variables
    }else{
        printf("Wrong UART RX/TX GPIO");
        __disable_irq();
        while(1);
    }
    
        // UART1
        bool u1_dma_cond = (u_conf.UART == USART1 && u_conf.dma == DMA2 && u_conf.dma_channel_tx == 4 && u_conf.dma_stream_tx == 7 &&
                           (u_conf.dma_channel_rx == 4 && (u_conf.dma_stream_rx == 2 || u_conf.dma_stream_rx == 5)));
   
         // UART2
         bool u2_dma_cond  = (u_conf.UART == USART2 && u_conf.dma == DMA1 && u_conf.dma_channel_tx == 4 && u_conf.dma_stream_tx == 6 &&
                              u_conf.dma_channel_rx == 4 && u_conf.dma_stream_rx == 5);
    
        // UART3
        bool u3_dma_cond  = (u_conf.UART == USART3 && u_conf.dma == DMA1 && ((u_conf.dma_channel_tx == 4 && u_conf.dma_stream_tx == 3) || (u_conf.dma_channel_tx == 7 && u_conf.dma_stream_tx == 4))&&
                             u_conf.dma_channel_rx == 4 && u_conf.dma_stream_rx == 1);

        // UART4
        bool u4_dma_cond = (u_conf.UART == UART4 && u_conf.dma == DMA1 && u_conf.UART == UART4 && u_conf.dma_channel_tx == 4 && u_conf.dma_stream_tx == 4 &&
                            u_conf.dma_channel_rx == 4 && u_conf.dma_stream_rx == 2);

        // UART5
        bool u5_dma_cond = (u_conf.UART == UART5 && u_conf.dma == DMA1 && u_conf.dma_channel_tx == 4 && u_conf.dma_stream_tx == 7 &&
                            u_conf.dma_channel_rx == 4 && u_conf.dma_stream_rx == 0);

        // UART6
        bool u6_dma_cond = (u_conf.UART == USART6 && u_conf.dma == DMA2 && (u_conf.dma_channel_tx == 5 && (u_conf.dma_stream_tx == 6 || u_conf.dma_stream_tx == 7)) &&
                           (u_conf.dma_channel_rx == 5 && (u_conf.dma_stream_rx == 1 || u_conf.dma_stream_rx == 2)));

        bool u_dma_cond = (u1_dma_cond || u2_dma_cond || u3_dma_cond || u4_dma_cond || u5_dma_cond || u6_dma_cond);                    
    
    if(u_dma_cond){             
        m_dma_stream_tx =  (DMA_Stream_TypeDef *)((uint32_t)u_conf.dma + 0x10 + (0x18 * u_conf.dma_stream_tx));
        m_dma_stream_rx = (DMA_Stream_TypeDef *)((uint32_t)u_conf.dma + 0x10 + (0x18 * u_conf.dma_stream_rx));
        m_dma_channel_tx = u_conf.dma_channel_tx;
        m_dma_channel_rx = u_conf.dma_channel_rx;
        m_dma = u_conf.dma;                              // If the validation of DMA channels and streams is successful, assign the struct to m-variables
    }else{
        printf("Wrong DMA channel/streams");
        __disable_irq();
        while(1);
    }
    uint32_t clock = 0;
    if (m_UART == USART1) {
        clock = 90000000;
    }else{
        clock = 45000000;
    }
    if(!(clock / (u_conf.BR*32) == 0 && clock / (u_conf.BR*32) > 0xFFF)){
        m_BR = u_conf.BR;
    }else{
        printf("Wrong BaudRate");
        __disable_irq();                            // If the validation of baud rate is successful, assign struct baudrate to m_BR
        while(1);
    }

}

// Initialization
void UART_DMA::init() {
    if (m_dma == DMA1)      RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    else if (m_dma == DMA2) RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;        // Enable DMA clock

    if (m_UART == USART1)       RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    else if (m_UART == USART2)  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    else if (m_UART == USART3)  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    else if (m_UART == UART4)   RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
    else if (m_UART == UART5)   RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
    else if (m_UART == USART6)  RCC->APB2ENR |= RCC_APB2ENR_USART6EN;   // Enable UART clock


    if (m_RX_Port == GPIOA || m_TX_Port == GPIOA)       RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (m_RX_Port == GPIOB || m_TX_Port == GPIOB)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (m_RX_Port == GPIOC || m_TX_Port == GPIOC)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (m_RX_Port == GPIOD || m_TX_Port == GPIOD)  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // Enable GPIO clock
    
    // TX GPIO

    m_TX_Port->MODER &= ~(0x3 << (m_TX_Pin*2));     // Clear MODE setting
    m_TX_Port->MODER |= (0x2 << (m_TX_Pin*2));      // Output MODE

    if(m_TX_Pin < 8){
        m_TX_Port->AFR[0]    &=      ~(0xf << (m_TX_Pin*4));
        if(m_UART == USART1 ||m_UART == USART2 ||m_UART == USART3){
            m_TX_Port->AFR[0]    |=      (0x7 << (m_TX_Pin*4));
        }else{
            m_TX_Port->AFR[0]    |=      (0x8 << (m_TX_Pin*4));         // Alternate function for TX pin < 8
        }
    }else{
        m_TX_Port->AFR[1]     &=     ~(0xf << ((m_TX_Pin-8)*4));
        if(m_UART == USART1 ||m_UART == USART2 ||m_UART == USART3){
            m_TX_Port->AFR[1]    |=      (0x7 << (m_TX_Pin-8)*4);
        }else{
            m_TX_Port->AFR[1]    |=      (0x8 << (m_TX_Pin-8)*4);       // Alternate function for the rest of the pins
        }
    }

    m_TX_Port->OSPEEDR |= (0x3 << (m_TX_Pin * 2));                      // Output speed
    m_TX_Port->PUPDR |= (0x1 << (m_TX_Pin * 2));                        // Pull-up
    m_TX_Port->OTYPER &= ~(0x1 << (m_TX_Pin));                          // Output type of I/O port


    // RX GPIO
       
    m_RX_Port->MODER &= ~(0x3 << (m_RX_Pin*2));     // Clear MODE setting
    m_RX_Port->MODER |= (0x2 << (m_RX_Pin*2));      // Output MODE   

    if(m_RX_Pin < 8){
        m_RX_Port->AFR[0]    &=      ~(0xf << (m_RX_Pin*4));
        if(m_UART == USART1 ||m_UART == USART2 ||m_UART == USART3){
            m_RX_Port->AFR[0]    |=      (0x7 << (m_RX_Pin*4));
        }else{
            m_RX_Port->AFR[0]    |=      (0x8 << (m_RX_Pin*4));         // Alternate function for RX pin < 8
        }
    }else{
        m_RX_Port->AFR[1]     &=     ~(0xf << ((m_RX_Pin-8)*4));
        if(m_UART == USART1 ||m_UART == USART2 ||m_UART == USART3){
            m_RX_Port->AFR[1]    |=      (0x7 << (m_RX_Pin-8)*4);
        }else{
            m_RX_Port->AFR[1]    |=      (0x8 << (m_RX_Pin-8)*4);       // Alternate function for the rest of the pins
        }
    }
    

    m_RX_Port->OSPEEDR |= (0x3 << (m_RX_Pin * 2));                     // Output speed
    m_RX_Port->PUPDR |= (0x1 << (m_RX_Pin * 2));                       // Pull-up

    m_UART->CR1 = 0;         // Reset CR1 register

    uint32_t clock = 0;
    if (m_UART == USART1 || (m_UART == USART6)) {
        clock = 90000000;    // Static clock speeds dictated by APB1ENR and APB2ENR, specifically for UART1 and UART6 USING APB2ENR
    }else{
        clock = 45000000;
    }

    // Baud rate calculation
    uint8_t fraction;
    double usartdiv = (clock / (m_BR * 16));
    uint16_t mantissa = static_cast<uint16_t>(usartdiv);   // Decimal part of the BRR register (12 bit)

    if((usartdiv - mantissa) >= 0.5 && (static_cast<uint8_t>((usartdiv - mantissa)*16+1)<16)){
        fraction = static_cast<uint8_t>((usartdiv - mantissa)*16+1); // Overflow prevention (static cast)
    }else{
        fraction = static_cast<uint8_t>((usartdiv - mantissa)*16); // Fractional part of the BRR register (4 bit)
    }

    if(!(static_cast<uint8_t>((usartdiv - mantissa)*16+1) < 16)){
        mantissa++; // Overflow prevention (static cast)
    }

    if (mantissa == 0 || mantissa > 0xFFF) {
        printf("Wrong BR");
         __disable_irq();
        while(1);           // Baud rate verification
    }
    m_UART->BRR = mantissa << 4 | fraction;   // Inserting into BRR register after calculations
    
    //UART CR
    m_UART->CR2 = 0;
    m_UART->CR2 |= USART_CR2_STOP_1; // 2 stop bits

    
    //DMA
    m_dma_stream_tx->CR = 0;
    m_dma_stream_tx->CR |= (m_dma_channel_tx << DMA_SxCR_CHSEL_Pos);  // DMA TX channel select
    
    m_dma_stream_rx->CR = 0;
    m_dma_stream_rx->CR |= (m_dma_channel_rx << DMA_SxCR_CHSEL_Pos);  // DMA RX channel select
    
    // DMA interrupts
    IRQn_Type txIRQ = IRQnStreamType(m_dma_stream_tx);
    NVIC_EnableIRQ(txIRQ);                                // Enable interrupt in NVIC interrupt controller
    NVIC_SetPriority(txIRQ, 1);                           // Set the priority of the UART interrupt in NVIC interurpt controller
    clearTXbusy();

    IRQn_Type rxIRQ = IRQnStreamType(m_dma_stream_rx);
    NVIC_EnableIRQ(rxIRQ);                               // Enable interrupt in NVIC interrupt controller
    NVIC_SetPriority(rxIRQ, 1);                          // Set the priority of the UART interrupt in NVIC interurpt controller
    clearRXbusy();
    
    //UART ENABLE
    m_UART->CR3 |= USART_CR3_DMAT;      // DMA enable transmitter
    m_UART->CR3 |= USART_CR3_DMAR;      // DMA enable reciever
    m_UART->CR1 |= USART_CR1_UE;        // USART enable              
    m_UART->CR1 |= USART_CR1_TE;        // Transmiter enable
    m_UART->CR1 |= USART_CR1_RE;        // Reciever enable
};  

// Single byte functions
void UART_DMA::send(uint8_t data) {
    while (!((m_UART->SR)&USART_SR_TXE)){};               // Wait for TXE bit to set -> This will indicate that the buffer is empty
    m_UART->CR1 |= USART_CR1_TE;                        // Transmitter enable
    m_UART->DR = data;                                  // Send Data
}

uint8_t UART_DMA::read() {
    while (!((m_UART->SR)&USART_SR_RXNE)){};              // Wait for TXE bit to set -> This will indicate that the buffer is empty
    m_UART->CR1 |= USART_CR1_RE;                        // Reciever enable
    return static_cast <uint8_t>(m_UART -> DR);         // Revieve Data
}

// Multi-byte functions
void UART_DMA::transmit(uint8_t* txData, uint16_t size) {
    while (m_TX_busy);                                  // Wait for end of the last transmission
    m_TX_busy = true;

    m_dma_stream_tx->CR &= ~DMA_SxCR_EN;              
    while (m_dma_stream_tx->CR & DMA_SxCR_EN);          // Disable dma before configuration

    m_dma_stream_tx->M0AR = (uint32_t)txData;           // Memory address
    m_dma_stream_tx->PAR = (uint32_t)(&m_UART->DR);     // Peripherial address
    m_dma_stream_tx->NDTR = size;                       // Data length

    m_dma_stream_tx->CR |= DMA_SxCR_DIR_0;              // Direction: memory -> peripherial
    m_dma_stream_tx->CR |= DMA_SxCR_MINC;               // Memory address incrementation
    m_dma_stream_tx->CR |= DMA_SxCR_TCIE;               // Enable end-of-transfer interrupt

    m_dma_stream_tx->CR |= DMA_SxCR_EN;                 // Enable DMA again
}

void UART_DMA::receive(uint8_t* rxData, uint16_t size) {
    while (m_RX_busy);                                  // Wait for end of the last transmission
    m_RX_busy = true;

    m_dma_stream_rx->CR &= ~DMA_SxCR_EN;                
    while (m_dma_stream_rx->CR & DMA_SxCR_EN);          // Disable dma before configuration

    m_dma_stream_rx->M0AR = (uint32_t)(rxData);         // Memory address
    m_dma_stream_rx->PAR = (uint32_t)(&m_UART->DR);     // Peripherial address
    m_dma_stream_rx->NDTR = size;                       // Data length

    m_dma_stream_rx->CR &= ~DMA_SxCR_DIR;               // Direction: peripherial -> memory
    m_dma_stream_rx->CR |= DMA_SxCR_MINC;               // Memory address incrementation
    m_dma_stream_rx->CR |= DMA_SxCR_TCIE;               // Enable end-of-transfer interrupt

    //Stream Enable
    m_dma_stream_rx->CR |= DMA_SxCR_EN;                 // Enable DMA again

}

// Interrupts
void UART_DMA::enUARTint(uint8_t mode) {
        switch (mode){
    case 0:
        m_UART->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_RXNEIE);
        break;
    case 1:
        m_UART->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_RXNEIE);
        m_UART->CR1 |= USART_CR1_TXEIE;
        break;
    case 2:
        m_UART->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_RXNEIE);
        m_UART->CR1 |= USART_CR1_RXNEIE;
        break;
    case 3:
        m_UART->CR1 |= (USART_CR1_TXEIE | USART_CR1_RXNEIE);
        break;
    default:
        break;
    }
    
    if(mode < 4){
        IRQn_Type uartIRQ = NonMaskableInt_IRQn;

        if (m_UART == USART1)       uartIRQ = USART1_IRQn;
        else if (m_UART == USART2)  uartIRQ = USART2_IRQn;
        else if (m_UART == USART3)  uartIRQ = USART3_IRQn;
        else if (m_UART == UART4)   uartIRQ = UART4_IRQn;   
        else if (m_UART == UART5)   uartIRQ = UART5_IRQn;   
        else if (m_UART == USART6)  uartIRQ = USART6_IRQn;  // Enable interrupt matching to UART number
            if(mode != 0){
                NVIC_SetPriority(uartIRQ, 2);               // Set the priority of the UART interrupt in NVIC interurpt controller
                NVIC_EnableIRQ(uartIRQ);
            }else{
                NVIC_DisableIRQ(uartIRQ);
            }
    }
    
}

void UART_DMA::dma_clr_ifcr(DMA_Stream_TypeDef* stream){
    uint8_t stream_index = 0;
    DMA_TypeDef* dma;

    if ((stream == DMA1_Stream0)||(stream == DMA1_Stream1)||(stream == DMA1_Stream2)||(stream == DMA1_Stream3)||
        (stream == DMA1_Stream4)||(stream == DMA1_Stream5)||(stream == DMA1_Stream6)||(stream == DMA1_Stream7)) dma = DMA1;  // DMA1

    if ((stream == DMA2_Stream0)||(stream == DMA2_Stream1)||(stream == DMA2_Stream2)||(stream == DMA2_Stream3)||
        (stream == DMA2_Stream4)||(stream == DMA2_Stream5)||(stream == DMA2_Stream6)||(stream == DMA2_Stream7)) dma = DMA2;  // DMA2

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
    else if (stream == DMA1_Stream7 || stream == DMA2_Stream7) stream_index = 7;         // Stream index assignment
    else return; 
    
    if (stream_index < 4) {
        dma->LIFCR |= LIFCR_FLAGS[stream_index];           // Clear low interrupt flag register
    } else {
        dma->HIFCR |= HIFCR_FLAGS[stream_index - 4];       // Clear high interrupt flag register
    }
}

IRQn_Type UART_DMA::IRQnStreamType(DMA_Stream_TypeDef *dma_stream){
    //DMA1
    if      (dma_stream == DMA1_Stream0) return DMA1_Stream0_IRQn;
    else if (dma_stream == DMA1_Stream1) return DMA1_Stream1_IRQn;
    else if (dma_stream == DMA1_Stream2) return DMA1_Stream2_IRQn;
    else if (dma_stream == DMA1_Stream3) return DMA1_Stream3_IRQn;
    else if (dma_stream == DMA1_Stream4) return DMA1_Stream4_IRQn;
    else if (dma_stream == DMA1_Stream5) return DMA1_Stream5_IRQn;
    else if (dma_stream == DMA1_Stream6) return DMA1_Stream6_IRQn;
    else if (dma_stream == DMA1_Stream7) return DMA1_Stream7_IRQn;      // Stream selection for DMA1
    //DMA2
    else if (dma_stream == DMA2_Stream0) return DMA2_Stream0_IRQn;
    else if (dma_stream == DMA2_Stream1) return DMA2_Stream1_IRQn;
    else if (dma_stream == DMA2_Stream2) return DMA2_Stream2_IRQn;
    else if (dma_stream == DMA2_Stream3) return DMA2_Stream3_IRQn;
    else if (dma_stream == DMA2_Stream4) return DMA2_Stream4_IRQn;
    else if (dma_stream == DMA2_Stream5) return DMA2_Stream5_IRQn;
    else if (dma_stream == DMA2_Stream6) return DMA2_Stream6_IRQn;
    else if (dma_stream == DMA2_Stream7) return DMA2_Stream7_IRQn;      // Stream selection for DMA2
    else return NonMaskableInt_IRQn;
}

// Busy flags 
bool UART_DMA::isTXbusy(){
    return m_TX_busy;                                   // Check RX busy flag status
}

bool UART_DMA::isRXbusy(){
    return m_RX_busy;                                   // Check RX busy flag status
}

void UART_DMA::clearTXbusy(){
    while (!(m_UART->SR & USART_SR_TXE)){};
	dma_clr_ifcr(m_dma_stream_tx);
    m_TX_busy = false;                                  // Clear TX busy flag
}

void UART_DMA::clearRXbusy(){
    while ((m_UART->SR & USART_SR_RXNE)){};
	dma_clr_ifcr(m_dma_stream_tx);
    m_RX_busy = false;                                  // Clear RX Busy flag
}
//Enable/disable functions
void UART_DMA::TXdisable(){
   m_UART->CR1 &= ~USART_CR1_TE;                        // Disable transmission
}

void UART_DMA::RXdisable(){
   m_UART->CR1 &= ~USART_CR1_RE;                        // Disable reception
}

void UART_DMA::enable(){
    m_UART->CR1 |= USART_CR1_UE;                        // Enable UART
};

void UART_DMA::disable(){
    m_UART->CR1 &= ~USART_CR1_UE;                       // Disable UART
};
}
