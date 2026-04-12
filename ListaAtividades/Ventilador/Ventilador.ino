const int ntc = A0;
const int ventilador = 9; // PWM

void setup() {}

void loop() {
  int valor = analogRead(ntc);

  //  inverter (porque NTC é inverso)
  int pwm = map(valor, 700, 300, 0, 255);

  // limita faixa (segurança)
  pwm = constrain(pwm, 0, 255);

  analogWrite(ventilador, pwm);
}