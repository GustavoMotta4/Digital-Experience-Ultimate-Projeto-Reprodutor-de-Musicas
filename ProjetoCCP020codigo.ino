#include <LiquidCrystal.h>
#include <avr/pgmspace.h>

// Inicialização do LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definição dos Pinos
const int pinoBuzzer = 8;
const int pinoLedVerde = 7; 
const int pinoLedVermelho = 6; 

const int btnUp    = A0; 
const int btnDown  = A1; 
const int btnPlay  = A2; 
const int btnStop  = A3; 

// Variáveis de controle de estado
int musicaAtual = 0;
bool tocando = false;
bool pausado = false;
int notaAtual = 0;
int tempoAtual = 225;

// Tabela de frequências das notas musicais
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

void setup() {
  lcd.begin(16, 2);
  pinMode(pinoBuzzer, OUTPUT); 
  pinMode(pinoLedVerde, OUTPUT); 
  pinMode(pinoLedVermelho, OUTPUT);
  
  pinMode(btnUp, INPUT_PULLUP); 
  pinMode(btnDown, INPUT_PULLUP);
  pinMode(btnPlay, INPUT_PULLUP); 
  pinMode(btnStop, INPUT_PULLUP);

  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
}

void loop() {
}