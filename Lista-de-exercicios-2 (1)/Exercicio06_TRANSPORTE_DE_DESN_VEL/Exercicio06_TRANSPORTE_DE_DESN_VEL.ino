// Exercício 6 - TRANSPORTE DE DESNÍVEL


// Entradas: botaoStart(START), botaoStop(STOP), S1(cilindroEmpurrador1 avançado), S2(peça na esteiraEntrada),
//           S3(cilindroEmpurrador2 avançado), S4(peça saiu esteiraSaida)
// Saídas: esteiraEntrada, esteiraSaida, cilindroEmpurrador1, cilindroEmpurrador2, Ligada
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: Ligada=ON; esteiraEntrada=ON; estado=S1_M1_ATIVA

  [S1_M1_ATIVA]  esteiraEntrada=ON
    -> S2 (peça detectada): esteiraEntrada=OFF; cilindroEmpurrador1 avança; estado=S2_C1_AVANCA

  [S2_C1_AVANCA]  cilindroEmpurrador1=ON
    -> S1 (cilindroEmpurrador1 no fim): cilindroEmpurrador1 mantém; cilindroEmpurrador2 avança; estado=S3_C2_AVANCA

  [S3_C2_AVANCA]  cilindroEmpurrador2=ON
    -> S3 (cilindroEmpurrador2 no fim): cilindroEmpurrador2 mantém; esteiraSaida=ON; estado=S4_M2_ATIVA

  [S4_M2_ATIVA]  esteiraSaida=ON
    -> S4 (peça passou): esteiraSaida=OFF; cilindroEmpurrador1=OFF; cilindroEmpurrador2=OFF; estado=S0_IDLE (novo ciclo)

  botaoStop -> IDLE; desliga tudo

PSEUDO-CÓDIGO:
  estado=IDLE
  LOOP:
    SE botaoStop: desliga tudo; IDLE; Ligada=OFF
    SE IDLE: SE botaoStart: Ligada=ON; esteiraEntrada=ON; estado=S1
    SE S1_M1_ATIVA: esteiraEntrada=ON; SE S2: esteiraEntrada=OFF; cilindroEmpurrador1=ON; estado=S2_C1_AVANCA
    SE S2_C1_AVANCA: cilindroEmpurrador1=ON; SE S1: cilindroEmpurrador2=ON; estado=S3_C2_AVANCA
    SE S3_C2_AVANCA: cilindroEmpurrador2=ON; SE S3: esteiraSaida=ON; estado=S4_M2_ATIVA
    SE S4_M2_ATIVA: esteiraSaida=ON; SE S4: esteiraSaida=OFF;cilindroEmpurrador1=OFF;cilindroEmpurrador2=OFF; estado=S0_IDLE
*/
const int E6_B1 = 22;
const int E6_B0 = 23;
const int E6_S1 = 24;
const int E6_S2 = 25;
const int E6_S3 = 26;
const int E6_S4 = 27;
const int E6_M1 = 30;
const int E6_M2 = 31;
const int E6_C1 = 32;
const int E6_C2 = 33;
const int E6_LIG = 34;
enum Estado_Ex6 { E6_IDLE, E6_M1_ATIVA, E6_C1_AVANCA,
                  E6_C2_AVANCA, E6_M2_ATIVA };

Estado_Ex6 estadoEx6 = E6_IDLE;

void ex6_setup() {
  pinMode(E6_B1, INPUT_PULLUP); pinMode(E6_B0, INPUT_PULLUP);
  pinMode(E6_S1, INPUT); pinMode(E6_S2, INPUT);
  pinMode(E6_S3, INPUT); pinMode(E6_S4, INPUT);
  pinMode(E6_M1, OUTPUT); pinMode(E6_M2, OUTPUT);
  pinMode(E6_C1, OUTPUT); pinMode(E6_C2, OUTPUT);
  pinMode(E6_LIG, OUTPUT);
}

void ex6_loop() {
  bool botaoStart = !digitalRead(E6_B1), botaoStop = !digitalRead(E6_B0);
  bool s1 = digitalRead(E6_S1), s2 = digitalRead(E6_S2);
  bool s3 = digitalRead(E6_S3), s4 = digitalRead(E6_S4);

  if (botaoStop) {
    estadoEx6 = E6_IDLE;
    digitalWrite(E6_M1, LOW); digitalWrite(E6_M2, LOW);
    digitalWrite(E6_C1, LOW); digitalWrite(E6_C2, LOW);
    digitalWrite(E6_LIG, LOW);
    return;
  }

  switch (estadoEx6) {
    case E6_IDLE:
      if (botaoStart) { digitalWrite(E6_LIG, HIGH); digitalWrite(E6_M1, HIGH); estadoEx6 = E6_M1_ATIVA; }
      break;
    case E6_M1_ATIVA:
      if (s2) { digitalWrite(E6_M1, LOW); digitalWrite(E6_C1, HIGH); estadoEx6 = E6_C1_AVANCA; }
      break;
    case E6_C1_AVANCA:
      if (s1) { digitalWrite(E6_C2, HIGH); estadoEx6 = E6_C2_AVANCA; }
      break;
    case E6_C2_AVANCA:
      if (s3) { digitalWrite(E6_M2, HIGH); estadoEx6 = E6_M2_ATIVA; }
      break;
    case E6_M2_ATIVA:
      if (s4) {
        digitalWrite(E6_M2, LOW); digitalWrite(E6_C1, LOW);
        digitalWrite(E6_C2, LOW); estadoEx6 = E6_IDLE;
      }
      break;
  }
}


