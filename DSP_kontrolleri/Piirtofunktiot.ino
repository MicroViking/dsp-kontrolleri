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
//Kanavat puuttuu!!!!!
void piirraKanavat (int8_t kanava) {
  
  void drawRect(uint16_t x0, 70, uint16_t w, uint16_t h, uint16_t color);
  void fillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color);
  
}
//Vetimen piirto
void piiraVedin(int8_t vedin){
  int y;
  int x;
  switch(vedin){ 
    //keskipisteet
    case 0: 
      y = volume;
      x= 290;
      brake;
    case 1: 
      y = 90;
      x = channel[currentChannel].getBalanssi;
      brake;
     case 2:
      y = 150;
      x = channel[currentChannel].getBasso;
     brake; 
     case 3;
      y = 210;
      x = channel[currentChannel].getDiskantti;
      brake;
    
  }
  if(vedin==0){
  //volume slideri
  tft.drawRoundRect(x-20, y-10, x+20, y+10, 6, BLACK);
  tft.fillRoundRect(x-19, y-9, x+19, y+10, 6, WHITE);  
  }
  else {
    //muut sliderit
    tft.drawRoundRect(x-10, y-20, x+10, y+20, 6, BLACK);
    tft.fillRoundRect(x-9, y-19, x+9, y+19, 6, WHITE);
  }  
  
}
//Vetimen poisto
void poistaVedin(int8_t vedin){
  int y, x;
  switch(vedin){ 
    //Keskipisteet
    case 0:
      x = 290
      y = volume
      brake;
    case 1: 
      x = channel[currentChannel].getBalanssi;
      y = 90;
      brake;
     case 2:
      x = channel[currentChannel].getBasso;
      y = 150;
     brake; 
     case 3;
      x = channel[currentChannel].getDiskantti; 
      y = 210;
      brake;
  }
  //volume slideri poisto
  if(vedin==0){
  tft.fillRect(x-20, y-10, x-10, 20,  BLUE);
  tft.fillRect(x-10, y-10, x+10, 20,  WHITE);
  tft.fillRect(x+20, y-10, x+10, 20,  BLUE);
  }
  else {
    //muiden sliderien poisto
  tft.fillRect(x-10, y-20, x+10, 10,  BLUE);
  tft.fillRect(x-10, y-10, x+10, 20,  WHITE);
  tft.fillRect(x-10, y+10, x+10, 10,  BLUE);
  }
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             



void piirraMute() {
   //Piirretään mutelaatikon kehys
   tft.drawRect(0, 60, 60, 60, CYAN);
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[currentChannel].getMute == false) tft.fillRect(1,  61, 58, 58, GREEN);
   else tft.fillRect(1,  61, 58, 58, RED);
   //Piirretään kajarikuvake ja otetaan huomioon kanavakohtainen asetus
   //Piirretään magneetti
    tft.fillRect(1,  61, 58, 58, RED);
    //Piirretään kajari
    int x =17;
    int y = 83;
    int h = 17;
    for (i=0; i<13; i++) {
       tft.drawLine(x,y,1,h,WHITE);
      x++;
      y--;
      h=h+2;
    }
     
     
   if (channel[currentChannel].getMute == false) {
   
     
     //kajari viivat
     tft.drawLine(33, 28, 1, 4, WHITE);
     tft.drawLine(36, 80, 1, 4, WHITE;
     tft.drawLine(36, 96, 1, 4, WHITE;
     tft.drawLine(39, 83, 1, 10, WHITE;
     tft.drawLine(42, 76, 1, 4, WHITE;
     tft.drawLine(42, 100, 1, 4, WHITE;
     tft.drawLine(45, 80, 1, 20, WHITE;
     
   }
   else {
    //Häivytetään kajarin kaikuviivat taustaan
     tft.drawLine(33, 28, 1, 4, RED);
     tft.drawLine(36, 80, 1, 4, RED;
     tft.drawLine(36, 96, 1, 4, RED;
     tft.drawLine(39, 83, 1, 10, RED;
     tft.drawLine(42, 76, 1, 4, RED;
     tft.drawLine(42, 100, 1, 4, RED;
     tft.drawLine(45, 80, 1, 20, RED;
   }
}  

  void piirraKompressori(){
    //Piirretään mutelaatikon !!
   tft.drawRect(0, 180, 60, 60, CYAN);
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[currentChannel].getKompressori == false) tft.fillRect(1,  181, 58, 58, RED);
   else tft.fillRect(1,  181, 58, 58, GREEN);
   //kompressorin kuvake
   tft.drawLine(15, 190, 30, 2, WHITE;
   tft.drawLine(45, 190, 2, 10, WHITE;
   tft.drawLine(15, 190, 2, 30, WHITE;
   tft.drawLine(15, 220, 25, 2, WHITE;
   tft.drawLine(40, 118, 10, 4, WHITE;
   tft.drawLine(44, 222, 2, 8, WHITE;
   tft.drawLine(20, 195, 20, 1, WHITE;
   tft.drawLine(20, 200, 20, 1, WHITE;
   tft.drawLine(20, 205, 20, 1, WHITE;
   tft.drawLine(20, 210, 20, 1, WHITE;
   tft.drawLine(20, 215, 20, 1, WHITE;
   
   
  }
  
  void piirraLoudness(){
    //kehys
  tft.drawRect(260, 180, 60, 60, CYAN);
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (loudness == false) tft.fillRect(261,  181, 58, 58, RED);
   else tft.fillRect(1,  61, 58, 58, GREEN);
   tft.drawLine(270, 220, 10, 3, WHITE;
   tft.drawLine(280, 205, 3, 15, WHITE;
   tft.drawLine(280, 205, 20, 3, WHITE;
   tft.drawLine(300, 205, 3, 15, WHITE;
   tft.drawLine(300, 220, 10, 3, WHITE;
  }
  
  
