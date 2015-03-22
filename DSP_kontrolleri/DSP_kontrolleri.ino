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
#define TS_MAXY 970

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
    // Kanava kohtaiset boolean muuttujat
    bool mute;
    bool kompressori;
    
    // kanavakohtaisten slidereiden koordinaatit
    uint8_t bassoKoordinaatti; 
    uint8_t diskanttiKoordinaatti;
    uint8_t balanssiKoordinaatti;
    
    //i2c registeriosoitteet
    uint8_t muteOsoite;
    uint8_t kompressoriOsoite;
    uint8_t toneOsoite;
    
    //i2c tulostus taulukot
    uint8_t i2cTone[4];
    uint8_t i2cVasen[4];
    uint8_t i2cOikea[4];
    uint8_t i2cMute[4];
    uint8_t i2cKomp[8];
};
//Neljä sisääntuloa
struct audioKanava channel[4];

//Ulostuloasetukset
struct ulostulo {
  bool loudness;
  uint8_t volumeKoordinaatti;
  uint8_t volumeOsoite;
  uint8_t loudnessOsoite;
  //i2c tulostus taulukot
  uint8_t i2cVolume[4];
  uint8_t i2cLoud[4];
};
//Yksi ulostulo
ulostulo output;
//Mikä kanava on auki milloinkin
uint8_t currentChannel = 0;
bool boot = true;

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
  boot = false;
}

void loop() {
  ///Luetaan kosketuspiste
  int kosketus = tarkistatouch();
  switch (kosketus) {
    case 0:
        //Kaikki kanavan sisäiset funktiot palauttava nollan
        //delay(10);
        break;
    case 1:
        Serial.println("Suoritetaan tapaus 1.");
        Serial.println("Piirretaan kanava 1");
        piirraKanava(0);
        //Koska tahdotaan nopeuttaa kanavan vaihdossa piirtoaikaa tarkastetaan ovatko eri kanavien asetusarvot samat
        //ja tarvittaessa päivitetään kanavan laatikot ja sliderit
        tarkastaPiirto(0);
        //Päivitetään nykyinen kanava muuttuja
        currentChannel = 0;
        //delay(10);
        break;
    case 2:
        Serial.println("Suoritetaan tapaus 2.");
        Serial.println("Piirretaan kanava 2");
        piirraKanava(1);
        tarkastaPiirto(1);
        currentChannel = 1;
        //delay(10);
        break; 
    case 3:
        Serial.println("Suoritetaan tapaus 3.");
        Serial.println("Piirretaan kanava 3");
        piirraKanava(2);
        tarkastaPiirto(2);
        currentChannel = 2;
        //delay(10);
        break;
    case 4:
        Serial.println("Suoritetaan tapaus 4.");
        Serial.println("Piirretaan kanava 4");
        piirraKanava(3);
        tarkastaPiirto(3);
        currentChannel = 3;
        //delay(10);
        break;
  }
  
  //palautaPinnit();
  //delay(10);
}
