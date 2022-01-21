//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html

#include <AFMotor.h>
     
    AF_DCMotor motorIz(4); // crea motorIz para controlar el motor conectado a #2
    AF_DCMotor motorDer(1); // crea motorDer para controlar el motor conectado a #3
  
#include <SoftwareSerial.h>
SoftwareSerial BT1(A0,A1); // RX, TX recordar que se cruzan, HC06_RX->A1 y HC06Tx->A0

//Variables Globales (definidas fuera de las funciones) de control y/o lectura
char valor; //un solo byte, un caracter ASCII
String estado_pitch;// texto
String datos; //datos que llegan
int pitch;// variable que almacena la inclinacion del morro
int roll;// almacena el valor roll= inclinacion lateral


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
    Serial.println(pitch);
    Serial.println(roll);
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
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    }
 //Atrás
 if (pitch >10 && roll >-10 && roll <10 ){
   //int pitch_abs = pitch*(-1); //eliminamos el signo negativo
   int veloc = map (pitch, 0,90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(BACKWARD);
   motorDer.run(BACKWARD);
    }
 //Detenido
 if (pitch >-10 && pitch <10 && roll >-10 && roll <10 ){
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);  
    } 

 //Giro Derecha Adelante

if (pitch >-10 && pitch <10 && roll <-10 ){
   int veloc = map (roll, 0,-90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc/2);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
    
 //Giro Izquierda Adelante

if (pitch >-10 && pitch <10 && roll >10 ){
   int veloc = map (roll, 0,90, 0,255);
   motorIz.setSpeed(veloc/2); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
//Giro Derecha Atras

if (pitch <-10 && roll <-10 ){
   int veloc = map (roll, 0,-90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(BACKWARD);
    } 

//Giro Izquierda Atras

if (pitch <-10 && roll >10 ){
   int veloc = map (roll, 0,90, 0,255);
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
      
      int indice_R = datos.indexOf('R');//encuentra la osicion de "R" en la cadena
      String roll_str = datos.substring(indice_R+1); // almacena la subcadena después de "R"
      roll = roll_str.toInt();//variable que almacena el valor roll como número entero
     // Serial.println(roll);
      datos = ""; //vaciamos la cadena
      }//end if (length >0)
   
 

  
  }// end function BT_envio_datos




void test_cocherobot(){
  BT1.println("Motor test!");
      
  motorIz.setSpeed(150);      // set the speed to 0  0/255
  motorDer.setSpeed(150);     // set the speed to 0  0/25
  
  Serial.print("tick FORWARD ");
  motorIz.run(FORWARD);      // turn it on going forward
  motorDer.run(FORWARD);      // turn it on going forward
  delay(1000);
  
  Serial.print("tock BACKWARD ");
  motorIz.run(BACKWARD);     // the other way
  motorDer.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.print("tack GIRO DERECHA ");
  motorIz.run(FORWARD);     // the other way
  motorDer.run(BACKWARD);     // the other way
  delay(1000);
   
  Serial.print("tack GIRO IZQUIERDA ");
  motorDer.run(FORWARD);     // the other way
  motorIz.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.println("tuck RELEASE");
  motorIz.run(RELEASE);      // stopped
  motorDer.run(RELEASE);      // stopped
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
