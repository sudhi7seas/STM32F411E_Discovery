
#include "led.h"

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

int main(void)
		
{
	uint32_t i;
		
	led_init();
		
	while(1)
	{
			
	 led_turn_on(GPIOD,LED_ORANGE);
	 led_turn_on(GPIOD,LED_BLUE);
			
	 for(i=0;i<500000;i++);
			
	 led_turn_off(GPIOD,LED_ORANGE);
	 led_turn_off(GPIOD,LED_BLUE);
			
	 for(i=0;i<500000;i++);
			
	}
		
		
}
	
	
