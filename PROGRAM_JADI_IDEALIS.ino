#include <LiquidCrystal.h>
#include "HX711.h" //Header lokal untuk modul strain-gauge

//-------variabel dan pin lcd-------------------
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int potPin = A0;    // Analog pin 0 untuk mengatur kecerahan
int ledPin = 6;     // Pin PWM untuk LED
int potValue = 0;   // variable untuk mentimpan hasil dari potensio
int kecerahan = 0;  // Convert potValue menjadi kecerahan
//-------variabel sensor ping-------------------
int trig = 52;
int echo = 53; 
long duration, cm ;
//--------Variabel Modul HX711-------------------
#define calibration_factor 22970 //kalibrasi untuk skala KG (22970), didapat dari hasil kalibrasi xx
#define DOUT 22 
#define CLK  24
HX711 scale(DOUT, CLK);
//---------Variabel Idealis
long ideal;
long berat;
long kurangi;
long tambah;


void setup() {
 //-------setup lcd------------------------------
  pinMode(ledPin, OUTPUT); 
  lcd.begin(16, 2); 
  //------setup sensor ping----------------------
  Serial.begin (9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //------setup Modul HX711----------------------
  scale.set_scale(calibration_factor); //dapet dari nilai kalibrasi
  scale.tare(); //mereset nilai berat ke 0 ketika tak ada beban 

}

void loop() {
  berat=scale.get_units();
  delay(2000);
  if (berat>=20){
    //-------set kursor dan kecerahan lcd----------
    //lcd.print("  H1A015020"); 
    //lcd.setCursor(5,2);             
    potValue = analogRead(potPin);  
    kecerahan=map(potValue, 0, 1024, 0, 255); 
    analogWrite(ledPin, kecerahan);         
    //-------set nilai tinggi & tampilkan ----------
    lcd.setCursor(0,0);
    lcd.print(" TINGGI BADAN :"); 
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    pinMode(echo, INPUT);
    duration = pulseIn(echo, HIGH);
    cm = ((196)-(duration/58.2));// tinggi gantungan alat, bisa diubah sesuai keinginan 
    lcd.setCursor(5,1);
    lcd.print(         cm);
    lcd.print(" CM       ");
  
    delay(2000);
    //---------set nilai berat & tampilan ------------
    lcd.setCursor(0,0);
    lcd.print("  BERAT BADAN : ");
    lcd.setCursor(5,1);
    lcd.print(scale.get_units(), 1); //scale.get_units() returns a float
  
    lcd.print(" KG      "); 
    delay (2000);
    //---------set niali ideal & tampilkan-------------
    ideal= ((cm - 100)-((cm-100)*0.1)); //metode perhitungan berat ideal BROCA (tribute to Pierre Paul Broca)
    lcd.setCursor(0,0);
    lcd.print("  BERAT IDEAL : ");
    lcd.setCursor(5,1);
    lcd.print(ideal);
    lcd.print(" KG      ");
    delay(2000);
  if(ideal>berat){
    lcd.setCursor(0,0);
    lcd.print(" TAMBAH BB ANDA ");
    tambah=ideal-berat;
    lcd.setCursor(5,1);
    lcd.print(tambah);
    lcd.print(" KG      ");
    delay(2000);
    
  }//tutup ideal>berat
  if(ideal<berat){
    lcd.setCursor(0,0);
    lcd.print("KURANGI BB ANDA ");
    kurangi=berat-ideal;
    lcd.setCursor(5,1);
    lcd.print(kurangi);
    lcd.print(" KG      ");
    delay(2000);
  }//tutup ideal<berat
  else{
    lcd.setCursor(0,0);
    lcd.print("     ERROR      ");
    delay(2000);
    }//tutup else error
  }// tutup if berat > 20kg
  else {
    potValue = analogRead(potPin);  
    kecerahan=map(potValue, 0, 1024, 0, 255); 
    analogWrite(ledPin, kecerahan);
    lcd.setCursor(0,0);
    lcd.print("    WELCOME TO  ");
    lcd.setCursor(0,1);
    lcd.print("     IDEALIS    ");
    }//tutup else berat < 20kg
}//tutup void loop

