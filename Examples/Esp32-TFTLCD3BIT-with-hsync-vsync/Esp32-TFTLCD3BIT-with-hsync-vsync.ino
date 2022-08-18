#include <LCD3BitIS.h>
#include <GfxWrapper.h>


//////////////////////////////////

uint8_t colors[8]{
    0b000000,
    0b110000,
    0b000011,
    0b001100,
    0b111100,
    0b110011,
    0b001111,
    0b111111
};

#define BLACK    0b000000
#define BLUE     0b110000
#define RED      0b000011
#define GREEN    0b001100
#define CYAN     0b111100
#define MAGENTA  0b110011
#define YELLOW   0b001111
#define WHITE    0b111111


#define REDPIN    21    //
#define GREENPIN  18    //
#define BLUEPIN   17    //
#define HSYNCPIN   2    //
#define VSYNCPIN  15    //
#define CLOCKPIN   4    //

LCD3BitIS tft; //R1G1B1
const Mode LCD3BitIS::MODE480x272(0, 54, 42, 480, 1, 2, 12, 272, 1, 0, 0, 0); //для LMS430HF02 sync Hsync/Vsync
GfxWrapper<LCD3BitIS> gfx(tft, 480, 272); //включение совместимости с GFX-Adafruit
/////////////////////////////////////////////////////////////////////

void show_mosaic(){
      for (int i = 0;i<100;i++){
        tft.rect(random(0,480),random(0,270),20,20,colors[random(1,7)]);
        tft.circle(random(0,480),random(0,270),10,colors[random(1,7)]);
      }
}



void setup()
{

 tft.setFrameBufferCount(2);//закомментировать при недостатке памяти на двойной буфер
 tft.init(tft.MODE480x272, REDPIN, GREENPIN, BLUEPIN, HSYNCPIN, VSYNCPIN, CLOCKPIN);
 //tft.init(tft.MODE480x272, REDPIN,REDPIN1,GREENPIN,GREENPIN1,BLUEPIN,BLUEPIN1,HSYNCPIN,VSYNCPIN,CLOCKPIN);
}

void loop()
{
  tft.clear();
  show_mosaic();
  tft.show();
  delay(1000);
}
