const int ntc = A0;
const int ledPWM = 2;
const int ledMax = 3;

void setup() {
  pinMode(ledMax, OUTPUT);
}

void loop() {
  int valor = analogRead(ntc);

  int temp30 = 400;
  int temp60 = 700;

  int pwm = 0;

  if (valor < temp30) {
    pwm = 51; // 20%
  }
  else if (valor < temp60) {
    pwm = map(valor, temp30, temp60, 51, 255);
  }
  else {
    pwm = 255;
    digitalWrite(ledMax, HIGH);
  }

  analogWrite(ledPWM, pwm);
}