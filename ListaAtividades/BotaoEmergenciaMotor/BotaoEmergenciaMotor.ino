const int pot = A0;
const int emergencia = 3;
const int motor = 2;   // LED PWM (motor)
const int status = 4;  // LED de falha

unsigned long tempo = 0;
bool estadoPisca = false;

void setup() {
  pinMode(emergencia, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  pinMode(status, OUTPUT);
}

void loop() {

  //  EMERGÊNCIA ATIVADA
  if (digitalRead(emergencia) == LOW) {

    analogWrite(motor, 0);   //  FORÇA motor desligado

    // pisca LED de falha
    if (millis() - tempo >= 200) {
      tempo = millis();
      estadoPisca = !estadoPisca;
      digitalWrite(status, estadoPisca);
    }

    return; //  MUITO IMPORTANTE → trava o resto do código
  }

  //  FUNCIONAMENTO NORMAL
  int valor = analogRead(pot);

  int pwm = map(valor, 0, 1023, 0, 255);

  analogWrite(motor, pwm);

  digitalWrite(status, LOW); // LED apagado
}