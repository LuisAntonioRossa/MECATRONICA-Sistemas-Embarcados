// Exercício 2 - MISTURADOR DE TINTA


// Entradas: Start1(I0), Stop1(I2), Start2(I1), Stop2(I3),
//           HighLevel(I4), LowLevel(I5)
// Saídas: Pump1(Q0.0), Pump2(Q0.1), MixerMotor(Q0.2),
//         SteamValve(Q0.3), DrainValve(Q0.4), DrainPump(Q0.5)
// Contador de ciclos completos
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE]
    -> START1 ou START2 pressionado -> [S1_FILL1]

  [S1_FILL1]  Pump1=ON
    -> Stop1 (nível alto detectado via HighLevel) -> [S2_FILL2]

  [S2_FILL2]  Pump2=ON
    -> Stop2 (independente) -> [S3_CHECK_LEVEL]

  [S3_CHECK_LEVEL]
    -> HighLevel ativo -> [S4_MIX_HEAT] (inicia timer 10s)

  [S4_MIX_HEAT]  MixerMotor=ON, SteamValve=ON
    -> timer>=10s -> [S5_DRAIN]

  [S5_DRAIN]  DrainValve=ON, DrainPump=ON
    -> tanque vazio (LowLevel desativado) -> [S6_COUNT]

  [S6_COUNT]  contadorCiclos++
    -> volta a [S0_IDLE]

PSEUDO-CÓDIGO:
  estado = S0_IDLE; contador = 0
  LOOP:
    lê entradas
    SE estado == S0_IDLE:
      desliga tudo
      SE start1 OU start2: estado = S1_FILL1
    SE S1_FILL1: Pump1=ON; SE stop1: Pump1=OFF; estado=S2_FILL2
    SE S2_FILL2: Pump2=ON; SE stop2: Pump2=OFF; estado=S3_CHECK_LEVEL
    SE S3_CHECK_LEVEL: SE highLevel: tInicio=millis(); estado=S4_MIX_HEAT
    SE S4_MIX_HEAT: Mixer=ON; Steam=ON; SE timer>=10s: estado=S5_DRAIN
    SE S5_DRAIN: DrainValve=ON; DrainPump=ON; SE !lowLevel: estado=S6_COUNT
    SE S6_COUNT: contador++; estado=S0_IDLE
*/

// --- Pinos Exercício 2 ---
const int E2_START1 = 22;
const int E2_STOP1 = 24;
const int E2_START2 = 23;
const int E2_STOP2 = 25;
const int E2_HIGH_LEVEL = 26;
const int E2_LOW_LEVEL = 27;
const int E2_PUMP1 = 30;
const int E2_PUMP2 = 31;
const int E2_MIXER = 32;
const int E2_STEAM = 33;
const int E2_DRAIN_V = 34;
const int E2_DRAIN_P = 35;
enum Estado_Ex2 { E2_IDLE, E2_FILL1, E2_FILL2,
                  E2_CHECK_LEVEL, E2_MIX_HEAT,
                  E2_DRAIN, E2_COUNT };

Estado_Ex2 estadoEx2 = E2_IDLE;
unsigned long tInicioEx2 = 0;
int contadorCiclosEx2 = 0;

void ex2_desligaTudo() {
  digitalWrite(E2_PUMP1,   LOW);
  digitalWrite(E2_PUMP2,   LOW);
  digitalWrite(E2_MIXER,   LOW);
  digitalWrite(E2_STEAM,   LOW);
  digitalWrite(E2_DRAIN_V, LOW);
  digitalWrite(E2_DRAIN_P, LOW);
}

void ex2_setup() {
  pinMode(E2_START1,     INPUT_PULLUP);
  pinMode(E2_STOP1,      INPUT_PULLUP);
  pinMode(E2_START2,     INPUT_PULLUP);
  pinMode(E2_STOP2,      INPUT_PULLUP);
  pinMode(E2_HIGH_LEVEL, INPUT);
  pinMode(E2_LOW_LEVEL,  INPUT);
  pinMode(E2_PUMP1,      OUTPUT);
  pinMode(E2_PUMP2,      OUTPUT);
  pinMode(E2_MIXER,      OUTPUT);
  pinMode(E2_STEAM,      OUTPUT);
  pinMode(E2_DRAIN_V,    OUTPUT);
  pinMode(E2_DRAIN_P,    OUTPUT);
}

void ex2_loop() {
  bool start1    = !digitalRead(E2_START1);
  bool stop1     = !digitalRead(E2_STOP1);
  bool start2    = !digitalRead(E2_START2);
  bool stop2     = !digitalRead(E2_STOP2);
  bool highLevel = digitalRead(E2_HIGH_LEVEL);
  bool lowLevel  = digitalRead(E2_LOW_LEVEL);
  unsigned long agora = millis();

  switch (estadoEx2) {
    case E2_IDLE:
      ex2_desligaTudo();
      if (start1 || start2) estadoEx2 = E2_FILL1;
      break;

    case E2_FILL1:
      digitalWrite(E2_PUMP1, HIGH);
      if (stop1) {
        digitalWrite(E2_PUMP1, LOW);
        estadoEx2 = E2_FILL2;
      }
      break;

    case E2_FILL2:
      digitalWrite(E2_PUMP2, HIGH);
      if (stop2) {
        digitalWrite(E2_PUMP2, LOW);
        estadoEx2 = E2_CHECK_LEVEL;
      }
      break;

    case E2_CHECK_LEVEL:
      if (highLevel) {
        tInicioEx2 = agora;
        estadoEx2 = E2_MIX_HEAT;
      }
      break;

    case E2_MIX_HEAT:
      digitalWrite(E2_MIXER, HIGH);
      digitalWrite(E2_STEAM, HIGH);
      if (agora - tInicioEx2 >= 10000UL) {
        digitalWrite(E2_MIXER, LOW);
        digitalWrite(E2_STEAM, LOW);
        estadoEx2 = E2_DRAIN;
      }
      break;

    case E2_DRAIN:
      digitalWrite(E2_DRAIN_V, HIGH);
      digitalWrite(E2_DRAIN_P, HIGH);
      if (!lowLevel) {
        digitalWrite(E2_DRAIN_V, LOW);
        digitalWrite(E2_DRAIN_P, LOW);
        estadoEx2 = E2_COUNT;
      }
      break;

    case E2_COUNT:
      contadorCiclosEx2++;
      estadoEx2 = E2_IDLE;
      break;
  }
}


