//Criar um programa que faça um LED piscar vinte vezes usando for.//
int led = 8; 

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(led, HIGH); 
    delay(500);             
    digitalWrite(led, LOW);  
    delay(500);              
  }

  while(true); // para o programa depois de piscar 20 vezes
}