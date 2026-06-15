// Exercício 10 - FURADEIRA AUTOMÁTICA


// Entradas: botaoStart(START), S1(cilindroFixador avançado=peça presa), S2(cilindroFuracao avançado=brocou),
//           S3(cilindroFuracao recuado), S4(cilindroFixador recuado)
// Saídas: cilindroFixador(fixador), cilindroFuracao(furadeira avança/recua), motorFuradeira(motor furadeira), Ligada
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: Ligada=ON; cilindroFixador=ON; estado=S1_FIXA_PECA

  [S1_FIXA_PECA]  cilindroFixador=ON (avança fixando)
    -> S1 (cilindroFixador avançado): motorFuradeira=ON; cilindroFuracao=ON; estado=S2_PERFURA_AVANCA

  [S2_PERFURA_AVANCA]  cilindroFuracao=ON, motorFuradeira=ON
    -> S2 (cilindroFuracao avançado): cilindroFuracao=OFF(recua); estado=S3_PERFURA_RECUA

  [S3_PERFURA_RECUA]  motorFuradeira=ON (furadeira voltando)
    -> S3 (cilindroFuracao recuado): motorFuradeira=OFF; cilindroFixador=OFF; estado=S4_SOLTA_PECA

  [S4_SOLTA_PECA]  cilindroFixador recuando
    -> S4 (cilindroFixador recuado): Ligada=OFF; estado=S0_IDLE (pronto novo ciclo)

PSEUDO-CÓDIGO:
  LOOP:
    SE IDLE: SE botaoStart: Ligada=ON; cilindroFixador=ON; estado=FIXA
    SE FIXA: SE S1: motorFuradeira=ON; cilindroFuracao=ON; estado=PERFURA_AVANCA
    SE PERFURA_AVANCA: SE S2: cilindroFuracao=OFF; estado=PERFURA_RECUA
    SE PERFURA_RECUA: SE S3: motorFuradeira=OFF; cilindroFixador=OFF; estado=SOLTA
    SE SOLTA: SE S4: Ligada=OFF; estado=IDLE
*/
const int E10_B1 = 2;
const int E10_S1 = 3;
const int E10_S2 = 4;
const int E10_S3 = 5;
#define E10_S4   6   // cilindroFixador recuado (sem botão stop neste exercício)
const int E10_C1 = 7;
const int E10_C2 = 8;
const int E10_M1 = 9;
const int E10_LIG = 10;
enum Estado_Ex10 { E10_IDLE, E10_FIXA, E10_PERF_AVANCA,
                   E10_PERF_RECUA, E10_SOLTA };

Estado_Ex10 estadoEx10 = E10_IDLE;

void ex10_setup() {
  pinMode(E10_B1, INPUT_PULLUP);
  for (int p : {E10_S1,E10_S2,E10_S3,E10_S4}) pinMode(p, INPUT);
  for (int p : {E10_C1,E10_C2,E10_M1,E10_LIG}) pinMode(p, OUTPUT);
}

void ex10_loop() {
  bool botaoStart = !digitalRead(E10_B1);
  bool s1 = digitalRead(E10_S1), s2 = digitalRead(E10_S2);
  bool s3 = digitalRead(E10_S3), s4 = digitalRead(E10_S4);

  switch (estadoEx10) {
    case E10_IDLE:
      if (botaoStart) {
        digitalWrite(E10_LIG, HIGH);
        digitalWrite(E10_C1, HIGH);
        estadoEx10 = E10_FIXA;
      }
      break;
    case E10_FIXA:
      if (s1) {
        digitalWrite(E10_M1, HIGH);
        digitalWrite(E10_C2, HIGH);
        estadoEx10 = E10_PERF_AVANCA;
      }
      break;
    case E10_PERF_AVANCA:
      if (s2) { digitalWrite(E10_C2, LOW); estadoEx10 = E10_PERF_RECUA; }
      break;
    case E10_PERF_RECUA:
      if (s3) {
        digitalWrite(E10_M1, LOW);
        digitalWrite(E10_C1, LOW);
        estadoEx10 = E10_SOLTA;
      }
      break;
    case E10_SOLTA:
      if (s4) {
        digitalWrite(E10_LIG, LOW);
        estadoEx10 = E10_IDLE;
      }
      break;
  }
}


