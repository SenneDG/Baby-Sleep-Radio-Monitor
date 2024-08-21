# Baby Sleep Radio Monitor
Project done for the Engineering Experience class @ Group T - Faculty of Engineering Technology / academic year 2022-23
[Full Text PDF](Baby%20Sleep%20Radio%20Monitor.pdf)


This repository contains the part needed for wireless nRF24 communication from STM8 to ESP32. Reading temperature and position from NTC and HALL sensors.

## Abstract
The Baby Radio Monitoring System (BRMS) is a device designed to address Sudden Infant Death Syndrome (SIDS), the leading cause of death for one-month- to one-year-olds. The design integrates a room temperature and sleeping position monitor since both factors are thought to increase the risk of SIDS, according to the Centers for Disease Control and Prevention. The BRMS is furthermore capable of detecting whether a baby is crying. All temperature, position, and audio data is captured at the baby’s side, processed by a microcontroller, and then sent wirelessly to the parent’s side.
The temperature monitor was built using a thermistor as its core component. An STM8S105K4 microcontroller closely measures the voltage across this temperature-dependent resistor. This way, the BRMS is capable of tracking the temperature in the baby’s room with up to 0.5 ◦C precision.

The position monitor was built using a Hall sensor as its core component. In addition, a magnet is placed onto the baby’s chest which interacts with the Hall sensor. The voltage across the sensor changes according to the magnetic field strength applied to it. Again, the STM8 records this voltage and can hence determine in which position the baby is sleeping.

For the cry detector, audio signals arriving from a microphone were processed with an ESP32-WROOM- 32 microcontroller using digital processing techniques. The cry detector achieved an 88.4% accuracy in distinguishing infant cries, showing the effectiveness of the cry detection algorithm. Whenever crying, flipping, or unsafe temperature is detected at the infant’s side of the monitor, the parent is warned through an LCD display present at their side. Hence, the BRMS is an effective baby monitoring system.

### Wireless Communication
The software needed to control the Si24R1 via STM8 was developed according the [STM8S105K4](https://www.alldatasheet.com/datasheet-pdf/pdf/933892/STMICROELECTRONICS/STM8S105K4.html) and the [nRF24](https://www.sparkfun.com/datasheets/Components/SMD/nRF24L01Pluss_Preliminary_Product_Specification_v1_0.pdf)
 datasheets. They explain the specific pinout mapping that had to be used.
| NAME           | PIN |
|----------------|-----|
| Chip Enable (CE)          | B0  | 
| Chip Select Not (CSN)            | E5  | 
| SCK        | C5 (SPI_SCK)  | 
| MOSI | C6 (SPI_MOSI) |
| MISO | C7 (SPI_MISO) |

Moreover, all 30 registers had to be set separately to the correct values specified in the nRF24 datasheet. The most important registers to make the transmission work are:

| NAME           | PIN |
|----------------|-----|
| CONFIG | 0x0A (TX), 0x0B (RX) |
| EN_AA | 0x3F |
| EN_RXADDR | 0x03 |
| SETUP_AW | 0x03 |
| RF_CH | 0x1C (channel 28) |
| RF_SETUP | 0x05 (1Mbps, -12dB) |
| STATUS | 0x0E |

The software written starts by reading the temperature and position status of the sensors at every cycle. Then, the data is transmitted to the Parent’s Module as an array value[3], which comprises the
lower byte of the temperature, the upper byte of the temperature, and a position status bit. The nR24L01 write payload() function employs the SPI interface to send the data from the STM8 to the
nRF24 module, which then transmits the data to the Parent’s Module. Following the transmission, a delay is introduced using the delay ms() function before the loop restarts.
