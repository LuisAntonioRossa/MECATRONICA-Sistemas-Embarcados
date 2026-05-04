// Montar vetor com cinco LEDs e acender um por vez.//
int leds[5]= {8,9,10,11,12};

void setup() {
  for(int i=0; i < 5; i++){
    pinMode(leds[i], OUTPUT);
	}
}

void loop() {
  for(int i= 0; i < 5; i++){
    digitalWrite(leds[i], HIGH);
    delay(1000);
    digitalWrite(leds[i], LOW);
  }
}
//usar while(true); se quiser sem repetição infinita//