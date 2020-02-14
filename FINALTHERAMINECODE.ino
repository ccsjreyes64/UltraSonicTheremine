#include <NewPing.h> // includes NewPing library
#include <toneAC.h> // includes ToneAC library
#include <Wire.h> // I honestly have no clue but its necessary
#include <LiquidCrystal_I2C.h> // includes LiquidCrystal Library
#define TRIGGER_PIN 6 // sets trig pin for ultrasonic sensor to 6
#define ECHO_PIN 7 // sets echo pin for ultrasonic sensor to 7
#define MAX_DISTANCE 64 // sets maximum distance for ultrasonic sensor to 64 CM
LiquidCrystal_I2C lcd(0x3F, 16, 2); // declares lcd screen
NewPing myHC_SR04(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // declares pins for ultrasonic sensor
int C_MAJOR[8] =
{
  262, 294, 330, 349, 392, 440, 494, 523
}; // array for C major scale/ quick major mode

int CHROMATIC[13] =
{
  262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523
}; // array for chromatic scale/ advanced use mode

int C_MINOR[8] =
{
  262, 294, 311, 349, 392, 415, 466, 523
}; // array for C minor scale/ quick minor mode

int Bb_MAJOR[8] =
{
  233, 262, 294, 311, 349, 392, 440, 466
}; // array for Bb major scale/ quick major mode

int Bb_MINOR[8] =
{
  233, 262, 277, 311, 349, 370, 415, 466
}; // array for C minor scale/ quick minor mode

int G_MAJOR[8] =
{
  196, 220, 247, 262, 294, 330, 370, 392
}; // array for G major scale/ quick major mode

int G_MINOR[8] =
{
  196, 220, 233, 262, 294, 311, 349, 392
}; // array for G minor scale/ quick minor mode

int Value1 = 0; // value for array code (Used later)
int Value2 = 0; // value for array code (Used Later)
int PotValue = 0; // variable for the current value of the potentiometer
int melody = 0; // variable for freqency for speaker to play at

int ButtonPin = 2; // variable for Button Pin
int GamerSwitchPin = 3; // variable for Switch Pin

void setup()
{
  Serial.begin(9600); // begins serial monitor
  pinMode(3, INPUT); // declares pin as input
  pinMode(2, INPUT); // same as above
  lcd.init(); // initiates screen
  lcd.backlight(); // initiates screen backlight
  lcd.print("Mode:"); // permenantly prints "Mode:" on top of lcd
}

void loop()
{
  lcd.setCursor(0, 1); // sets the cursor of lcd on bottom of lcd
  PotValue = analogRead(0); // sets PotValue var to current value of potentiometer
  Serial.println(PotValue); // prints value of potentiometer for testing
 
  if (digitalRead(GamerSwitchPin) == LOW)
    // if switch is off
  {
    lcd.print("EPIC GAMER MODE"); // print "EPIC GAMER MODE" on bottom of lcd
    Value1 = myHC_SR04.ping(); // Make "Value1" ping in millimeters
    melody = Value1; // make speaker play frequency of the ultrasonic sensors ping
    delay(10);
  }
  else
    if (PotValue >= 0 && PotValue < 128.5)
      // if pot is in lowest position
  {
    lcd.print("C_MAJOR              "); // print "C_MAJOR" to bottom of lcd screen (spaces to clear past what is printed)
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3)); // converts the average of 3 pings of ultrasonic sensor to distance in CM
    Value2 = Value1/5; // determines length between notes (smaller denominator, smaller distance between note change)
    melody = C_MAJOR[Value2]; // sets melody respective to what number Value2 is
    Serial.println("C_MAJOR"); // Serial print "C_MAJOR" for testing
    delay(10); // ALL OTHER CODE FOR DIFFERENT SCALES WORKS THE SAME WAY BUT WITH DIFFERENT AND CORRESPONDING ARRAYS (I just didn't want to write when I didnt't need to)
  }
  else
    if (PotValue < 257)
      // if pot is in second lowest position
  {
    lcd.print("C_MINOR             ");
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
    Value2 = Value1/5;
    melody = C_MINOR[Value2];
    Serial.println("C_MINOR");
    delay(10);
  }
  else
    if (PotValue < 385.5)
      // if pot is in 3rd lowest position
  {
    lcd.print("Bb_MAJOR           ");
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
    Value2 = Value1/5;
    melody = Bb_MAJOR[Value2];
    Serial.println("Bb_MAJOR");
    delay(10);
  }
  else
    if (PotValue < 514)
      // if pot is in middle position
  {
    lcd.print("Bb_MINOR          ");
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
    Value2 = Value1/5;
    melody = Bb_MINOR[Value2];
    Serial.println("Bb_MINOR");
    delay(10);
  }
  else
    if (PotValue < 642.5)
      // if pot is in 3rd highest position
  {
    lcd.print("G_MAJOR           ");
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
    Value2 = Value1/6;
    melody = G_MAJOR[Value2];
    Serial.println("G_MAJOR");
    delay(10);
  }
  else
    if (PotValue < 771)
      // if pot is in second highest position
  {
    lcd.print("G_MINOR           ");
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
    Value2 = Value1/5;
    melody = G_MINOR[Value2];
    Serial.println("G_MINOR");
    delay(10);
  }
  else
    if (PotValue < 1028)
      // if pot is in highest position
  {
    lcd.print("CHROMATIC         ");
    Value1 = myHC_SR04.convert_cm(myHC_SR04.ping_median(3));
    Value2 = Value1/2.85;
    melody = CHROMATIC[Value2];
    Serial.println(Value2);
    Serial.println("CHROMATIC");
    delay(10);
  }

  if (digitalRead(ButtonPin) == LOW)
    // if the button is not pressed
  {
    Serial.println("off"); // print off on serial monitor for testing
    toneAC(); // makes the speaker make no sound
  }
  else
  {
    toneAC(melody);
    delay(10);
  }
}
