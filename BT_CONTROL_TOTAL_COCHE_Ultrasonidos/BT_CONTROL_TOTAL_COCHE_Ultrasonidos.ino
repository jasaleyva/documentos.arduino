//Este programa añade un sensor de ultrasonidos HC-SR04 al coche robot
//Cuando se detecte un obstáculo cerca delante del coche
//se iniciará la secuencia automática para evitarlo
//y se encenderá una LUZ roja

//-------------------------------------------
//Bluetooth
#include <SoftwareSerial.h> //biblioteca de comunicacion en serie
 //creamos la instancia BT1 para manejar el modulo esclavo bluetooth
SoftwareSerial BT1(A0,A1);

// El módulo bluetooth se conecta así
// Bluetooth_RX  -> A1_arduino
// Bluetooth_TX  -> A0_arduino
// Bluetooth_GND -> GND_arduino
// Bluetooth_VCC -> 5V_arduino

//Variables de control y/o lectura bluetooth
char valor; //un solo byte, un caracter ASCII

//----------------------------------------------
#include <AFMotor.h>
AF_DCMotor motorDer(2);
//asegurate que tienes conectado el motor derecho al puerto 1
AF_DCMotor motorIz(1);

//--------------------------------------------------------------------
//UN SENSOR ULTRASÓNICO HC-SR04 MIDE LA DISTANCIA A OBSTÁCULOS.
//conexiones del sensor HC-SR04
//trigger A2
//echo    A3
//Gnd     tierra (GND)
//Vcc     5V

//Definicion de constantes y variables usadas por el sensor ultrasonidos
const int echoPin = A3; // pin echo que recoge el rebote del pulso ultrasonico
const int trigPin = A2; // pin disparo del sensor ultrasonico
const int pinLED =  A5; // el led rojo se conecta al pin analógico A5
long tiempo; //µs que tarda el echo en ser detectado por sensor HC-SR04
long distancia; //cm hasta el obstáculo que detecta el sensor

// --------------------------------------------------------------------------------




void setup() {
  Serial.begin(9600);//iniciamos conexión motor serie
  BT1.begin(9600);   //iniciamos conexión bluetooth

//Iniciamos los pines del sensor ultrasonidos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
//iniciamos el pin del LED como salida y lo probamos
pinMode(pinLED, OUTPUT);
analogWrite(pinLED, 255);
delay(1000);
analogWrite(pinLED, 0);
 
//Probamos que las ruedas funcionan
//Definimos la velocidad de giro de ambas ruedas
  motorDer.setSpeed(110);     // veloc entre 0-255
  motorIz.setSpeed(110);     // veloc entre 0-255
//ADELANTE
  motorDer.run(FORWARD);      // gira marcha adelante
  motorIz.run(FORWARD);      // gira marcha adelante
  delay(2000);
//ATRÁS
  motorDer.run(BACKWARD);      // gira marcha adelante
  motorIz.run(BACKWARD);      // gira marcha adelante
  delay(1000);
//DERECHA
  motorDer.run(RELEASE);      // gira marcha adelante
  motorIz.run(FORWARD);      // gira marcha adelante
  delay(1000);
//IZQUIERDA
  motorIz.run(RELEASE);      // gira marcha adelante
  motorDer.run(FORWARD);      // gira marcha adelante
  delay(1000);  
//STOP
  motorDer.run(RELEASE);      // gira marcha adelante
  motorIz.run(RELEASE);      // gira marcha adelante
  delay(1000);
 }// fin del setup()


void loop() {
//Primero, medimos la distancia al obstáculo
    digitalWrite(trigPin, LOW);   // Resetea el disparador ulstrasónico
    delayMicroseconds(2);   //damos un tiempo de espera antes de lanzar un pulso  
    digitalWrite(trigPin, HIGH);  // Manda EL PULSO
    delayMicroseconds(10);    //el pulso dura 10 microsegundos
    digitalWrite(trigPin, LOW); // Deshabilita la transimison de otros pulsos
    //el pin echo detecta el pulso rebotado
    tiempo = pulseIn(echoPin, HIGH) ; //mide el tiempo de ida y vuelta del pulso en µs
    distancia = tiempo / 58.28  ; // Calcula la distancia al obstáculo en cm.
    //imprimimos la distancia a obstáculo en el monitor serie
    Serial.println(String(distancia) + " cm.");  
    delay(100); //retardo para separar medidas consecutivas de distancia.
 
    
//Segundo, si hay un obstáculo cerca hay que 
// encender el Led rojo y evitar choque
   if (distancia < 20 && distancia >1) {
      analogWrite(pinLED, 255);//LED rojo encendido
    //se inicia maniobra para evitar el obstáculo
      motorDer.run(BACKWARD);
      motorIz.run(BACKWARD);
      delay(500);
      motorDer.run(BACKWARD); 
      motorIz.run(FORWARD);
      delay(600); //el tiempo de giro se puede modificar a voluntad
      motorDer.run(RELEASE);
      motorIz.run(RELEASE);
            
      }
   else {analogWrite(pinLED, 0);} //LED rojo apagado 
    
//Tercero, leemos el dato entrante via Bluetooth  
  if (BT1.available())  //Si el puerto serie (Bluetooth) está disponible...
  {
    valor = BT1.read();
    Serial.println(valor);  //imprime el valor en el monitor serie  
    
//Cuarto, decidimos qué tiene que hacer el coche
//según el valor recibido por bluetooth  
   
//Si el dato entrante es "0" se debe PARAR
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
