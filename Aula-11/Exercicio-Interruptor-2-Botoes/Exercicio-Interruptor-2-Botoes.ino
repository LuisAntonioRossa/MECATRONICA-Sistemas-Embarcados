const int ledPin = 9;
const int interruptPin= 2;
const int interruptPin2= 3;
bool state = LOW;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
   attachInterrupt(digitalPinToInterrupt(interruptPin2), blink2, FALLING);
}
void loop(){
  digitalWrite(ledPin, state);
}
void blink(){
  state = !state;
}
void blink2(){
  state = !state;
}