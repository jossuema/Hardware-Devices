#include <LedControl.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pines y configuración del sensor de sonido
const int soundSensorAnalogPin = A0; // Pin analógico donde se conecta el sensor de sonido
const int soundSensorDigitalPin = 2; // Pin digital donde se conecta el sensor de sonido
const int numDevices = 1; // Número de matrices LED conectadas

// Pines de la matriz LED
const int DIN = 11;
const int CS = 10;
const int CLK = 13;

// Inicializa la matriz LED
LedControl lc = LedControl(DIN, CLK, CS, numDevices);

// Inicializa el LCD (dirección I2C, tamaño del display)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Cambia la dirección si es necesario

void setup() {
  Serial.begin(9600);
  pinMode(soundSensorDigitalPin, INPUT);

  // Configura la matriz LED
  lc.shutdown(0, false); // Despierta la pantalla
  lc.setIntensity(0, 8); // Establece el brillo a un valor medio (0-15)
  lc.clearDisplay(0); // Limpia la pantalla

  // Configura el LCD
  lcd.init(); // Usa lcd.init() en lugar de lcd.begin()
  lcd.backlight();
  lcd.clear();
  lcd.print("Nivel de sonido");

  Serial.println("Setup completado");
}

void loop() {
  int soundLevel = analogRead(soundSensorAnalogPin); // Lee el nivel de sonido
  int soundDetected = digitalRead(soundSensorDigitalPin); // Lee el estado del pin digital

  // Depuración: Imprimir valores leídos
  Serial.print("Nivel de sonido: ");
  Serial.print(soundLevel);
  Serial.print(" | Sonido detectado: ");
  Serial.println(soundDetected);

  int mappedLevel = map(soundLevel, 50, 90, 0, 8);
  mappedLevel = constrain(mappedLevel, 0, 8); // Asegura que el valor esté entre 0 y 8

  // Muestra el nivel de sonido en el LCD
  lcd.setCursor(0, 1);
  lcd.print("Nivel: ");
  lcd.print(mappedLevel);
  lcd.print("   "); // Espacios adicionales para borrar valores anteriores

  // Mostrar nivel de sonido en la matriz LED
  displaySoundLevel(mappedLevel);

  delay(100); // Pausa de 100ms entre lecturas
}

void displaySoundLevel(int level) {
  lc.clearDisplay(0); // Limpia la pantalla

  // Enciende las filas correspondientes al nivel de sonido
  for (int row = 0; row < level; row++) {
    lc.setColumn(0, row, B11111111); // Enciende todas las columnas de la fila
  }
}
