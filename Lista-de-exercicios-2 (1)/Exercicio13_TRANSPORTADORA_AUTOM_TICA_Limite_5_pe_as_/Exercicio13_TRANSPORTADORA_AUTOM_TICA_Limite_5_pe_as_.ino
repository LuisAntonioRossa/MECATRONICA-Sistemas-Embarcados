// Exercício 13 - TRANSPORTADORA AUTOMÁTICA (Limite 5 peças)


// Entradas: botaoStart(START), botaoStop(STOP), S1(entrada esteiraEntrada), S2(fim esteiraEntrada/início esteiraSaida),
//           S3(fim esteiraSaida)
// Saídas: esteiraEntrada, esteiraSaida, Ligada, LimitePecas(após 5 ciclos)
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: Ligada=ON; aguarda S1; estado=S1_AGUARDA_PECA

  [S1_AGUARDA_PECA]
    -> S1 ativo: esteiraEntrada=ON; estado=S2_M1_ATIVA

  [S2_M1_ATIVA]  esteiraEntrada=ON
    -> S2: esteiraEntrada=OFF; esteiraSaida=ON; estado=S3_M2_ATIVA

  [S3_M2_ATIVA]  esteiraSaida=ON
    -> S3: esteiraSaida=OFF; contPecas++
      SE contPecas>=5: LimitePecas=ON; estado=S4_LIMITE
      SENÃO: estado=S1_AGUARDA_PECA

  [S4_LIMITE]  LimitePecas=ON
    -> botaoStop: LimitePecas=OFF; contPecas=0; estado=S0_IDLE

  botaoStop (a qualquer momento, exceto em S4) -> IDLE sem zerar contador

PSEUDO-CÓDIGO:
  contPecas=0
  LOOP:
    SE botaoStop e estado!=S4_LIMITE: para tudo; Ligada=OFF; IDLE (NÃO zera cont)
    SE botaoStop e estado==S4_LIMITE: zera cont; IDLE
    SE IDLE: SE botaoStart: Ligada=ON; estado=AGUARDA_PECA
    SE AGUARDA_PECA: SE S1: esteiraEntrada=ON; estado=M1_ATIVA
    SE M1_ATIVA: SE S2: esteiraEntrada=OFF;esteiraSaida=ON; estado=M2_ATIVA
    SE M2_ATIVA: SE S3: esteiraSaida=OFF; contPecas++; 
      SE>=5: LimitePecas=ON; LIMITE
      SENÃO: estado=AGUARDA_PECA
    SE LIMITE: aguarda botaoStop para reiniciar
*/
const int E13_B1 = 22;
const int E13_B0 = 23;
const int E13_S1 = 24;
const int E13_S2 = 25;
const int E13_S3 = 26;
const int E13_M1 = 30;
const int E13_M2 = 31;
const int E13_LIG = 32;
const int E13_LIMITE = 33;
enum Estado_Ex13 { E13_IDLE, E13_AGUARDA_PECA, E13_M1_ATIVA,
                   E13_M2_ATIVA, E13_LIMITE };

Estado_Ex13 estadoEx13 = E13_IDLE;
int contPecasEx13 = 0;

void ex13_setup() {
  for (int p : {E13_B1,E13_B0}) pinMode(p, INPUT_PULLUP);
  for (int p : {E13_S1,E13_S2,E13_S3}) pinMode(p, INPUT);
  for (int p : {E13_M1,E13_M2,E13_LIG,E13_LIMITE}) pinMode(p, OUTPUT);
}

void ex13_loop() {
  bool botaoStart = !digitalRead(E13_B1), botaoStop = !digitalRead(E13_B0);
  bool s1 = digitalRead(E13_S1), s2 = digitalRead(E13_S2);
  bool s3 = digitalRead(E13_S3);

  if (botaoStop) {
    if (estadoEx13 == E13_LIMITE) contPecasEx13 = 0;
    estadoEx13 = E13_IDLE;
    for (int p : {E13_M1,E13_M2,E13_LIG,E13_LIMITE}) digitalWrite(p, LOW);
    return;
  }

  switch (estadoEx13) {
    case E13_IDLE:
      if (botaoStart) { digitalWrite(E13_LIG, HIGH); estadoEx13 = E13_AGUARDA_PECA; }
      break;
    case E13_AGUARDA_PECA:
      if (s1) { digitalWrite(E13_M1, HIGH); estadoEx13 = E13_M1_ATIVA; }
      break;
    case E13_M1_ATIVA:
      if (s2) {
        digitalWrite(E13_M1, LOW); digitalWrite(E13_M2, HIGH);
        estadoEx13 = E13_M2_ATIVA;
      }
      break;
    case E13_M2_ATIVA:
      if (s3) {
        digitalWrite(E13_M2, LOW);
        contPecasEx13++;
        if (contPecasEx13 >= 5) {
          digitalWrite(E13_LIMITE, HIGH);
          estadoEx13 = E13_LIMITE;
        } else {
          estadoEx13 = E13_AGUARDA_PECA;
        }
      }
      break;
    case E13_LIMITE:
      // aguarda botaoStop (tratado no topo)
      break;
  }
}


