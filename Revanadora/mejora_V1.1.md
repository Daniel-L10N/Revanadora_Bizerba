# Mejora V1.1: Implementación de Sensores para el Eje Guía

La siguiente mejora para el equipo rebanadora consiste en la implementación de un sensor para detectar el desplazamiento del brazo de carga sobre el eje guía. Esto se logrará utilizando un sensor de efecto Hall o, en su defecto, un sensor inductivo. A continuación, se detalla la propuesta:

## Sensor de Efecto Hall

El sensor de efecto Hall detectará variaciones en el campo magnético. Estas variaciones permitirán determinar si el brazo de carga se está desplazando sobre el eje guía. Para implementar esta solución:

1. **Configuración del sensor**: Se establecerán rangos de variación del campo magnético que indiquen el movimiento del brazo.
2. **Limitaciones del hardware**: Si el hardware no permite medir con precisión las variaciones del campo magnético, se optará por un sensor inductivo.

## Sensor Inductivo

En caso de utilizar un sensor inductivo, este se colocará en el centro del equipo. Esto reducirá las probabilidades de que el brazo de carga pase sin ser detectado. El sensor detectará el paso del brazo cuando este se desplace frente a él.

### Código de Ejemplo: Sensor Inductivo con `millis()`

El siguiente código utiliza un sensor inductivo para detectar el paso del brazo. Se emplea la función `millis()` para gestionar el tiempo y evitar bloqueos en el programa.

```cpp
const int sensorPin = 2; // Pin digital conectado al sensor inductivo
const int ledPin = 13;   // LED indicador (opcional)
bool brazoDetectado = false;
unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 500; // Tiempo mínimo entre detecciones (en ms)

void setup() {
    pinMode(sensorPin, INPUT);
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int estadoSensor = digitalRead(sensorPin);
    unsigned long tiempoActual = millis();

    // Detectar si el brazo pasa frente al sensor
    if (estadoSensor == HIGH && !brazoDetectado && (tiempoActual - tiempoAnterior >= intervalo)) {
        brazoDetectado = true;
        tiempoAnterior = tiempoActual;
        digitalWrite(ledPin, HIGH); // Enciende el LED (opcional)
        Serial.println("Brazo detectado");
    }

    // Restablecer el estado cuando el brazo ya no está frente al sensor
    if (estadoSensor == LOW) {
        brazoDetectado = false;
        digitalWrite(ledPin, LOW); // Apaga el LED (opcional)
    }
}
```

### Consideraciones

- **Colocación del sensor**: Asegúrate de que el sensor esté correctamente alineado con el brazo de carga.
- **Pruebas y calibración**: Realiza pruebas para ajustar los rangos de detección y minimizar errores.
- **Seguridad**: Implementa medidas de seguridad para evitar daños al equipo o al operador.

Con esta mejora, se espera optimizar el funcionamiento del equipo rebanadora y garantizar una detección precisa del movimiento del brazo de carga.