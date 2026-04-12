const int mais = 2;
const int menos = 3;
const int motor = 9;

int pwm = 0;

bool ultimoMais = HIGH;
bool ultimoMenos = HIGH;

void setup() {
  pinMode(mais, INPUT_PULLUP);
  pinMode(menos, INPUT_PULLUP);
}

void loop() {

  bool leituraMais = digitalRead(mais);
  bool leituraMenos = digitalRead(menos);

  // clique +
  if (ultimoMais == HIGH && leituraMais == LOW) {
    pwm += 25;
  }

  // clique -
  if (ultimoMenos == HIGH && leituraMenos == LOW) {
    pwm -= 25;
  }

  ultimoMais = leituraMais;
  ultimoMenos = leituraMenos;

  // limites
  pwm = constrain(pwm, 0, 255);

  analogWrite(motor, pwm);
}