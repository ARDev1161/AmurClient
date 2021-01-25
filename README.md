# Client software for Amur distribution board (ADB-0.42)
This is application for communicate with robot on RPi base with [AmurClient].

## Requirements:
  1) PiGPIO - for install read: http://abyz.me.uk/rpi/pigpio/download.html
  2) CMake - for install read: https://snapcraft.io/install/cmake/raspbian
  3) Protobuf & gRPC - for install read: https://grpc.io/docs/languages/cpp/quickstart/
  4) libconfig
  5) GStreamer

## Compile AmurClient
  	git clone https://github.com/ARDev1161/AmurClient.git
	cd AmurClient
	mkdir bin && cd bin
	
	cmake -DCMAKE_BUILD_TYPE=Release \
	-DProtobuf_INCLUDE_DIR=~/.local/include \
	-DProtobuf_LIBRARY=~/.local/lib/libprotobuf.a \
	-DProtobuf_PROTOC_EXECUTABLE=~/.local/bin/protoc \
	-DProtobuf_PROTOC_LIBRARY=~/.local/lib/libprotoc.a \
	../
	
	cmake --build . -- -j4

## Sensors of Amur:
  1) Camera - OV5647
  2) Inertial sensor - MPU-9250
  3) Encoders wheel: left, right - HOA0901
  4) Encoders hand internal: left, right - HOA0901
  5) Encoders hand outter: left, right - HOA0901
  6) ADC module - ADS1115(address - 0x48)
  7) RTC module - DS3231(address - 0x68) with AT24C32(address - 0x57)
  8) Barometer - BMP-280
  9) Battery voltage

## Controls of Amur:
  1) ServoX, ServoY - MG90S
  2) Motor wheel: left, right
  3) Motor hand internal: left, right
  4) Motor hand outter: left, right

## GPIO using:
  * GPIO4   -   Data from 74HC165
  * GPIO17  -   Clk 74HC165
  * GPIO18  -   Not master reset 74HC595
  * GPIO27  -   SH/Not(LD) 74HC165
  * GPIO22  -   Clk inh 74HC165
  * GPIO23  -   Data to 74HC595
  * GPIO24  -   SHcp 74HC595
  * GPIO25  -   STcp 74HC595
  * GPIO5   -   freePin 3
  * GPIO6   -   freePin 4
  * GPIO12  -   PWM1 right
  * GPIO13  -   PWM1 left
  * GPIO19  -   freePin 1
  * GPIO16  -   Not OE 74HC595
  * GPIO26  -   freePin 2
  * GPIO20  -   PWM2 right
  * GPIO21  -   PWM2 left

### GPIO freePins header(from left to right):
    Use for LoRa(SX1278)
  1) GPIO19 - Rx enable
  2) GPIO26 - Tx enable
  3) GPIO5 - DI0
  4) GPIO6 - Reset

### SPI0 header(from up to down):
    Use for LoRa(SX1278)
  1) CE1
  2) CE0
  3) SCLK
  4) MISO
  5) MOSI

### I2C1 header(from left to right):
    Use for ADS1115
  1) Vpd
  2) SCL
  3) SDA
  4) GND

### UART0 header(from left to right):
  1) Vpd
  2) Tx
  3) Rx
  4) GND

### Voltage jumper(for peripheral devices - Vpd):
  1) Left - 3.3V
  2) Right - 5V

### 74HC595 using:
  bites trancieve in register from last to first: from 16 to 1

  (First byte - right)
  * 1bit    -   right relay
  * 2bit    -   clk2 right motor shield (Hand right motor - A2 input)
  * 3bit    -   clk1 right motor shield (Wheel right motor - A1 input)
  * 4bit    -   cnt1 right motor shield (Wheel right motor - B1 input)
  * 5bit    -   cnt2 right motor shield (Hand right motor - B2 input)
  * 6bit    -   en1 right motor shield (Wheel right motor)
  * 7bit    -   en2 right motor shield (Hand right motor)
  * 8bit    -   right LED light

  (Second byte - left)
  * 9bit    -   left relay
  * 10bit   -   clk2 left motor shield (Wheel left motor - A2 input)
  * 11bit   -   clk1 left motor shield (Hand left motor - A1 input)
  * 12bit   -   cnt1 left motor shield (Hand left motor - B1 input)
  * 13bit   -   cnt2 left motor shield (Wheel left motor - B2 input)
  * 14bit   -   en1 left motor shield (Hand left motor)
  * 15bit   -   en2 left motor shield (Wheel left motor)
  * 16bit   -   left LED light
  
### 74HC165 using:
  bites recieve by register from first to last: from 1 to 16

  (First byte - right)
  * 1bit    -   LR2B encoder (Hand outer right encoder - B signal)
  * 2bit    -   LR1B encoder (Hand internal right encoder - B signal)
  * 3bit    -   LL2B encoder (Hand outer left encoder - B signal)
  * 4bit    -   LL1B encoder (Hand internal left encoder - B signal)
  * 5bit    -   LL1A encoder (Hand internal left encoder - A signal)
  * 6bit    -   LL2A encoder (Hand outer left encoder - A signal)
  * 7bit    -   LR1A encoder (Hand internal right encoder - A signal)
  * 8bit    -   LR2A encoder (Hand outer right encoder - A signal)

  (Second byte - left)
  * 9bit    -   freeInPin
  * 10bit   -   freeInPin
  * 11bit   -   freeInPin
  * 12bit   -   freeInPin
  * 13bit   -   R1A encoder (Wheel left encoder - A signal)
  * 14bit   -   R1B encoder (Wheel left encoder - B signal)
  * 15bit   -   R2B encoder (Wheel right encoder - B signal)
  * 16bit   -   R2A encoder (Wheel right encoder - A signal)

[AmurClient]:https://github.com/ARDev1161/AmurClient
