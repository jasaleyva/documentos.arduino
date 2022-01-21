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
int pitch; //valor del pitch (inclinacion del morro) enviado por el movil
int roll; //valor del roll (inclinacion lateral) enviado por el movil


void setup() {

  Serial.begin(9600);
  BT1.begin(9600);
  test_cocherobot();
    
}

void loop() {

  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  {
    valor = BT1.read();  //Lee el dato entrante via Bluetooth

    if (valor == 'P')   //Si el dato entrante es del PITCH
    {
      //PITCH();   //Llama la función que controla el MOTOR IZQUIERDO
     pitch = BT_Pitch();//funcion que deuelve el valor Pitch
    }
    if (valor == 'RR')   //Si el dato entrante es del ROLL
    {
  //    BT_Roll();//funcion que deuelve el valor Pitch
//      ROLL();    
    }  
  
     if (valor == 'SS')   //Si el dato entrante es una S
    {
      MSTOP();     //Llama la función que DETIENE AMBOS MOTORES
    }
  } //end of if (BT1(available)

}//end of loop

int BT_Pitch (){
  int pitch1;
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    datos_in += c;    //Crea una cadena tipo String con los datos entrantes
  }// end while
  if (datos_in.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      //datos_in = datos_in.toInt();
      //int x = datos_in.toInt();
      pitch1 = datos_in.toInt(); // se alamacenan los datos entrantes como numero entero
      Serial.println("Pitch1 "+ pitch1 ); 
      /*
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
    */
    datos_in = ""; //vaciamos la cadena
    }//end if
  return pitch1;
  }// end function BT_Pitch
  
/*
void BT_Roll (){
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    datos_in += c;    //Crea una cadena tipo String con los datos entrantes
  }// end while
  if (datos_in.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      //datos_in = datos_in.toInt();
      int y = datos_in.toInt();
      Serial.println("Roll"+datos_in); 
      if (y > 15 && x >=-9 && x <=9) {     // girar IZQUIERDA; 
         int veloc = map (y, 0,90, 0,255);
         motorIz.setSpeed(veloc); 
         motorDer.setSpeed(veloc/2);
         motorIz.run(FORWARD);
         motorDer.run(FORWARD);
     } 
     else if (y < -15 && x >=-9 && x <=9) { //girar DERECHA
         y = abs(y); //eliminamos el signo negativo
         int veloc = map (y, 0,90, 0,255);
         motorIz.setSpeed(veloc/2); 
         motorDer.setSpeed(veloc);
         motorIz.run(BACKWARD);
         motorDer.run(BACKWARD);
    }
    else { 
         motorIz.run(RELEASE);
         motorDer.run(RELEASE);
    }



      
    datos_in = ""; //vaciamos la cadena
    }//end if
  
  }// end function BT_Roll
*/

/*
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
*/
/*
void ROLL (int x){
 
   if (x > 10) {     // GIRA IZQU; 
   int veloc = map (x, 0,90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(BACKWARD);
   motorDer.run(FORWARD);
   } 
  else if ((x < -10)) { //GIRA DER
    x = abs(x); //eliminamos el signo negativo
    int veloc = map (x, 0,90, 0,255);
    motorIz.setSpeed(veloc); 
    motorDer.setSpeed(veloc);
    motorIz.run(FORWARD);
    motorDer.run(BACKWARD);
  }
  else { 
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);
    }

    
}// end of ROLL
*/

/*
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
   
  
   if (velocidad <0){
    velocidad = abs(velocidad);
    motorIz.setSpeed(velocidad); 
    motorIz.run(BACKWARD); }
   else  { 
    motorIz.setSpeed(velocidad); 
    motorIz.run(FORWARD); }
   
   estado_pitch = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}
*/

/*
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
 
   estado_pitch = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}
*/

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
