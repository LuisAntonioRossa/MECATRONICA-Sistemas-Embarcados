const int botaoA = 4;
const int botaoB = 5;
const int ledPrensa = 2;
const int ledErro = 3;

unsigned long tempoA = 0;
unsigned long tempoB = 0;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(ledPrensa, OUTPUT);
  pinMode(ledErro, OUTPUT);
}

void loop() {
  if (digitalRead(botaoA) == LOW) {
    tempoA = millis();
  }

  if (digitalRead(botaoB) == LOW) {
    tempoB = millis();
  }

  // verifica diferença de tempo
  if (abs((long)(tempoA - tempoB)) <= 500) {
    digitalWrite(ledPrensa, HIGH);
    digitalWrite(ledErro, LOW);
  } else {
    digitalWrite(ledPrensa, LOW);
    digitalWrite(ledErro, HIGH);
  }
}