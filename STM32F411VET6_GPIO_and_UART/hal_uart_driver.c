// hal_uart_driver.c

#include "hal_uart_driver.h"
#include "stm32f411xe.h"    

// UART initialization
void uart_init(void)
{
	    // Enable UART clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    
    // Configure UART pins (assuming USART2 on PA2 and PA3)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= (7 << 8) | (7 << 12);  // AF7 for USART2

    // Configure UART
    USART2->BRR = SystemCoreClock / 115200;
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	
	
	
	
//    // Enable clock for USART2 and GPIOA
//    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  // USART2 clock enable
//    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // GPIOA clock enable

//    // Configure PA2 (TX) and PA3 (RX) for USART2
//    GPIOA->MODER |= (2 << GPIO_MODER_MODER2_Pos) | (2 << GPIO_MODER_MODER3_Pos);
//    GPIOA->AFR[0] |= (7 << (2 * 4)) | (7 << (3 * 4));  // Set AF7 (USART2) for PA2 and PA3
//  // AF7 for USART2

//    // Configure USART2 parameters (115200 baud rate, 8 data bits, no parity, 1 stop bit)
//    USART2->BRR = 0x0683;  // Baud rate 115200 (for 16 MHz clock)
//    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;  // Enable TX, RX, and USART
}

// Send a string over UART
void uart_send_string(const char *str)
{
    while (*str)
    {
        while (!(USART2->SR & USART_SR_TXE));  // Wait until TX buffer is empty
        USART2->DR = *str++;                   // Send character
    }
}

// Receive a string over UART
void uart_receive_string(char *buffer, int max_len)
{
    int i = 0;
    char ch;

    while (i < max_len - 1)  // Leave space for null terminator
    {
        while (!(USART2->SR & USART_SR_RXNE));  // Wait until data is received
        ch = USART2->DR;  // Read the received character

        if (ch == '\n' || ch == '\r')  // Stop reading at newline
            break;

        buffer[i++] = ch;  // Store received character in buffer
    }
    buffer[i] = '\0';  // Null-terminate the string
}
