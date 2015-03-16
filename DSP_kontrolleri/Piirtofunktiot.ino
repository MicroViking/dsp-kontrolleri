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
void teeLayout(){
   //Piirretään mutelaatikon kehys
   //tft.drawRect(0, 60, 60, 60, CYAN);
   //Piirretään kompressori !!
   //tft.drawRect(0, 180, 60, 60, CYAN);
   //Loudnessin kehys
   //tft.drawRect(260, 180, 60, 60, CYAN);
   //Balanssi, Basso, Diskantti sliderien kehys
   //tft.drawRect(60, 60, 200, 180, CYAN);
   
   //Paksut viivat
   tft.fillRect(58, 60, 2, 120, CYAN);
   tft.fillRect(0, 55, 260, 4,CYAN);
   tft.fillRect(260, 0, 3, 240, CYAN);
   //Ohuet viivat ylhäällä
   tft.fillRect(64, 0, 1, 57, CYAN);
   tft.fillRect(128, 0, 1, 57, CYAN);
   tft.fillRect(192, 0, 1, 57, CYAN);
   //Ohuet viivat vaakatasossa
   tft.fillRect(0, 120, 60, 1, CYAN);
   tft.fillRect(0, 180, 60, 1, CYAN);
   tft.fillRect(260, 120, 60, 1, CYAN);
   //Balanssin viiva
   tft.drawRoundRect(70, 80, 180, 20, 10, WHITE);
   //Basson viiva
   tft.drawRoundRect(70, 240, 180, 20, 10, WHITE);
   //Diskantin viiva
   tft.drawRoundRect(70, 300, 180, 20, 10, WHITE);
   //Volume viiva
   tft.drawRoundRect(180, 10, 20, 160, 10, WHITE);
   //Piirretään tyhjä loora
   tft.fillRect(0, 121, 59, 58, BLUE);
   
   piirraKanava(0 , true);
   piirraMute();
   piirraKompressori();
   piirraLoudness();
   piirraVedin(0);
   piirraVedin(1);
   piirraVedin(2);
   piirraVedin(3);
}
void piirraKanava(uint8_t i, bool boot){
  int x;
  switch(i){
    case 0:
    x = 0;
    break;
    case 1:
    x = 66;
    break;
    case 2:
    x = 131;
    break;
    case 3:
    x = 196;
    break;
  }
  if(boot == true){
  //kanava yksi
    tft.fillRect(0, 0, 64, 56, LIGHTGREY);
    tft.drawChar(10, 10, '1', BLACK, 3);
    tft.drawString(30, 30, "ch", BLACK, 1);
    //kanava 2
    tft.fillRect(66, 0, 65,56, BLUE);
    tft.drawChar(76, 10, '2', WHITE, 3);
    tft.drawString(96, 30, "ch", WHITE, 1);
    //Kanava 3
    tft.fillRect(131, 0, 65,56, BLUE);
    tft.drawChar(141, 10, '3', WHITE, 3);
    tft.drawString(161, 30, "ch", WHITE, 1);
    //Kanava 4
    tft.fillRect(196, 0, 65,56, BLUE);
    tft.drawChar(206, 10, '4', WHITE, 3);
    tft.drawString(226, 30, "ch", WHITE, 1);
  }
  else {
    char numero[1];
    sprintf(numero, "%i",i+1);
    tft.fillRect(x, 0, 65,56, LIGHTGREY);
    tft.drawString(x+10, 10, numero, BLACK, 3);
    tft.drawString(x+30, 30, "ch", BLACK, 1);
  }
}

void poistaKanava(uint8_t i){
  int x;
  switch(i){
    case 0:
    x = 0;
    break;
    case 1:
    x = 66;
    break;
    case 2:
    x = 131;
    break;
    case 3:
    x = 196;
    break;
  }
  char numero[1];
    sprintf(numero, "%i",i++);
    tft.fillRect(x, 0, 65,56, BLUE);
    tft.drawString(x+10, 10, numero, WHITE, 3);
    tft.drawString(x+30, 30, "ch", WHITE, 1);
}

