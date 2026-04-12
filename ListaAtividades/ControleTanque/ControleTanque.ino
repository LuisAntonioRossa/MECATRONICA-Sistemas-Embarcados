const int nivel = A0;
const int temp = A1;
const int botao = 2;

const int valvula = 3;
const int aquecedor = 9;
const int alarme = 4;

bool sistema = false;
bool ultimoBotao = HIGH;

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(valvula, OUTPUT);
  pinMode(alarme, OUTPUT);
}

void loop() {

  // liga sistema
  bool leitura = digitalRead(botao);
  if (ultimoBotao == HIGH && leitura == LOW) {
    sistema = !sistema;
  }
  ultimoBotao = leitura;

  if (!sistema) {
    digitalWrite(valvula, LOW);
    analogWrite(aquecedor, 0);
    digitalWrite(alarme, LOW);
    return;
  }

  int n = analogRead(nivel);
  int t = analogRead(temp);

  //  nível
  if (n < 300) digitalWrite(valvula, HIGH);
  if (n > 800) digitalWrite(valvula, LOW);

  //  temperatura (NTC invertido)
  if (t > 600) {
    analogWrite(aquecedor, 200);
  }

  if (t < 500) {
    analogWrite(aquecedor, 0);
    digitalWrite(alarme, HIGH);
  } else {
    digitalWrite(alarme, LOW);
  }
}