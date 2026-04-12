const int pot = A0;
const int valvula = 2;
const int alarme = 4;

bool podeAbrir = true; // memória do sistema

unsigned long tempoAnterior = 0;

void setup() {
  pinMode(valvula, OUTPUT);
  pinMode(alarme, OUTPUT);
}

void loop() {
  int nivel = analogRead(pot);

  int n80 = 819; // 80%
  int n95 = 972; // 95%
  int n30 = 307; // 30%

  //  nível crítico (transbordo)
  if (nivel >= n95) {
    podeAbrir = false; // trava o sistema
    digitalWrite(valvula, LOW); // fecha válvula

    // pisca alarme
    if (millis() - tempoAnterior >= 200) {
      tempoAnterior = millis();
      digitalWrite(alarme, !digitalRead(alarme));
    }
  }

  //  condição segura para reabrir
  else if (nivel <= n30) {
    podeAbrir = true;
    digitalWrite(alarme, LOW);
  }

  //  controle normal
  if (podeAbrir && nivel < n80) {
    digitalWrite(valvula, HIGH);
  } else {
    digitalWrite(valvula, LOW);
  }
}