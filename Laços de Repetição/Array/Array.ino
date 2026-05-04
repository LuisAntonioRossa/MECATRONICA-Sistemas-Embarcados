// Uso de Arrays //
int leds[3] = {8,9,10};
void setup() {
 for(int i=0; i<3; i++){
 pinMode(leds[i], OUTPUT);
 }
}
void loop() {
 for(int i=0; i<3; i++){
 digitalWrite(leds[i], HIGH);
 delay(300);
 digitalWrite(leds[i], LOW);
 }
}