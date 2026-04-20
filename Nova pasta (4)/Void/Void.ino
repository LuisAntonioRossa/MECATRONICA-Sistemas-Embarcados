//usando VOID
const int ledPin = 13;

// Nossa função personalizada void
void piscarLed(int tempo, int vezes) {
  for (int i = 0; i < vezes; i++) {
    digitalWrite(ledPin, HIGH);
    delay(tempo);
    digitalWrite(ledPin, LOW);
    delay(tempo);
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  piscarLed(500, 3); // Chama a função para piscar 3 vezes
  delay(2000);
}