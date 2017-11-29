#include <Gamer.h>
#include "display.h"

// Make a copy of the library
Gamer gamer;
/*
 * TODO
 *------------------- 
 *  1-Simplify the code
 *  2-make it more understandable
 *  3-optimize it
 */
//Modes
/*
* 0 = Tempo
* 1 = Time Signature
* 2 = tap_tempo
* 3 = stored_music
*/
byte MODE = 0;

//Animation
  int displayCount = 0;
  bool reverseMode = false;
//metronome
int noteDuration = 96;
byte bpm = 120;
int tempoDelay = (60.000/bpm)*1000; // get the delay between beeps
float lastMills = 0-tempoDelay;
int barCount = 0;
byte beats = 4;
bool metronomeStart = false;
byte maxBPM = 255;
int displayDelay = 100;
float displayMills = 0-displayDelay;
int currentPreset = 0;
byte presets[] = {126,98,88,120,124,120,94,140,94,150,88,136,96};

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
     if (millis() > displayMills+displayDelay){
         showNumbers();
     }
  }
}

void animateMetronome(){
    //Si excede la longitud deja de pintar cuadros
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
      //Serial.print("barcount:");
      //Serial.println(barCount);
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
  else{ //presets
    getNumberDisplay(presets[currentPreset]);
    gamer.printImage(display[0]);
  }
  delay(50);
}

void getNumberDisplay(int number){
    int digits[3] = {0,0,0};
    for(int j = 0; j<3; j++ )
    {
      //Serial.println(number % 10);
      digits[j] = number % 10;
      number /= 10;
    }
    for(int i = 0; i<8;i++){
      if(MODE == 1){
        display[0][i]= right_numbers[digits[1]][i] | middle_numbers[digits[0]][i] | bar[0][i] ;
      }
      else if (MODE == 2){
        display[0][i]=right_numbers[digits[2]][i] | middle_numbers[digits[1]][i]  | left_numbers[digits[0]][i] | preset_logo[0][i];
      }
      else{
        display[0][i]=right_numbers[digits[2]][i] | middle_numbers[digits[1]][i]  | left_numbers[digits[0]][i] ;
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
    else if(MODE == 2){
      presetInputs();//TODO IMPLEMENT
      bpm = presets[currentPreset];
      resetMetronome();
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

void presetInputs(){
  if(currentPreset > 12 ){currentPreset = 12;}
  else if(currentPreset < 0){currentPreset =0; }
  if(gamer.isPressed(UP)){
    currentPreset += 1;
    bpm = presets[currentPreset];
    resetMetronome();
    gamer.playTone(0);
    gamer.stopTone();
  }
  else if(gamer.isPressed(DOWN))
  {
    currentPreset -= 1;
    bpm = presets[currentPreset];
    resetMetronome();
    gamer.playTone(0);
    gamer.stopTone();
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
  tempoDelay = (60.000/bpm)*1000; //recalcular el delay porque el bpm puede canviar
  lastMills = 0-tempoDelay;
  barCount = 0;
  gamer.clear();
  //gamer.stopTone();
}

void doMetronome(){
  long mills = millis();
  if(mills > lastMills+noteDuration){
    //gamer.stopTone();
    if(beats==1){
      gamer.printImage(cls[0]);
    }
    
  }
  if (mills > lastMills+tempoDelay) {
    if (barCount == beats) { // 4 beeps(or more) in a bar
      barCount = 0;
    }      
    if (barCount == 0) {
       //gamer.playTone(255);
    } else {
       //gamer.playTone(128);
    }
    animateMetronome();
    barCount++;
    lastMills = mills;
  }
}  
