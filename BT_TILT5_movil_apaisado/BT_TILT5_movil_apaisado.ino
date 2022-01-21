//Movil en apaisado... ROLL y PICTH se intercambian así...
//Adelante-> ROLL > 10º
//Atrás  --> ROLL <-10º

//Giro Derecha Adelante --> Pitch <-20º
//Giro Izquierda Adelante --> Pitch >20º


//PROYECTO ESCOLAR
//Título: Coche_Robot_controlado_por_sensor_orientacion_del_movil
//Versión 3.0
//Fecha 03/nov/2019
//Autor: Javier S. Leyva https://www.educa2.madrid.org/web/jsanzleyva/2


//----------------------- A G R A D E C I M I E N T O S ---------------------------------------------------------------

//Gracias a Eduard M. por su tutorial de cómo usar el sensor de orientación de un móvil android
//con App inventor
//https://appinventor.pevest.com/2014/10/29/sensors-using-the-orientation-sensor/

//Gracias a Eduardo Vega por su vídeo tutorial y su web sobre cómo enviar datos desde el móvil android
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
int MAX = 75 ; //máxima veloc de una rueda, nunca superior a 255
int offset = MAX*0.2; //corrección veloc que se resta a la rueda derecha ya que el motor izqu es más lento

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

//ROLL --> inclinacion del movil apaisado adelante/atrás, rango [90,-90]
//PITCH -->inclinación del móvil apaisado derecha/izqu.,  rango [-90,+90]

//Detenido --> ROLL +-10º, Pitch +-20º
//Adelante-> ROLL >10º, , pitch +-20º
//Atrás --> ROLL < -10º, pitch +-20º
//Giro Derecha Adelante --> Pitch <-45º, roll>20
//Giro Izquierda Adelante --> Pitch >45º, roll>20
//Giro Derecha atrás--> Pitch <-45, roll <-20
//Giro Izqu Atrás-----> Pitch  >45, roll <-20
 

 //Adelante: morro móvil inclinado hacia arriba >10º
 if (roll >10 && pitch >-20 && pitch <20 ){
   int veloc = map (roll, 10, 90, 15,MAX);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc-offset);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    }
 //Atrás: morro móvil hacia inclinado hacia abajo >10º
 if (roll <-10 && pitch >-20 && pitch <20 ){
   int veloc = map (roll, -10,-90, 15, MAX);
   motorIz.setSpeed(veloc); 
   motorDer.setSpeed(veloc-offset);
   motorIz.run(BACKWARD);
   motorDer.run(BACKWARD);
    }
 //Detenido: móvil en posicion horizontal +- 10º
 if (pitch >-20 && pitch <20 && roll >-10 && roll <10 ){
    motorIz.run(RELEASE);
    motorDer.run(RELEASE);  
    } 

//Giro Derecha Adelante: móvil inclinado hacia la derecha >20º
if (pitch <-45 && roll >20 ){;
  
   int veloc_p = map (pitch, -45,-90, 0,MAX); // rango veloc 0-255  
   int veloc_rueda_lenta = (MAX-veloc_p);
   int veloc_rueda_rapida = MAX;
   motorDer.setSpeed(veloc_rueda_lenta );
   motorIz.setSpeed(veloc_rueda_rapida);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 
//Giro Izq Adelante: móvil inclinado hacia izquierda >20º
if (pitch >45 && roll >20 ){;
   int veloc_p = map (pitch, 45,90, 0,MAX); // rango veloc 0-255  
   int veloc_rueda_lenta = (MAX-veloc_p);
   int veloc_rueda_rapida = MAX;
   motorIz.setSpeed(veloc_rueda_lenta );
   motorDer.setSpeed(veloc_rueda_rapida);
   motorIz.run(FORWARD);
   motorDer.run(FORWARD);
    } 

//Giro Der  Atrás: móvil inclinado hacia la der y hacia atrás
if (pitch <-45 && roll <-20){;
  
   int veloc_p = map (pitch, -45,-90, 0,MAX); // rango veloc 0-255  
   motorIz.setSpeed(veloc_p );
   motorDer.setSpeed(veloc_p);
   motorIz.run(FORWARD);
   motorDer.run(BACKWARD);
    } 
//Giro Iz  Atrás: móvil inclinado hacia la Izq  y hacia atrás
if (pitch >45 && roll <-20 ){;
  
   int veloc_p = map (pitch, 45,90, 0,MAX); // rango veloc 0-255  
   motorIz.setSpeed(veloc_p );
   motorDer.setSpeed(veloc_p);
   motorDer.run(FORWARD);
   motorIz.run(BACKWARD);
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
  delay(500);
  
  Serial.print("tock BACKWARD ");
  motorIz.run(BACKWARD);     // motor IZQ gira hacia atrás
  motorDer.run(BACKWARD);     // motor DER gira hacia atrás
  delay(500);
  
  Serial.print("tack GIRO DERECHA ");
  motorIz.run(FORWARD); 
  motorDer.run(BACKWARD); 
  delay(500);
  
  Serial.println("tuck RELEASE");
  motorIz.run(RELEASE);      // motor IZQ PARA
  motorDer.run(RELEASE);      // motor DER PARA
  delay(1000);
  Serial.print("tack GIRO IZQUIERDA ");
  motorDer.run(FORWARD); 
  motorIz.run(BACKWARD); 
  delay(500);
  
  Serial.println("tuck RELEASE");
  motorIz.run(RELEASE);      // motor IZQ PARA
  motorDer.run(RELEASE);      // motor DER PARA
  delay(1000);
  } //end de test_cocherobot()
  
