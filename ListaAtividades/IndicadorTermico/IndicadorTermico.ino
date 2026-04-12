const int ntc = A0;
const int leds[] = {2,3,4,5};

void setup() {
  for (int i = 0; i < 4; i++) pinMode(leds[i], OUTPUT);
}

void loop() {
  int valor = analogRead(ntc);

  int nivel = 0;

  if (valor < 700) nivel = 1;
  if (valor < 600) nivel = 2;
  if (valor < 500) nivel = 3;
  if (valor < 400) nivel = 4;

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], i < nivel);
  }
}