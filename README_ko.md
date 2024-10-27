[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AM2320

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/am2320/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AM2320은 교정된 디지털 신호 출력을 갖춘 온도 및 습도 복합 센서입니다. 전용 RH&T 수집 기술은 높은 신뢰성과 우수한 장기 안정성을 보장합니다. 센서는 용량성 감지 소자와 고성능 마이크로프로세서에 연결된 고정밀 통합 온도 측정 소자로 구성됩니다. 제품의 통신 모드는 단일 버스 및 표준 I2C 통신 모드를 채택합니다. 표준 단일 버스 인터페이스는 시스템 통합을 빠르고 쉽게 만듭니다. I2C 통신 모드는 표준 통신 타이밍을 사용하며, 사용자는 추가 배선 없이 I2C 통신 버스에 직접 연결할 수 있으며 사용하기 쉽습니다. 두 통신 방식 모두 습도, 온도 및 CRC 확인과 같은 온도 보정 디지털 정보의 직접 출력을 사용합니다. 사용자는 디지털 출력에 대한 2차 계산을 수행할 필요가 없으며, 온도에 대한 습도를 보정할 필요도 없으므로 정확한 온도 및 습도를 얻을 수 있습니다. 두 통신 모드는 자유롭게 전환할 수 있으며, 사용자는 자유롭게 선택하여 편리하게 사용할 수 있으며, 널리 사용되어야 합니다. 본 제품은 4선으로 연결이 간편하며, 사용자 요구에 맞춰 특수 패키지 형태를 제공할 수 있습니다.

LibDriver AM2320은 LibDriver에서 출시한 AM2320의 전체 기능 드라이버입니다. 온도 및 상대 습도를 읽는 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver AM2320의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver AM2320용 플랫폼 독립적인 IIC, onewire 버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver AM2320드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver AM2320프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver AM2320오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 AM2320데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC, onewire 버스 템플릿을 참조하여 지정된 플랫폼에 대한IIC,  onewire 버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/am2320/index.html](https://www.libdriver.com/docs/am2320/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.