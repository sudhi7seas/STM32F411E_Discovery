*** Settings ***
Library    tests\\STM32TestLibrary.py

*** Test Cases ***
Flash And Verify Firmware
    Flash Device Firmware
    Initialize Device

Test Orange LED
    Turn LED orange ON
    Sleep    1s
    Turn LED orange OFF
    Sleep    1s

Test Blue LED
    Turn LED blue ON
    Sleep    1s
    Turn LED blue OFF
    Sleep    1s

Test All LEDs Sequence
    Test All LEDs

*** Keywords ***
Sleep
    [Arguments]    ${duration}
    BuiltIn.Sleep    ${duration}
