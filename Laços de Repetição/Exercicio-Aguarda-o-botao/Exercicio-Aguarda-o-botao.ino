//Outro método de aguardo do botão além do exmeplo
int botao = 2;   
int led = 13;   

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  // fica preso aqui até o botão ser pressionado
  while (digitalRead(botao) == HIGH) {
    // não faz nada, só espera
  }

  // quando sair do while
  digitalWrite(led, HIGH); 
}