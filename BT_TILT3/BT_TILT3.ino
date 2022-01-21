//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html

#include <AFMotor.h>
     
    AF_DCMotor motorIz(2, MOTOR12_1KHZ); // create motor #1, 1KHz pwm
    AF_DCMotor motorDer(3, MOTOR12_1KHZ); // create motor #2, 1KHz pwm
  
#include <SoftwareSerial.h>
SoftwareSerial BT1(A0,A1); // RX, TX recordar que se cruzan, BT_RX->A1 y BT_Tx->A0

//Variables de control y/o lectura
char valor; //un solo byte, un caracter ASCII
String estado_pitch;// texto
String datos_in;


void setup() {

  Serial.begin(9600);
  BT1.begin(9600);
  test_cocherobot();
}
void loop(){
 
  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  {
    valor = BT1.read();  //Lee el dato entrante via Bluetooth

    if (valor == 'P')   //Si el dato entrante es del PITCH
    {
      //PITCH();   //Llama la función que controla el MOTOR IZQUIERDO
      BT_envio_datos();
    }
    if (valor == 'll')   //Si el dato entrante es del ROLL
    {
      BT_Roll();
//      ROLL();     //Llama la función que controla el MOTOR DERECHO
    }
     if (valor == 'S')   //Si el dato entrante es una S
    {
      MSTOP();     //Llama la función que DETIENE AMBOS MOTORES
    }
  }
}

void BT_envio_datos (){
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    datos_in += c;    //Crea una cadena tipo String con los datos entrantes
    
  }// end while
  if (datos_in.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      int pitch = datos_in.toInt(); //toma el primer valor de datos_in, (i.e:  -58R25->-58)
      Serial.println(pitch);
      
      int indice_R = datos_in.indexOf('R');
      String roll = datos_in.substring(indice_R+1);
      Serial.println(roll);
      
      int y = datos_in.toInt();
      //Serial.println(datos_in); 
      PITCH(y);
      datos_in = ""; //vaciamos la cadena
    }//end if
  
  }// end function BT_envio_datos

void BT_Roll (){
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    datos_in += c;    //Crea una cadena tipo String con los datos entrantes
  }// end while
  if (datos_in.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      datos_in = datos_in.toInt();
      int y = datos_in.toInt();
      Serial.println(datos_in); 
      ROLL(y);
      datos_in = ""; //vaciamos la cadena
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

void PITCH_OLD()
{
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    estado_pitch += c;    //Crea una cadena tipo String con los datos entrantes
  }
  if (estado_pitch.length() > 0)  //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
    estado_pitch = estado_pitch.toInt();
   Serial.println("posición ---> " + estado_pitch);
   ADELANTE ();
   
   /*
   if (velocidad <0){
    velocidad = abs(velocidad);
    motorIz.setSpeed(velocidad); 
    motorIz.run(BACKWARD); }
   else  { 
    motorIz.setSpeed(velocidad); 
    motorIz.run(FORWARD); }
   */
   estado_pitch = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}

void MD()
{
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    estado_pitch += c;    //Crea una cadena tipo String con los datos entrantes
  }
  if (estado_pitch.length() > 0)  //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
   int velocidad = estado_pitch.toInt();//alternativa long veloc = Serial.parseInt(estado_pitch)
   Serial.println("posición ---> " + estado_pitch);
  /* 
   if (velocidad <0){
    velocidad = abs(velocidad);
    motorDer.setSpeed(velocidad); 
    motorDer.run(BACKWARD); }
   else  { 
    motorDer.setSpeed(velocidad); 
    motorDer.run(FORWARD); }
   */
   estado_pitch = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}

void MSTOP()
{  
   delay(30);
   motorDer.run(RELEASE);
   motorIz.run(RELEASE); 
   motorDer.setSpeed(0);
   motorIz.setSpeed(0); 
   BT1.end();//finaliza la conexión serie para que no reciba más datos del móvil
  }

void test_cocherobot(){
  BT1.println("Motor test!");
      
  motorIz.setSpeed(250);      // set the speed to 0  0/255
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

 void ADELANTE (){
    motorIz.setSpeed(200);      // set the speed to 0  0/255
    motorDer.setSpeed(200);     // set the speed to 0  0/25
    Serial.print("tickFORWARD ");
    motorIz.run(FORWARD);      // turn it on going forward
    motorDer.run(FORWARD);      // turn it on going forward
    }
