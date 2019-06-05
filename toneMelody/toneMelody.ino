/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_A5,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_G5,
  NOTE_,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_E5,NOTE_CS5,NOTE_D5,
  NOTE_, NOTE_,NOTE_A5,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_G5,
  NOTE_,NOTE_D5,NOTE_D5,NOTE_D5,NOTE_FS5,NOTE_CS5,NOTE_D5,
  NOTE_,NOTE_D5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_G5,
  NOTE_,NOTE_D5,NOTE_FS5,NOTE_E5,NOTE_E5,NOTE_FS5,NOTE_FS5,
  NOTE_,NOTE_D5,NOTE_FS5,NOTE_FS5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5, NOTE_D5, NOTE_D5,
  NOTE_,NOTE_D5,NOTE_D5,NOTE_FS5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_B5,
  NOTE_,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_A5,NOTE_G5,NOTE_FS5,
  NOTE_,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_A5,NOTE_A5,NOTE_E5,
  NOTE_,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_G5,NOTE_FS5,NOTE_FS5,
  NOTE_,NOTE_D5,NOTE_FS5,NOTE_A5,NOTE_A5,NOTE_A5,NOTE_B5,
  NOTE_,NOTE_B5,NOTE_B5,NOTE_A5,NOTE_A5,NOTE_FS5,
  NOTE_,NOTE_D5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_G5,NOTE_G5,NOTE_E5,
  NOTE_,NOTE_E5,NOTE_E5,NOTE_E5,NOTE_G5,NOTE_FS5,NOTE_FS5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4
  
};
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
const int buttonPin = 7;
int buttonState = 0;
byte colDataMatrix[8] = { B01111111,
   B10111111,
   B11011111,
   B11101111,
   B11110111,
   B11111011,
   B11111101,
   B11111110
  };
                      
byte rowDataMatrix[8] = { B01000100,
                          B10101010,
                          B00000000,
                          B00000000,
                          B01111100,
                          B00101000,
                          B00010000,
                          B00000000
  };
  byte rowDataMatrix1[8] = {
                          B11111111,
                          B01000000,
                          B00100100,
                          B00011000,
                          B00011000,
                          B00100100,
                          B00000010,
                          B11111111
  };
  // 定義顯示器顯示的時間 (延遲時間), 預設 1ms
int delay_time = 1;
       

void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);
  // iterate over the notes of the melody:

}

void loop() {
buttonState = digitalRead(buttonPin);
if(buttonState == LOW){
 
for(int i = 0; i < 8 ; i++){

digitalWrite(latchPin,LOW);

shiftOut(dataPin, clockPin, MSBFIRST, colDataMatrix[i]);
shiftOut(dataPin, clockPin, MSBFIRST, rowDataMatrix[i]);

digitalWrite(latchPin,HIGH);
delay(delay_time);
  }

}
else if(buttonState == HIGH){
    for (int thisNote = 0; thisNote < 114; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(3, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(3);
         }
  for(int i = 0; i < 8 ; i++){
digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, colDataMatrix[i]);  //mask(col)
  shiftOut(dataPin, clockPin, rowDataMatrix1[i]);  //row
  digitalWrite(latchPin, 1);
  }
  
}

}

void pickDigit(int x) {

byte rowByte = 1 << x;

shiftOut(dataPin, clockPin, MSBFIRST, rowByte);

}
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {



  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);


  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);


  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);


    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {        
      pinState= 0;
    }

   
    digitalWrite(myDataPin, pinState);

    digitalWrite(myClockPin, 1);
  
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}
