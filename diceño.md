🧱 Diseño de hardware – PLC con ATmega328
🔧 Microcontrolador
ATmega328P-PU (montado directo en placa)

Cristal de 16 MHz conectado a XTAL1 y XTAL2

2 capacitores cerámicos de 22 pF entre cada pin del cristal y GND

Resistencia de 10 kΩ entre RESET y Vcc

Capacitor de 100 nF entre Vcc y GND (desacoplo)

⚡ Fuente de alimentación
Entrada: 12 V DC desde bornera

Regulador lineal: 7805 para convertir 12 V → 5 V

Condensadores:

100 µF entre entrada 12 V y GND

100 µF entre salida 5 V y GND

Salida: 5 V para alimentar ATmega328 y lógica

🟢 Entradas optoacopladas (PC817 ×4)
Cada entrada incluye:

Resistencia limitadora: 1 kΩ–2.2 kΩ en serie con el LED del opto

LED interno del optoacoplador conectado a señal externa

Salida del opto conectada al pin digital del ATmega328

Pull-down externo de 10 kΩ si se requiere estabilidad

Entrada	Pin ATmega328	Función lógica
btArranque	D2	Botón de arranque
btApagado	D3	Botón de apagado
finalCarrera	D4	Final de recorrido
sensorHall	D5	Sensor de efecto Hall
🔴 Salidas de relé (Steren 12 V 5 A ×2)
Cada salida incluye:

Transistor NPN (ej. 2N2222 o BC547)

Resistencia de base: 1 kΩ entre pin ATmega y base

Colector conectado al relé

Emisor a GND

Diodo 1N4007 en paralelo con bobina del relé (protección contra contracorriente)

Relé alimentado directamente con 12 V

Salida	Pin ATmega328	Función lógica
releMotor	D8	Motor principal
releFoco	D9	Foco piloto
💡 LED de estado
Pin D13 conectado a LED con resistencia de 330 Ω

Indica encendido o estado lógico del sistema

🧩 Conectores y distribución
Bornera de entrada 12 V con protección (fusible o PPTC)

Borneras para entradas optoacopladas (señales externas)

Borneras para salidas de relé (NO/NC/COM)

Header ISP opcional para programación del ATmega328

🧾 Esquema modular en Proteus
Organiza el diseño así:

🔋 Izquierda: fuente de 12 V, regulador 7805, capacitores

🧠 Centro: ATmega328, cristal, LED, pines etiquetados

🟢 Arriba: entradas optoacopladas (PC817)

🔴 Abajo: transistores y relés Steren con diodos