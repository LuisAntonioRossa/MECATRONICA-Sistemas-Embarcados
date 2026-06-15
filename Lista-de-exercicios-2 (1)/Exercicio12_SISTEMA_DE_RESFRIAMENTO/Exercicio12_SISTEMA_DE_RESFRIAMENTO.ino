// Exercício 12 - SISTEMA DE RESFRIAMENTO


// Entradas: botaoStart(START), botaoStop(STOP), S1(cilindroPosicionador avançado), S2(posição resfr.),
//           S3(saída)
// Saídas: esteira, cilindroPosicionador, V1(ventoinha resfriamento 5s), Ligada
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: esteira=ON; cilindroPosicionador=ON; Ligada=ON; estado=S1_AVANCA_C1

  [S1_AVANCA_C1]  esteira=ON, cilindroPosicionador=ON
    -> S1 (cilindroPosicionador avançado, peça passou): cilindroPosicionador=OFF(recua); estado=S2_M1_PARA_S2

  [S2_M1_PARA_S2]  esteira=ON
    -> S2: esteira=OFF; V1=ON; tInicio=millis(); estado=S3_RESFRIA

  [S3_RESFRIA]  V1=ON (5s)
    -> timer>=5s: V1=OFF; esteira=ON; estado=S4_SAIDA

  [S4_SAIDA]  esteira=ON
    -> S3: esteira=OFF; cilindroPosicionador=OFF; Ligada=OFF; estado=S0_IDLE

  botaoStop -> IDLE

PSEUDO-CÓDIGO:
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: esteira=ON;cilindroPosicionador=ON;Ligada=ON; estado=AVANCA_C1
    SE AVANCA_C1: SE S1: cilindroPosicionador=OFF; estado=M1_PARA_S2
    SE M1_PARA_S2: SE S2: esteira=OFF;V1=ON;tInicio=millis(); estado=RESFRIA
    SE RESFRIA: SE timer>=5s: V1=OFF;esteira=ON; estado=SAIDA
    SE SAIDA: SE S3: esteira=OFF;Ligada=OFF; estado=IDLE
*/
const int E12_B1 = 2;
const int E12_B0 = 3;
const int E12_S1 = 4;
const int E12_S2 = 5;
const int E12_S3 = 6;
const int E12_M1 = 7;
const int E12_LIG = 8;
const int E12_C1 = 9;
const int E12_V1 = 10;
enum Estado_Ex12 { E12_IDLE, E12_AVANCA_C1, E12_M1_PARA_S2,
                   E12_RESFRIA, E12_SAIDA };

Estado_Ex12 estadoEx12 = E12_IDLE;
unsigned long tInicioEx12 = 0;

void ex12_setup() {
  for (int p : {E12_B1,E12_B0}) pinMode(p, INPUT_PULLUP);
  for (int p : {E12_S1,E12_S2,E12_S3}) pinMode(p, INPUT);
  for (int p : {E12_M1,E12_LIG,E12_C1,E12_V1}) pinMode(p, OUTPUT);
}

void ex12_loop() {
  bool botaoStart = !digitalRead(E12_B1), botaoStop = !digitalRead(E12_B0);
  bool s1 = digitalRead(E12_S1), s2 = digitalRead(E12_S2);
  bool s3 = digitalRead(E12_S3);
  unsigned long agora = millis();

  if (botaoStop) {
    estadoEx12 = E12_IDLE;
    for (int p : {E12_M1,E12_LIG,E12_C1,E12_V1}) digitalWrite(p, LOW);
    return;
  }

  switch (estadoEx12) {
    case E12_IDLE:
      if (botaoStart) {
        digitalWrite(E12_M1, HIGH); digitalWrite(E12_C1, HIGH);
        digitalWrite(E12_LIG, HIGH);
        estadoEx12 = E12_AVANCA_C1;
      }
      break;
    case E12_AVANCA_C1:
      if (s1) { digitalWrite(E12_C1, LOW); estadoEx12 = E12_M1_PARA_S2; }
      break;
    case E12_M1_PARA_S2:
      if (s2) {
        digitalWrite(E12_M1, LOW); digitalWrite(E12_V1, HIGH);
        tInicioEx12 = agora; estadoEx12 = E12_RESFRIA;
      }
      break;
    case E12_RESFRIA:
      if (agora - tInicioEx12 >= 5000UL) {
        digitalWrite(E12_V1, LOW); digitalWrite(E12_M1, HIGH);
        estadoEx12 = E12_SAIDA;
      }
      break;
    case E12_SAIDA:
      if (s3) {
        digitalWrite(E12_M1, LOW); digitalWrite(E12_LIG, LOW);
        estadoEx12 = E12_IDLE;
      }
      break;
  }
}


