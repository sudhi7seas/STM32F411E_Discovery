import json
import os
import serial
import time
import subprocess
from pathlib import Path

class STM32Core:
    def __init__(self, config_path=None):
        self.config = self._load_config(config_path)
        self._initialize_from_config()

    def _load_config(self, config_path=None):
        """Load configuration from JSON file."""
        if config_path is None:
            config_path = Path(__file__).parent.parent / 'config' / 'stm32_config.json'
        
        with open(config_path) as f:
            return json.load(f)

    def _initialize_from_config(self):
        """Initialize attributes from config."""
        self.binary_path = self.config['device']['binary_path']
        self.programmer_path = self.config['device']['programmer_path']
        self.serial_port = self.config['communication']['serial_port']
        self.serial_baudrate = self.config['communication']['baudrate']
        self.serial_timeout = self.config['communication']['timeout']
        self.command_delay = self.config['communication']['command_delay']
        self.retry_count = self.config['retry']['count']
        self.retry_delay = self.config['retry']['delay']

    def _send_uart_command(self, ser, command):
        """Send a command over UART with retry mechanism."""
        for attempt in range(self.retry_count):
            try:
                ser.reset_input_buffer()
                ser.reset_output_buffer()
                ser.write(f"{command}\n".encode())
                time.sleep(self.command_delay)
                response = ser.readline().decode().strip()
                
                if response == "OK":
                    return True
                    
            except serial.SerialException as e:
                if attempt == self.retry_count - 1:
                    raise
            
            time.sleep(self.retry_delay)
        
        return False

    def verify_uart_connection(self):
        """Verify UART connection is working properly."""
        with serial.Serial(self.serial_port, 
                         baudrate=self.serial_baudrate,
                         timeout=self.serial_timeout) as ser:
            ser.write(b"TEST\n")
            time.sleep(0.5)
            return bool(ser.in_waiting)

    def flash_firmware(self):
        """Flash firmware to the device."""
        command = [
            self.programmer_path,
            "-c", "port=SWD",
            "-w", self.binary_path, "0x08000000",
            "-v",
            "--start"
        ]
        
        result = subprocess.run(command, check=True, capture_output=True, text=True)
        time.sleep(3)  # Wait for device initialization
        return result.returncode == 0

    def control_led(self, led_color, action):
        """Control LED state."""
        command = f"LED_{action.upper()} {led_color.lower()}"
        
        with serial.Serial(self.serial_port, 
                         baudrate=self.serial_baudrate,
                         timeout=self.serial_timeout) as ser:
            return self._send_uart_command(ser, command)
            