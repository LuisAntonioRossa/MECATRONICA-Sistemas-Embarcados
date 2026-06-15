// Exercício 8 - SELETOR DE PEÇAS POR MATERIAL (Plástico/Metal)


// Entradas: botaoStart(START), botaoStop(STOP), S1(peça na entrada),
//           S2(sensor indutivo=metal), S3(sensor capacitivo=qualquer),
//           S4(fim cilindroPlastico), S5(sensor caixa plástico)
// Saídas: esteira, cilindroPlastico(metal), cilindroMetal(plástico), Ligada
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE]
    -> botaoStart: Ligada=ON; aguarda S1; estado=S1_AGUARDA_PECA

  [S1_AGUARDA_PECA]
    -> S1 detecta peça: esteira=ON; estado=S2_TRANSFERE

  [S2_TRANSFERE]  esteira=ON
    -> fim esteira: analisa S2(metal) e S3(capacit)
       SE metal (S2 ativo): estado=S3_METAL
       SE plástico (S3 ativo, S2 não): estado=S3_PLASTICO

  [S3_METAL]  cilindroPlastico=ON (empurra para rampa metal)
    -> S4 (fim curso cilindroPlastico): esteira=OFF; cilindroPlastico=OFF; estado=S4_RECUA_C1

  [S4_RECUA_C1]
    -> sensor recuo cilindroPlastico: estado=S0_IDLE

  [S3_PLASTICO]  cilindroMetal=ON
    -> S5 (sensor caixa plástico): esteira=OFF; cilindroMetal=OFF; estado=S5_RECUA_C2

  [S5_RECUA_C2]
    -> sensor recuo cilindroMetal: estado=S0_IDLE

  botaoStop -> IDLE

PSEUDO-CÓDIGO:
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: Ligada=ON; estado=AGUARDA_PECA
    SE AGUARDA_PECA: SE S1: esteira=ON; estado=TRANSFERE
    SE TRANSFERE:
      SE S2(indutivo): esteira=OFF; cilindroPlastico=ON; estado=METAL
      SE S3(capac) E !S2: esteira=OFF; cilindroMetal=ON; estado=PLASTICO
    SE METAL: SE S4: cilindroPlastico=OFF; recua; SE recuado: IDLE
    SE PLASTICO: SE S5: cilindroMetal=OFF; recua; SE recuado: IDLE
*/
const int E8_B1 = 22;
const int E8_B0 = 23;
const int E8_S1 = 24;
#define E8_S2    25   // indutivo (metal)
#define E8_S3    26   // capacitivo (qualquer)
#define E8_S4    27   // fim de curso cilindroPlastico
#define E8_S4R   28   // recuado cilindroPlastico
#define E8_S5    29   // sensor caixa plástico
#define E8_S5R   30   // recuado cilindroMetal
const int E8_M1 = 40;
const int E8_C1 = 41;
const int E8_C2 = 42;
const int E8_LIG = 43;
enum Estado_Ex8 { E8_IDLE, E8_AGUARDA_PECA, E8_TRANSFERE,
                  E8_METAL, E8_RECUA_C1, E8_PLASTICO, E8_RECUA_C2 };

Estado_Ex8 estadoEx8 = E8_IDLE;

void ex8_setup() {
  for (int p : {E8_B1,E8_B0}) pinMode(p, INPUT_PULLUP);
  for (int p : {E8_S1,E8_S2,E8_S3,E8_S4,E8_S4R,E8_S5,E8_S5R}) pinMode(p, INPUT);
  for (int p : {E8_M1,E8_C1,E8_C2,E8_LIG}) pinMode(p, OUTPUT);
}

void ex8_loop() {
  bool botaoStart = !digitalRead(E8_B1), botaoStop = !digitalRead(E8_B0);
  bool s1 = digitalRead(E8_S1), s2 = digitalRead(E8_S2);
  bool s3 = digitalRead(E8_S3), s4 = digitalRead(E8_S4);
  bool s4r = digitalRead(E8_S4R), s5 = digitalRead(E8_S5);
  bool s5r = digitalRead(E8_S5R);

  if (botaoStop) {
    estadoEx8 = E8_IDLE;
    for (int p : {E8_M1,E8_C1,E8_C2,E8_LIG}) digitalWrite(p, LOW);
    return;
  }

  switch (estadoEx8) {
    case E8_IDLE:
      for (int p : {E8_M1,E8_C1,E8_C2}) digitalWrite(p, LOW);
      if (botaoStart) { digitalWrite(E8_LIG, HIGH); estadoEx8 = E8_AGUARDA_PECA; }
      break;
    case E8_AGUARDA_PECA:
      if (s1) { digitalWrite(E8_M1, HIGH); estadoEx8 = E8_TRANSFERE; }
      break;
    case E8_TRANSFERE:
      if (s2) { digitalWrite(E8_M1, LOW); digitalWrite(E8_C1, HIGH); estadoEx8 = E8_METAL; }
      else if (s3) { digitalWrite(E8_M1, LOW); digitalWrite(E8_C2, HIGH); estadoEx8 = E8_PLASTICO; }
      break;
    case E8_METAL:
      if (s4) { digitalWrite(E8_C1, LOW); estadoEx8 = E8_RECUA_C1; }
      break;
    case E8_RECUA_C1:
      if (s4r) estadoEx8 = E8_IDLE;
      break;
    case E8_PLASTICO:
      if (s5) { digitalWrite(E8_C2, LOW); estadoEx8 = E8_RECUA_C2; }
      break;
    case E8_RECUA_C2:
      if (s5r) estadoEx8 = E8_IDLE;
      break;
  }
}
