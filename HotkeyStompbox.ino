/*  Hotkey Stompbox
 *  
 * Hardware:
 *  RP2040 microcontroller board
 *  2x footswitch
 *  4x tactile micro switches
 *  
 *  by Barito 2025
*/

#include <Keyboard.h>

#define FOOT_SWITCHES 2
#define TACT_SWITCHES 4
#define LATCHING

const byte fSwitchPin[FOOT_SWITCHES] = {7, 4}; //SW1, SW2
const byte tSwitchPin[TACT_SWITCHES] = {3, 2, 5, 6}; //SW3, SW4, SW5, SW6
const byte aLEDpin = 15; //activity LED
boolean fState[FOOT_SWITCHES];
boolean tState[TACT_SWITCHES];
boolean LEDstate;
unsigned long fDebT[FOOT_SWITCHES];
unsigned long tDebT[TACT_SWITCHES];

const int dbTime = 100;

byte fKeys[FOOT_SWITCHES] =  {' ', 't'};
byte tKeys[TACT_SWITCHES] =  {'i', 'j', 'k', 'l'};

unsigned long lifeTime;
byte lifeCount;

const unsigned long noLossDel = 10;
                                             
void setup() {
  for (int a=0; a<FOOT_SWITCHES; a++){
    pinMode(fSwitchPin[a], INPUT);
    fState[a] = digitalRead(fSwitchPin[a]);
  }
  for (int a=0; a<TACT_SWITCHES; a++){
    pinMode(tSwitchPin[a], INPUT);
    tState[a] = digitalRead(tSwitchPin[a]);
  }
  pinMode(aLEDpin, OUTPUT);
  Keyboard.begin();
}

void loop() {
  LifeCheck();
  Foot_Press();
  Tact_Press();
}

void Foot_Press(){
  for (int a=0; a<FOOT_SWITCHES; a++){
    if(digitalRead(fSwitchPin[a]) != fState[a] && millis() - fDebT[a] > dbTime){
      fState[a] = !fState[a];
      fDebT[a] = millis();
      #ifdef LATCHING
        Keyboard.write(fKeys[a]);
        delay(noLossDel);
      #else
        if(fState[a]==HIGH){//at press
          Keyboard.write(fKeys[a]);
          delay(noLossDel);
        }
      #endif
    }
  }
}

void Tact_Press(){
  for (int a=0; a<TACT_SWITCHES; a++){
    if(digitalRead(tSwitchPin[a]) != tState[a] && millis() - tDebT[a] > dbTime){
      tState[a] = !tState[a];
      tDebT[a] = millis();
      if(tState[a]==HIGH){//at press
        Keyboard.write(tKeys[a]);
        delay(noLossDel);
      }
    }
  }
}

void LifeCheck(){
  if(lifeCount <= 11 && millis()-lifeTime > 200){
    lifeTime = millis();
    lifeCount++;
    LEDstate =! LEDstate;
  }
  digitalWrite(aLEDpin, LEDstate);
}
