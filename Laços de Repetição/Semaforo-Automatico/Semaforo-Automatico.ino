//Semáforo automatico//
int leds[3] = {8,9,10};
int tempos[3] = {5000, 2000, 4000};

void setup() {
  // configura todos os pinos como saída
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // percorre cada cor do semáforo
  for (int i = 0; i < 3; i++) {
    
    // apaga todos antes
    for (int j = 0; j < 3; j++) {
      digitalWrite(leds[j], LOW);
    }

    // liga o LED atual
    digitalWrite(leds[i], HIGH);

    // espera o tempo definido
    delay(tempos[i]);
  }
}