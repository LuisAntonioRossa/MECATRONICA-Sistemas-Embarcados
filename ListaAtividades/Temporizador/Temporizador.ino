const int botao = 3;
const int led = 2;

unsigned long inicio = 0;
bool ligado = false;

bool ultimoBotao = HIGH;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {

  bool leitura = digitalRead(botao);

  // clique
  if (ultimoBotao == HIGH && leitura == LOW) {
    ligado = true;
    inicio = millis();
  }

  ultimoBotao = leitura;

  if (ligado) {
    digitalWrite(led, HIGH);

    if (millis() - inicio >= 5000) {
      ligado = false;
      digitalWrite(led, LOW);
    }
  }
}