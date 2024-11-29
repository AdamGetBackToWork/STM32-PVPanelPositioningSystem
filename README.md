# Photovoltaic Panel Positioning System

Author: Adam Szajgin \
Date: 02/2024 - 06/2024 \
As part of: Microcontroller Programming University course \
Under: Warsaw University of Technology Faculty of Electronics and Infromation Technology \

> I know the name "OLED-I2C" is misleading, however i dont want to waste time on changing it...(STM32CubeIDE project name changes
tend to be difficult) it was a working name and
it will remain as such. \
> I know that the comments are in polish. I had to, sorry :(

### General Premise of the Project:

The idea was this - I was to create an embedded system project. Whatever that would be, it had to use an STM32 based controller, use at least 3 peripherals, use at least 3 different comms protocols and generally just work. 

I came up with the project of positioning system for pv panel, as at the time I was researching anthennas and radars - they often have such systems on their own. 
However they use much more complex inputs than "light" so I had to stick to the solar version for my positioning system.
So yeah, I needed motors and photoresistors, so the system could move autonomously - posistion itself to where the light
comes from. But that seemed easy, so I decided to make an improvement to the system - an ability to steer it from the phone
or the PC, via bluetooth. The list of peripherals extended, but I also had to be able to switch between the states of the system, 
so i needed a button and a screen to change and display the state of the system. Therefore, the system would have to positioning
states - automatic - solar positioning algorithm, and bluetooth - manual positioning.

So I had to start with the uC, I chose the STM32 Nucleo L073RZT6, as it was cheap, used little power, and had enough drivers for my intended peripherals. 

## Hardware

Let's discuss the hardware first, as to know what the f we're programming later...

### Used peripherials
- x2 Servos SG90
- x1 OLED screen
- x4 photoresistors 5-10k
- x1 monostate button (pushutton switch)
- x1 HC-06 bluetooth module

### Electronic schematics



## Software

### Project Structure

The only interesting dirs are Inc and Src. So here they are:

- Inc
  - DisplayManager.h
  - GFX.h
  - ManualSteering.h
  - SSD1306.h
  - ServoManager.h
  - SolarAlgorithm.h
  - SolarPositioningAlgorithm.h
  - adc.h
  - dataStructs.h
  - dma.h
  - font_ascii_5x7.h
  - gpio.h
  - i2c.h
  - main.h
  - stm32l0xx_it.h
  - systemStructs.h
  - tim.h
  - usart.h
-Src
  -
###  Positioning algorithms - explanation

- Manual Positioning 
  
  For this steering method I chose a way of interrupts, as they are memory efficient and predictable to handle responsibly.
  
  The HC-06 awaits signals from the device its connected to, when it receives a signal, it then sends an "interrupt req"
  to the STM32. The board, then enters the UART interrupt handler - "listening" to incoming signals. It collects the received
  signal, assigns it to a uint8_t "rxData", and processes it accordingly in the ManualSteering(...) function.
  The fun part is the assignment of "rxData", as the HC-06 sends everything according to the ASCII table, I had to "code n
  decode" the signals. So from the android app i made, whenever i pressed a button, it was sending via the bluetooth pipe
  the assigned letter, e.g when i pressed position 1 (maximum top position) it was sending letter "N" - ASCII 78. Then,
  when it arrived to the uC it was decoded from 78 to N, and the servos were positioned accordingly.

- Solar Positioning Algorithm 

  Again, using interrupts, this time from timer TIM2, the ADC was enabled. Unfortunately, the L073RZT6 has ONLY 1 ADC...
  so i had to use multiple channels of it. But again, it had no way of accessing the multiple channels separately
  (cheap stuff ik), so I had to iterate through all of them in a single interrupt and asses read values from ADC to uint16_t
  variables using DMA. It was harder than it sounds and took me ages.

  Those stored values were then compared in the solarPositioningAlgorithm(...), and the position variables were incremented
  or decremented, according to the result of comparison algorithms. Then the servos were positioned accordingly to those position
  variables.

### Data structures

#### file systemStructs.h
Contains definitions of the structures used in the system to store ADC results system state and v/h angles. 

##### Contents
- **ADCResults**: Structure for storing measurement results from four ADC sensors.
- **SystemState**: Structure for storing the current state of the system, including reception states, positioning, and angle settings.

##### Structures

###### ADCResults
The `ADCResults` structure is used to store the results from the Analog-to-Digital Converter (ADC). It includes the following fields:

- `volatile uint16_t lux`: Light intensity value from the main sensor.
- `volatile uint16_t lux1`: Light intensity value from the first additional sensor.
- `volatile uint16_t lux2`: Light intensity value from the second additional sensor.
- `volatile uint16_t lux3`: Light intensity value from the third additional sensor.

###### SystemState
The `SystemState` structure is used to store the current state of the system. It includes the following fields:

- `char receivingState`: Data reception state.
- `char positioningState`: Positioning state.
- `int stateMemory[2]`: System state memory (two elements).
- `int verticalAngle`: Vertical angle of the system.
- `int horizontalAngle`: Horizontal angle of the system.

---

#### file dataStructs.h
Contains definitions of the structures used in the system to store sensor data and servo angles. 

##### Contents
- **SensorData**: Structure for storing measurement results from four ADC channels.
- **ServoAngles**: Structure for storing the current angles of the servos.

##### Structures

###### SensorData
The `SensorData` structure is used to store measurement results from sensors (four ADC channels). It includes the following field:

- `uint16_t adcResults[4]`: Array of ADC results (four channels).

###### ServoAngles
The `ServoAngles` structure is used to store the angles of the servos. It includes the following fields:

- `int horizontalAngle`: Horizontal angle of the servo.
- `int verticalAngle`: Vertical angle of the servo.

### Protocols

  - UART: for communication between HC-06 and the STM32, only one way tho, from the HC-06 to the board, no need for vice-versa
  - I2C: for communication with the OLED screen. Of course using DMA.
  - PWM: for servo steering using width modulation






