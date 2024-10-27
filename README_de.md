[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AM2320
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/am2320/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

AM2320 ist ein Temperatur- und Feuchtigkeitsverbundsensor mit einem kalibrierten digitalen Signalausgang. Die dedizierte RH&T-Erfassungstechnologie sorgt für hohe Zuverlässigkeit und hervorragende Langzeitstabilität. Der Sensor besteht aus einem kapazitiven Sensorelement und einem hochpräzisen integrierten Temperaturmesselement, das an einen Hochleistungsmikroprozessor angeschlossen ist. Der Kommunikationsmodus des Produkts verwendet Einzelbus- und Standard-I2C-Kommunikationsmodi. Die Standard-Einzelbusschnittstelle macht die Systemintegration schnell und einfach. Der I2C-Kommunikationsmodus verwendet Standardkommunikationstaktung, und der Benutzer kann sich ohne zusätzliche Verkabelung direkt an den I2C-Kommunikationsbus anschließen und ist einfach zu verwenden. Beide Kommunikationsmethoden verwenden die direkte Ausgabe temperaturkompensierter digitaler Informationen wie Feuchtigkeit, Temperatur und überprüfen CRC. Der Benutzer muss keine sekundären Berechnungen am digitalen Ausgang durchführen und auch keine Feuchtigkeitskompensation für die Temperatur durchführen, sodass genaue Temperatur- und Feuchtigkeitswerte ermittelt werden können. Die beiden Kommunikationsmodi können frei umgeschaltet werden, und der Benutzer kann sie frei wählen und bequem verwenden, und sie sollten weit verbreitet sein. Das Produkt ist 4-adrig, einfach anzuschließen und die spezielle Verpackungsform kann je nach Benutzeranforderungen bereitgestellt werden.

LibDriver AM2320 ist der voll funktionsfähige Treiber von AM2320, der von LibDriver gestartet wurde. Er bietet die Funktion zum Lesen von Temperatur und relativer Luftfeuchtigkeit. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver AM2320-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver AM2320 IIC, onewire.

/test enthält den Testcode des LibDriver AM2320-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver AM2320-Beispielcode.

/doc enthält das LibDriver AM2320-Offlinedokument.

/Datenblatt enthält AM2320-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC, onewire-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC, onewire-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/am2320/index.html](https://www.libdriver.com/docs/am2320/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.