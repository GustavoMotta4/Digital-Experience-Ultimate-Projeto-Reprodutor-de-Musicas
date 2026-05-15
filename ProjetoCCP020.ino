  /*
  * PROJETO: Reprodutor de Músicas (CCP020 - Digital Experience Ultimate)
  * INSTITUIÇÃO: Centro Universitário FEI
  * * CRÉDITOS DAS MÚSICAS:
  * As sequências de notas e a lógica de temporização utilizadas neste projeto 
  * foram adaptadas do repositório público "Arduino Songs" de Robson Couto.
  * Fonte: https://github.com/robsoncouto/arduino-songs
  */
  #include <LiquidCrystal.h>
  #include <avr/pgmspace.h>

  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
  //Pinos
  const int pinoBuzzer = 8;
  const int pinoLedVerde = 7; 
  const int pinoLedVermelho = 6; 

  const int btnUp    = A0; 
  const int btnDown  = A1; 
  const int btnPlay  = A2; 
  const int btnStop  = A3; 

  int musicaAtual = 0;
  bool tocando = false;
  bool pausado = false;
  int notaAtual = 0;
  int tempoAtual = 225;
  //Notas
  #define NOTE_E2  82
  #define NOTE_E3  165
  #define NOTE_D3  147
  #define NOTE_C3  131
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_A2  110
  #define NOTE_A3  220
  #define NOTE_G3  196
  #define NOTE_F3  175
  #define NOTE_DS3 156
  #define NOTE_FS3 185
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_B4  494
  #define NOTE_C4  262
  #define NOTE_E4  330
  #define NOTE_C5  523
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F4  349
  #define NOTE_A5  880
  #define NOTE_GS5 831
  #define NOTE_G5  784
  #define NOTE_CS5 554
  #define NOTE_FS5 740
  #define NOTE_F5  698
  #define NOTE_B5  988
  #define REST     0

  //Músicas

  //Música 1 - DOOM
  const uint16_t m1_notas[] PROGMEM = {
    NOTE_E2, NOTE_E2, NOTE_E3, NOTE_E2, NOTE_E2, NOTE_D3, NOTE_E2, NOTE_E2,
    NOTE_C3, NOTE_E2, NOTE_E2, NOTE_AS2, NOTE_E2, NOTE_E2, NOTE_B2, NOTE_C3,
    NOTE_E2, NOTE_E2, NOTE_E3, NOTE_E2, NOTE_E2, NOTE_D3, NOTE_E2, NOTE_E2,
    NOTE_C3, NOTE_E2, NOTE_E2, NOTE_AS2,
    NOTE_E2, NOTE_E2, NOTE_E3, NOTE_E2, NOTE_E2, NOTE_D3, NOTE_E2, NOTE_E2,
    NOTE_C3, NOTE_E2, NOTE_E2, NOTE_AS2, NOTE_E2, NOTE_E2, NOTE_B2, NOTE_C3,
    NOTE_E2, NOTE_E2, NOTE_E3, NOTE_E2, NOTE_E2, NOTE_D3, NOTE_E2, NOTE_E2,
    NOTE_C3, NOTE_E2, NOTE_E2, NOTE_AS2
  };
  const int8_t m1_dur[] PROGMEM = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, -2,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, -2
  };
  const int m1_tam = 56;

  //Música 2 - Fur Elise
  const uint16_t m2_notas[] PROGMEM = {
    NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5,
    NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_E4, NOTE_GS4, NOTE_B4,
    NOTE_C5, NOTE_E4, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, 
    NOTE_D5, NOTE_C5, NOTE_A4, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_E4, 
    NOTE_C5, NOTE_B4, NOTE_A4
  };
  const int8_t m2_dur[] PROGMEM = {
    16, 16, 16, 16, 16, 16, 16, 16, -8, 16, 16, 16, -8, 16, 16, 16, 8, 16, 16, 16,
    16, 16, 16, 16, 16, 16, -8, 16, 16, 16, -8, 16, 16, 16, 4
  };
  const int m2_tam = 35;

  //Música 3 - Star Wars

  const uint16_t m3_notas[] PROGMEM = {
    NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_C5, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4
  };
  const int8_t m3_dur[] PROGMEM = {
    4, 4, 4, -8, 16, 4, -8, 16, 2, 4, 4, 4, -8, 16, 4, -8, 16, 2
  };
  const int m3_tam = 18;

  //Música 3 - Tetris

  const uint16_t m4_notas[] PROGMEM = {
    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, REST,
    REST, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
    NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, REST
  };
  const int8_t m4_dur[] PROGMEM = {
    4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, -4, 8, 4, 4, 4, 4, 4, 4,
    8, 4, 8, 4, 8, 8, -4, 8, 4, 8, 8, 4, 8, 8, 4, 4, 4, 4, 4, 4
  };
  const int m4_tam = 40;

  //Música 5 - Take on me

  const uint16_t m5_notas[] PROGMEM = {
    NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, REST, NOTE_B4, REST, NOTE_E5, 
    REST, NOTE_E5, REST, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
    NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, REST, NOTE_D5, REST, NOTE_FS5, 
    REST, NOTE_FS5, REST, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
  };
  const int8_t m5_dur[] PROGMEM = {
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
  };
  const int m5_tam = 32;

  void atualizaLCD() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Musica: "); 
    lcd.print(musicaAtual + 1);
    lcd.setCursor(0, 1);
    lcd.print("Aguardando...");
  }

  void reset() {
    tocando = false; 
    pausado = false; 
    notaAtual = 0;
    noTone(pinoBuzzer); 
    atualizaLCD();
  }

  void setup() {
    lcd.begin(16, 2);
    pinMode(pinoBuzzer, OUTPUT); 
    pinMode(pinoLedVerde, OUTPUT); 
    pinMode(pinoLedVermelho, OUTPUT);
    pinMode(btnUp, INPUT_PULLUP); 
    pinMode(btnDown, INPUT_PULLUP);
    pinMode(btnPlay, INPUT_PULLUP); 
    pinMode(btnStop, INPUT_PULLUP);
    atualizaLCD();
  }

  void loop() {
    if (digitalRead(btnUp) == LOW) { 
      musicaAtual++;
      if(musicaAtual > 4) musicaAtual = 0;
      atualizaLCD(); 
      delay(250); 
    }
    
    if (digitalRead(btnDown) == LOW) { 
      musicaAtual--;
      if(musicaAtual < 0) musicaAtual = 4;
      atualizaLCD(); 
      delay(250); 
    }

    if (digitalRead(btnPlay) == LOW) {
      if (!tocando) {
        tocando = true; 
        pausado = false;
        lcd.clear(); 
        lcd.setCursor(0, 0); 
        lcd.print("Tocando...");
        lcd.setCursor(0, 1); 
        lcd.print("Musica "); 
        lcd.print(musicaAtual + 1);
      } else { 
        pausado = !pausado; 
        lcd.setCursor(0, 0);
        if (pausado) lcd.print("PAUSADO        ");
        else lcd.print("Tocando...     ");
      }
      delay(250);
    }

    if (digitalRead(btnStop) == LOW) { 
      reset(); 
      delay(250); 
    }

    if (tocando && !pausado) {
      int tam = 0; 
      const uint16_t* notasPtr; 
      const int8_t* durPtr;
      
      //BPM
      
      if(musicaAtual == 0) { notasPtr = m1_notas; durPtr = m1_dur; tam = m1_tam; tempoAtual = 225; }
      else if(musicaAtual == 1) { notasPtr = m2_notas; durPtr = m2_dur; tam = m2_tam; tempoAtual = 80; }
      else if(musicaAtual == 2) { notasPtr = m3_notas; durPtr = m3_dur; tam = m3_tam; tempoAtual = 120; }
      else if(musicaAtual == 3) { notasPtr = m4_notas; durPtr = m4_dur; tam = m4_tam; tempoAtual = 144; }
      else if(musicaAtual == 4) { notasPtr = m5_notas; durPtr = m5_dur; tam = m5_tam; tempoAtual = 140; }

      if (notaAtual < tam) {
        uint16_t freq = pgm_read_word(&notasPtr[notaAtual]);
        int8_t duracaoNota = pgm_read_byte(&durPtr[notaAtual]);
        
        long tempoInteiro = (60000 * 4) / tempoAtual;
        int duracaoReal;

        if(duracaoNota > 0) {
          duracaoReal = tempoInteiro / duracaoNota;
        } else {
          duracaoReal = (tempoInteiro / abs(duracaoNota)) * 1.5;
        }
        
        if (freq != REST) {
          tone(pinoBuzzer, freq, duracaoReal * 0.9);
        } else {
          noTone(pinoBuzzer);
        }

        delay(duracaoReal);
        noTone(pinoBuzzer);
        notaAtual++;

        lcd.setCursor(0, 0);
        if (pausado) lcd.print("PAUSADO        ");
        else lcd.print("Tocando...     ");
        
      } else { 
        reset(); 
      }
    }
  // LED
    digitalWrite(pinoLedVerde, (tocando && !pausado));
    digitalWrite(pinoLedVermelho, (tocando && pausado));
  }