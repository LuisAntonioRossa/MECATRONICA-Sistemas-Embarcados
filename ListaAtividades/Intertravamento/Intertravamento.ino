const int led = 4;
const int bot1 = 3;
const int bot2 = 2;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
}

void loop()
{
 int estadoA = digitalRead (bot1);
  int estadoB = digitalRead (bot2);
 if (bot1 == 1 && bot2 == 1) {
    digitalWrite(led, HIGH);
} else {
    digitalWrite(led, LOW);
}
}