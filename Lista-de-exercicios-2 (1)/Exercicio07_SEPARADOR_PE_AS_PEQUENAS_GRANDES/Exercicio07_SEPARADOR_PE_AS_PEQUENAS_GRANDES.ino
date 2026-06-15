// Exercício 7 - SEPARADOR PEÇAS PEQUENAS/GRANDES


// Entradas: botaoStart(START), botaoStop(STOP), S1(caixa grandes), S2-S4(altura),
//           S5(caixa pequenas), S6(sensor grandes final)
// Saídas: esteira, cilindroGuia, cilindroSeparador, Ligada
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: esteira=ON; cilindroGuia=ON; Ligada=ON; estado=S1_TRANSPORTA

  [S1_TRANSPORTA]  esteira=ON, cilindroGuia=ON
    -> sensores altura (S3/S4): SE grande: estado=S2_AGUARDA_GRANDE
                                 SE pequena: estado=S2_AGUARDA_PEQUENA

  [S2_AGUARDA_GRANDE]  esteira=ON (segue até fim)
    -> S6 (sensor caixa grande): esteira=OFF; cilindroGuia=OFF; estado=S0_IDLE

  [S2_AGUARDA_PEQUENA]  esteira=ON até S4
    -> S4: cilindroSeparador=ON; estado=S3_C2_AVANCA

  [S3_C2_AVANCA]
    -> S5 (caixa pequena): esteira=OFF; cilindroGuia=OFF; cilindroSeparador=OFF; estado=S0_IDLE

  botaoStop -> IDLE

PSEUDO-CÓDIGO:
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: esteira=ON;cilindroGuia=ON;Ligada=ON; estado=S1_TRANSPORTA
    SE S1_TRANSPORTA:
      lê altura: SE grande (ex: S3 e S4 ativos): estado=S2_GRANDE
                 SE pequena (só S3): estado=S2_PEQUENA
    SE S2_GRANDE: esteira=ON; SE S6: esteira=OFF;cilindroGuia=OFF; IDLE
    SE S2_PEQUENA: SE S4: cilindroSeparador=ON; estado=S3_C2_AVANCA
    SE S3_C2_AVANCA: SE S5: esteira=OFF;cilindroGuia=OFF;cilindroSeparador=OFF; IDLE
*/
const int E7_B1 = 2;
const int E7_B0 = 3;
#define E7_S1  4   // sensor caixa grandes (lado)
#define E7_S2  5   // não usado diretamente
#define E7_S3  6   // sensor altura (baixo = peça presente)
#define E7_S4  7   // sensor altura (alto = peça grande)
#define E7_S5  8   // sensor caixa pequenas
#define E7_S6  9   // sensor ao cair na caixa grande
const int E7_M1 = 10;
const int E7_C1 = 11;
const int E7_C2 = 12;
const int E7_LIG = 13;
enum Estado_Ex7 { E7_IDLE, E7_TRANSPORTA, E7_AGUARDA_GRANDE,
                  E7_AGUARDA_PEQUENA, E7_C2_AVANCA };

Estado_Ex7 estadoEx7 = E7_IDLE;

void ex7_setup() {
  pinMode(E7_B1, INPUT_PULLUP); pinMode(E7_B0, INPUT_PULLUP);
  for (int p : {E7_S1,E7_S2,E7_S3,E7_S4,E7_S5,E7_S6}) pinMode(p, INPUT);
  for (int p : {E7_M1,E7_C1,E7_C2,E7_LIG}) pinMode(p, OUTPUT);
}

void ex7_loop() {
  bool botaoStart = !digitalRead(E7_B1), botaoStop = !digitalRead(E7_B0);
  bool s3 = digitalRead(E7_S3), s4 = digitalRead(E7_S4);
  bool s5 = digitalRead(E7_S5), s6 = digitalRead(E7_S6);

  if (botaoStop) {
    estadoEx7 = E7_IDLE;
    digitalWrite(E7_M1, LOW); digitalWrite(E7_C1, LOW);
    digitalWrite(E7_C2, LOW); digitalWrite(E7_LIG, LOW);
    return;
  }

  switch (estadoEx7) {
    case E7_IDLE:
      digitalWrite(E7_M1, LOW); digitalWrite(E7_C1, LOW);
      digitalWrite(E7_C2, LOW); digitalWrite(E7_LIG, LOW);
      if (botaoStart) {
        digitalWrite(E7_M1, HIGH); digitalWrite(E7_C1, HIGH);
        digitalWrite(E7_LIG, HIGH);
        estadoEx7 = E7_TRANSPORTA;
      }
      break;

    case E7_TRANSPORTA:
      // aguarda passagem pelos sensores de altura
      if (s3) {  // peça presente nos sensores
        if (s4) estadoEx7 = E7_AGUARDA_GRANDE;   // grande: s3 e s4
        else    estadoEx7 = E7_AGUARDA_PEQUENA;   // pequena: só s3
      }
      break;

    case E7_AGUARDA_GRANDE:
      digitalWrite(E7_M1, HIGH);
      if (s6) {
        digitalWrite(E7_M1, LOW); digitalWrite(E7_C1, LOW);
        estadoEx7 = E7_IDLE;
      }
      break;

    case E7_AGUARDA_PEQUENA:
      if (s4) {  // chegou ao ponto de desvio
        digitalWrite(E7_C2, HIGH);
        estadoEx7 = E7_C2_AVANCA;
      }
      break;

    case E7_C2_AVANCA:
      if (s5) {
        digitalWrite(E7_M1, LOW); digitalWrite(E7_C1, LOW);
        digitalWrite(E7_C2, LOW); estadoEx7 = E7_IDLE;
      }
      break;
  }
}


