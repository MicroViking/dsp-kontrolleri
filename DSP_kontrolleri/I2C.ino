
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

void sendDSPcommand (uint8_t registeri, uint8_t value) {
    uint8_t osoite = 0x69; //DSP piirin osoite kirjoitusbitillä
    i2c.beginTransmission(osoite); // Kutsutaan DSP:tä ottamaan dataa vastaa ja ensimäinen bitti on kirjoitus
    i2c.write(registeri);        // Kerrotaan DSP:lle mihen registeriin kirjoitetaan
    i2c.write(value);              // Kirjoitetaan valituun regeisteriin   
    i2c.endTransmission();    // stop transmitting
    delay(1);   
  }
/*TODO
  Voimakkuus sliderien i2c rajapinnan tarvitsemia funktioita. Palautettavat arvot pitää olla tavun kokoisia
*/
//Palautetaan positiiveset voluumi asetukset DSP voluumin säätööön 
uint8_t getOikeaVoimakkuus (uint8_t i) {
  uint8_t balanssi = channel[currentChannel].balanssiKoordinaatti;
  balanssi = map(balanssi, 75, 245, -100, 100);
  if (balanssi >= 0) return 0;
  //koska luvut ovat negatiivisia niin pitää lisätä balanssin arvo 100 jolloin luku hiipuu sadasta kohti nollaa.
  else return 100 + balanssi;
}
uint8_t getVasenVoimakkuus (uint8_t i) {
  uint8_t balanssi = channel[currentChannel].balanssiKoordinaatti;
  balanssi = map(balanssi, 75, 245, -100, 100);
  if (balanssi <= 0) return 0;
  //Koska luvut ovat postiivisia niin miinustetaan sadasta joten luku hiipuu kohti nollaa
  else return 100 - balanssi;
}
uint8_t getVoimakkuus (uint8_t i) {
  uint8_t y = output.volumeKoordinaatti;
  y = map(y, 15, 165, -10, 100);
  if (y <= 0) return 0 - y;
  //Koska luvut ovat postiivisia niin miinustetaan sadasta joten luku hiipuu kohti nollaa
  else return 0 - y;
}
