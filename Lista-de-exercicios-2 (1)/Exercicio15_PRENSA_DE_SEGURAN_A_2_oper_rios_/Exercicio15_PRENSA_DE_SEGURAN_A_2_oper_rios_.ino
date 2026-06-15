// Exercício 15 - PRENSA DE SEGURANÇA (2 operários)


// Entradas: comandoOperadorA(operário 1), comandoOperadorB(operário 2)
// Saída: contatorPrensa(contator motor prensa)
// Regras: ambos devem acionar; tolerância 3s entre acionamentos;
//         se um soltar, tem 3s para recolocar; senão repete manobra
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE]
    -> comandoOperadorA pressionado: tA=millis(); estado=S1_AGUARDA_B
    -> comandoOperadorB pressionado: tB=millis(); estado=S2_AGUARDA_A

  [S1_AGUARDA_B]  comandoOperadorA ativo
    -> comandoOperadorB pressionado dentro de 3s: contatorPrensa=ON; estado=S3_PRENSANDO
    -> timer comandoOperadorA >= 3s sem comandoOperadorB: estado=S0_IDLE (manobra falhou)
    -> comandoOperadorA solto antes de comandoOperadorB: estado=S0_IDLE

  [S2_AGUARDA_A]  comandoOperadorB ativo
    -> comandoOperadorA pressionado dentro de 3s: contatorPrensa=ON; estado=S3_PRENSANDO
    -> timer comandoOperadorB >= 3s sem comandoOperadorA: estado=S0_IDLE
    -> comandoOperadorB solto antes de comandoOperadorA: estado=S0_IDLE

  [S3_PRENSANDO]  contatorPrensa=ON
    -> comandoOperadorA solto: tFalha=millis(); estado=S4_AGUARDA_RECOLOCAR_A
    -> comandoOperadorB solto: tFalha=millis(); estado=S4_AGUARDA_RECOLOCAR_B

  [S4_AGUARDA_RECOLOCAR_A]
    -> comandoOperadorA recolocado dentro de 3s: contatorPrensa=ON; estado=S3_PRENSANDO
    -> timer >= 3s: contatorPrensa=OFF; estado=S0_IDLE (repete manobra)

  [S4_AGUARDA_RECOLOCAR_B]
    -> comandoOperadorB recolocado dentro de 3s: contatorPrensa=ON; estado=S3_PRENSANDO
    -> timer >= 3s: contatorPrensa=OFF; estado=S0_IDLE

PSEUDO-CÓDIGO:
  estado=IDLE; contatorPrensa=OFF
  LOOP:
    SE IDLE:
      SE comandoOperadorA e !comandoOperadorB: tA=millis(); estado=AGUARDA_B
      SE comandoOperadorB e !comandoOperadorA: tB=millis(); estado=AGUARDA_A
      SE comandoOperadorA e comandoOperadorB:  contatorPrensa=ON; estado=PRENSANDO

    SE AGUARDA_B:
      SE !comandoOperadorA: estado=IDLE (soltou antes)
      SE comandoOperadorB: contatorPrensa=ON; estado=PRENSANDO
      SE millis()-tA>=3s: estado=IDLE

    SE AGUARDA_A: (simétrico)

    SE PRENSANDO:
      SE !comandoOperadorA: tFalha=millis(); estado=AGUARDA_RECOLOCAR_A
      SE !comandoOperadorB: tFalha=millis(); estado=AGUARDA_RECOLOCAR_B

    SE AGUARDA_RECOLOCAR_A:
      SE comandoOperadorA: contatorPrensa=ON; estado=PRENSANDO
      SE millis()-tFalha>=3s: contatorPrensa=OFF; estado=IDLE

    SE AGUARDA_RECOLOCAR_B: (simétrico)
*/
const int E15_A = 2;
const int E15_B = 3;
#define E15_R    4   // contator prensa

enum Estado_Ex15 { E15_IDLE, E15_AGUARDA_B, E15_AGUARDA_A,
                   E15_PRENSANDO, E15_RECOLOCA_A, E15_RECOLOCA_B };

Estado_Ex15 estadoEx15 = E15_IDLE;
unsigned long tEx15 = 0;

void ex15_setup() {
  pinMode(E15_A, INPUT_PULLUP);
  pinMode(E15_B, INPUT_PULLUP);
  pinMode(E15_R, OUTPUT);
}

void ex15_loop() {
  bool a = !digitalRead(E15_A);
  bool b = !digitalRead(E15_B);
  unsigned long agora = millis();

  switch (estadoEx15) {
    case E15_IDLE:
      digitalWrite(E15_R, LOW);
      if (a && b) { digitalWrite(E15_R, HIGH); estadoEx15 = E15_PRENSANDO; }
      else if (a)  { tEx15 = agora; estadoEx15 = E15_AGUARDA_B; }
      else if (b)  { tEx15 = agora; estadoEx15 = E15_AGUARDA_A; }
      break;

    case E15_AGUARDA_B:
      if (!a) { estadoEx15 = E15_IDLE; }
      else if (b) { digitalWrite(E15_R, HIGH); estadoEx15 = E15_PRENSANDO; }
      else if (agora - tEx15 >= 3000UL) { estadoEx15 = E15_IDLE; }
      break;

    case E15_AGUARDA_A:
      if (!b) { estadoEx15 = E15_IDLE; }
      else if (a) { digitalWrite(E15_R, HIGH); estadoEx15 = E15_PRENSANDO; }
      else if (agora - tEx15 >= 3000UL) { estadoEx15 = E15_IDLE; }
      break;

    case E15_PRENSANDO:
      if (!a) { tEx15 = agora; estadoEx15 = E15_RECOLOCA_A; }
      else if (!b) { tEx15 = agora; estadoEx15 = E15_RECOLOCA_B; }
      break;

    case E15_RECOLOCA_A:
      if (a) { digitalWrite(E15_R, HIGH); estadoEx15 = E15_PRENSANDO; }
      else if (agora - tEx15 >= 3000UL) {
        digitalWrite(E15_R, LOW); estadoEx15 = E15_IDLE;
      }
      break;

    case E15_RECOLOCA_B:
      if (b) { digitalWrite(E15_R, HIGH); estadoEx15 = E15_PRENSANDO; }
      else if (agora - tEx15 >= 3000UL) {
        digitalWrite(E15_R, LOW); estadoEx15 = E15_IDLE;
      }
      break;
  }
}


