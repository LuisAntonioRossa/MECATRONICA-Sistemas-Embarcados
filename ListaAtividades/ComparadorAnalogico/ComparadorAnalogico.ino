const int pot = A0;  // potenciômetro
const int led = 2;   // LED de saída

unsigned long tempoAnterior = 0; // controle de tempo (para piscar)

void setup() {
  pinMode(led, OUTPUT); // define LED como saída
}

void loop() {
  int valor = analogRead(pot); // lê de 0 a 1023

  //  ABAIXO DE 2V (≈ 409)
  if (valor <= 409) {
    digitalWrite(led, LOW); // LED desligado
  }

  //  ENTRE 2V E 4V
  else if (valor > 409 && valor < 818) {

    // usa millis para piscar sem travar
    if (millis() - tempoAnterior >= 300) {
      tempoAnterior = millis();

      // inverte o LED (pisca)
      digitalWrite(led, !digitalRead(led));
    }
  }

  // ACIMA DE 4V
  else {
    digitalWrite(led, HIGH); // LED sempre ligado
  }
}