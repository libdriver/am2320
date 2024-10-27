[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AM2320

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/am2320/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AM2320數位溫濕度感測器是一款含有己校準數位信號輸出的溫濕度複合型感測器。 採用專用的溫濕度採集科技，確保產品具有極高的可靠性與卓越的長期穩定性。 感測器包括一個電容式感濕元件和一個高精度集成測溫元件，並與一個高性能微處理器相連接。 該產品具有品質卓越、超快響應、抗干擾能力强、性價比極高等優點。 AM2320通信方式採用單匯流排、標準I2C兩種通信方式。 標準單匯流排介面，使系統集成變得簡易快捷。 超小的體積、極低的功耗，訊號傳輸距離可達20米以上，使其成為各類應用甚至最為苛刻的應用場合的最佳選擇。 I2C通信方式採用標準的通信時序，用戶可直接掛在I2C通信匯流排上，無需額外佈線，使用簡單。 兩種通信方式都採用直接輸出經溫度補償後的濕度、溫度及校驗CRC等數位資訊，用戶無需對數位輸出進行二次計算，也無需要對濕度進行溫度補償，便可得到準確的溫濕度資訊。 兩種通信方式可自由切換，用戶可自由選擇，使用方便，應該領域廣泛。 產品為4引線，連接方便，特殊封裝形式可根據用戶需求而提供。

LibDriver AM2320是LibDriver推出的AM2320全功能驅動，該驅動提供溫度、相對濕度讀取的功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver AM2320的源文件。

/interface目錄包含了LibDriver AM2320與平台無關的IIC, onewire總線模板。

/test目錄包含了LibDriver AM2320驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver AM2320編程範例。

/doc目錄包含了LibDriver AM2320離線文檔。

/datasheet目錄包含了AM2320數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC, onewire總線模板，完成指定平台的IIC, onewire總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/am2320/index.html](https://www.libdriver.com/docs/am2320/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。
