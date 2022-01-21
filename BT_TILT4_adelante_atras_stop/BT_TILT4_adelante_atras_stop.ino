//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html

#include <AFMotor.h>
     
    AF_DCMotor motorIz(2, MOTOR12_1KHZ); // crea motorIz para controlar el motor conectado a #2
    AF_DCMotor motorDer(3, MOTOR12_1KHZ); // crea motorDer para controlar el motor conectado a #3
  
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
    if (valor == 'S')   //Si el dato entrante es una S
      {
      MSTOP();     //Llama la función que DETIENE AMBOS MOTORES
      }
    if (valor == 'P')   //Es el primer caracter de la cadena tipo: P-69R-58 
       {
       BT_envio_datos();//funcion que toma el resto de la cadena -69R58  y separa los datos -69 y -58
       }
    Serial.println(pitch);
    Serial.println(roll);
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
        //Movimiento del coche robot
  //Adelante
  //Atrás
  //Detenido
  //Giro Derecha Adelante
  //Giro Izquierda Adelante
  //Giro Derecha Atras
  //Giro Izquierda Atras
 
 
 //Adelante
 if (pitch >10 && roll >-10 && roll <10 ){
   int veloc = map (pitch, 0,90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    }
 //Atrás
 if (pitch <-10 && roll >-10 && roll <10 ){
   //int pitch_abs = pitch*(-1); //eliminamos el signo negativo
   int veloc = map (pitch, 0,-90, 0,255);
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
 }//end if (length >0)
  
  }// end function BT_envio_datos

void BT_Roll (){
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    datos += c;    //Crea una cadena tipo String con los datos entrantes
  }// end while
  if (datos.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      datos = datos.toInt();
      int y = datos.toInt();
      Serial.println(datos); 
      ROLL(y);
      datos = ""; //vaciamos la cadena
    }//end if
  
  }// end function BT_envio_datos



void PITCH (int x){
 
   if (x > 10) {     // marcha = "FORWARD"; 
   int veloc = map (x, 0,90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
   } 
  else if ((x < -10)) { //MARCHA ATRÁS BACKWARD
    x = abs(x); //eliminamos el signo negativo
    int veloc = map (x, 0,90, 0,255);
    motorIz.setSpeed(veloc); 
    motorDer.setSpeed(veloc);
    motorIz.run(BACKWARD);
    motorDer.run(BACKWARD);
  }
  else { 
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);
    }

    
}// end of PITCH


void ROLL (int x){
 
   if (x > 10) {     // GIRA IZQU; 
   int veloc = map (x, 0,50, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(BACKWARD);
   motorDer.run(FORWARD);
   } 
  else if ((x < -10)) { //GIRA DER
    x = abs(x); //eliminamos el signo negativo
    int veloc = map (x, 0,50, 0,255);
    motorIz.setSpeed(veloc); 
    motorDer.setSpeed(veloc);
    motorIz.run(FORWARD);
    motorDer.run(BACKWARD);
  }
  else { 
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);
    }

    
}// end of PITCH





void MSTOP()
{  
   delay(30);
   motorDer.run(RELEASE);
   motorIz.run(RELEASE); 
   BT1.end();//finaliza la conexión serie para que no reciba más datos del móvil
  }

void test_cocherobot(){
  BT1.println("Motor test!");
      
  motorIz.setSpeed(255);      // set the speed to 0  0/255
  motorDer.setSpeed(255);     // set the speed to 0  0/25
  Serial.print("tick FORWARD ");
      
  motorIz.run(FORWARD);      // turn it on going forward
  motorDer.run(FORWARD);      // turn it on going forward
  delay(2000);
  Serial.print("tock BACKWARD ");
      
  motorIz.run(BACKWARD);     // the other way
  motorDer.run(BACKWARD);     // the other way
  delay(1000);
      
  Serial.println("tuck RELEASE");
  motorIz.run(RELEASE);      // stopped
  motorDer.run(RELEASE);      // stopped
  delay(1000);
  }
