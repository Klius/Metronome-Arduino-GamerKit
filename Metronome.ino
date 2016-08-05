#include <Gamer.h>
#include "display.h"

// Make a copy of the library
Gamer gamer;

//Modes
/*
* 0 = Tempo
* 1 = Time Signature
* 2 = tap_tempo
*/
int MODE = 0;

//metronome
int noteDuration = 15;
int bpm = 120;
int del = (60/(float)bpm)*1000-noteDuration; // get the delay between beeps
float lastMills = 0-del;
int barCount = 0;
int beats = 4;
int bars = 4;
int metronomeStart = false;
int maxBPM = 255;
int displayDelay = 100;
float displayMills = 0-displayDelay;


void setup() {
  // Start Gamer!
   Serial.begin(9600);
  gamer.begin();
}

void loop() {
  readInputs();
  if(metronomeStart){
    doMetronome();
  }else{  
   // gamer.clear();
     if (millis() > displayMills+displayDelay){
         showNumbers();
     }
  }

}
void showNumbers(){
  if(MODE == 0){
    getNumberDisplay(bpm);
    gamer.printImage(display[0]);
  }
  else if(MODE == 1){
    getNumberDisplay(beats*10+bars);
    gamer.printImage(display[0]);
  }
  delay(50);
}
void getNumberDisplay(int number){
    int digits[3] = {0,0,0};
    for(int j = 0; j<3; j++ )
    {
      Serial.println(number % 10);
      digits[j] = number % 10;
      number /= 10;
    }
    for(int i = 0; i<8;i++){
      if(MODE == 0){
        display[0][i]=right_numbers[digits[2]][i] | middle_numbers[digits[1]][i]  | left_numbers[digits[0]][i] ;
      }
      else{
        display[0][i]= right_numbers[digits[1]][i] | bar[0][i] | left_numbers[digits[0]][i] ;
      }
    }
    
}
void readInputs(){
  if(!metronomeStart){
    if(MODE == 0){
      tempoInputs();
    }
    if(MODE == 1){
      timeInputs();
    }
    if(gamer.isPressed(LEFT)){
    if (MODE-1 >= 0){
      MODE -= 1;
    }
  }
  if(gamer.isPressed(RIGHT)){
    if (MODE+1 <2){
      MODE += 1;
    }
  }
  }
  if(gamer.isPressed(START)){
    if (metronomeStart){
      metronomeStart=false;
      resetMetronome();
    }
    else{
      metronomeStart=true;
    }
  }
}
void timeInputs(){
}
void tempoInputs(){
if(gamer.isHeld(UP)) { 
      if(bpm +1 < maxBPM){
        bpm = bpm+1;
      }
      resetMetronome();
      gamer.playTone(0);
      gamer.stopTone();
    }
    else if(gamer.isHeld(DOWN)) {
      if(bpm -1 > 0){
        bpm = bpm-1;
      }
      resetMetronome();
      gamer.playTone(0);
      gamer.stopTone();
    }
}
void resetMetronome(){
  del = (60/(float)bpm)*1000-noteDuration; // get the delay between beeps
  lastMills = 0-del;
  barCount = 0;
  gamer.clear();
}
void doMetronome(){
  long mills = millis();
  if (mills > lastMills+del) {
    if (barCount == beats) { // 4 beeps in a bar
      barCount = 0;
    }      
    if (barCount == 0) {
       gamer.playTone(0);
       delay(noteDuration);
       gamer.stopTone();
    } else {
      gamer.playTone(128);
      delay(noteDuration);
      gamer.stopTone();
    }
    gamer.printImage(images[barCount]);
    barCount++;
    lastMills = mills;
  }
}  
