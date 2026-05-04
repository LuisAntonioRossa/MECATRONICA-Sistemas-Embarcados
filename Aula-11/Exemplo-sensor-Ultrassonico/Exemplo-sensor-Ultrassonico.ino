#include <Ultrasonic.h>

Ultrasonic ultrasonic(12, 13);
int distance;

const int led = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  distance = ultrasonic.read();

  if(distance <= 10){
    digitalWrite(led, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }
  if(distance > 10 && distance <= 20){
    digitalWrite(led, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }
  if(distance > 20 && distance <= 30){
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
   }
  if(distance > 30 && distance <= 40){
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    }
}
