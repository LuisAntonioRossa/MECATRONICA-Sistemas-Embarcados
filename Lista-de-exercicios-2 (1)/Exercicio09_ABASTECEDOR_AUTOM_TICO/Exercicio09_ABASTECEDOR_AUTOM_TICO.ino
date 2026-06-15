// Exercício 9 - ABASTECEDOR AUTOMÁTICO


// Entradas: botaoStart(START), botaoStop(STOP), S1(caixa passa cilindroAlimentador), S2(posição enchimento),
//           S3(cilindroEnchimento recuado=abre bico), S4(saída)
// Saídas: esteira(esteira), cilindroAlimentador(alimenta caixa), cilindroEnchimento(bico enchimento), Ligada
// Operador retira caixa em S4 para reiniciar
// ============================================================
/*
DIAGRAMA DE ESTADOS:

  [S0_IDLE] -> botaoStart: esteira=ON; cilindroAlimentador=ON; Ligada=ON; estado=S1_ALIMENTA

  [S1_ALIMENTA]  esteira=ON, cilindroAlimentador=ON (avança alimentando caixa)
    -> S1 (caixa passou cilindroAlimentador): cilindroAlimentador=OFF (recua); esteira continua; estado=S2_M1_CONTINUA

  [S2_M1_CONTINUA]  esteira=ON (cilindroAlimentador continua recuando em background)
    -> S2 (caixa chegou posição enchimento): esteira=OFF; cilindroEnchimento=OFF(recua=abre bico);
       tInicio=millis(); estado=S3_ENCHENDO

  [S3_ENCHENDO]  cilindroEnchimento=OFF(bico aberto), timer 6s
    -> timer>=6s: cilindroEnchimento=ON(fecha bico/avança); estado=S4_FECHA_BICO

  [S4_FECHA_BICO]  cilindroEnchimento=ON (fecha)
    -> S3 (cilindroEnchimento avançado = bico fechado): esteira=ON; estado=S5_SAIDA

  [S5_SAIDA]  esteira=ON
    -> S4 (caixa chegou saída): esteira=OFF; estado=S6_AGUARDA_RETIRADA

  [S6_AGUARDA_RETIRADA]
    -> !S4 (operador retirou): estado=S0_IDLE (novo ciclo)

  botaoStop -> IDLE

PSEUDO-CÓDIGO:
  LOOP:
    SE botaoStop: para tudo; IDLE
    SE IDLE: SE botaoStart: esteira=ON;cilindroAlimentador=ON;Ligada=ON; estado=S1_ALIMENTA
    SE S1_ALIMENTA: SE S1: cilindroAlimentador=OFF; estado=S2_M1_CONTINUA
    SE S2_M1_CONTINUA: SE S2: esteira=OFF; cilindroEnchimento=OFF; tInicio=millis(); estado=S3_ENCHENDO
    SE S3_ENCHENDO: SE millis()-tInicio>=6000: cilindroEnchimento=ON; estado=S4_FECHA_BICO
    SE S4_FECHA_BICO: SE S3: esteira=ON; estado=S5_SAIDA
    SE S5_SAIDA: SE S4: esteira=OFF; estado=S6_AGUARDA_RETIRADA
    SE S6_AGUARDA_RETIRADA: SE !S4: estado=S0_IDLE
*/
const int E9_B1 = 2;
const int E9_B0 = 3;
const int E9_S1 = 4;
const int E9_S2 = 5;
const int E9_S3 = 6;
const int E9_S4 = 7;
const int E9_M1 = 8;
const int E9_LIG = 9;
const int E9_C1 = 10;
const int E9_C2 = 11;
enum Estado_Ex9 { E9_IDLE, E9_ALIMENTA, E9_M1_CONT,
                  E9_ENCHENDO, E9_FECHA_BICO, E9_SAIDA,
                  E9_AGUARDA_RETIRADA };

Estado_Ex9 estadoEx9 = E9_IDLE;
unsigned long tInicioEx9 = 0;

void ex9_setup() {
  for (int p : {E9_B1, E9_B0}) pinMode(p, INPUT_PULLUP);
  for (int p : {E9_S1, E9_S2, E9_S3, E9_S4}) pinMode(p, INPUT);
  for (int p : {E9_M1, E9_LIG, E9_C1, E9_C2}) pinMode(p, OUTPUT);
}

void ex9_loop() {
  bool botaoStart = !digitalRead(E9_B1), botaoStop = !digitalRead(E9_B0);
  bool s1 = digitalRead(E9_S1), s2 = digitalRead(E9_S2);
  bool s3 = digitalRead(E9_S3), s4 = digitalRead(E9_S4);
  unsigned long agora = millis();

  if (botaoStop) {
    estadoEx9 = E9_IDLE;
    for (int p : {E9_M1, E9_LIG, E9_C1, E9_C2}) digitalWrite(p, LOW);
    return;
  }

  switch (estadoEx9) {
    case E9_IDLE:
      if (botaoStart) {
        digitalWrite(E9_M1, HIGH); digitalWrite(E9_C1, HIGH);
        digitalWrite(E9_LIG, HIGH);
        estadoEx9 = E9_ALIMENTA;
      }
      break;

    case E9_ALIMENTA:
      if (s1) {
        digitalWrite(E9_C1, LOW);  // cilindroAlimentador recua (deixa passar)
        estadoEx9 = E9_M1_CONT;
      }
      break;

    case E9_M1_CONT:
      if (s2) {
        digitalWrite(E9_M1, LOW);
        digitalWrite(E9_C2, LOW);  // cilindroEnchimento recua = abre bico de enchimento
        tInicioEx9 = agora;
        estadoEx9 = E9_ENCHENDO;
      }
      break;

    case E9_ENCHENDO:
      if (agora - tInicioEx9 >= 6000UL) {
        digitalWrite(E9_C2, HIGH);  // cilindroEnchimento avança = fecha bico
        estadoEx9 = E9_FECHA_BICO;
      }
      break;

    case E9_FECHA_BICO:
      if (s3) {  // cilindroEnchimento avançado (bico fechado)
        digitalWrite(E9_M1, HIGH);
        estadoEx9 = E9_SAIDA;
      }
      break;

    case E9_SAIDA:
      if (s4) {
        digitalWrite(E9_M1, LOW);
        estadoEx9 = E9_AGUARDA_RETIRADA;
      }
      break;

    case E9_AGUARDA_RETIRADA:
      if (!s4) estadoEx9 = E9_IDLE;  // operador retirou
      break;
  }
}


