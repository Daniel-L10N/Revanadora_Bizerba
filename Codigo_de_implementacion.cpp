// Pines conectados a los relés..
const int reles[6] = {1, 2, 3, 4, 5, 12};
// Pines conectados a las entradas digitales de los optocopladores..
const int entradasOpto[6] = {17, 18, 19, 21, 22, 23}; 

//Definiendo botonera
const int btArranque = entradasOpto[0]; // Entrada digital (btn de arranque)
const int btApagado = entradasOpto[1];  // Entrada digital (btn de apagar)

//Definiendo Sistema de Seguridad
const int finalDeCarrera = entradasOpto[2]; // Entrada digital (btn de finalizacion de uso del equipo)
// Falta implementar el sonsor de efecto hall

void setup() {
  Serial.begin(115200); //Inicio de comunicacion serial para pruebas con pc, comentar a final del programa.

  // Configura entrada con resistencia pull-up - pulldown interna
  pinMode(btArranque, INPUT_PULLDOWN); // LOW cuando no presionado, con proteccion contra pin flotante.
  pinMode(btApagado, INPUT_PULLUP);

  // Configura los relés como salidas
  for (int i = 0; i < 2; i++) {
    pinMode(reles[i], OUTPUT);
    digitalWrite(reles[i], LOW); // Inicializacion el nivel bajo LOW
  }
  for (int i = 2; i < 6; i++){ // INICIALIZANDO RELES PARA EVITAR FALLOS EN LOGICA ELECTRICA.
    pinMode(reles[i], OUTPUT);

  }
}

void loop() {

  if (digitalRead(btArranque) == HIGH && digitalRead(btApagado)== HIGH && digitalRead(finalDeCarrera) == HIGH) { // Botón presionado ejecutar. y no esta precionado el de apagado y la maquina no se encuentra en estado de descanso.
    Serial.print("PIN arranque ");
    Serial.println(digitalRead(btArranque));
    digitalWrite(reles[0], HIGH); // Activar relé numero 1, que activa rele de motor
    digitalWrite(reles[1], HIGH); // Activar rele nuemro 2 de foco piloto

  }else if (digitalRead(btApagado) == LOW){ // Ejecutar si se preciona el boton apagado
    Serial.print("PIN Apagador ");
    Serial.println(digitalRead(btApagado));
    digitalWrite(reles[0], LOW); 
    digitalWrite(reles[1], LOW);

  }else if (digitalRead(finalDeCarrera) == LOW){// Ejecutar si se llega al 0 en la linea de uso.
    Serial.print("PIN finalDeCarrera ");
    Serial.println(digitalRead(finalDeCarrera));
    digitalWrite(reles[0], LOW);
    digitalWrite(reles[1], LOW); 
  }
}
