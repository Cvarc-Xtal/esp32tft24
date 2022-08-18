#include <LCD6BitI.h>
#include <GfxWrapper.h>


//////////////////////////////////
#define BLACK     0b000000

#define LIGHTBLUE 0b110000
#define BLUE      0b100000
#define DARKBLUE  0b010000

#define LIGHTRED  0b000011
#define RED       0b000010
#define DARKRED   0b000001

#define LIGHTGREEN 0b001100
#define GREEN      0b001000
#define DARKGREEN  0b000100

#define CYAN     0b111100
#define MAGENTA  0b110011
#define YELLOW   0b001111
#define WHITE    0b111111

//////////////////////////////
#define REDPIN    21    //
#define REDPIN1   19    //
#define GREENPIN  18    //
#define GREENPIN1  5    //
#define BLUEPIN   17    //
#define BLUEPIN1  16    //
#define HSYNCPIN  -1    //
#define DEPIN     15    //
#define CLOCKPIN   4    //

LCD6BitI tft;//R2G2B2
const Mode LCD6BitI::MODE480x272(0, 48,  0, 480,  0, 14, 0, 272, 1, 0, 1, 1); //для LB043WQ2-TD01 sync DE only
GfxWrapper<LCD6BitI> gfx(tft, 480, 272); //включение совместимости с GFX-Adafruit
/////////////////////////////////////////////////////////////////////

void show_mosaic(){
      for (int i = 0;i<100;i++){
        tft.rect(random(0,480),random(0,270),20,20,random(1,63));
        tft.circle(random(0,480),random(0,270),10,random(1,63));
      }
}



void setup()
{
 tft.init(tft.MODE480x272, REDPIN,REDPIN1,GREENPIN,GREENPIN1,BLUEPIN,BLUEPIN1,HSYNCPIN,DEPIN,CLOCKPIN);
}

void loop()
{
  tft.clear();
  show_mosaic();
  tft.show();
  delay(1000);
}
