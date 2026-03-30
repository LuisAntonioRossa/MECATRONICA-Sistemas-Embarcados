const int botaoPin = 3;
const int ledPin = 8;

int estadoBotao = HIGH;
int ultimoEstadoBotao = HIGH;

unsigned long ultimoTempoDebounce = 0;
unsigned long delayDebounce = 50; 

void setup() {
  pinMode(botaoPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int leitura = digitalRead(botaoPin);

  if (leitura != ultimoEstadoBotao) {
    ultimoTempoDebounce = millis();
  }

  if ((millis() - ultimoTempoDebounce) > delayDebounce) {
    if (leitura != estadoBotao) {
      estadoBotao = leitura;

      if (estadoBotao == LOW) {
        digitalWrite(ledPin, !digitalRead(ledPin)); 
      }
    }
  }

  ultimoEstadoBotao = leitura;
}