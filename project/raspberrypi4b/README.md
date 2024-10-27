### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

DATA Pin: DATA GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(am2320 REQUIRED)
```

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
./am2320 -i

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
./am2320 -p

am2320: DATA pin connected to GPIO17(BCM).
am2320: SCL connected to GPIO3(BCM).
am2320: SDA connected to GPIO2(BCM).
```

```shell
./am2320 -t read --interface=gpio --times=3

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
am2320: read temperature and humidity.
am2320: temperature: 28.5C.
am2320: humidity: 45.9%.
am2320: temperature: 28.5C.
am2320: humidity: 45.7%.
am2320: temperature: 28.5C.
am2320: humidity: 45.6%.
am2320: read temperature.
am2320: temperature: 28.5C.
am2320: temperature: 28.4C.
am2320: temperature: 28.4C.
am2320: read humidity.
am2320: humidity: 45.3%.
am2320: humidity: 45.2%.
am2320: humidity: 45.2%.
am2320: finish read test.
```

```shell
./am2320 -e read --interface=iic --times=3

am2320: 1/3.
am2320: temperature is 28.00C.
am2320: humidity is 46.00%.
am2320: 2/3.
am2320: temperature is 28.00C.
am2320: humidity is 46.20%.
am2320: 3/3.
am2320: temperature is 28.00C.
am2320: humidity is 46.30%.
```
```shell
./am2320 -e reg1 --interface=iic --value=0x2345

am2320: set user reg1 0x2345.
```
```shell
./am2320 -e reg1 --interface=iic

am2320: get user reg1 0x2345.
```
```shell
./am2320 -e reg2 --interface=iic --value=0x6789

am2320: set user reg2 0x6789.
```
```shell
./am2320 -e reg2 --interface=iic

am2320: get user reg2 0x6789.
```
```shell
./am2320 -h

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

#### 3.3 Command Problem

1. There is some unknown problem in the iic and gpio interface of am2320 on the raspberry board, one command may try many times to run successfully or run failed.Wake up command will cause "Remote I/O error" and it is  a normal phenomenon.
