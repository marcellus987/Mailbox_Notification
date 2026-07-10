# Mailbox Notification Device Project
Repository for my mailbox notification project. Code for transmitter and receiver is placed under separate folder. 

**<u>Note</u>:** You must clone the drivers needed for this project under "drivers" repository. This is a must until I figure out
how to group them. Or, just download each individual drivers necessary for the project. Thank you!

**<u>FYI</u>:** This is project is currently ***In Progress***, I made significant changes locally before I updating this remote repository (bad habit, I know).

<hr>

## <u>Pins used (Transmitter STM32-blackpill)</u>:
### RYLR689 LoRa module:
- PA5: SCK
- PA6: MISO
- PA7: MOSI
- PA8: NSS (CS)
- PB0: RF CONTROL
- PB1: RF CONTROL
- PB5: BUSY
- PB6: DIO
- PB8: RESET

### IR beam transmitter and receiver sensor:
- PB10: IR beam receiver output.
- PB12: IR beam receiver power.
- PB13: IR beam transmitter power.

### For debug:
- PC13: User LED for debugging purposes.

## <u>Pins used (Receiver STM32-blackpill)</u>:
### RYLR689 LoRa module:
- PA5: SCLK
- PA6: MISO
- PA7: MOSI
- PA8: NSS (CS)
- PB0: RF CONTROL
- PB1: RF CONTROL
- PB5: BUSY
- PB6: DIO
- PB8: RESET

### DS3231 (RTC module):
- PB9: SDA
- PB10: SCL

### SD-card module (SPI-based):
- PA1: CS
- PA5: SCLK
- PA6: MISO
- PA7: MOSI

## LED indication lights:
- **TBD**
  
### For debug:
- PC13: User LED for debugging purposes.

<hr>

# Flow:
- **TBU**: I will update this with an image of a diagram, typing it is not easy.

<hr>

# Demo:
- **TBU**: I will post a simple demonstration video here.
