

uint8_t tarkistatouch() {
  pinMode(13, OUTPUT);
  //Luetaan kosketuspiste
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
   
  
  
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
    //Serial.println(p.z);
  if (p.z) {
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
      // turn from 0->1023 to tft.width
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);    
      //Serial.println(p.x);
      //Serial.println(p.y);
      return suoritaKosketus(p.y, p.x);  
    }
  }
  //Jos kosketus ei osu oikeaa alueeseen
  return 0; 
}


byte suoritaKosketus(byte y, byte x) {
    /**TO
      Välilehtitunnistus ja evätään tunnistus jos kosketus on voluumin säätimen kohdalla
      256 on 64*64*64*64 eli raja johon asti välilehtien laatikot piirtyvät
      Ensimäinen if siksi että näitä ajoja ei ajeta muutakuin silloin ku ollaan sallituissa rajoissa kosketuksen kanssa,
      siten säästetään prosessoriaikaa.
    **/
    
    if (y > 2 && y < 58 && x < 258) {
      if ( x > 2 && x < 62) { 
        //Nykyisen välilehden tarkistus
        if (currentChannel != 0) {
          //Välilehti ei ollut aktiivinen, vaihdetaan nykyisen kanavan taustaväri
          poistaKanava(currentChannel);
          //Päivitetään valittu kanava muuttujaan
          currentChannel = 0;
          //Väritetään kanavan tausta uudestaan
          piirraKanava(currentChannel, false);
          return 1;
        }
      }
      else if (x > 67 && x < 127) {
        if (currentChannel != 1) {
          poistaKanava(currentChannel);
          currentChannel = 1;
          piirraKanava(currentChannel, false);
          return 1;
        }
      }
      else if (x > 132 && x < 192) {
        if (currentChannel != 2) {
          poistaKanava(currentChannel);
          currentChannel = 2;
          piirraKanava(currentChannel, false);
          return 1;
        }
      }
      else if (x > 197 && x < 257) {
        if (currentChannel != 3) {
          poistaKanava(currentChannel);
          currentChannel = 3;
          piirraKanava(currentChannel, false);
          return 1;
        }
      }
      
    }
    /**
      Tähän kanavakohtaiset laatikoiden tunnistukset
    **/
    else if (x > 2 && x < 58 && y > 62) {
      if (y > 62 && y < 118) {     
        if (channel[currentChannel].mute) channel[currentChannel].mute = false;
        else channel[currentChannel].mute = true;
        sendDSPcommand(channel[currentChannel].muteOsoite, uint8_t(channel[currentChannel].mute));
        piirraMute();
        return 1;   
      }
      /* Ei tehdä keksimäisen kanvakohtaisen ruudun kosketukselle mitään.
      else if (y > 122 && y < 178) {
        //Ei funktionaalisuutta tässä laatikossa
        //piirraTyhja();
        return 1;   
      }*/
      
      //Mikäli kompressoria nappia painetaan
      else if (y > 182 && y < 238) {    
        if (channel[currentChannel].kompressori) channel[currentChannel].kompressori = false;
        else channel[currentChannel].kompressori = true;
        sendDSPcommand(channel[currentChannel].kompressoriOsoite, uint8_t(channel[currentChannel].kompressori));
        piirraLoudness();
        return 1;   
      }
    }
     /**
      Kanavakohtainen slideritunnistus
    **/
    else if (x > 62 && x < 258 && y > 62) {
      //Ollaan kosketettu joitakin kanavakohtaisia slidereita
      
      //Tarkastellaan onko kosketetettu balanssia
      if (y > 70 && y < 110) {
        if (x != channel[currentChannel].balanssiKoordinaatti) {
          poistaVedin(1);
          channel[currentChannel].balanssiKoordinaatti = x;
          piirraVedin(1);
          return 1;
        }
           
      }
      else if (y > 130 && y < 170) {
        if (x != channel[currentChannel].bassoKoordinaatti) { 
          poistaVedin(2);
          channel[currentChannel].bassoKoordinaatti = x;
          piirraVedin(2);
          return 1;
        }   
      }
      else if (y > 190 && y < 230) {
        if (x != channel[currentChannel].diskanttiKoordinaatti) {
          poistaVedin(3);
          channel[currentChannel].diskanttiKoordinaatti = x;     
          piirraVedin(3);
          return 1;
        }    
      }
    }
    /**
      Päävoimakkuus ja loudness
    **/
    else if (x > 260) {
       //Voimakkuus sliderin tunnistus
      if (y > 30 && y < 150) {
        if (y != output.volumeKoordinaatti) { 
           //Poistetaan edellinen piirto
           poistaVedin(0);
           //Talletetetaan nykyinen kosketuskordinaatti
           output.volumeKoordinaatti = y;
           //Piirretään tallennetun kordinaatin mukaan uusi vetimen sijainti
           piirraVedin(0);
           return 1;
        }
      }
      /**
        Loudness
      **/
    
      else if (y > 182) {
         if (output.loudness == true) output.loudness = false;
         else output.loudness == true;
         piirraLoudness();
         return 1;       
      }            
    }
    return 0;
}   
//Siivotaan touchscreenin jäljet. Pinnit voivat olla kosketuksen
//tunnistuksen jälkeen väärin ja näillä palautetaan asetukset.
void palautaPinnit() {
   pinMode(XM, OUTPUT);
   digitalWrite(XM, LOW);
   pinMode(YP, OUTPUT);
   digitalWrite(YP, HIGH);
   //pinMode(YM, OUTPUT);
   //digitalWrite(YM, LOW);
   //pinMode(XP, OUTPUT);
   //digitalWrite(XP, HIGH); 
}
  
