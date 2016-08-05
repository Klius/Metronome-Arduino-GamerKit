#include <Gamer.h>
#include "display.h"

// Make a copy of the library
Gamer gamer;

//metronome
int noteDuration = 15;
int bpm = 120;
int del = (60/(float)bpm)*1000-noteDuration; // get the delay between beeps
float lastMills = 0-del;
int barCount = 0;
int bars = 20;
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
     if (millis() > inputMills+inputDelay){
       showNumbers();
     }
  }

}
void showNumbers(){
  getNumberDisplay();
  gamer.printImage(display[0]);
  delay(50);
}
void getNumberDisplay(){
    int bpm_digits[3] = {0,0,0};
    int copy_bpm = bpm;
    for(int j = 0; j<3; j++ )
    {
      Serial.println(copy_bpm % 10);
      bpm_digits[j] = copy_bpm % 10;
      copy_bpm /= 10;
    }
    for(int i = 0; i<8;i++){
      display[0][i]=right_numbers[bpm_digits[2]][i] | middle_numbers[bpm_digits[1]][i]  | left_numbers[bpm_digits[0]][i] ;
    }
    
}
void readInputs(){
  if(!metronomeStart){
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

void resetMetronome(){
  del = (60/(float)bpm)*1000-noteDuration; // get the delay between beeps
  lastMills = 0-del;
  barCount = 0;
  gamer.clear();
}
void doMetronome(){
  long mills = millis();
  if (mills > lastMills+del) {
    if (barCount == bars) { // 4 beeps in a bar
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
