### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

DATA Pin: PA8.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. AM2320 

#### 3.1 Command Instruction

1. Show am2320 chip and driver information.

   ```shell
   am2320 (-i | --information)
   ```

2. Show am2320 help.

   ```shell
   am2320 (-h | --help)
   ```

3. Show am2320 pin connections of the current board.

   ```shell
   am2320 (-p | --port)
   ```

4. Run am2320 read test, num means test times. 

   ```shell
   am2320 (-t read | --test=read) [--interface=<gpio | iic>] [--times=<num>]
   ```

5. Run am2320 read function, num means test times.

   ```shell
   am2320 (-e read | --example=read) [--interface=<gpio | iic>] [--times=<num>]
   ```
6. Run am2320 set reg1 function, hex is the set value and it is hex.

   ```shell
   am2320 (-e reg1 | --example=reg1) [--interface=<iic>] [--value=<hex>]
   ```

7. Run am2320 get reg1 function.

   ```shell
   am2320 (-e reg1 | --example=reg1) [--interface=<iic>]
   ```
8. Run am2320 set reg2 function, hex is the set value and it is hex.

   ```shell
   am2320 (-e reg2 | --example=reg2) [--interface=<iic>] [--value=<hex>]
   ```

9. Run am2320 get reg2 function.

   ```shell
   am2320 (-e reg2 | --example=reg2) [--interface=<iic>]
   ```

#### 3.2 Command Example

```shell
am2320 -i

am2320: chip is ASAIR AM2320.
am2320: manufacturer is ASAIR.
am2320: interface is GPIO IIC.
am2320: driver version is 1.0.
am2320: min supply voltage is 3.1V.
am2320: max supply voltage is 5.5V.
am2320: max current is 0.95mA.
am2320: max temperature is 60.0C.
am2320: min temperature is -20.0C.
```

```shell
am2320 -p

am2320: DATA pin connected to GPIOA PIN8.
am2320: IIC interface SCL connected to GPIOB PIN8.
am2320: IIC interface SDA connected to GPIOB PIN9.
```

```shell
am2320 -t read --interface=iic --times=3

am2320: chip is ASAIR AM2320.
am2320: manufacturer is ASAIR.
am2320: interface is GPIO IIC.
am2320: driver version is 1.0.
am2320: min supply voltage is 3.1V.
am2320: max supply voltage is 5.5V.
am2320: max current is 0.95mA.
am2320: max temperature is 60.0C.
am2320: min temperature is -20.0C.
am2320: start read test.
am2320: type is 0x0000.
am2320: version is 0x00.
am2320: status is 0x00.
am2320: device id is 0x00000000.
am2320: set user reg1 0xF6F7.
am2320: check reg1 ok.
am2320: set user reg2 0x934B.
am2320: check reg2 ok.
am2320: read temperature and humidity.
am2320: temperature: 28.6C.
am2320: humidity: 46.5%.
am2320: temperature: 28.6C.
am2320: humidity: 46.5%.
am2320: temperature: 28.6C.
am2320: humidity: 46.5%.
am2320: read temperature.
am2320: temperature: 28.6C.
am2320: temperature: 28.6C.
am2320: temperature: 28.6C.
am2320: read humidity.
am2320: humidity: 46.5%.
am2320: humidity: 46.5%.
am2320: humidity: 46.5%.
am2320: finish read test.
```

```shell
am2320 -e read --interface=iic --times=3

am2320: 1/3.
am2320: temperature is 28.60C.
am2320: humidity is 46.50%.
am2320: 2/3.
am2320: temperature is 28.60C.
am2320: humidity is 47.90%.
am2320: 3/3.
am2320: temperature is 28.60C.
am2320: humidity is 48.90%.
```
```shell
am2320 -e reg1 --interface=iic --value=0x2345

am2320: set user reg1 0x2345.
```
```shell
am2320 -e reg1 --interface=iic

am2320: get user reg1 0x2345.
```
```shell
am2320 -e reg2 --interface=iic --value=0x6789

am2320: set user reg2 0x6789.
```
```shell
am2320 -e reg2 --interface=iic

am2320: get user reg2 0x6789.
```
```shell
am2320 -h

Usage:
  am2320 (-i | --information)
  am2320 (-h | --help)
  am2320 (-p | --port)
  am2320 (-t read | --test=read) [--interface=<gpio | iic>] [--times=<num>]
  am2320 (-e read | --example=read) [--interface=<gpio | iic>] [--times=<num>]
  am2320 (-e reg1 | --example=reg1) [--interface=<iic>]
  am2320 (-e reg1 | --example=reg1) [--interface=<iic>] [--value=<hex>]
  am2320 (-e reg2 | --example=reg2) [--interface=<iic>]
  am2320 (-e reg2 | --example=reg2) [--interface=<iic>] [--value=<hex>]

Options:
  -e <read | reg1 | reg2>, --example=<read | reg1 | reg2>
                                  Run the driver example.
  -h, --help                      Show the help.
  -i, --information               Show the chip information.
      --interface=<gpio | iic>    Set the chip interface.([default: iic])
  -p, --port                      Display the pin connections of the current board.
  -t <read>, --test=<read>        Run the driver test.
      --times=<num>               Set the running times.([default: 3])
      --value=<hex>               Set the value[hex].([default: 0x0000])
```

