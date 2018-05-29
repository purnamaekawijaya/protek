#include <LiquidCrystal.h>

//-------variabel dan pin lcd-------------------
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int potPin = A0;    // Analog pin 0 untuk mengatur kecerahan
int ledPin = 6;     // Pin PWM untuk LED
int potValue = 0;   // variable untuk mentimpan hasil dari potensio
int kecerahan = 0;  // Convert potValue menjadi kecerahan
//-------variabel sensor ping-------------------
int trig = 8;
int echo = 9; 
long duration, cm ;



void setup() {
 //-------setup lcd------------------------------
  pinMode(ledPin, OUTPUT); 
  lcd.begin(16, 2); 
  lcd.print(" TINGGI BADAN :"); 
  lcd.setCursor(0,1);
  //------setup sensor ping----------------------
  Serial.begin (9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  //-------set kursor dan kecerahan lcd----------
  //lcd.print("  H1A015020"); 
  lcd.setCursor(5,2);             
  potValue = analogRead(potPin);  
  kecerahan=map(potValue, 0, 1024, 0, 255); 
  analogWrite(ledPin, kecerahan);         
  //---------------------------------------------
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  cm = ((200)-(duration/58.2));
  lcd.print(         cm);
  lcd.print(" CM       ");
  lcd.println();
  delay(500);
}
