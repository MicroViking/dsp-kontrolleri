
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
//Palautetaan positiiveset voluumi asetukset DSP voluumin säätööön 
int8_t i2cVedin(uint8_t vedin) {
  uint8_t x;
  switch (vedin) {
    case 1: 
      x = map(channel[currentChannel].balanssiKoordinaatti, 90, 230, 0, 40);
      break;
    case 2:
      x = map(channel[currentChannel].bassoKoordinaatti, 90, 230, 0, 40);
      break;
    case 3:
      x = map(channel[currentChannel].diskanttiKoordinaatti, 90, 230, 0, 40);
      break;
  }
  if (x < 21) x = (20-x)*-1;
  else x = x-20;
  //Palautetaan negatiivisia lukuja tai positiivisä DSP:lle
  //channel[currentChannel].i2cTone[3] = x;
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
