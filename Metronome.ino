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

//Animation
  int displayCount = 0;
  bool reverseMode = false;
//metronome
int noteDuration = 15;
int bpm = 120;
int del = (60/(float)bpm)*1000-noteDuration; // get the delay between beeps
float lastMills = 0-del;
int barCount = 0;
int beats = 4;
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
void animateMetronome(){

    if(barCount >= NUMFRAMESIMAGES){
      gamer.printImage(spaceship[displayCount]);
      
      
      if (reverseMode){
        displayCount -= 1;
      }
      else{
        displayCount += 1;
      }
      
      if(displayCount == SPACESHIPFRAMESIMAGES){
        reverseMode = true;
        displayCount -= 2;
      }else if(displayCount<=0){
        reverseMode = false;
      }
      
    }
    else{
      Serial.print("barcount:");
      Serial.println(barCount);
      gamer.printImage(images[barCount]);
    }
}
void showNumbers(){
  if(MODE == 0){
    getNumberDisplay(bpm);
    gamer.printImage(display[0]);
  }
  else if(MODE == 1){
    getNumberDisplay(beats);
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
        display[0][i]= right_numbers[digits[1]][i] | middle_numbers[digits[0]][i] | bar[0][i] ;
      }
    }
    
}
void readInputs(){
  if(!metronomeStart){
    if(MODE == 0){
      tempoInputs();
    }
    else if(MODE == 1){
      timeInputs();
    }
    else{
      MODE = 0;
    }
    if(gamer.isPressed(LEFT)){
      MODE -= 1;
    }
    if(gamer.isPressed(RIGHT)){
      MODE += 1;
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
  if(beats > 64 || beats <= 0){beats = 1;}
  if(gamer.isPressed(UP)){
    beats += 1;
  }
  else if(gamer.isPressed(DOWN))
  {
    beats -= 1;
  }
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
    animateMetronome();
    barCount++;
    lastMills = mills;
  }
}  
