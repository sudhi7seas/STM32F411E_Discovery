
#include "led.h"
#include <string.h>

/**
  * @brief   Initializes the LEDs
  * @param   None
  * @retval  None
  */
	
void led_init(void)
{
	
	gpio_pin_conf_t led_pin_conf;
	/* enable the clock for the GPIOD port */
	
	_HAL_RCC_GPIOD_CLK_ENABLE();
	
	led_pin_conf.pin = LED_ORANGE;
  led_pin_conf.mode = GPIO_PIN_OUTPUT_MODE;
  led_pin_conf.op_type = GPIO_PIN_OP_TYPE_PUSHPULL;
  led_pin_conf.speed = GPIO_PIN_SPEED_MED;
  led_pin_conf.pull = GPIO_PIN_NO_PUSH_PULL;
  hal_gpio_init(GPIOD, &led_pin_conf);	
	
	
	led_pin_conf.pin = LED_BLUE;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_GREEN;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
	led_pin_conf.pin = LED_RED;
	hal_gpio_init(GPIOD, &led_pin_conf);
	
}

/**
  * @brief   Turns on the LED
  * @param   *GPIOx: Base address of the GPIO port
  * @param   Pin: pin number of the LED
  * @retval  None
  */

 void led_turn_on(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	
	hal_gpio_write_to_pin(GPIOx,pin,1);
}


/**
  * @brief   Turns off the LED
  * @param   *GPIOx: Base address of the GPIO port
  * @param   Pin: pin number of the LED
  * @retval  None
  */

 void led_turn_off(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	
	hal_gpio_write_to_pin(GPIOx,pin,0);
}

/**
  * @brief   Toggles the LED
  * @param   *GPIOx: Base address of the GPIO port
  * @param   Pin: pin number of the LED
  * @retval  None
  */

void led_toggle(GPIO_TypeDef *GPIOx, uint16_t pin)
{
	
	if (hal_gpio_read_from_pin(GPIOx,pin))
	{
		hal_gpio_write_to_pin(GPIOx,pin,0);
	}
	
	else
		
	{
		hal_gpio_write_to_pin(GPIOx,pin,1);
	}

}

#include "led.h"
#include "hal_uart_driver.h"  // Include the UART driver

int main(void)
{
    uint32_t i;
    char command[100];  // To store received command

    led_init();  // Initialize LEDs
    uart_init();  // Initialize UART for communication

    while (1)
    {
        // Receive command via UART
        uart_receive_string(command, sizeof(command));

        // Process the command to control LEDs
        if (strcmp(command, "LED_ON orange") == 0)
        {
            led_turn_on(GPIOD, LED_ORANGE);
            uart_send_string("OK\n");  // Send response back
        }
        else if (strcmp(command, "LED_OFF orange") == 0)
        {
            led_turn_off(GPIOD, LED_ORANGE);
            uart_send_string("OK\n");
        }
        else if (strcmp(command, "LED_ON blue") == 0)
        {
            led_turn_on(GPIOD, LED_BLUE);
            uart_send_string("OK\n");
        }
        else if (strcmp(command, "LED_OFF blue") == 0)
        {
            led_turn_off(GPIOD, LED_BLUE);
            uart_send_string("OK\n");
        }
        else
        {
            uart_send_string("UNKNOWN COMMAND\n");  // Send error for unknown commands
        }

        // Introduce a small delay to avoid flooding the UART
        for (i = 0; i < 50000; i++);
    }
}

	
	
