
/*
  int määrittää palautusarvon tyypin. int16_t, int32_t, int8_t = -23313->235421, unsigned int = 0->3414134234, char, unsigned char, void = ei palauta mitään
  
  otaYhteys = funktion nimi ja aina ensimäinen kirjain pienellä ja lisäsanat isolla
  
  byte a jne määrittää funktiolla syötettävien parametrien tyypit.
  
  DSP SLAVE osoitteet
  
  BASE ADDRESS   CS0   R/W  SLAVE ADDRESS
  0110 10        0     0    0x68
  0110 10        0     1    0x69
  0110 10        1     0    0x6A
  0110 10        1     1    0x6B
 

*/
uint16_t mapx(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
  float result;
  float in_mi(in_min);
  float in_ma(in_max);
  float out_mi(out_min);
  float out_ma(out_max);
  float xin(x);
  result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return uint16_t(result);
}

uint8_t muunnaKoordinaatti(uint16_t k) {
 if (k <93) return 90; 
 else if (k < 102) return 97;
 else if (k < 113) return 108;
 else if (k < 123) return 118;
 else if (k < 133) return 129;
 else if (k < 144) return 139;
 else if (k < 154) return 150;
 else if (k < 165) return 160;
 else if (k < 175) return 171;
 else if (k < 186) return 181;
 else if (k < 196) return 192;
 else if (k < 207) return 202;
 else if (k < 217) return 213;
 else if (k < 228) return 223;
 else return 230;
}

void DSPkomento (uint8_t registeri, uint8_t tavut[], uint8_t lkm) {
    
   uint8_t osoite = 0x68; //DSP piirin osoite kirjoitusbitillä
   i2c.beginTransmission(osoite); // Kutsutaan DSP:tä ottamaan dataa vastaa ja ensimäinen bitti on kirjoitus
   i2c.write(registeri); // Kerrotaan DSP:lle mihen registeriin kirjoitetaan
      
   i2c.write(tavut, lkm); // Kirjoitetaan tavut  
      
   i2c.endTransmission();    // stop transmitting
    
      
}
/*TODO
  Voimakkuus sliderien i2c rajapinnan tarvitsemia funktioita. Palautettavat arvot pitää olla tavun kokoisia
*/
//Palautetaan i2c luku koordinaateista
int16_t i2cLuku(uint16_t k) {
  int16_t l;
  l = map(k, 90, 230, -20, 20);
  //if (l == 0) l = -20;
  //else if (l < 20) l = (20-l)*-1;
  //else if (l >= 20) l = l-20;
  Serial.print("i2c Luki on:  ");
  Serial.println(l);
  //Palautetaan negatiivisia lukuja tai positiivisä DSP:lle
  //channel[currentChannel].i2cTone[3] = x;
  return l;
}
//Muutetaan i2C luku koordinaateiksi
uint16_t i2cKoordinaatiksi(int16_t k) {
 uint16_t modulo, x;
 //if (k == 0) k=20;
 //else if (k == -20) k=0;
 //else k = k+20;
 modulo = k % 3;
 switch (modulo) {
   case 0:
     //if (k >0) k--;
     Serial.print("Modulo tapaus 0: ");   
     Serial.println(k);
     break;
   case 1:
     Serial.print("Modulo tapaus 1: ");  
     k--;
     Serial.println(k);
     break;
   case -1:
     Serial.print("Modulo tapaus 1: ");  
     k++;
     Serial.println(k);
     break;
   case 2:
     k++;
     Serial.print("Modulo tapaus 2 eli 3db luku:"); 
     Serial.println(k);
     break;
   case -2:
     k--;
     Serial.print("Modulo tapaus 2 eli 3db luku:"); 
     Serial.println(k);
     break;     
 }
 Serial.print("Muutettava i2c luku: ");
 Serial.println(k); 
 x = map(k, -20, 20, 90, 230);
 Serial.print("i2cK palautti koordinaatin: ");
 Serial.println(x);
 return x;
}

int8_t i2cVoimakkuus() {
  //Mapataan volumen koordinaatit DSB voluumi lukuihin
  int8_t x = map(output.volumeKoordinaatti, 25, 145, 0, 130);
  //DSB:ssä volumea voi kasvatta 10db
  if (x < 11) x = 10-x;
  //Koska volume on 0:sta -120db pitää 130 luvut pienentää 10:llä ja kertoa negatiiviseksi
  else x = (x-10)*-1;
  //Serial.print("Voimakkuus: ");
  //Serial.println(x);
  return x;
}
