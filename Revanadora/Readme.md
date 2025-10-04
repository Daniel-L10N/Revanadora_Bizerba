# 🧾 Proyecto: Tarjeta de Control para Rebanadora Industrial

## 🟢 Resumen General

- **Motivo**: Reemplazo de tarjeta original quemada.
- **Controlador principal**: ESP32-WROOM-DA montado sobre placa tipo PLC.
- **Alimentación general**: Fuente externa de 12 V DC.
- **Motor**: Monofásico 110 V AC, 1/3 HP (~250 W).
- **Control de potencia**: Relé de estado sólido (SSR) activado por relé intermedio de 12 V.
- **Entradas protegidas**: 3 señales aisladas con optoacopladores.
- **Indicador visual**: LED de 12 V controlado por relé.

---

## ⚡ Alimentación

| Componente            | Voltaje | Fuente             | Observaciones                          |
|----------------------|---------|--------------------|----------------------------------------|
| Placa PLC ESP32      | 12 V DC | Fuente externa     | Regulación interna a 3.3 V incluida    |
| Relés (x2)           | 12 V DC | Fuente externa     | Uno para motor, otro para LED          |
| Sensor Hall          | 12 V DC | Fuente externa     | Detecta movimiento                     |
| LED indicador        | 12 V DC | Fuente externa     | Encendido cuando motor está activo     |

### 🔒 Protecciones recomendadas

- Fusible de entrada: 2 A lento en línea de 12 V DC.
- Fusible de salida: 5 A rápido en línea de motor (antes del SSR).
- Diodos flyback en bobinas de relés.
- Capacitores de filtrado en entrada de fuente (1000 µF + 100 nF).
- Varistor en línea de 110 V AC (protección contra picos).

---

## 🧠 Controlador – ESP32-WROOM-DA

- Montado sobre placa PLC con:
  - Regulador interno.
  - Optoacopladores para entradas.
  - Relés integrados (6 disponibles, se usan 2).
- Alimentado directamente con 12 V DC.
- Comunicación posible por WiFi/Bluetooth (opcional).

---

## 🔘 Entradas digitales (aisladas con optoacopladores)

| Entrada           | Tipo | Función                                 | Estado lógico en ESP |
|------------------|------|------------------------------------------|-----------------------|
| Botón arranque   | NA   | Inicia ciclo, activa motor               | HIGH cuando presionado|
| Botón paro       | NC   | Detiene motor inmediatamente             | LOW cuando presionado |
| Final de carrera | NC   | Apaga motor al llegar a posición 0       | LOW cuando activado   |

---

## 🧲 Sensor de efecto Hall

- Detecta campo magnético en eje de brazo.
- Señal digital enviada al ESP32.
- Si no hay pulsos por 15 s → sistema entra en modo standby (motor apagado).

---

## 🔁 Salidas digitales

| Salida           | Tipo     | Controlador | Función                          |
|------------------|----------|-------------|----------------------------------|
| Relé motor       | Relé 12 V| ESP32       | Activa SSR → motor ON/OFF       |
| Relé LED         | Relé 12 V| ESP32       | Enciende LED cuando motor está activo |

---

## 💡 Indicadores

- LED de 12 V conectado a relé.
- Encendido solo cuando el motor está en funcionamiento.

---

## 🔄 Lógica de operación (flujo básico)

```plaintext
INICIO
↓
Esperar botón de arranque
↓
Si ARRANQUE presionado → activar relé motor + relé LED
↓
Mientras motor encendido:
    - Si PARO presionado → apagar motor + LED
    - Si FINAL DE CARRERA activado → apagar motor + LED
    - Si no hay pulsos Hall por 15 s → apagar motor + LED
↓
Esperar nuevo arranque
