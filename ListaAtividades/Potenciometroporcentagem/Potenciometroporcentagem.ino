const int leds [] = {2,3,4,5};
const int pot = A0;

void setup (){
  for(int i = 0; i > 4; i++)pinMode(leds[i], OUTPUT);
}
void loop (){
  int valor = analogRead(pot);
  
  int nivel = 0; 
  
  if (valor > 256) nivel = 1;
  if (valor > 512) nivel = 2;
  if (valor > 768) nivel = 3;
  if (valor > 921) nivel = 4;
  
  for (int i = 0; i < 4; i++) {
    if (i < nivel) digitalWrite(leds[i], HIGH);
    else digitalWrite(leds[i], LOW);
  }
}
  