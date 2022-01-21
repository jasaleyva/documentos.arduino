//Movil controla Lampara de 230V mediante BT y RELE  v.1
//JAVIER S. 

//CONEXIONES del RELE
//RELE COM - a circuito de LAMPARA
//RELE NC  - NADA
//RELE NO  - a circuito de LAMPARA
//RELE D+  - a 5V Arduino
//RELE D-  - a GND Arduino
//RELE IN  - a D9 Arduino 

#include <SoftwareSerial.h>

//creamos un objeto para comunicacion serie llamado BT1
SoftwareSerial BT1(A0,A1); //RX, TX
// En HC06 se cruzan los cables, A0 y A1 así: 
//    HC06_RX..A1 
//    HC06_TX->A0

//Variables de control y/o lectura
char valor;           //un solo byte, un caracter ASCII

void setup() {
 BT1.begin(9600); //comienza la comunicación serie con BT1
 pinMode(9, OUTPUT);
}
void loop() {

  //Si el puerto serie (Bluetooth) está disponible
  if (BT1.available())  {
    valor = BT1.read();  //Lee el dato entrante via Bluetooth     
  }

  if (valor == 'A')   //Si el dato entrante es A, encender la lampara 
      {digitalWrite(9, HIGH); }
  else if (valor == 'B')   //Si el dato entrante es B, apagarla
      {digitalWrite(9, LOW);}
}
