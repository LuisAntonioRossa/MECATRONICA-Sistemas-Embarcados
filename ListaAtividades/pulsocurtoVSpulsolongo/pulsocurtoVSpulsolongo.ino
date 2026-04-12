const int botao = 4;
const int led1 = 2;
const int led2 = 3;
unsigned long tempoPress = 0;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  if (digitalRead(botao) == LOW) {
    tempoPress = millis();

    while (digitalRead(botao) == LOW);

    unsigned long duracao = millis() - tempoPress;

    if (duracao < 1000) digitalWrite(led1, HIGH);
    if (duracao > 2000) digitalWrite(led2, HIGH);
  }
}