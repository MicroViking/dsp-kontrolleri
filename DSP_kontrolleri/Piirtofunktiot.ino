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

void setupVariables() {
  for(int i=0; i<4;i++) {
    channel[i].mute = false;
    channel[i].kompressori = false;
    channel[i].balanssiKoordinaatti = 160;
    channel[i].bassoKoordinaatti = 160;
    channel[i].diskanttiKoordinaatti = 160;
    for (int y=0; y<4; y++) {
      channel[i].i2cTone[y] = 0;
      channel[i].i2cVasen[y] = 0; 
      channel[i].i2cOikea[y] = 0;
      channel[i].i2cMute[y] = 0;
      
    }
    for (int k=0; k<8; k++) {
     channel[i].i2cKomp[k] = 0; 
    }
  }
  output.loudness = false;
  output.volumeKoordinaatti = 35;
  for (int y=0; y<4; y++){
    output.i2cVolume[y] = 0;
    output.i2cLoud[y] = 0;
  }
}

uint8_t palautaKoordinaatti(uint8_t kanava) {
  uint8_t x;
  switch (kanava) {
     case 0:
       x = 0;
       break;
     case 1:
       x = 65;
       break;
     case 2:
       x = 131;
       break;
     case 3:
       x = 196;
       break;
  }
  return x;
}
void teeLayout(){
   piirraKanavat();
   piirraLaatikot();
   piirraLoudness();
  
  
    //Paksut viivat
   
   tft.fillRect(0, 57, 260, 4,  ORANGE);
   tft.fillRect(259, 0, 4, 240, ORANGE);
   
   /*
   tft.fillRect(58, 60, 3, 120, ORANGE);
   //Ohuet viivat ylhäällä
   tft.fillRect(64, 0, 2, 57, RED);
   tft.fillRect(129, 0, 2, 57, RED);
   tft.fillRect(194, 0, 2, 57, RED);
   //Ohuet viivat vaakatasossa
   tft.fillRect(0, 120, 60, 2, CYAN);
   tft.fillRect(0, 180, 60, 1, CYAN);
   tft.fillRect(260, 180, 60, 1, CYAN);
   //Pystyssä olevat viivat
   tft.fillRect(59, 58, 1, 181, CYAN);
   //Slideri laatikon täyttö
   //tft.fillRect(60, 59, 200, 181, ORANGE);
   //Volume sliderin laatikko
   //tft.fillRect(263, 0, 57, 180, ORANGE);
   */
  
   //Piirretään vetimien vetoalueet
   piirraSliderit();
   
   //Piirretäänn vedettävät vetimet
   piirraVedin(currentChannel, 0);
   piirraVedin(currentChannel, 1);
   piirraVedin(currentChannel, 2);
   piirraVedin(currentChannel, 3);
   
}

void piirraSliderit() {
    
    uint16_t vol[2];
    uint16_t bas[2];
    uint16_t dis[2]; 
    uint16_t bal[2];
    uint16_t * volxy;
    uint16_t * basxy;
    uint16_t * disxy;
    uint16_t * balxy;
    
    volxy = palautaVedinKordinaatti (currentChannel, 0, vol);
    balxy = palautaVedinKordinaatti (currentChannel, 1, bal);
    basxy = palautaVedinKordinaatti (currentChannel, 2, bas);
    disxy = palautaVedinKordinaatti (currentChannel, 3, dis);
    
   //Balanssi sliderin vetoalueen piirto 70-250px
   //tft.drawRoundRect(70, 80, 180, 20, 10, WHITE);
   tft.drawString(62, 64, "Balanssi", ORANGE, 1);
   tft.fillRoundRect(balxy[0]-90, balxy[1]-10, 180, 20, 10, WHITE);
   
   //Basson sliderin vetoalueen piirto 70-250px
   //tft.drawRoundRect(70, 150, 180, 20, 10, WHITE);
   tft.drawString(62, 124, "Basso", ORANGE, 1);
   tft.fillRoundRect(basxy[0]-90, basxy[1]-10, 180, 20, 10, WHITE);
   
   //Diskantin sliderin vetoalueen piirto 70-250px
   //tft.drawRoundRect(70, 200, 180, 20, 10, WHITE);
   tft.drawString(62, 184, "Diskantti", ORANGE, 1);
   tft.fillRoundRect(disxy[0]-90, disxy[1]-10, 180, 20, 10, WHITE);
   
   /*
     Volume sliderin vetoalueen piirto 70-250px
     Koska volumen sliderin y ei koskaan muutu voi se olla vakio
     */
   tft.fillRoundRect(volxy[0]-10, 5, 20, 160, 10, WHITE);
   tft.drawString(275, 168, "Volume", ORANGE, 1);   
}

void piirraKanavat() {
    piirraKanava(3);
    piirraKanava(2);
    piirraKanava(1);
    piirraKanava(0);   
}
void piirraLaatikot() {
    piirraMute(currentChannel);
    piirraKompressori(currentChannel);
}


