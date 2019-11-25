#include <toneAC.h>

#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#define TRIGGER_PIN 6
#define ECHO_PIN 7
#define MAX_DISTANCE 64
LiquidCrystal_I2C lcd(0x27,16,2);
NewPing myHC_SR04(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

  int C_MAJOR[8] = {262, 294, 330, 349, 392, 440, 494, 523} ;  // array for C major scale/ quick major mode
  int CHROMATIC[13] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523} ;// array for chromatic scale/ advanced use mode
  int Value1 = 0;
  int Value2 = 0;
void setup() {
  
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  lcd.init()
  lcd.backlight();

  }


void loop() {
 if(digitalRead(3) == HIGH){
 Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
  Value2 = Value1/8;
 Serial.println(C_MAJOR[Value2]);
 Serial.println("Switch hit");
 toneAC(C_MAJOR[Value2]);
 delay(10);
}
else{
  Value1 =  myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
  Value2 = Value1/4;
  Serial.println(CHROMATIC[Value2]);
  toneAC(CHROMATIC[Value2]);
  delay(10);
}
if(digitalRead(4) == HIGH){
  
}
}
