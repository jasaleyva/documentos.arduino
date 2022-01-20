//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html

#include <AFMotor.h>
     
    AF_DCMotor motorIz(2, MOTOR12_1KHZ); // create motor #1, 1KHz pwm
    AF_DCMotor motorDer(3, MOTOR12_1KHZ); // create motor #2, 1KHz pwm
  
#include <SoftwareSerial.h>
SoftwareSerial BT1(A0,A1); // RX, TX recordar que se cruzan, BT_RX->A1 y BT_Tx->A0

//Variables de control y/o lectura
char valor; //un solo byte, un caracter ASCII
String estado;// texto

void setup() {

  Serial.begin(9600);
  BT1.begin(9600);
  
  Serial.println("Motor test!");
      
  motorIz.setSpeed(250);      // set the speed to 0  0/255
  motorDer.setSpeed(255);     // set the speed to 0  0/25
  Serial.print("tickFORWARD ");
      
  motorIz.run(FORWARD);      // turn it on going forward
  motorDer.run(FORWARD);      // turn it on going forward
  delay(2000);
  Serial.print("tockBACKWARD ");
      
  motorIz.run(BACKWARD);     // the other way
  motorDer.run(BACKWARD);     // the other way
  delay(1000);
      
  Serial.print("tuckRELEASE");
  motorIz.run(RELEASE);      // stopped
  motorDer.run(RELEASE);      // stopped
  delay(1000);  
}

void loop() {

  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  {
    valor = BT1.read();  //Lee el dato entrante via Bluetooth

    if (valor == 'I')   //Si el dato entrante es una I
    {
      MI();   //Llama la función que controla el MOTOR IZQUIERDO
    }
    if (valor == 'D')   //Si el dato entrante es una D
    {
      MD();     //Llama la función que controla el MOTOR DERECHO
    }
     if (valor == 'S')   //Si el dato entrante es una S
    {
      MSTOP();     //Llama la función que DETIENE AMBOS MOTORES
    }
  }
}


void MI()
{
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    estado += c;    //Crea una cadena tipo String con los datos entrantes
  }
  if (estado.length() > 0)  //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
   int velocidad=estado.toInt();
   //Serial.println("posición ---> " + estado);
   motorIz.setSpeed(velocidad); 
   motorIz.run(FORWARD);  
   estado = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}
void MD()
{
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    estado += c;    //Crea una cadena tipo String con los datos entrantes
  }
  if (estado.length() > 0)  //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
   int velocidad=estado.toInt();
   motorDer.setSpeed(velocidad); 
   motorDer.run(FORWARD);  
   estado = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}

void MSTOP()
{  
   delay(30);
   motorDer.run(RELEASE);
   motorIz.run(RELEASE); 
   motorDer.setSpeed(0);
   motorIz.setSpeed(0); 
   
  }
