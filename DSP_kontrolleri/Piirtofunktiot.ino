/* 320*240 pikseliä
  laatikon mitat = 64 * 60 pikseliä
  pystylaatikoiden mitat = 60 * 60 pikseliä
  volansäätimen mitat = 64 * 240 pikseliä 
  sliderien maksimi mitata 240 * 60 pikseliä 
  
  Nolla y = ylä reuna
  Maksimi 240 y = ala reuna
  Nolla x = vasen reuna
  Maksimi 320 x = oikea reuna
*/

void pyyhiruutu() {  
 tft.fillScreen(BLACK); 
}

void piirraKanavat (int8_t kanava) {
  
  void drawRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
  void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
  
}

void piirraMute() {
   //Piirretään mutelaatikon kehys
   void drawRect(0, 60, 60, 60, CYAN);
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[currentChannel].getMute == false) fillRect(1,  61, 58, 58, GREEN);
   else fillRect(1,  61, 58, 58, RED);
   //Piirretään kajarikuvake ja otetaan huomioon kanavakohtainen asetus
   if (channel[currentChannel].getMute == false) {
     void drawLine(5, 80, 2, 20, WHITE);
     
     
   }
   else {
     //Piirretään kajari valkosella
     void drawLine(5, 80, 2, 20, WHITE);
     //Häivytetään kajarun kaikuviivat taustaan
     void drawLine(5, 80, 2, 20, RED);
     
     
   }
  
}  
