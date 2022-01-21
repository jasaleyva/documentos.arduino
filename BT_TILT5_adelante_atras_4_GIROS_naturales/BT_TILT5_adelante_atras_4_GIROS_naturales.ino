//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html

#include <AFMotor.h>
     
    AF_DCMotor motorIz(1); // crea motorIz para controlar el motor conectado a #2
    AF_DCMotor motorDer(2); // crea motorDer para controlar el motor conectado a #3
  
#include <SoftwareSerial.h>
SoftwareSerial BT1(A0,A1); // RX, TX recordar que se cruzan, HC06_RX->A1 y HC06Tx->A0
// El módulo bluetooth se conecta así
// Bluetooth_RX  -> A1_arduino
// Bluetooth_TX  -> A0_arduino
// Bluetooth_GND -> GND_arduino
// Bluetooth_VCC -> 5V_arduino

//Variables Globales (definidas fuera de las funciones) de control y/o lectura
char valor; //un solo byte, un caracter ASCII
String estado_pitch;// texto
String datos; //datos que llegan
int pitch;// variable que almacena la inclinacion del morro
int roll;// variable que almacena la inclinacion lateral
int offset = 0; //corrección veloc,ya que el motor izqu es más lento

void setup() {

  Serial.begin(9600);
  BT1.begin(9600);
  test_cocherobot();
}
void loop(){
 
  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  { 
    valor = BT1.read();  //Lee el primer caracter (un byte) entrante via Bluetooth y lo asigna a la variable "valor"
    if (valor == 'P')   //Es el primer caracter de la cadena tipo: P-69R-58 
       {
       BT_envio_datos();//funcion que toma el resto de la cadena -69R58  y separa los datos -69 y -58, además controla los dos motores
       }
    Serial.println(pitch); //imprime en el puerto serie el valor numerico de PITCH
    Serial.println(roll); // lo mismo pero para el ROLL
//..................................................................................................
  //Movimientos del coche robot
  //Adelante
  //Atrás
  //Detenido
  //Giro Derecha Adelante
  //Giro Izquierda Adelante
  //Giro Derecha Atras
  //Giro Izquierda Atras
 

 //Adelante
 if (pitch <-10 && roll >-10 && roll <10 ){
   int veloc = map (pitch, 0,-90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc-offset);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    }
 //Atrás
 if (pitch >10 && roll >-10 && roll <10 ){
   //int pitch_abs = pitch*(-1); //eliminamos el signo negativo
   int veloc = map (pitch, 0,90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc-offset);
   motorIz.run(BACKWARD);
   motorDer.run(BACKWARD);
    }
 //Detenido
 if (pitch >-10 && pitch <10 && roll >-10 && roll <10 ){
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);  
    } 

 //Giro Derecha Adelante 
if (pitch <-10  && roll <-10 ){
//if (pitch >-10 && pitch <10 && roll <-10 ){
   int veloc = map (roll, 0,-90, 0,255); // rango veloc 0-255
   motorIz.setSpeed(veloc);
   motorDer.setSpeed(veloc/2);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
    
 //Giro Izquierda Adelante 

if (pitch <-10  && roll >10 ){
//if (pitch >-10 && pitch <10 && roll >10 ){
   int veloc = map (roll, 0,90, 0,255);
   motorIz.setSpeed(veloc/2);
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
//Giro Derecha Atras

if (pitch  >10  && roll <-10 ){
   int veloc = map (roll, 0,-90, 0,100);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(BACKWARD);
    } 

//Giro Izquierda Atras 

if (pitch  >10  && roll >10 ){
   int veloc = map (roll, 0,90, 0,100);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(BACKWARD );
   motorDer.run(FORWARD);
    } 
//Fin de movimientos del coche robot ............................................................................

}//end of BT1.available 


 
}//end of loop()

void BT_envio_datos (){
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee un byte entrante y lo almacena en una variable tipo char
    datos += c;    //Crea una cadena tipo String con los datos (bytes) entrantes
    }// end while
    
  if (datos.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      pitch = datos.toInt(); //toma el primer valor de datos, (i.e:  -58R25->-58)
      //Serial.println(pitch);//lo imprime en el puerto Serie
      int indice_R = datos.indexOf('R');//encuentra la posicion de "R" en la cadena
      String roll_str = datos.substring(indice_R+1); // almacena la subcadena después de "R"
      roll = roll_str.toInt();//variable que almacena el valor roll como número entero
      // Serial.println(roll);
      datos = ""; //vaciamos la cadena
      }//end if (length >0)
}// end function BT_envio_datos




void test_cocherobot(){
  BT1.println("Motor test!");
      
  motorIz.setSpeed(150);      // define la veloc en el rango 0-255
  motorDer.setSpeed(150);     // 
  
  Serial.print("tick FORWARD ");
  motorIz.run(FORWARD);      // motor IZQ gira hacia adelante
  motorDer.run(FORWARD);      // motor DER gira hacia adelante
  delay(1000);
  
  Serial.print("tock BACKWARD ");
  motorIz.run(BACKWARD);     // motor IZQ gira hacia atrás
  motorDer.run(BACKWARD);     // motor DER gira hacia atrás
  delay(1000);
  
  Serial.print("tack GIRO DERECHA ");
  motorIz.run(FORWARD); 
  motorDer.run(BACKWARD); 
  delay(1000);
   
  Serial.print("tack GIRO IZQUIERDA ");
  motorDer.run(FORWARD); 
  motorIz.run(BACKWARD); 
  delay(1000);
  
  Serial.println("tuck RELEASE");
  motorIz.run(RELEASE);      // motor IZQ PARA
  motorDer.run(RELEASE);      // motor DER PARA
  delay(1000);
  }
  
/*
void MSTOP()
{  
   delay(30);
   motorDer.run(RELEASE);
   motorIz.run(RELEASE); 
   BT1.end();//finaliza la conexión serie para que no reciba más datos del móvil
  }
*/
