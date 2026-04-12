const int led = 2;
const int botaoA = 3;
const int botaoB = 4;

unsigned long inicio = 0;
bool ligado = false;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
 if (digitalRead(botaoA) == LOW) {
    ligado = true;
    inicio = millis();
  }

  if (ligado) {
    digitalWrite(led, HIGH);

    if (millis() - inicio >= 5000 || digitalRead(botaoB) == LOW) {
      ligado = false;
      digitalWrite(led, LOW);
    }
  }
}
  
