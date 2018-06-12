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
#define calibration_factor 22970 //kalibrasi untuk skala KG (22970), didapat dari hasil kalibrasi
#define DOUT 22 
#define CLK  24
HX711 scale(DOUT, CLK);

void setup() {
 //-------setup lcd------------------------------
  pinMode(ledPin, OUTPUT); 
  lcd.begin(16, 2); 
  //------setup sensor ping----------------------
  Serial.begin (9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //------setup Modul HX711----------------------
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

}

void loop() {
  //-------set kursor dan kecerahan lcd----------
  //lcd.print("  H1A015020"); 
  //lcd.setCursor(5,2);             
  potValue = analogRead(potPin);  
  kecerahan=map(potValue, 0, 1024, 0, 255); 
  analogWrite(ledPin, kecerahan);         
  //--------set nilai tinggi --------------------
  lcd.setCursor(0,0);
  lcd.print(" TINGGI BADAN :"); 
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  cm = ((200)-(duration/58.2));
  lcd.setCursor(5,1);
  lcd.print(         cm);
  lcd.print(" CM       ");
  
  delay(1000);
  //--------------------------------------------
  lcd.setCursor(0,0);
  lcd.print("  BERAT BADAN : ");
  lcd.setCursor(5,1);
  lcd.print(scale.get_units(), 1); //scale.get_units() returns a float
  
  lcd.print(" KG      "); 
  
  delay (1000);
}

