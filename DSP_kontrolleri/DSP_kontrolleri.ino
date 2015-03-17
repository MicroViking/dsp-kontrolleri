#include <inttypes.h>
#include <TFTLCD.h>
#include <TouchScreen.h>
#include <Wire.h>

#define ROTATION 0;
//DSB osoitteet eri registereille
#define input1MuteOsoite 33
#define input1KompressoriOsoite 43
#define input2MuteOsoite 34
#define input2KompressoriOsoite 37
#define input3MuteOsoite 35
#define input3KompressoriOsoite 49
#define input4MuteOsoite 36
#define input4KompressoriOsoite 55
#define outputVolumeOsoite = 31 
#define outputToneOsoite = 32
#define outputVasenOsoite = 30 
#define outputOikeaOsoite = 29 
#define outputLoudnessOsoite = 64 

//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 120
#define TS_MINY 80
#define TS_MAXX 900
#define TS_MAXY 1024

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// Kosketus muuttuja
TSPoint p;

#define MINPRESSURE 10
#define MAXPRESSURE 1000

//LCD Pinnien asetukset
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
// optional
#define LCD_RESET A4


// Color definitions
#define BLACK           0x0000      /*   0,   0,   0 */
#define NAVY            0x000F      /*   0,   0, 128 */
#define DARKGREEN       0x03E0      /*   0, 128,   0 */
#define DARKCYAN        0x03EF      /*   0, 128, 128 */
#define MAROON          0x7800      /* 128,   0,   0 */
#define PURPLE          0x780F      /* 128,   0, 128 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY       0xC618      /* 192, 192, 192 */
#define DARKGREY        0x7BEF      /* 128, 128, 128 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define GREEN           0x07E0      /*   0, 255,   0 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define RED             0xF800      /* 255,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define WHITE           0xFFFF      /* 255, 255, 255 */
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define PINK            0xF81F

// TFT objekti
TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// i2c Objekti
TwoWire i2c;

//Sisääntuloasetukset
struct audioKanava {
    bool mute;
    bool kompressori;
    uint8_t bassoKoordinaatti; // Bassosliderin koordinaatti
    uint8_t diskanttiKoordinaatti;
    uint8_t balanssiKoordinaatti;
    uint8_t muteOsoite, kompressoriOsoite;  
};
//Neljä sisääntuloa
struct audioKanava channel[4];

//Ulostuloasetukset
struct ulostulo {
  bool loudness;
  uint8_t volumeKoordinaatti;
  uint8_t volumeOsoite;
  uint8_t toneOsoite;
  uint8_t vasenOsoite;
  uint8_t oikeaOsoite;
  uint8_t loudnessOsoite;
};
//Yksi ulostulo
ulostulo output;
//Mikä kanava on auki milloinkin
uint8_t currentChannel = 0;


void setup() {
  Serial.begin(9600);
  i2c.begin();
  setupVariables();
   
  tft.reset();
  tft.initDisplay();
  
  tft.setRotation(1);
  tft.fillScreen(BLUE); 
  //Tulostetaaan aloitusruutu
  teeLayout();
  pinMode(10, OUTPUT);
}

void loop() {
  ///Luetaan kosketuspiste
  int kosketus = tarkistatouch();
  switch (kosketus) {
    case 0:
      break;
    case 1:
      if (currentChannel != 0) {
        poistaKanava();
        //Päivitetään valittu kanava muuttujaan
        currentChannel = kosketus-1;
        //Väritetään kanavan tausta uudestaan
        piirraKanava(false);
      }
      break;
    case 2:
      if (currentChannel != 1) {
        poistaKanava();
        //Päivitetään valittu kanava muuttujaan
        currentChannel = kosketus-1;
        //Väritetään kanavan tausta uudestaan
        piirraKanava(false);
      }
      break; 
    case 3:
      if (currentChannel != 2) {
        poistaKanava();
        //Päivitetään valittu kanava muuttujaan
        currentChannel = kosketus-1;
        //Väritetään kanavan tausta uudestaan
        piirraKanava(false);
      }
      break;
      case 4:
      if (currentChannel != 3) {
        poistaKanava();
        //Päivitetään valittu kanava muuttujaan
        currentChannel = kosketus-1;
        //Väritetään kanavan tausta uudestaan
        piirraKanava(false);
      }
      break;
  }
  //palautaPinnit();
}
