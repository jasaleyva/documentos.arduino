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
  
#include <SoftwareSerial.h> //inlcuimos la librería para usar otros pines  diferentes de D0 y D1 como
//puertos serie
//definimos los puertos serie para conexión BT entre arduino y el móvil, A0->RX(arduino) y A1->TX(arduino)
SoftwareSerial BT1(A0,A1);
// RX, TX recordar que se conectan cruzados: HC-06_RX->A1 y HC-06_Tx->A0


//------------------------------- V A R I A B L E S -------------------------------------------------------------
//El movil envía a arduino una cadena de texto con los datos de su orientación en este formato: PXXRYY
//P y R son letras que se usan para indicar valor de Pitch y de Roll
//XX es el valor de orientación delante-atrás del móvil (PITCH),
//e YY es su orientación lateral (ROLL), ambos varían en el rango [-90, +90]

//Variables Globales (definidas fuera de las funciones)
char dato_d; //un solo byte (un caracter ASCII) almacena el primer carácter ("D") proveniente del móvil via BT, 
String datos; //variable que almacena cada valor posterior a la "D" que llega del móvil en una cadena de texto tipo XXMYY
//int pitch;// variable que almacena la inclinacion del morro
//int roll;// variable que almacena la inclinacion lateral
int   direccion = 0; // variable que almacena la dirección del coche
int   magnitud = 0;//variable que almacena la intensidad del movimiento del coche.
float seno_dir = 0;
float coseno_dir = 0;
int   veloc = 0;
float reduccion =0;
int   offset = 0; //corrección veloc,ya que el motor izqu es más lento

void setup() {

  Serial.begin(9600); //iniciamos el monitor serie de arduino
  BT1.begin(9600); //iniciamos el puerto serie para el Blue Tooth
  test_cocherobot(); //probamos los dos motores del coche
} // fin del setup()
void loop(){
 
  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible
  { 
    dato_d = BT1.read();  //Lee el primer caracter (un byte) entrante via Bluetooth y lo asigna a la variable "dato_d"
    if (dato_d == 'D')   //si ha llegado a arduino desde el movil el primer caracter ("D") de la cadena tipo: DXXMYY 
       {
       BT_recibir_datos();//funcion que toma el resto de la cadena -69M58  y separa los datos en direccion=XX y magnitud=YY
       }
    Serial.println("direccion"+direccion); //imprime en el puerto serie el valor numerico de la dirección
    Serial.println("magnitud" +magnitud); // lo mismo pero para la magnitud del movimiento
   // Serial.println("velocidad");
    //Serial.println(veloc);
    //Serial.println("reduccion");
    //Serial.println(reduccion);
    
//.............................M O V I M I E N T O S del coche robot.....................................................................
//Adelante
//Atrás
//Detenido
//Giro Derecha Adelante
//Giro Izquierda Adelante
//Giro Derecha Atras
//Giro Izquierda Atras


//SIGNIFICADO DEL LA DIRECCION (ÁNGULO ENTRE -180 0 +180º)
//  0º este (3 h)
//  90º norte (12 h)
//  180º=-180º oeste (9 h)
// -90º SUR (6 h)

seno_dir   = sin(direccion);
coseno_dir = cos(direccion);
//Serial.println("seno_dir");
//Serial.println(seno_dir);
//Serial.println("coseno_dir");
//Serial.println(coseno_dir);

//---------------------------------------------------------
//  Si sen_dir es + => ADELANTE
//  Si sen_dir es - => ATRAS
//  Si cos_dir es + => GIRO DER
//  Si cos_dir es - => GIRO IZQU

 //ADELANTE
 //Cuadrante I y II (0 a 90º y 90º a 180º)
 if (seno_dir > 0){
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
   veloc = map (magnitud, 0,100, 0,255);
   reduccion = map (coseno_dir, 0,1, 0, 255);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc);
   /*
   if (coseno_dir > 0){
    //ADELANTE y DER
    motorIz.setSpeed(veloc); 
    motorDer.setSpeed(veloc-reduccion);
   
    }
   if (coseno_dir < 0){
     //ADELANTE e IZQ
     motorIz.setSpeed(veloc-reduccion); 
     motorDer.setSpeed(veloc);
    }
    */
  }
 //ATRÁS
 //Cuadrante III y IV (0 a -90º y -90º a -180º)
 if (seno_dir < 0){
   motorIz.run(BACKWARD);
   motorDer.run(BACKWARD);
   veloc = map (magnitud, 0,100, 0,255);
   reduccion = map (coseno_dir, 0,1, 0, 255);
   
   if (coseno_dir > 0){
    //ATRAS y DER
    motorIz.setSpeed(veloc-reduccion); 
    motorDer.setSpeed(veloc);
    }
   if (coseno_dir < 0){
     //ATRAS e IZQ
     motorIz.setSpeed(veloc); 
     motorDer.setSpeed(veloc-reduccion);
    }
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
      //la variable direccion  almacena el ángulo (número entero)
      //, este valor es el número que hay en la cadena datos antes de la M, (i.e:  -58M25 -> -58)
      direccion = datos.toInt(); 
      
      //Ahora nos preocupamos de obtener el valor de magnitud, el número que hay después de M
      int indice_M = datos.indexOf('M');//encuentra la posicion de "M" en la cadena
      String magnitud_str = datos.substring(indice_M+1); // almacena la subcadena después de "M"
      magnitud = magnitud_str.toInt();//variable que almacena la intensidad de la inclinación
      
      datos = ""; //vaciamos la cadena, para poder empezar la siguiente lectura de datos provenientes del móvil
      }//end if (length >0)
}// end function BT_envio_datos




void test_cocherobot(){
  //esta función chequea que funcionan correctamente ambos motores
  Serial.println("Motor test!");
      
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
  
