const int ntc = A0;
const int aquecedor = 2;

//  limites 
int limiteBaixo = 600; // temperatura baixa (~ ligar)
int limiteAlto = 500;  // temperatura alta (~ desligar)

// estado do sistema (histerese)
bool ligado = false;

void setup() {
  pinMode(aquecedor, OUTPUT);
}

void loop() {

  int valor = analogRead(ntc);

  //  LIGA quando está "frio"
  if (valor >= limiteBaixo) {
    ligado = true;
  }

  //  DESLIGA quando está "quente"
  if (valor <= limiteAlto) {
    ligado = false;
  }

  // aplica no LED
  digitalWrite(aquecedor, ligado);
}