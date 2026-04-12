const int botaoA = 2;
const int botaoB = 3;
const int maquina = 4;

unsigned long tempoA = 0;
unsigned long tempoB = 0;

void setup() {
  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(maquina, OUTPUT);
}

void loop() {
  if (digitalRead(botaoA) == LOW) tempoA = millis();
  if (digitalRead(botaoB) == LOW) tempoB = millis();

  if (abs((long)(tempoA - tempoB)) <= 200) {
    digitalWrite(maquina, HIGH);
  } else {
    digitalWrite(maquina, LOW);
  }
}