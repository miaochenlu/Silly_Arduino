#include <LiquidCrystal.h>
#include "pitches.h"

const int speakerpin = 8;
const int TrigPin = 9; 
const int EchoPin = 10;
float cm; 
   
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50; 

const byte pinDT = 13;
const byte pinClk = 2;
const byte pinSw = 3;
volatile byte clk = LOW;
volatile byte lastClk = LOW;

int count;
int lastcount;

int flagclk = 0;
volatile byte sw = HIGH;
volatile byte lastsw = HIGH;
   
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int ledPin=14;

volatile int change=0;
void play1();
void play2();
void play3();
void play4();
void (*pf[])() = {play1, play2, play3, play4};

void play1()
{
    lastcount = 0;
    lcd.clear();  
    lcd.setCursor(0, 0); 
    lcd.print("The song of ZJU"); 
    beforeandnext();
    int melody[] = {
        330, 330, 330, 392, 262, 294, 349, 330, 
        392, 440, 392, 349, 440, 440, 494, 440, 392, 
        392, 1046, 494, 440, 392, 349, 330, 440, 294, 330, 294, 
        330, 330, 440, 440, 392, 392, 392, 392, 523, 494, 
        494, 523, 578, 523, 494, 440, 392, 294, 440, 112, 262
    };

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = {
        2, 2, 2, 1, 2, 1, 2, 1, 
        2, 2, 2, 2, 1, 2, 2, 2, 1, 
        2, 1, 4, 4, 4, 4, 2, 2, 2, 2, 1, 
        2, 2, 2, 4, 4, 2, 2, 2, 2, 1, 
        4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 1, 
    };

    for (int thisNote = 0; thisNote < sizeof(noteDurations)/sizeof(int); thisNote++) {
        if(change % 4 != 0) break;
        if(count != 0) break;
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        digitalWrite(ledPin, HIGH);
        delay(0.8 * pauseBetweenNotes);
        digitalWrite(ledPin, LOW);
        delay(0.2 * pauseBetweenNotes);
        noTone(8);
    }
    if(count != 0) (*pf[count])();
}

void play2()
{
    lastcount = 1;
    lcd.clear();  
    lcd.setCursor(0, 0); 
    lcd.print("Calabash boys"); 
    beforeandnext();

    int tune[] = {      
        294, 294, 370, 
        294, 294, 370, -1, 
        495, 495, 495, 441, 495, 
        441, 294, 370, -1, 
        589, 495, 495, 441, 495, 
        441, 294, 330, -1, 
        556, 556, 441, 370, 
        441, 
    };

    float duration[] = {
        1, 1, 1+1, 
        0.5, 1, 1+0.5, 1, 
        1, 1, 0.5, 0.5, 1, 
        0.5, 1, 1+0.5, 1, 
        0.5, 0.5, 0.5, 0.5, 1+1, 
        0.5, 1, 1+0.5, 1, 
        1+1, 0.5, 0.5, 1, 
        1+1+1+1, 
    };
    int length;

    length = sizeof(tune) / sizeof(tune[0]);
    for(int x = 0; x < length; x++) {
        if(change % 4 != 0) break;
        if(count != 1) break;
        tone(8, tune[x]);
        digitalWrite(ledPin, HIGH);
        delay(300 * duration[x]);
        digitalWrite(ledPin, LOW);
        delay(100 * duration[x]);
        noTone(8);
    }
    if(count != 1) (*pf[count])();
}

void play3()
{
    lastcount = 2;
    lcd.clear();  
    lcd.setCursor(0, 0); 
    lcd.print("Castle in the sky"); 
    beforeandnext();

    int tune[] =  {  
      // NOTE_D0, NOTE_D0, NOTE_D0, NOTE_D6, NOTE_D7, NOTE_DH1, NOTE_D7, NOTE_DH1, NOTE_DH3, NOTE_D7, NOTE_D7, NOTE_D7, NOTE_D3, NOTE_D3, 
      // NOTE_D6, NOTE_D5, NOTE_D6, NOTE_DH1, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D3, NOTE_D4, NOTE_D3, NOTE_D4, NOTE_DH1, 
      // NOTE_D3, NOTE_D3, NOTE_D0, NOTE_DH1, NOTE_DH1, NOTE_DH1, NOTE_D7, NOTE_D4, NOTE_D4, NOTE_D7, NOTE_D7
       -1, -1, -1, 495, 556, 589, 556, 589, 700, 556, 556, 556, 370, 370, 
       495, 441, 495, 589, 441, 441, 441, 370, 393, 370, 393, 589, 
       370, 370, -1, 589, 589, 589, 556, 393, 393, 556, 556
    };

    float duration[]= {  
        1, 1, 1, 0.5, 0.5,      
        1+0.5, 0.5, 1, 1,      
        1, 1, 1, 0.5, 0.5, 
        1+0.5, 0.5, 1, 1,      
        1, 1, 1, 1,           
        1+0.5, 0.5, 1, 1,  
        1, 1, 0.5, 0.5, 0.5, 0.5,     
        1+0.5, 0.5, 1, 1, 1
    };

    int length;
    length = sizeof(tune) / sizeof(tune[0]);
    for(int x = 0; x < length; x++) {
        if(change % 4 != 0) break;
        if(count != 2) break;
        tone(8, tune[x]);
        digitalWrite(ledPin, HIGH);
        delay(700 * duration[x]);
        digitalWrite(ledPin, LOW);
        delay(100 * duration[x]);
        noTone(8);
    }
    if(count != 2) (*pf[count])();
}

