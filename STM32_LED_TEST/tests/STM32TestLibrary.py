from robot.api.deco import keyword
from robot.api import logger
from libraries.STM32Core import STM32Core

class STM32TestLibrary:
    """Robot Framework test library for STM32 LED testing."""
    
    def __init__(self, config_path=None):
        self.core = STM32Core(config_path)

    @keyword("Initialize Device")
    def initialize_device(self):
        """Initialize the device and verify communication."""
        try:
            if not self.core.verify_uart_connection():
                raise RuntimeError("Failed to establish UART connection")
            logger.info("Device initialization successful")
            return True
        except Exception as e:
            logger.error(f"Device initialization failed: {e}")
            raise

    @keyword("Flash Device Firmware")
    def flash_firmware(self):
        """Flash the firmware to the device."""
        try:
            if self.core.flash_firmware():
                logger.info("Firmware flashed successfully")
                return True
            raise RuntimeError("Firmware flashing failed")
        except Exception as e:
            logger.error(f"Firmware flashing failed: {e}")
            raise

    @keyword("Turn LED ${color} ${action}")
    def control_led(self, color, action):
        """Control LED state with specified color and action."""
        try:
            if self.core.control_led(color, action):
                logger.info(f"Successfully turned {action} {color} LED")
                return True
            raise RuntimeError(f"Failed to turn {action} {color} LED")
        except Exception as e:
            logger.error(f"LED control failed: {e}")
            raise

    @keyword("Test All LEDs")
    def test_all_leds(self):
        """Test all LEDs in sequence."""
        test_sequence = [
            ("orange", "ON"),
            ("orange", "OFF"),
            ("blue", "ON"),
            ("blue", "OFF")
        ]
        
        for color, action in test_sequence:
            if not self.control_led(color, action):
                raise RuntimeError(f"Failed to {action} {color} LED")
            
        logger.info("All LED tests completed successfully")
        return True
    