// === CONFIGURACIÓN DE PINES ===
const int releMotor = 8;
const int entradasOpto[4] = {2, 3, 4, 5};

const int btArranque      = entradasOpto[0]; // D2
const int btApagado       = entradasOpto[1]; // D3
const int finalDeCarrera  = entradasOpto[2]; // D4
const int sensorHall      = entradasOpto[3]; // D5

// === TEMPORIZADORES ===
unsigned long tiempoInicial = 0;
unsigned long tiempoEstablecido = 20000;
unsigned long tiempoActual = 0;

// Estado lógico del relé
bool releActivo = false;

void setup() {
  // Entradas con resistencias pull-down físicas
  pinMode(btArranque, INPUT);
  pinMode(btApagado, INPUT);
  pinMode(finalDeCarrera, INPUT);
  pinMode(sensorHall, INPUT);

  // Salida del relé
  pinMode(releMotor, OUTPUT);
  digitalWrite(releMotor, LOW);
}

void loop() {
  // Condición de arranque
  if (digitalRead(btArranque) == HIGH &&
      digitalRead(btApagado) == HIGH &&
      digitalRead(finalDeCarrera) == HIGH) {

    digitalWrite(releMotor, HIGH);
    releActivo = true;
    tiempoInicial = millis();
  }

  // Reinicio de temporizador si hay señal del sensor Hall
  if (digitalRead(sensorHall) == HIGH && releActivo) {
    tiempoInicial = millis();
  }

  // Condiciones de apagado si el relé está activo
  if (releActivo) {
    tiempoActual = millis();

    if (digitalRead(btApagado) == LOW ||
        digitalRead(finalDeCarrera) == LOW ||
        (tiempoActual - tiempoInicial >= tiempoEstablecido)) {

      digitalWrite(releMotor, LOW);
      releActivo = false;
    }
  }
}