void pyyhiruutu() {  
 tft.fillScreen(BLACK); 
}
//Vetimen piirto
void piirraVedin(int8_t vedin){
  int y;
  int x;
  switch(vedin){ 
    //keskipisteet
    case 0: 
      y = output.volumeKoordinaatti;
      x= 290;
      break;
    case 1: 
      y = 90;
      x = channel[currentChannel].balanssiKoordinaatti;
      break;
    case 2:
      y = 150;
      x = channel[currentChannel].bassoKoordinaatti;
      break; 
    case 3:
      y = 210;
      x = channel[currentChannel].diskanttiKoordinaatti;
      break;
    
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
      x = 290;
      y = output.volumeKoordinaatti;
      break;
    case 1: 
      x = channel[currentChannel].balanssiKoordinaatti;
      y = 90;
      break;
     case 2:
      x = channel[currentChannel].bassoKoordinaatti;
      y = 150;
      break; 
     case 3:
      x = channel[currentChannel].diskanttiKoordinaatti; 
      y = 210;
      break;
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

   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[currentChannel].mute == false) tft.fillRect(1,  61, 58, 58, GREEN);
   else tft.fillRect(1,  61, 58, 58, RED);
   //Piirretään kajarikuvake ja otetaan huomioon kanavakohtainen asetus
   //Piirretään magneetti
    tft.fillRect(1,  61, 58, 58, RED);
    //Piirretään kajari
    int x =17;
    int y = 83;
    int h = 17;
    for (int i=0; i<13; i++) {
       tft.fillRect(x,y,1,h,WHITE);
      x++;
      y--;
      h=h+2;
    }
     
     
   if (channel[currentChannel].mute == false) {
   
     
     //kajari viivat
     tft.fillRect(33, 28, 1, 4, WHITE);
     tft.fillRect(36, 80, 1, 4, WHITE);
     tft.fillRect(36, 96, 1, 4, WHITE);
     tft.fillRect(39, 83, 1, 10, WHITE);
     tft.fillRect(42, 76, 1, 4, WHITE);
     tft.fillRect(42, 100, 1, 4, WHITE);
     tft.fillRect(45, 80, 1, 20, WHITE);
     
   }
   else {
    //Häivytetään kajarin kaikuviivat taustaan
     tft.fillRect(33, 28, 1, 4, RED);
     tft.fillRect(36, 80, 1, 4, RED);
     tft.fillRect(36, 96, 1, 4, RED);
     tft.fillRect(39, 83, 1, 10, RED);
     tft.fillRect(42, 76, 1, 4, RED);
     tft.fillRect(42, 100, 1, 4, RED);
     tft.fillRect(45, 80, 1, 20, RED);
   }
}  

  void piirraKompressori(){
    
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[currentChannel].kompressori == false) tft.fillRect(1,  181, 58, 58, RED);
   else tft.fillRect(1,  181, 58, 58, GREEN);
   //kompressorin kuvake
   tft.fillRect(15, 190, 30, 2, WHITE);
   tft.fillRect(45, 190, 2, 10, WHITE);
   tft.fillRect(15, 190, 2, 30, WHITE);
   tft.fillRect(15, 220, 25, 2, WHITE);
   tft.fillRect(40, 118, 10, 4, WHITE);
   tft.fillRect(44, 222, 2, 8, WHITE);
   tft.fillRect(20, 195, 20, 1, WHITE);
   tft.fillRect(20, 200, 20, 1, WHITE);
   tft.fillRect(20, 205, 20, 1, WHITE);
   tft.fillRect(20, 210, 20, 1, WHITE);
   tft.fillRect(20, 215, 20, 1, WHITE);
   
   
  }
  
  void piirraLoudness(){
    
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (output.loudness == false) tft.fillRect(261,  181, 58, 58, RED);
   else tft.fillRect(1,  61, 58, 58, GREEN);
   tft.fillRect(270, 220, 10, 3, WHITE);
   tft.fillRect(280, 205, 3, 18, WHITE);
   tft.fillRect(280, 205, 20, 3, WHITE);
   tft.fillRect(300, 205, 3, 15, WHITE);
   tft.fillRect(300, 220, 10, 3, WHITE);
  }
  
  
