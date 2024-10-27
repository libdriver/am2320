[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AM2320

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/am2320/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AM2320 is a temperature and humidity composite sensor with a calibrated digital signal output. Dedicated RH&T gathering technology ensures high reliability and excellent long-term stability. The sensor consists of a capacitive sensing element and a high precision integrated temperature measuring element connected to a high performance microprocessor. The communication mode of the product adopts single bus and standard I2C communication modes. The standard single bus interface makes system integration quick and easy. The I2C communication mode uses standard communication timing, and the user can directly hang on the I2C communication bus without additional wiring and is easy to use. Both communication methods use direct output of temperature-compensated digital information such as humidity, temperature and check CRC. The user does not need to perform secondary calculation on the digital output, nor does it need to compensate the humidity for temperature, so that accurate temperature and humidity can be obtained. The two communication modes can be switched freely, and the user can freely choose and use it conveniently, and it should be widely used. The product is 4-lead, easy to connect, and the special package form can be provided according to user needs.

LibDriver AM2320 is the full function driver of AM2320 launched by LibDriver.It provides the function of reading temperature and relative humidity. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver AM2320 source files.

/interface includes LibDriver AM2320 IIC, onewire platform independent template.

/test includes LibDriver AM2320 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver AM2320 sample code.

/doc includes LibDriver AM2320 offline document.

/datasheet includes AM2320 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC, onewire platform independent template and finish your platform IIC, onewire driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_am2320_basic.h"

uint8_t res;
uint32_t i;
float temperature;
float humidity;

/* init */
res = am2320_basic_init(AM2320_INTERFACE_IIC);
if (res != 0)
{
    return 1;
}

/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 2000ms */
    am2320_interface_delay_ms(2000);

    /* read data */
    res = am2320_basic_read((float *)&temperature, (float *)&humidity);
    if (res != 0)
    {
        (void)am2320_basic_deinit();

        return 1;
    }

    /* output */
    am2320_interface_debug_print("am2320: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)3);
    am2320_interface_debug_print("am2320: temperature is %0.2fC.\n", temperature);
    am2320_interface_debug_print("am2320: humidity is %0.2f%%.\n", humidity); 
}

/* deinit */
(void)am2320_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/am2320/index.html](https://www.libdriver.com/docs/am2320/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.