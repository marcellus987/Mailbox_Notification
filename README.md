# Mailbox Notification Device Project
Repository for my mailbox notification project. Code for transmitter and receiver are placed under separate folder. 

**<u>Note</u>:** You must clone the drivers needed for this project under "drivers" repository. This is a must until I figure out
how to group them. Or, just download each individual drivers necessary for the project. Thank you!

**<u>FYI</u>:** This project is currently ***In Progress***, I made significant changes locally before I updating this remote repository (bad habit, I know).

<hr>

## <u>Pins used (Transmitter STM32-blackpill)</u>:
### RYLR689 LoRa module:
- PA5: SCK
- PA6: MISO
- PA7: MOSI
- PA8: NSS (CS)
- PB0: RF CONTROL: RFSW_V1_PIN_POS
- PB1: RF CONTROL: RFSW_V2_PIN_POS
- PB5: BUSY
- PB8: RESET (Active-Low)
- PB9: DIO (Interrupt)

### IR beam transmitter and receiver sensor:
- PB10: IR beam receiver output.
- PB12: IR beam receiver power.
- PB13: IR beam transmitter power.

### For debug:
- PC13: User LED for debugging purposes.

<hr>

## <u>Pins used (Receiver STM32-blackpill)</u>:
### RYLR689 LoRa module:
- PA5: SCLK
- PA6: MISO
- PA7: MOSI
- PA8: NSS (CS)
- PB0: RF CONTROL: RFSW_V1_PIN_POS
- PB1: RF CONTROL: RFSW_V2_PIN_POS
- PB5: BUSY
- PB8: RESET (Active-Low)
- PB9: DIO (Interrupt)

### DS3231 (RTC module):
- PB6: SCL
- PB7: SDA

### SD-card module (SPI-based):
- PA1: CS
- PA5: SCLK
- PA6: MISO
- PA7: MOSI

### OLED Display (SPI-based):
- PA4: CS
- PA5: SCLK
- PA7: MOSI
- PB14: DC
- PB15: RESET (Active-Low)

## LED indication lights:
- PB12: Yellow LED 
- PB13: Blue LED
  
### For debug:
- PC13: User LED for debugging purposes.

<hr>

# Flow:
- **TBU**: I will update this with an image of a diagram, typing it is not easy.

<hr>

# Demo:

### Image(s):

**<u>Components:<u>**
- STM32F411CEU (blackpill): for Tx and Rx, RYLR689 LoRa module, SD card module, DS3231 RTC module, IR transmitter-receiver (Not shown, TBU), Reed switch (Normally open. Not shown, TBU) .
![Components used in this project.](/demo/images/components.jpg)

**<u>Tx/Rx devices:<u>**
![Tx and Rx Devices.](/demo/images/transmitter_receiver_device_labeled.jpg)

### Video(s):
- **TBU**: I will post a simple demonstration video here.
