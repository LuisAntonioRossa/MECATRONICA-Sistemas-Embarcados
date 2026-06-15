// Exercício 11 - PASTEURIZADORA


// Entradas: botaoStart(START), botaoStop(STOP), S1(peça entrada), S2(pos. aquecimento),
//           S3(pos. resfriamento), S4(saída caixa)
// Saídas: esteira(esteira), resistenciaAquecimento(resistência aquecimento), ventoinhaResfriamento(ventoinha resfriamento), Ligada
// Aquecimento 3s em S2, Resfriamento 2s em S3
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: Ligada=ON; aguarda S1; estado=S1_AGUARDA_PECA

  [S1_AGUARDA_PECA]
    -> S1 ativo: esteira=ON; estado=S2_TRANSPORTA_S2

  [S2_TRANSPORTA_S2]  esteira=ON
    -> S2 (posição aquecimento): esteira=OFF; resistenciaAquecimento=ON; tInicio=millis(); estado=S3_AQUECE

  [S3_AQUECE]  resistenciaAquecimento=ON (3s)
    -> timer>=3s: resistenciaAquecimento=OFF; esteira=ON; estado=S4_TRANSPORTA_S3

  [S4_TRANSPORTA_S3]  esteira=ON
    -> S3 (posição resfriamento): esteira=OFF; ventoinhaResfriamento=ON; tInicio=millis(); estado=S5_RESFRIA

  [S5_RESFRIA]  ventoinhaResfriamento=ON (2s)
    -> timer>=2s: ventoinhaResfriamento=OFF; esteira=ON; estado=S6_TRANSPORTA_S4

  [S6_TRANSPORTA_S4]  esteira=ON
    -> S4 (saída): esteira=OFF; Ligada=ON; estado=S1_AGUARDA_PECA (novo ciclo)

  botaoStop -> IDLE

PSEUDO-CÓDIGO:
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: Ligada=ON; estado=AGUARDA_PECA
    SE AGUARDA_PECA: SE S1: esteira=ON; estado=TRANSPORTA_S2
    SE TRANSPORTA_S2: SE S2: esteira=OFF;resistenciaAquecimento=ON;tInicio=millis(); estado=AQUECE
    SE AQUECE: SE timer>=3s: resistenciaAquecimento=OFF;esteira=ON; estado=TRANSPORTA_S3
    SE TRANSPORTA_S3: SE S3: esteira=OFF;ventoinhaResfriamento=ON;tInicio=millis(); estado=RESFRIA
    SE RESFRIA: SE timer>=2s: ventoinhaResfriamento=OFF;esteira=ON; estado=TRANSPORTA_S4
    SE TRANSPORTA_S4: SE S4: esteira=OFF; estado=AGUARDA_PECA
*/
const int E11_B1 = 22;
const int E11_B0 = 23;
const int E11_S1 = 24;
const int E11_S2 = 25;
const int E11_S3 = 26;
const int E11_S4 = 27;
const int E11_M1 = 30;
const int E11_R1 = 31;
const int E11_V1 = 32;
const int E11_LIG = 33;
enum Estado_Ex11 { E11_IDLE, E11_AGUARDA_PECA, E11_TRANSP_S2,
                   E11_AQUECE, E11_TRANSP_S3, E11_RESFRIA,
                   E11_TRANSP_S4 };

Estado_Ex11 estadoEx11 = E11_IDLE;
unsigned long tInicioEx11 = 0;

void ex11_setup() {
  for (int p : {E11_B1,E11_B0}) pinMode(p, INPUT_PULLUP);
  for (int p : {E11_S1,E11_S2,E11_S3,E11_S4}) pinMode(p, INPUT);
  for (int p : {E11_M1,E11_R1,E11_V1,E11_LIG}) pinMode(p, OUTPUT);
}

void ex11_loop() {
  bool botaoStart = !digitalRead(E11_B1), botaoStop = !digitalRead(E11_B0);
  bool s1 = digitalRead(E11_S1), s2 = digitalRead(E11_S2);
  bool s3 = digitalRead(E11_S3), s4 = digitalRead(E11_S4);
  unsigned long agora = millis();

  if (botaoStop) {
    estadoEx11 = E11_IDLE;
    for (int p : {E11_M1,E11_R1,E11_V1,E11_LIG}) digitalWrite(p, LOW);
    return;
  }

  switch (estadoEx11) {
    case E11_IDLE:
      for (int p : {E11_M1,E11_R1,E11_V1}) digitalWrite(p, LOW);
      if (botaoStart) { digitalWrite(E11_LIG, HIGH); estadoEx11 = E11_AGUARDA_PECA; }
      break;

    case E11_AGUARDA_PECA:
      if (s1) { digitalWrite(E11_M1, HIGH); estadoEx11 = E11_TRANSP_S2; }
      break;

    case E11_TRANSP_S2:
      if (s2) {
        digitalWrite(E11_M1, LOW);
        digitalWrite(E11_R1, HIGH);
        tInicioEx11 = agora;
        estadoEx11 = E11_AQUECE;
      }
      break;

    case E11_AQUECE:
      if (agora - tInicioEx11 >= 3000UL) {
        digitalWrite(E11_R1, LOW);
        digitalWrite(E11_M1, HIGH);
        estadoEx11 = E11_TRANSP_S3;
      }
      break;

    case E11_TRANSP_S3:
      if (s3) {
        digitalWrite(E11_M1, LOW);
        digitalWrite(E11_V1, HIGH);
        tInicioEx11 = agora;
        estadoEx11 = E11_RESFRIA;
      }
      break;

    case E11_RESFRIA:
      if (agora - tInicioEx11 >= 2000UL) {
        digitalWrite(E11_V1, LOW);
        digitalWrite(E11_M1, HIGH);
        estadoEx11 = E11_TRANSP_S4;
      }
      break;

    case E11_TRANSP_S4:
      if (s4) {
        digitalWrite(E11_M1, LOW);
        estadoEx11 = E11_AGUARDA_PECA;  // novo ciclo automático
      }
      break;
  }
}


