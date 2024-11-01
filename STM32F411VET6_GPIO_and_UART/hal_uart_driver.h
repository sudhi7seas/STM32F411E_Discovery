// hal_uart_driver.h

#ifndef HAL_UART_DRIVER_H
#define HAL_UART_DRIVER_H

// Function declarations for UART
void uart_init(void);
void uart_send_string(const char *str);
void uart_receive_string(char *buffer, int max_len);

#endif  // HAL_UART_DRIVER_H
