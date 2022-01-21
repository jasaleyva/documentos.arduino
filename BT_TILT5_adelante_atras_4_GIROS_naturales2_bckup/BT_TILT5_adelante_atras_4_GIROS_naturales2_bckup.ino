//PROYECTO ESCOLAR
//Título: Coche_Robot_controlado_por_sensor_orientacion_del_movil
//Versión 1.0
//Fecha 22/sept/2019
//Autor: Javier S. Leyva https://www.educa2.madrid.org/web/jsanzleyva/2


//----------------------- A G R A D E C I M I E N T O S ---------------------------------------------------------------

//Gracias a Eduard M. por su tutorial de cómo usar el sensor de orientación de un móvil android
//con App inventor
//https://appinventor.pevest.com/2014/10/29/sensors-using-the-orientation-sensor/

//Gracias a Eduardo Vega por su vídeo tutorial y su web sobre cómo enviar datos desde el móvil andorid
//a una placa arduino vía BlueTooth
//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html
//-----------------------------------------------------------------------------------------------------


//-------------L I B R E R I A S ----------------------------------------------------------------------
#include <AFMotor.h> //incliumos la librería para manejar los motores  
     
    AF_DCMotor motorIz(1); // crea motorIz para controlar el motor conectado a #1
    AF_DCMotor motorDer(2); // crea motorDer para controlar el motor conectado a #2
  
#include <SoftwareSerial.h> //inlcuimos la librería para usar otros pines como
//puertos serie diferentes de D0 y D1
//definimos los puertos serie para conexión BT entre arduino y el móvil, A0->RX(arduino) y A1->TX(arduino)
SoftwareSerial BT1(A0,A1);
// RX, TX recordar que se conectan cruzados: HC-06_RX->A1 y HC-06_Tx->A0


//------------------------------- V A R I A B L E S -------------------------------------------------------------
//El movil envía a arduino una cadena de texto con los datos de su orientación en este formato: PXXRYY
//P y R son letras que se usan para indicar valor de Pitch y de Roll
//XX es el valor de orientación delante-atrás del móvil (PITCH),
//e YY es su orientación lateral (ROLL), ambos varían en el rango [-90, +90]

//Variables Globales (definidas fuera de las funciones)
char dato_p; //un solo byte (un caracter ASCII) almacena el primer carácter ("P") proveniente del móvil via BT, 
String datos; //variable que almacena cada valor posterior a la "P" que llega del móvil en una cadena de texto tipo XXRYY
int pitch;// variable que almacena la inclinacion del morro
int roll;// variable que almacena la inclinacion lateral
int offset = 0; //corrección veloc,ya que el motor izqu es más lento

void setup() {

  Serial.begin(9600); //iniciamos el monitor serie de arduino
  BT1.begin(9600); //iniciamos el puerto serie para el Blue Tooth
  test_cocherobot(); //probamos los dos motores del coche
} // fin del setup()
void loop(){
 
  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  { 
    dato_p = BT1.read();  //Lee el primer caracter (un byte) entrante via Bluetooth y lo asigna a la variable "dato_p"
    if (dato_p == 'P')   //si ha llegado a arduino desde el movil el primer caracter ("P") de la cadena tipo: PXXRYY 
       {
       BT_recibir_datos();//funcion que toma el resto de la cadena -69R58  y separa los datos en pitch=XX y roll=YY
       }
    Serial.println(pitch); //imprime en el puerto serie el valor numerico de PITCH
    Serial.println(roll); // lo mismo pero para el ROLL
    
//.............................M O V I M I E N T O S del coche robot.....................................................................
//Adelante
//Atrás
//Detenido
//Giro Derecha Adelante
//Giro Izquierda Adelante
//Giro Derecha Atras
//Giro Izquierda Atras
 

 //Adelante: morro móvil inclinado hacia arriba
 if (pitch <-10 && roll >-10 && roll <10 ){
   int veloc = map (pitch, 0,-90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    }
 //Atrás: morro móvil hacia inclinado hacia abajo
 if (pitch >10 && roll >-10 && roll <10 ){
   //int pitch_abs = pitch*(-1); //eliminamos el signo negativo
   int veloc = map (pitch, 0,90, 0,255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(BACKWARD);
   motorDer.run(BACKWARD);
    }
 //Detenido: móvil en posicion horizontal +- 10º
 if (pitch >-10 && pitch <10 && roll >-10 && roll <10 ){
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);  
    } 

 //Giro Derecha Adelante: morro del móvil inclinado hacia adelante y derecha
if (pitch <-10  && roll <-10 ){
   int veloc_r = map (roll, 0,-90, 0,255); // rango veloc 0-255
   int veloc_p = map (pitch, 0,-90, 0,255); // rango veloc 0-255
   
   //hay que evitar que el valor de setSpeed sea < 0 
   int veloc_rueda_lenta = veloc_p - veloc_r;
   if (veloc_rueda_lenta < 0){veloc_rueda_lenta = 0;} // evitamos que la veloc sea negativa
   motorDer.setSpeed(veloc_rueda_lenta);
   motorIz.setSpeed(veloc_p);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
    
 //Giro Izquierda Adelante: morro movil inclinado hacia adelante e izquierda

if (pitch <-10  && roll >10 ){
   int veloc_r = map (roll, 0,90, 0,255);
   int veloc_p = map (pitch, 0,-90, 0,255);
   //hay que evitar que el valor de setSpeed sea < 0 
   int veloc_rueda_lenta = veloc_p - veloc_r;
   if (veloc_rueda_lenta < 0){veloc_rueda_lenta = 0;} // evitamos que la veloc sea negativa
   
   motorIz.setSpeed(veloc_rueda_lenta); //nunca será <0 esta velocidad
   motorDer.setSpeed(veloc_p);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
//Giro Derecha Atras: morro movil inclinado hacia abajo y derecha

if (pitch  >10  && roll <-10 ){
   int veloc = map (roll, 0,-90, 0,150);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(FORWARD);
   motorDer.run(BACKWARD);
    } 

//Giro Izquierda Atras: morro movil inclinado hacia abajo e izquierda

if (pitch  >10  && roll >10 ){
   int veloc = map (roll, 0,90, 0,150);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   motorIz.run(BACKWARD );
   motorDer.run(FORWARD);
    } 
//Fin de movimientos del coche robot ............................................................................

}//end of BT1.available 


 
}//end of loop()

void BT_recibir_datos (){
  delay(30);
  while (BT1.available())
  {
    char c = BT1.read();   //Lee un byte entrante y lo almacena en una variable tipo char
    datos += c;    //Crea una cadena tipo String con los datos (bytes) entrantes
    }// end while
    
  if (datos.length() > 0) //Se verifica que la cadena tipo String tenga un largo mayor a cero
    { 
      //la variable pitch almacena el número entero del PITCH
      //, este valor es el número que hay en la cadena datos antes de la R, (i.e:  -58R25 -> -58)
      pitch = datos.toInt(); 
      //Ahora nos preocupamos de obtenes el valor de ROLL, el número que hay después de R
      int indice_R = datos.indexOf('R');//encuentra la posicion de "R" en la cadena
      String roll_str = datos.substring(indice_R+1); // almacena la subcadena después de "R"
      roll = roll_str.toInt();//variable que almacena el valor roll como número entero
      datos = ""; //vaciamos la cadena, para poder empezar la siguiente lectura de datos provenientes del móvil
      }//end if (length >0)
}// end function BT_envio_datos




void test_cocherobot(){
  //esta función chequea que funcionan correctamente ambos motores
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
  } //end de test_cocherobot()
  