void piirraKanava(uint8_t kanava) {
  uint8_t x = palautaKoordinaatti(kanava);
  if (kanava != currentChannel) {
      poistaKanava(currentChannel);
      currentChannel = kanava;
      char numero[1];
      sprintf(numero, "%i",kanava+1);
      tft.fillRect(x, 0, 63, 57, LIGHTGREY);
      tft.drawString(x+15, 15, numero, BLACK, 4);
      tft.drawString(x+40, 35, "ch", BLACK, 1);
   }
}


void poistaKanava(uint8_t kanava){ 
  uint8_t x = palautaKoordinaatti(kanava);
  char numero[1];
    sprintf(numero, "%i",kanava+1);
    tft.fillRect(x, 0, 63, 57, BLUE);
    tft.drawString(x+15, 15, numero, WHITE, 4);
    tft.drawString(x+40, 35, "ch", WHITE, 1);
}

//Palautetaan xy kordinaatit taulukkona siksi tarvitaan pointeri
uint16_t * palautaVedinKordinaatti (uint8_t kanava, uint8_t vedin, uint16_t koordinaatit[]) {
  switch(vedin){ 
    //keskipisteet
    case 0: 
      koordinaatit[1] = output.volumeKoordinaatti;
      koordinaatit[0] = 290;
      break;
    case 1: 
      koordinaatit[1] = 93;
      koordinaatit[0] = channel[kanava].balanssiKoordinaatti;
      break;
    case 2:
      koordinaatit[1] = 153;
      koordinaatit[0] = channel[kanava].bassoKoordinaatti;
      break; 
    case 3:
      koordinaatit[1] = 213;
      koordinaatit[0] = channel[kanava].diskanttiKoordinaatti;
      break;
    
  }
  return koordinaatit; 
}

//Vetimen piirto
void piirraVedin(uint8_t kanava, uint8_t vedin){
  
  // xy muuttujassa on nollapaikassa x koordinaatti ja 1 paikassa y koordinaatti
  uint16_t haku[2];
  uint16_t *xy = palautaVedinKordinaatti(kanava, vedin, haku);
  char luku[4];
  
  if(vedin==0){
    //volume slideri 
    int16_t u = i2cVoimakkuus();
    int16_t x = 0;
    //Sliderin tekstin korjaus siten että minus merkkiset on hieamn vasempana kuin muuten
    if (u < -99) {
      x = xy[0]-12;  
    }
    else if (u < -9) {
      x = xy[0]-9;
    }
    else if (u < 0) {
      x = xy[0]-6; 
    }
    else if (u < 10) {
      x = xy[0]-3;
    }
    else if (u < 21) {
      x = xy[0]-6;
    }
    itoa (u,luku,10);
    Serial.print("Slider ");
    Serial.print(vedin);
    Serial.print(" value: ");
    Serial.println(u);
    //sprintf(voluumi,"%1",u);
    tft.fillRoundRect(xy[0]-20, xy[1]-10, 40, 20, 8, WHITE);
    tft.drawRoundRect(xy[0]-20, xy[1]-10, 40, 20, 8, BLACK);
    tft.drawString(x, xy[1]-4, luku, BLACK, 1);  
  }
  else {
    //muut sliderit
    int16_t u = i2cVedin(vedin);
    Serial.print("i2C luku: ");
    Serial.println(u);    
    int16_t x = 0;
    //Sliderin tekstin korjaus siten että minus merkkiset on hieamn vasempana kuin muuten
    if (u < -9) {
      x = xy[0]-9;
    }
    else if (u < 0) {
      x = xy[0]-6; 
    }
    else if (u < 10) {
      x = xy[0]-3;
    }
    else if (u < 21) {
      x = xy[0]-6;
    }
    //Luvun muutos charriksi
    itoa (u,luku,10);
    Serial.print("Slider ");
    Serial.print(vedin);
    Serial.print(" value: ");
    Serial.println(u);
    tft.fillRoundRect(xy[0]-10, xy[1]-20, 20, 40, 8, WHITE);
    tft.drawRoundRect(xy[0]-10, xy[1]-20, 20, 40, 8, BLACK);
    tft.drawString(x, xy[1]-4, luku, BLACK, 1);
  }   
}

