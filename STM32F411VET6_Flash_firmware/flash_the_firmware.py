import subprocess
import os
import sys

def flash_stm32(binary_path, programmer_path):
    # Construct the command
    command = [
        programmer_path,
        "-c", "port=SWD",
        "-w", binary_path, "0x08000000",
        "-v",
        "--start"
    ]

    print(f"Attempting to run command: {' '.join(command)}")

    try:
        # Run the command
        result = subprocess.run(command, check=True, capture_output=True, text=True)
        print("Flashing successful!")
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print("Flashing failed!")
        print(f"Return code: {e.returncode}")
        print(f"stdout: {e.stdout}")
        print(f"stderr: {e.stderr}")
    except PermissionError:
        print("Permission denied. Try running the script as administrator.")
    except FileNotFoundError:
        print(f"Error: STM32CubeProgrammer CLI not found at {programmer_path}")
    except Exception as e:
        print(f"An unexpected error occurred: {str(e)}")

# Path to your binary file
binary_path = r"D:\Workspace\STM32F411E_DISCO\STM32F411VET6_GPIO_DRIVER\Objects\STM32F411VET6_GPIO_DRIVER.axf"

# Path to STM32CubeProgrammer CLI (adjust this path based on your installation)
programmer_path = r"C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe"

# Ensure the binary file exists
if not os.path.exists(binary_path):
    print(f"Error: Binary file not found at {binary_path}")
    sys.exit(1)

# Ensure the programmer exists
if not os.path.exists(programmer_path):
    print(f"Error: STM32CubeProgrammer CLI not found at {programmer_path}")
    sys.exit(1)

flash_stm32(binary_path, programmer_path)


