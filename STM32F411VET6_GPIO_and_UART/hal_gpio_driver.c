#include <stdint.h>
#include "hal_gpio_driver.h"


/*************************************************************************************************************************************************************/
/*                                                                                                                                                           */
/*                     Static helper functions                                                                                                               */
/*                                                                                                                                                           */
/*************************************************************************************************************************************************************/

/**
  * @brief   Configures the mode of a pin : input, output, alternate function or analog mode
  * @param   *GPIOx : GPIO Port Base address
  * @param   pin_no : GPIO pin number
  * @param   mode   : mode to be configured
	* @retval  None
  */

static void hal_gpio_configure_pin_mode(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t mode)
{
	  GPIOx->MODER  |= (mode << ( 2 * pin_no));
	
}

/**
  * @brief   Configures the output type a pin : push-pull or open drain
  * @param   *GPIOx  : GPIO Port Base address
  * @param   pin_no  : GPIO pin number
  * @param   op_type : mode to be configured
	* @retval  None
  */

static void hal_gpio_configure_pin_otype(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t op_type)
{
		
	  GPIOx->OTYPER  |= (op_type <<  pin_no);
	
	
}


/**
  * @brief   Activates the internal pull up or pull down registers 
  * @param   *GPIOx  : GPIO Port Base address
  * @param   pin_no  : GPIO pin number
  * @param   pupd` : specifies which registers to activate
	* @retval  None
  */

static void hal_gpio_configure_pin_pupd(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t pupd)
{
	
	  GPIOx->PUPDR  |= (pupd << ( 2 * pin_no));
	
	
	
	
}


/**
  * @brief   Configures the output type a pin : push-pull or open drain
  * @param   *GPIOx  : GPIO Port Base address
  * @param   pin_no  : GPIO pin number
  * @param   speed` : mode to be configured
	* @retval  None
  */

static void hal_gpio_configure_pin_speed(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint32_t speed)
{
	
	  GPIOx->OSPEEDR  |= (speed << ( 2 * pin_no));
	
	
}




/*************************************************************************************************************************************************************/
/*                                                                                                                                                           */
/*                     Driver exposed APIs                                                                                                                   */
/*                                                                                                                                                           */
/*************************************************************************************************************************************************************/

/**
  * @brief   Initializes the gpio pin
  * @param   *GPIOx : GPIO Port Base address
  * @param   *gpio_pin_conf : Pointer to the pin conf structure sent by application
  * @retval  None
  */

void hal_gpio_init(GPIO_TypeDef *GPIOx, gpio_pin_conf_t *gpio_pin_conf)
{
	
	hal_gpio_configure_pin_mode(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->mode);
	hal_gpio_configure_pin_speed(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->speed);
	hal_gpio_configure_pin_otype(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->op_type);
	hal_gpio_configure_pin_pupd(GPIOx,gpio_pin_conf->pin, gpio_pin_conf->pull);
	
	
}

/**
  * @brief   Read a value from a given pin number
  * @param   *GPIOx : GPIO Port Base address
  * @param   pin_no : GPIO pin number
  * @retval  uint8_t: Value read
  */

uint8_t hal_gpio_read_from_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no)
{
	
	uint8_t  value;
	
	/*   Read from the IDR register then right shift by the value of pin number to get the 
	     input status value of the pin to lsb  */
	
	value = ((GPIOx->IDR >> pin_no) & 0x00000001);
	return value;
	
}

/**
  * @brief   Write a value to a given pin number
  * @param   *GPIOx : GPIO Port Base address
  * @param   pin_no : GPIO pin number
  * @param   uint8_t: Value to be written
  * @retval  None
	*/

void hal_gpio_write_to_pin(GPIO_TypeDef *GPIOx, uint16_t pin_no, uint8_t val)
{
	
	if (val)
	{
		GPIOx->ODR |= ( 1 << pin_no );
	}
	
	else
	{
		GPIOx->ODR &= ~( 1 << pin_no );
	}
	
}


/**
  * @brief   Set the alternate functionality for the given pin number
  * @param   *GPIOx : GPIO Port Base address
  * @param   pin_no : GPIO pin number
  * @param   alt_fun_value: Alternate function to be configured with
  * @retval  None
	*/
void hal_gpio_set_alt_function (GPIO_TypeDef *GPIOx, uint16_t pin_no, uint16_t alt_fun_value)
{
	
	 if (pin_no <= 7)
	 {
		 
		 GPIOx->AFR[0] |= (alt_fun_value<< (( pin_no ) * 4)); 
	 }
	
	 /*    pin_no % 8 calculates the position within AFR[1] by finding the remainder when the pin number is divided by 8. 
	  *    This ensures that the pin number is offset correctly within the second register (AFR[1]).
	  *    Example: Pin 8 should correspond to the first 4 bits of AFR[1], so pin_no % 8 = 0.
    *    Pin 9 should correspond to the second 4 bits of AFR[1], so pin_no % 8 = 1.
	  *    pin_no % 8: This ensures that the calculation wraps around to bit positions within AFR[1], starting from 0 for pin 8, up to 7 for pin 15.
    *    * 4: Since each pin requires 4 bits to represent its alternate function, multiplying by 4 ensures the correct bit-shift to place the alternate function value in the correct position.
	  */
	else 
	{
		GPIOx->AFR[1] |= (alt_fun_value<< (( pin_no % 8) * 4));
		
	}
	
}