void play4()
{
    lastcount = 3;
    lcd.clear();  
    lcd.setCursor(0, 0); 
    lcd.print("super mario"); 
    beforeandnext();

    int melody[] = {
        NOTE_E7, NOTE_E7, 0, NOTE_E7,
        0, NOTE_C7, NOTE_E7, 0,
        NOTE_G7, 0, 0,  0,
        NOTE_G6, 0, 0, 0,
       
        NOTE_C7, 0, 0, NOTE_G6,
        0, 0, NOTE_E6, 0,
        0, NOTE_A6, 0, NOTE_B6,
        0, NOTE_AS6, NOTE_A6, 0,
       
        NOTE_G6, NOTE_E7, NOTE_G7,
        NOTE_A7, 0, NOTE_F7, NOTE_G7,
        0, NOTE_E7, 0, NOTE_C7,
        NOTE_D7, NOTE_B6, 0, 0,
       
        NOTE_C7, 0, 0, NOTE_G6,
        0, 0, NOTE_E6, 0,
        0, NOTE_A6, 0, NOTE_B6,
        0, NOTE_AS6, NOTE_A6, 0,
       
        NOTE_G6, NOTE_E7, NOTE_G7,
        NOTE_A7, 0, NOTE_F7, NOTE_G7,
        0, NOTE_E7, 0, NOTE_C7,
        NOTE_D7, NOTE_B6, 0, 0
    };

    int tempo[] = {
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
       
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
       
        9, 9, 9,
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
       
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
       
        9, 9, 9,
        12, 12, 12, 12,
        12, 12, 12, 12,
        12, 12, 12, 12,
    };

    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) 
    {
        if(change % 4 != 0) break;
        if(count != 3) break;
        int noteDuration = 1000 / tempo[thisNote];
   
        tone(8, melody[thisNote], noteDuration);
   
        int pauseBetweenNotes = noteDuration * 1.30;
        digitalWrite(ledPin, HIGH);
        delay(0.8 * pauseBetweenNotes);
        digitalWrite(ledPin, LOW);
        delay(0.2 * pauseBetweenNotes);
        noTone(8);
    }
    if(count != 3) (*pf[count])();
}



void beforeandnext()
{
    lcd.setCursor(0,1);
    lcd.print("pre");
    lcd.setCursor(12,1);
    lcd.print("next");
}


void setup() 
{ 
    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("welcome");
    
    Serial.begin(9600);
    pinMode(TrigPin, OUTPUT); 
    pinMode(EchoPin, INPUT); 
    pinMode(pinClk, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinSw, INPUT);
    digitalWrite(pinSw, HIGH);//加这句才会稳定
    attachInterrupt(digitalPinToInterrupt(pinClk), isp_clk, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinSw), modechange, CHANGE);
} 




void loop()
{
    if(change % 2 == 0 && change % 4 != 0) {
        while(1) {
            create();
            if(change % 4 == 0) break;
        }
    }
    if(change % 4 == 0 && change != 0) {
        (*pf[count])();
        while(1) {
            if(count != lastcount) (*pf[count])();
            if(change % 4 != 0) break; 
        }
    }
}

void create() 
{ 
    digitalWrite(TrigPin, LOW); 
    delayMicroseconds(2);       
    digitalWrite(TrigPin, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(TrigPin, LOW); 
    
    cm = pulseIn(EchoPin, HIGH) / 58.0; 
    cm = (int(cm * 100.0)) / 100.0; 
   
    if(cm >= 5 && cm < 6.5) {
        lcd.clear();  
        lcd.setCursor(0, 1); 
        lcd.print("Mode change"); 
        tone(speakerpin, 248);
        delay(500);
        noTone(8);
    }
    else if(cm >= 6.5 && cm < 8) {
        tone(speakerpin, 278);
        delay(500);
        noTone(8);
    }
    else if(cm >= 8&cm < 9.5) {
        tone(speakerpin, 294);
        delay(500);
        noTone(8);
    }
    else if(cm >= 9.5 && cm < 11) {
        tone(speakerpin, 330);
        delay(500);
        noTone(8);
    }
    else if(cm >= 11 && cm < 12.5) {
        tone(speakerpin, 350);
        delay(500);
        noTone(8);
    }
    else if(cm >= 12.5 && cm < 14) {
        tone(speakerpin, 393);
        delay(500);
        noTone(8);
    }
    else if(cm >= 14 && cm < 15.5) {
        tone(speakerpin, 441);
        delay(500);
        noTone(8);
    }
    else if(cm >= 15.5 && cm < 17) {
        tone(speakerpin, 495);
        delay(500);
        noTone(8);
    }
    else if(cm >= 17 && cm < 18.5) {
        tone(speakerpin, 556);
        delay(500);
        noTone(8);
    }
    else if(cm >= 18.5 && cm < 20) {
        tone(speakerpin, 589);
        delay(500);
        noTone(8);
    }
     // Serial.println(cm);
     delay(100); 
}



void isp_clk()
{
    int clk = digitalRead(pinClk); 
    int dt = digitalRead(pinDT); 
    if(clk != lastClk) {
        lastClk = clk;
        count += (clk != dt)? 1:-1; 

        if(count < 0) count = 3;
        if(count > 3) count = 0;
    }
    flagclk = 1;
}

void modechange()
{
    int sw = digitalRead(pinSw);
    if(sw != lastsw) {
        lastsw = sw;
        lcd.clear();  
        lcd.setCursor(0, 1); 
        lcd.print("Mode change"); 
        delay(100);
        lcd.clear();
        change += 1;
    }
}


