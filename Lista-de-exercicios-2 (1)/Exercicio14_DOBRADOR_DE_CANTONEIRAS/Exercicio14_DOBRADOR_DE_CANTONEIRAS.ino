// Exercício 14 - DOBRADOR DE CANTONEIRAS


// Entradas: botaoStart(START), botaoStop(STOP), S1(cilindroFixador avançado), S2(cilindroCorte avançado),
//           S3(cilindroDobra avançado), S4(material detectado)
// Saídas: esteira, cilindroFixador(fixador), cilindroCorte(corte), cilindroDobra(dobra), Ligada
// Sequência: esteira até S4 -> cilindroFixador fixa -> 2s -> cilindroDobra dobra -> 2s -> cilindroCorte corta -> recuam todos
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: Ligada=ON; esteira=ON; estado=S1_M1_ATIVA

  [S1_M1_ATIVA]  esteira=ON
    -> S4 (material): esteira=OFF; cilindroFixador=ON; estado=S2_C1_FIXA

  [S2_C1_FIXA]  cilindroFixador=ON avançando
    -> S1 (cilindroFixador avançado): tInicio=millis(); estado=S3_AGUARDA_2S_A

  [S3_AGUARDA_2S_A]  (2s para cilindroDobra)
    -> timer>=2s: cilindroDobra=ON; estado=S4_C3_DOBRA

  [S4_C3_DOBRA]  cilindroDobra=ON avançando
    -> S3 (cilindroDobra avançado): tInicio=millis(); estado=S5_AGUARDA_2S_B

  [S5_AGUARDA_2S_B]  (2s para cilindroCorte)
    -> timer>=2s: cilindroCorte=ON; estado=S6_C2_CORTA

  [S6_C2_CORTA]  cilindroCorte=ON avançando
    -> S2 (cilindroCorte avançado): cilindroFixador=OFF;cilindroCorte=OFF;cilindroDobra=OFF; estado=S7_RECUAM

  [S7_RECUAM]  todos recuando
    -> todos recuados (S1r,S2r,S3r): peça cai; Ligada=OFF; estado=S0_IDLE

  botaoStop -> IDLE

PSEUDO-CÓDIGO:
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: Ligada=ON;esteira=ON; estado=M1_ATIVA
    SE M1_ATIVA: SE S4: esteira=OFF;cilindroFixador=ON; estado=C1_FIXA
    SE C1_FIXA: SE S1: tInicio=millis(); estado=AGUARDA_2S_A
    SE AGUARDA_2S_A: SE timer>=2s: cilindroDobra=ON; estado=C3_DOBRA
    SE C3_DOBRA: SE S3: tInicio=millis(); estado=AGUARDA_2S_B
    SE AGUARDA_2S_B: SE timer>=2s: cilindroCorte=ON; estado=C2_CORTA
    SE C2_CORTA: SE S2: cilindroFixador=OFF;cilindroCorte=OFF;cilindroDobra=OFF; estado=RECUAM
    SE RECUAM: SE todos recuados: Ligada=OFF; IDLE
*/
const int E14_B1 = 22;
const int E14_B0 = 23;
#define E14_S1   24   // cilindroFixador avançado
#define E14_S2   25   // cilindroCorte avançado
#define E14_S3   26   // cilindroDobra avançado
#define E14_S4   27   // material detectado
#define E14_S1R  28   // cilindroFixador recuado
#define E14_S2R  29   // cilindroCorte recuado
#define E14_S3R  30   // cilindroDobra recuado
const int E14_M1 = 40;
const int E14_C1 = 41;
const int E14_C2 = 42;
const int E14_C3 = 43;
const int E14_LIG = 44;
enum Estado_Ex14 { E14_IDLE, E14_M1_ATIVA, E14_C1_FIXA,
                   E14_AGUARDA_2S_A, E14_C3_DOBRA,
                   E14_AGUARDA_2S_B, E14_C2_CORTA, E14_RECUAM };

Estado_Ex14 estadoEx14 = E14_IDLE;
unsigned long tInicioEx14 = 0;

void ex14_setup() {
  for (int p : {E14_B1,E14_B0}) pinMode(p, INPUT_PULLUP);
  for (int p : {E14_S1,E14_S2,E14_S3,E14_S4,E14_S1R,E14_S2R,E14_S3R}) pinMode(p, INPUT);
  for (int p : {E14_M1,E14_C1,E14_C2,E14_C3,E14_LIG}) pinMode(p, OUTPUT);
}

void ex14_loop() {
  bool botaoStart = !digitalRead(E14_B1), botaoStop = !digitalRead(E14_B0);
  bool s1 = digitalRead(E14_S1), s2 = digitalRead(E14_S2);
  bool s3 = digitalRead(E14_S3), s4 = digitalRead(E14_S4);
  bool s1r = digitalRead(E14_S1R), s2r = digitalRead(E14_S2R);
  bool s3r = digitalRead(E14_S3R);
  unsigned long agora = millis();

  if (botaoStop) {
    estadoEx14 = E14_IDLE;
    for (int p : {E14_M1,E14_C1,E14_C2,E14_C3,E14_LIG}) digitalWrite(p, LOW);
    return;
  }

  switch (estadoEx14) {
    case E14_IDLE:
      if (botaoStart) {
        digitalWrite(E14_LIG, HIGH); digitalWrite(E14_M1, HIGH);
        estadoEx14 = E14_M1_ATIVA;
      }
      break;
    case E14_M1_ATIVA:
      if (s4) { digitalWrite(E14_M1, LOW); digitalWrite(E14_C1, HIGH); estadoEx14 = E14_C1_FIXA; }
      break;
    case E14_C1_FIXA:
      if (s1) { tInicioEx14 = agora; estadoEx14 = E14_AGUARDA_2S_A; }
      break;
    case E14_AGUARDA_2S_A:
      if (agora - tInicioEx14 >= 2000UL) { digitalWrite(E14_C3, HIGH); estadoEx14 = E14_C3_DOBRA; }
      break;
    case E14_C3_DOBRA:
      if (s3) { tInicioEx14 = agora; estadoEx14 = E14_AGUARDA_2S_B; }
      break;
    case E14_AGUARDA_2S_B:
      if (agora - tInicioEx14 >= 2000UL) { digitalWrite(E14_C2, HIGH); estadoEx14 = E14_C2_CORTA; }
      break;
    case E14_C2_CORTA:
      if (s2) {
        digitalWrite(E14_C1, LOW); digitalWrite(E14_C2, LOW);
        digitalWrite(E14_C3, LOW); estadoEx14 = E14_RECUAM;
      }
      break;
    case E14_RECUAM:
      if (s1r && s2r && s3r) { digitalWrite(E14_LIG, LOW); estadoEx14 = E14_IDLE; }
      break;
  }
}


