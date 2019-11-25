int value = 0;

void setup(){
pinMode(11, INPUT);
}
void loop(){
value = analogRead(11);
Serial.println(value);
delay(10);
}