//control de LED conRELE  v.1
//JAVIER S. 
//Un LED conectado a Arduino es controlado por un relé
//El led se enciende/apaga en ciclo de 1.5 s
//y muestra su nivel lógico en el monitor Serie

//CONEXIONES RELE-LED-ARDUINO

//RELE COM - 5V ARDUINO
//RELE NC  - NADA
//RELE NO  - a R 220 del LED

//RELE D+  - a 5V Arduino
//RELE D-  - a GND Arduino
//RELE IN  - a D9 Arduino 

//LED +    - a R 220
//LED -    - a GND Arduino

void setup() {
  // etapa control del RELE conectada a D9
  pinMode(9, OUTPUT);
  //Iniciamos puerto comunicacion SERIE
  Serial.begin(9600);
}

void loop() {
  digitalWrite(9, HIGH);
  Serial.println("ALTO"); 
  delay(1500);
  digitalWrite(9, LOW);
  Serial.println("BAJO"); 
  delay(1500);
      
}
