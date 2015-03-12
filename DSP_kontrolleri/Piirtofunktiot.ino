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
     void drawLine(5, 80, 3, 20, WHITE);
     void drawLine(8, 80, 3, 20, WHITE);
     //väli
     void drawLine(9, 80, 3, 20, WHITE);
     void drawLine(12, 78, 3, 24, WHITE);
     void drawLine(15, 76, 3, 28, WHITE);
     void drawLine(18, 74, 3, 32, WHITE);
     void drawLine(21, 72, 3, 34, WHITE);
     void drawLine(24, 70, 3, 36, WHITE);
     void drawLine(27, 68, 3, 38, WHITE);
     void drawLine(30, 66, 3, 40, WHITE);
   if (channel[currentChannel].getMute == false) {
   
     
     //kajari viivat
     void drawLine(34, 90, 1, 1, WHITE);
     void drawLine(37, 80, 2, 20, WHITE;
     void drawLine(43, 70, 2, 40, WHITE;
     void drawLine(39, 60, 2, 60, WHITE;
     
     
   }
   else {
    //Häivytetään kajarin kaikuviivat taustaan
     void drawLine(34, 90, 1, 1, RED);
     void drawLine(37, 80, 2, 20, RED;
     void drawLine(43, 70, 2, 40, RED;
     void drawLine(39, 60, 2, 60, RED;
     
     
     
   }
  
}  
