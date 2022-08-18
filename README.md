# esp32tft24 

Использование дисплеев с параллельным интерфейсом TFT24 для ESP32

Драйвер использует библиотеку https://github.com/bitluni/ESP32Lib (в основном I2S-DMA и граф.классы)

Дисплеи с TFT24 интерфейсом распространены и вполне дешевы, но использовать их достаточно затруднительно
в виду полного отсутствия встроенной памяти  и большого количества необходимых пинов (вернее память-то
есть, но она только на одну строку).
Но если ограничить глубину цвета в выводимой информации и использовать достаточно большие резервы памяти ESP32,
то результат получается вполне неплохой. При глубине цвета в три бита (8 цветов) удается использовать двойной экранный
буфер используя конструкцию tft.clear(); <код вывода изображения> tft.show(); без артефактов и мерцания. При глубине цвета
в шесть бит (64 цвета) двойной буфер использовать не удасться, несмотря на достаточную память. Из-за особенностей 
организации IRAM в ESP32 невозможно выделить непрерывный участок для корректной работы DMA. Поэтому в этом режиме выводить изображение
немного посложнее. Но, если изображение не высокодинамичное, то можно также использовать конструкцию с очисткой экрана, как
указано выше для трехбитного цвета. Несмотря на то, что процесс отображения графического буфера
с момента инициализации идет непрерывно, нагрузка на процессор весьма невелика, так как разрабочик
ESP32Lib создал очень эффективный механизм передачи информации из памяти через IS2 интерфейс, запущенный 
в параллельном режиме, что позволяет создавать весьма динамичные сцены на экране без существенной нагрузки на процессор.

Я испытал работу с двумя типами таких дисплеев, различающиеся между собой способами синхронзации:
1.Hsync/Vsync модель LMS430HF02    разрешение 480x272, синхронизация как в VGA
2.DE - only   модель LB043WQ2-TD01 разрешение 480x272, синхронзация только сигналом DE
Примеры схем включения в папке Doc, примеры кода в папке Examples.
Для подключения дисплея можно использовать любые пины, кроме тех, которые INPUT-only(34,35,36,39)

Сразу хочу предупредить - использовать внешнюю микросхему PSRAM для буфера дисплея на получится.
И не спрашивайте почему. Потому что это espressif ))

Вполне возможно подключение и других такого рода дисплеев. Естественно сменив схему включения
и изменив тайминги в определении класса, согласно даташита на этот дисплей, согласно этому описанию:

const Mode LCD3BitI::MODE480x272(hfront,hsync,hback,pixels,vfront,vsync,vback,lines,divy,pixelclock,hpolaritynegative,vpolaritynegative);

где:

hfront             - неотображаемые пиксели в начале строки
hsync              - количество пикселей на горизонтальный синхроимпульс, включая hback
hback              - подбирается для каждой конкретной модели дисплея
pixels             - кол-во отображаемых пикселей в строке
vfront             - неотображаемые строки в начале кадра
vsync              - кол-во строк на вертикальный синхроимпульс, включая vback
vback              - подбирается для каждой конкретной модели дисплея
lines              - кол-во отображаемых строк в кадре
divy               - делитель PLLI2S (всегда ставить 1)
pixelclock         - частота PCLK (неважно - частота устанавливается в драйвере)
hpolaritynegative  - полярность горизонтального синхроимпульса
vpolaritynegative  - полярность вертикального синхроимпульса


Единственный недостаток такого рода дисплеев - высокое напряжение, необходимое для подсветки.
Но, учитывая, копеечную стоимость повышающих преобразователей, это пустяки )

Для вывода графической информации можно использовать не только все возможности, которые 
есть в библиотеке ESP32Lib, но также и все классы и граф.примитивы AdafruitGFX при помощи GFXWrapper.

Например:
```
#include <LCD6BitI.h>
#include <GfxWrapper.h>

#define R  21
#define R1 19
#define G  18
#define G1  5
#define B  17
#define B1 16
#define H  -1
#define D  15
#define C   4

LCD6BitI tft;//R2G2B2
const Mode LCD6BitI::MODE480x272(0, 48,  0, 480,  0, 14, 0, 272, 1, 0, 1, 1);
//определяем  gfx
GfxWrapper<LCD6BitI> gfx(tft, 480, 272);
void setup(){
	tft.init(tft.MODE480x272,R,R1,G,G1,B,B1,H,D,C);
}
void loop(){
  tft.clear();
  gfx.setFont(&times18pt8b);
  gfx.setTextSize(2);
  gfx.setTextColor(RGB565(GREEN),RGB565(BLACK));
  gfx.setCursor(240,45);
  gfx.print("Samples");
  delay(10000);
}
```
Макрос RGB565(встроенный) - корректор цвета из формата R2G2B2 или R1G1B1 в формат, предусмотренный в AdafruitGFX


Остальные примеры можно взять здесь: https://github.com/bitluni/ESP32Lib/tree/master/examples

Добавлю коротенькое видео с текущего моего проекта, где используется данный драйвер
в режиме шесть бит цветов:
https://youtu.be/01amlRFFrTA


