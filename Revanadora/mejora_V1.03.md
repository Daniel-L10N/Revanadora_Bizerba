```markdown
### Explicación del Sensor y Función de Muestra

El sensor Hall de 4 terminales tiene las siguientes conexiones:
- **Blanco**: Retorno de corriente.
- **Amarillo**: Señal negativa.
- **Café**: Entrada VCC (12V DC).
- **Verde**: Entrada GND.

Este sensor emite un pulso cada vez que una pieza con un imán pasa frente a él. Para integrar este sensor con nuestra placa, utilizamos un optoacoplador. La función a continuación cuenta los pulsos emitidos por el sensor y, después de un intervalo de 20 segundos utilizando la función `millis`, realiza una acción específica.

### Función de Muestra
```cpp
void manejarPulsos() {
    static unsigned long tiempoAnterior = 0;
    unsigned long tiempoActual = millis();

    if (tiempoActual - tiempoAnterior >= 20000) { // 20 segundos
        digitalWrite(17, LOW);
        tiempoAnterior = tiempoActual;
    }
}
```
```
