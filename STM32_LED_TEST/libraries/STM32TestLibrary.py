import subprocess
import os
import serial
import time
from robot.api.deco import keyword
from robot.api import logger

class STM32TestLibrary:
    def __init__(self, binary_path=None, programmer_path=None, serial_port=None):
        self.binary_path = binary_path
        self.programmer_path = programmer_path
        self.serial_port = serial_port
        self.serial_baudrate = 115200
        self.serial_timeout = 1
        self.command_delay = 0.5  # Delay between commands
        self.retry_count = 3      # Number of retries for failed commands

    @keyword("Set Binary Path")
    def set_binary_path(self, binary_path):
        if not os.path.exists(binary_path):
            raise FileNotFoundError(f"Binary file not found at {binary_path}")
        self.binary_path = binary_path
        logger.info(f"Binary path set to: {binary_path}")

    @keyword
    def set_programmer_path(self, programmer_path):
        if not os.path.exists(programmer_path):
            raise FileNotFoundError(f"STM32CubeProgrammer CLI not found at {programmer_path}")
        self.programmer_path = programmer_path
        logger.info(f"Programmer path set to: {programmer_path}")

    @keyword
    def set_serial_port(self, serial_port):
        self.serial_port = serial_port
        logger.info(f"Serial port set to: {serial_port}")

    @keyword
    def set_serial_parameters(self, baudrate=115200, timeout=1, command_delay=0.5):
        """Set serial communication parameters."""
        self.serial_baudrate = baudrate
        self.serial_timeout = timeout
        self.command_delay = command_delay
        logger.info(f"Serial parameters set - Baudrate: {baudrate}, Timeout: {timeout}, Command Delay: {command_delay}")

    def _send_uart_command(self, ser, command, retries=3):
        """
        Send a command over UART with retry mechanism and detailed debugging
        """
        for attempt in range(retries):
            try:
                # Clear any pending data
                ser.reset_input_buffer()
                ser.reset_output_buffer()
                
                # Log the command being sent
                logger.debug(f"Sending command (attempt {attempt + 1}/{retries}): {command}")
                
                # Send the command
                ser.write(f"{command}\n".encode())
                
                # Wait for a moment to ensure command is processed
                time.sleep(self.command_delay)
                
                # Read the response
                response = ser.readline().decode().strip()
                logger.debug(f"Received response: '{response}'")
                
                # Read any additional data (for debugging)
                additional_data = ser.read_all()
                if additional_data:
                    logger.debug(f"Additional data received: {additional_data}")
                
                if response == "OK":
                    return True
                else:
                    logger.warn(f"Unexpected response: {response}")
                    
            except serial.SerialException as e:
                logger.error(f"Serial communication error on attempt {attempt + 1}: {e}")
                if attempt == retries - 1:
                    raise
                
            time.sleep(0.5)  # Wait before retry
        
        return False

    @keyword
    def verify_uart_connection(self):
        """Verify UART connection is working properly."""
        try:
            with serial.Serial(self.serial_port, 
                             baudrate=self.serial_baudrate,
                             timeout=self.serial_timeout) as ser:
                logger.info("Testing UART connection...")
                ser.write(b"TEST\n")
                time.sleep(0.5)
                if ser.in_waiting:
                    response = ser.readline().decode().strip()
                    logger.info(f"UART test response: {response}")
                    return True
                else:
                    logger.error("No response from device")
                    return False
        except serial.SerialException as e:
            logger.error(f"Failed to verify UART connection: {e}")
            raise

    @keyword
    def flash_firmware(self):
        """Flashes the firmware to the STM32 device."""
        if not self.binary_path or not self.programmer_path:
            raise ValueError("Binary path and programmer path must be set before flashing.")
        
        command = [
            self.programmer_path,
            "-c", "port=SWD",
            "-w", self.binary_path, "0x08000000",
            "-v",
            "--start"
        ]
        
        try:
            logger.info(f"Attempting to flash firmware: {' '.join(command)}")
            result = subprocess.run(command, check=True, capture_output=True, text=True)
            logger.info("Flashing successful!")
            logger.debug(result.stdout)
            
            # Wait for device to reset and initialize
            logger.info("Waiting for device to initialize...")
            time.sleep(3)
            return True
            
        except Exception as e:
            logger.error(f"Flashing failed: {str(e)}")
            raise

    @keyword
    def test_single_led(self, led_color, action="ON"):
        """Test a single LED with detailed feedback."""
        if not self.serial_port:
            raise ValueError("Serial port must be set before testing LED.")
        
        command = f"LED_{action.upper()} {led_color.lower()}"
        
        try:
            with serial.Serial(self.serial_port, 
                             baudrate=self.serial_baudrate,
                             timeout=self.serial_timeout) as ser:
                if self._send_uart_command(ser, command):
                    logger.info(f"Successfully turned {action} {led_color} LED")
                    return True
                else:
                    logger.error(f"Failed to turn {action} {led_color} LED")
                    return False
        except serial.SerialException as e:
            logger.error(f"Serial communication error: {e}")
            raise

    @keyword
    def test_leds_via_uart(self):
        """Tests the LEDs via UART using the previously set serial port."""
        if not self.serial_port:
            raise ValueError("Serial port must be set before testing LEDs.")

        # First verify UART connection
        self.verify_uart_connection()
        
        # Test sequence with individual commands
        test_sequence = [
            ("orange", "ON"),
            ("orange", "OFF"),
            ("blue", "ON"),
            ("blue", "OFF")
        ]
        
        for led_color, action in test_sequence:
            if not self.test_single_led(led_color, action):
                raise RuntimeError(f"Failed to {action} {led_color} LED")
            time.sleep(self.command_delay)
        
        logger.info("All LED tests completed successfully!")
        return True
    