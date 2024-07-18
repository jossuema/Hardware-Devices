const int ledPin = 13;
const int a1 = 9; // Decenas
const int b1 = 10;
const int c1 = 11;
const int d1 = 12;
const int e1 = A0;
const int f1 = A1;
const int g1 = A2;
const int a2 = 2; // Unidades
const int b2 = 3;
const int c2 = 4;
const int d2 = 5;
const int e2 = 6;
const int f2 = 7;
const int g2 = 8;
const int buzzerPin = A3;  // Pin para el buzzer activo

unsigned long previousMillis = 0;
unsigned long interval = 1000;
int seconds = 0;

const int digits[10][7] = {
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},  // 0
  {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},     // 1
  {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},  // 2
  {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},  // 3
  {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},   // 4
  {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},  // 5
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}, // 6
  {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},    // 7
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH},// 8
  {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}  // 9
};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(c1, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(c2, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // Configura el pin del buzzer como salida
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int tens = seconds / 10;
    int ones = seconds % 10;

    displayDigit(tens, a1, b1, c1, d1, e1, f1, g1);
    displayDigit(ones, a2, b2, c2, d2, e2, f2, g2);

    seconds++;
    if (seconds > 59) {
      seconds = 0;
    }

    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);  // Activa el buzzer
    delay(100); 
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}

void displayDigit(int digit, int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(a, digits[digit][0]);
  digitalWrite(b, digits[digit][1]);
  digitalWrite(c, digits[digit][2]);
  digitalWrite(d, digits[digit][3]);
  digitalWrite(e, digits[digit][4]);
  digitalWrite(f, digits[digit][5]);
  digitalWrite(g, digits[digit][6]);
}
