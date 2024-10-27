[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AM2320

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/am2320/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AM2320は、校正されたデジタル信号出力を備えた温度と湿度の複合センサーです。専用のRH＆T収集技術により、高い信頼性と優れた長期安定性が保証されます。センサーは、高性能マイクロプロセッサに接続された静電容量センシング素子と高精度統合温度測定素子で構成されています。製品の通信モードは、シングルバスと標準I2C通信モードを採用しています。標準のシングルバスインターフェイスにより、システム統合が迅速かつ容易になります。I2C通信モードは標準の通信タイミングを使用し、ユーザーは追加の配線なしでI2C通信バスに直接接続でき、使いやすいです。どちらの通信方法も、湿度、温度、チェックCRCなどの温度補償されたデジタル情報の直接出力を使用します。ユーザーはデジタル出力に対して二次計算を実行する必要がなく、湿度を温度に補正する必要もありません。そのため、正確な温度と湿度が得られます。2つの通信モードは自由に切り替えることができ、ユーザーは自由に選択して便利に使用でき、広く使用されるはずです。この製品は4リードで接続が容易であり、ユーザーのニーズに応じて特別なパッケージ形式を提供できます。

LibDriver AM2320は、LibDriverによって起動されたAM2320の全機能ドライバーであり、温度と相対湿度を読み取る機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AM2320のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AM2320用のプラットフォームに依存しないIIC, onewireバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AM2320ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AM2320プログラミング例が含まれています。

/ docディレクトリには、LibDriver AM2320オフラインドキュメントが含まれています。

/ datasheetディレクトリには、AM2320データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIIC, onewireバステンプレートを参照して、指定したプラットフォームのIIC, onewireバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/am2320/index.html](https://www.libdriver.com/docs/am2320/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。