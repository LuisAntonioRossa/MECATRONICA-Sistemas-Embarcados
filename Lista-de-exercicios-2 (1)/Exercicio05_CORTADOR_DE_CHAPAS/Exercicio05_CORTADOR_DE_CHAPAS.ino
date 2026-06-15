// Exercício 5 - CORTADOR DE CHAPAS


// Entradas: botaoStart(START), botaoStop(STOP), S1(fim curso cilindroCorte avança),
//           sensorChapaPosicionada(chapa no lugar), sensorCaixaPosicionada(caixa presente)
// Saídas: M1(esteira chapas), M2(esteira caixas), cilindroCorte(cilindro corte), Ligada
// Ciclo de corte: 5 vezes por caixa
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: Ligada=ON; estado=S1_INICIO_CICLO

  [S1_INICIO_CICLO]  M1=ON; M2=ON (simultâneos)
    -> sensorChapaPosicionada (chapa no lugar): M1=OFF
    -> sensorCaixaPosicionada (caixa detectada): M2=OFF
    -> ambos desligados: estado=S2_CORTA

  [S2_CORTA] cilindroCorte=ON (avança)
    -> S1 (fim curso avançado): cilindroCorte=OFF (recua); contCortes++
    -> cilindroCorte recuado (lógica de sensor retorno): 
        SE contCortes<5: estado=S2_CORTA novamente
        SE contCortes==5: contCortes=0; estado=S3_PROX_CAIXA

  [S3_PROX_CAIXA]  M2=ON
    -> sensorCaixaPosicionada: M2=OFF; estado=S1_INICIO_CICLO

  botaoStop -> IDLE; Ligada=OFF

PSEUDO-CÓDIGO:
  estado=IDLE; contCortes=0; m1Parou=false; m2Parou=false
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: Ligada=ON; estado=S1_INICIO_CICLO; reset flags
    SE S1_INICIO_CICLO:
      M1=ON; M2=ON
      SE sensorChapaPosicionada: M1=OFF; m1Parou=true
      SE sensorCaixaPosicionada: M2=OFF; m2Parou=true
      SE m1Parou E m2Parou: estado=S2_CORTA; c1Avancando=true
    SE S2_CORTA:
      SE c1Avancando: cilindroCorte=ON; SE S1: cilindroCorte=OFF; c1Avancando=false
      SE !c1Avancando: cilindroCorte=OFF (recuando); SE sensor_recuo: 
        contCortes++; SE>=5: reset; S3_PROX_CAIXA; SENÃO c1Avancando=true
    SE S3_PROX_CAIXA: M2=ON; SE sensorCaixaPosicionada: M2=OFF; estado=S1_INICIO_CICLO
*/
const int E5_B1_START = 2;
const int E5_B0_STOP = 3;
#define E5_S1_C1ADV  4   // fim de curso cilindroCorte avançado
#define E5_S1R_C1REC 5   // fim de curso cilindroCorte recuado
#define E5_S2_CHAPA  6   // chapa no lugar
#define E5_S3_CAIXA  7   // caixa presente
const int E5_M1 = 8;
const int E5_M2 = 9;
const int E5_C1 = 10;
const int E5_LIGADA = 11;
enum Estado_Ex5 { E5_IDLE, E5_INICIO_CICLO, E5_CORTA_AVANCA,
                  E5_CORTA_RECUA, E5_PROX_CAIXA };

Estado_Ex5 estadoEx5 = E5_IDLE;
int contCortesEx5 = 0;
bool m1ParouEx5 = false;
bool m2ParouEx5 = false;

void ex5_setup() {
  pinMode(E5_B1_START,  INPUT_PULLUP);
  pinMode(E5_B0_STOP,   INPUT_PULLUP);
  pinMode(E5_S1_C1ADV,  INPUT);
  pinMode(E5_S1R_C1REC, INPUT);
  pinMode(E5_S2_CHAPA,  INPUT);
  pinMode(E5_S3_CAIXA,  INPUT);
  pinMode(E5_M1,        OUTPUT);
  pinMode(E5_M2,        OUTPUT);
  pinMode(E5_C1,        OUTPUT);
  pinMode(E5_LIGADA,    OUTPUT);
}

void ex5_loop() {
  bool b1Start   = !digitalRead(E5_B1_START);
  bool b0Stop    = !digitalRead(E5_B0_STOP);
  bool s1Avancou = digitalRead(E5_S1_C1ADV);
  bool s1Recuou  = digitalRead(E5_S1R_C1REC);
  bool s2Chapa   = digitalRead(E5_S2_CHAPA);
  bool s3Caixa   = digitalRead(E5_S3_CAIXA);

  if (b0Stop) {
    estadoEx5 = E5_IDLE;
    digitalWrite(E5_M1,     LOW);
    digitalWrite(E5_M2,     LOW);
    digitalWrite(E5_C1,     LOW);
    digitalWrite(E5_LIGADA, LOW);
    return;
  }

  switch (estadoEx5) {
    case E5_IDLE:
      digitalWrite(E5_M1,     LOW);
      digitalWrite(E5_M2,     LOW);
      digitalWrite(E5_C1,     LOW);
      digitalWrite(E5_LIGADA, LOW);
      if (b1Start) {
        digitalWrite(E5_LIGADA, HIGH);
        m1ParouEx5 = false;
        m2ParouEx5 = false;
        estadoEx5 = E5_INICIO_CICLO;
      }
      break;

    case E5_INICIO_CICLO:
      if (!m1ParouEx5) digitalWrite(E5_M1, HIGH);
      if (!m2ParouEx5) digitalWrite(E5_M2, HIGH);
      if (s2Chapa && !m1ParouEx5) { digitalWrite(E5_M1, LOW); m1ParouEx5 = true; }
      if (s3Caixa && !m2ParouEx5) { digitalWrite(E5_M2, LOW); m2ParouEx5 = true; }
      if (m1ParouEx5 && m2ParouEx5) {
        contCortesEx5 = 0;
        estadoEx5 = E5_CORTA_AVANCA;
      }
      break;

    case E5_CORTA_AVANCA:
      digitalWrite(E5_C1, HIGH);
      if (s1Avancou) {
        digitalWrite(E5_C1, LOW);
        estadoEx5 = E5_CORTA_RECUA;
      }
      break;

    case E5_CORTA_RECUA:
      if (s1Recuou) {
        contCortesEx5++;
        if (contCortesEx5 >= 5) {
          contCortesEx5 = 0;
          estadoEx5 = E5_PROX_CAIXA;
        } else {
          estadoEx5 = E5_CORTA_AVANCA;
        }
      }
      break;

    case E5_PROX_CAIXA:
      digitalWrite(E5_M2, HIGH);
      if (s3Caixa) {
        digitalWrite(E5_M2, LOW);
        m1ParouEx5 = false;
        m2ParouEx5 = false;
        estadoEx5 = E5_INICIO_CICLO;
      }
      break;
  }
}


