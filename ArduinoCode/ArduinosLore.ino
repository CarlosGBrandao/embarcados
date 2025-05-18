#include <Ultrasonic.h>

// Sensor ultrassônico
#define TRIG_PIN 7
#define ECHO_PIN 6
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

// Motores com L298N (direção)
#define IN1 9
#define IN2 10
#define IN3 3
#define IN4 4

// Controle de velocidade PWM
#define ENA 12  // para IN1/IN2 (motor A)
#define ENB 2   // para IN3/IN4 (motor B)

// Sensores MH de linha
#define SENSOR_ESQ A0
#define SENSOR_DIR A1

int valor = 128;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  pararMotores();
  Serial.begin(9600);
}

void loop() {
  long distancia = ultrasonic.Ranging(CM);
  int esq = digitalRead(SENSOR_ESQ);  // 0 = linha (preto)
  int dir = digitalRead(SENSOR_DIR);  // 0 = linha (preto)

  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.print(" cm | Sensor Esq: ");
  Serial.print(esq);
  Serial.print(" | Dir: ");
  Serial.println(dir);

  if (distancia > 0 && distancia < 20) {
    pararMotores();
    delay(150);
  }
  else if (esq == 0 && dir == 0) {
    pararMotores();
    delay(150);
    andarFrenteCurto();
  }
  else if (esq == 1 && dir == 0) {
    pararMotores();
    delay(150);
    virarEsquerdaCurto();
  }
  else if (esq == 0 && dir == 1) {
    pararMotores();
    delay(150);
    virarDireitaCurto();
  }
  else {
    pararMotores();
    delay(150);
  }

  delay(150);
}

// Funções com movimento curto (liga motor por 50ms e para)
void andarFrenteCurto() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, valor);
  analogWrite(ENB, valor);
  delay(50);
  pararMotores();
}

void virarEsquerdaCurto() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 0);
  analogWrite(ENB, valor);
  delay(50);
  pararMotores();
}

void virarDireitaCurto() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, valor);
  analogWrite(ENB, 0);
  delay(50);
  pararMotores();
}

void pararMotores() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
