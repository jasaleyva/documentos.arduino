#include <SoftwareSerial.h>
SoftwareSerial BT1(A0,A1); 

// El módulo bluetooth se conecta así
// Bluetooth_RX  -> A1_arduino
// Bluetooth_TX  -> A0_arduino
// Bluetooth_GND -> GND_arduino
// Bluetooth_VCC -> 5V_arduino

#include <AFMotor.h>
AF_DCMotor motorDer(2);
//asegurate que tienes conectado el motor derecho al puerto 1
AF_DCMotor motorIz(1);

//Variables de control y/o lectura
char valor; //un solo byte, un caracter ASCII
//String estado;// texto

void setup() {
  Serial.begin(9600);//iniciamos conexión montor serie
  BT1.begin(9600);   //iniciamos conexión bluetooth

  //Probamos que la rueda derecha funciona
  motorDer.setSpeed(100);     // veloc entre 0-255
  motorIz.setSpeed(100);     // veloc entre 0-255
  
  motorDer.run(FORWARD);      // gira marcha adelante
  delay(2000);
  motorDer.run(RELEASE);      // parado
  delay(500);   
  motorDer.run(BACKWARD);     // marcha atrás
  delay(1000);
  motorDer.run(RELEASE);      // parado

 //Probamos que la rueda izquierda funciona
  motorIz.run(FORWARD);      // gira marcha adelante
  delay(2000);
  motorIz.run(RELEASE);      // parado
  delay(500);   
  motorIz.run(BACKWARD);     // marcha atrás
  delay(1000);
  motorIz.run(RELEASE);      // parado
 }

void loop() {

  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  {

    valor = BT1.read();  //Lee el dato entrante via Bluetooth
    Serial.println(valor);  //imprime el valor en el monitor serie 
//Si el dato entrante es "0" se DETIENE
    if (valor == '0')   
    {
      motorDer.run(RELEASE);
      motorIz.run(RELEASE);
    }
//Si el dato entrante es "1" marcha ADELANTE
    else if (valor == '1')   
    {
     motorDer.run(FORWARD);
     motorIz.run(FORWARD);
    }
//Si el dato entrante es "2" marcha ATRÁS    
    else if (valor == '2')   
    {
      motorDer.run(BACKWARD);
      motorIz.run(BACKWARD);
    }
//Si el dato entrante es "3" Gira a la DERECHA    
    else if (valor == '3')   
    {
      motorDer.run(RELEASE);
      motorIz.run(FORWARD);
    }
//Si el dato entrante es "4" gira a IZQUIERDA
    else if (valor == '4')   
    {
       motorIz.run(RELEASE);
       motorDer.run(FORWARD);
    }
    
 
 }//fin del if (BT1.available())
} //fin del loop()