//Vetimen poisto
void poistaVedin(uint8_t kanava, uint8_t vedin){
  // xy muuttujassa on nollapaikassa x koordinaatti ja 1 paikassa y koordinaatti
  uint16_t haku[2];
  uint16_t *xy; 
  xy = palautaVedinKordinaatti(kanava, vedin, haku);
  
  //volume slideri poisto
  if(vedin==0){
  tft.fillRect(xy[0]-21, xy[1]-11, 11, 22,  BLUE);
  tft.fillRect(xy[0]-10, xy[1]-10, 20, 20,  WHITE);
  tft.fillRect(xy[0]+10, xy[1]-11, 10, 22,  BLUE);
  }
  else {
    //muiden sliderien poisto
  tft.fillRect(xy[0]-11, xy[1]-20, 22, 10,  BLUE);
  tft.fillRect(xy[0]-10, xy[1]-10, 20, 20,  WHITE);
  tft.fillRect(xy[0]-11, xy[1]+10, 22, 12,  BLUE);
  }
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
void tarkastaPiirto(uint8_t c) {
  //Tarkastetaan onko c:n asetukset samat kuin nykyisen asetukset, jos ei niin päivitetään muuttuvaan kanavaan kuvakkeet ja sliderisijainnit
  if (channel[currentChannel].mute != channel[c].mute) piirraMute(c);
  if (channel[currentChannel].kompressori != channel[c].kompressori) piirraKompressori(c); 
  if (channel[currentChannel].balanssiKoordinaatti != channel[c].balanssiKoordinaatti) {
    poistaVedin(currentChannel, 1);
    piirraVedin(c, 1);
  }
  if (channel[currentChannel].bassoKoordinaatti != channel[c].bassoKoordinaatti) {
    poistaVedin(currentChannel, 2);
    piirraVedin(c, 2);
  }
  if (channel[currentChannel].diskanttiKoordinaatti != channel[c].diskanttiKoordinaatti)  {
    poistaVedin(currentChannel, 3);
    piirraVedin(c, 3);
  }
}


void piirraMute(uint8_t kanava) {

   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[kanava].mute == false) tft.fillRect(0,  61, 58, 60, GREEN);
   else tft.fillRect(0,  61, 58, 60, RED);
   //Piirretään kajarikuvake ja otetaan huomioon kanavakohtainen asetus
   //Piirretään magneetti
    tft.fillRect(13,  81, 3, 17, WHITE);
    //Piirretään kajari
    int x =17;
    int y = 81;
    int h = 17;
    for (int i=0; i<13; i++) {
       tft.fillRect(x,y,1,h,WHITE);
      x++;
      y--;
      h=h+2;
    }
     
     
   if (channel[kanava].mute == false) {
   
     
     //kajari viivat
     tft.fillRect(33, 88, 1, 4, WHITE);
     tft.fillRect(36, 80, 1, 4, WHITE);
     tft.fillRect(36, 96, 1, 4, WHITE);
     tft.fillRect(39, 83, 1, 10, WHITE);
     tft.fillRect(42, 76, 1, 4, WHITE);
     tft.fillRect(42, 100, 1, 4, WHITE);
     tft.fillRect(45, 80, 1, 20, WHITE);
     
   }
   else {
    //Häivytetään kajarin kaikuviivat taustaan
     tft.fillRect(33, 88, 1, 4, RED);
     tft.fillRect(36, 80, 1, 4, RED);
     tft.fillRect(36, 96, 1, 4, RED);
     tft.fillRect(39, 83, 1, 10, RED);
     tft.fillRect(42, 76, 1, 4, RED);
     tft.fillRect(42, 100, 1, 4, RED);
     tft.fillRect(45, 80, 1, 20, RED);
   }
}  

void piirraKompressori(uint8_t kanava){
    
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (channel[kanava].kompressori == false) {
     tft.fillRect(0,  181, 59, 59, RED);
   }
   else {
     tft.fillRect(0,  181, 59, 59, GREEN);
   }
   //kompressorin kuvake
   tft.fillRect(10, 195, 30,  2, WHITE);
   tft.fillRect(40, 195,  2, 10, WHITE);
   tft.fillRect(10, 195,  2, 30, WHITE);
   tft.fillRect(10, 225, 25,  2, WHITE);
   tft.fillRect(35, 224, 10,  4, WHITE);
   tft.fillRect(39, 227,  2,  8, WHITE);
   tft.fillRect(15, 200, 20,  1, WHITE);
   tft.fillRect(15, 205, 20,  1, WHITE);
   tft.fillRect(15, 210, 20,  1, WHITE);
   tft.fillRect(15, 215, 20,  1, WHITE);
   tft.fillRect(15, 220, 20,  1, WHITE);
   
   
}
  
void piirraLoudness(){
    
   //Täytetään kehyksen sisäosa halutulla värillä ja otetaan huomioon kanavakohtaiset asetukset
   if (output.loudness == false) {
     Serial.println("Piirretään punainen Loudness");
     tft.fillRect(263,  181, 57, 59, RED);
   }
   else {
     Serial.println("Piirretään vihreä Loudness");
     tft.fillRect(263,  181, 57, 59, GREEN);
     
   }
   tft.fillRect(275, 210, 5, 3, WHITE);
   tft.fillRect(280, 195, 3, 18, WHITE);
   tft.fillRect(280, 195, 20, 3, WHITE);
   tft.fillRect(300, 195, 3, 15, WHITE);
   tft.fillRect(300, 210, 10, 3, WHITE);
   tft.drawString(268, 225, "Loudness", ORANGE, 1);
}
  
  
