*** Settings ***
Library           ../libraries/STM32TestLibrary.py
Library           BuiltIn

*** Test Cases ***
Flash Firmware And Test LEDs
    [Documentation]    Flash firmware and test LED functionality
    [Tags]            flash    led    regression
    [Timeout]         5 minutes
    
    Set Binary Path     D:\\Workspace\\STM32F411E_DISCO\\STM32F411VET6_GPIO_and_UART\\Objects\\STM32F411VET6_GPIO_DRIVER.axf
    Set Programmer Path    C:\\Program Files\\STMicroelectronics\\STM32Cube\\STM32CubeProgrammer\\bin\\STM32_Programmer_CLI.exe
    Set Serial Port    COM3
    Set Serial Parameters    baudrate=115200    timeout=1    command_delay=0.5
    
    # Flash firmware with verification
    ${flash_result}=    Run Keyword And Return Status    Flash Firmware
    Run Keyword If    not ${flash_result}    Fail    Firmware flashing failed
    
    # Verify UART connection
    ${uart_result}=    Run Keyword And Return Status    Verify UART Connection
    Run Keyword If    not ${uart_result}    Fail    UART connection verification failed
    
    # Test individual LEDs first
    Test Single LED    orange    ON
    Sleep    1s
    Test Single LED    orange    OFF
    Sleep    1s
    Test Single LED    blue    ON
    Sleep    1s
    Test Single LED    blue    OFF
    Sleep    1s
    
    # Run full LED test sequence
    ${led_result}=    Run Keyword And Return Status    Test LEDs Via UART
    Run Keyword If    not ${led_result}    Fail    LED testing failed