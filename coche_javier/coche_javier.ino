// ---------------------------------------------------------------------------
// ROBOT-COCHE
// DOS MOTORES DC MUEVEN AMBAS RUEDAS TRASERAS
// UN SENSOR ULTRASÓNICO MIDE LA DISTANCIA A OBSTÁCULOS.
// SI EL COCHE ESTÁ CERCA DE UN OBSTÁCULO DEBE EVITARLO
// A VECES EL SENSOR SE QUEDA COLGADO MIDIENDO DISTANCIAS 0, 0, 0, 0 CM, REITERADAMENTE
// LO ARREGLAMOS CON INSTRUCCIONES PARA EL DESBLOQUEO METIDAS EN UN BUCLE WHILE
// SOLUCION AL 0,0,0,0,0,0,...
//When I detect the sensor is stuck, I simply switch echo pin to OUTPUT,
//put it into LOW state, and after a while re-set it to INPUT, then cycle again.

//conexiones del sensor HC-SR04
//trigger A1
//echo    A0
//Gnd     tierra (GND)
//Vcc     5V
// ---------

//Definicion de constantes y variables usadas
const int trigPin = A1; // pin disparo del sensor ultrasonico
const int echoPin = A0; // pin echo que recoge el rebote del pulso ultrasonico 
int intentos = 0;//num de veces que el sensor ultrasónico se cuelga con 0

#include <AFMotor.h>
AF_DCMotor motorD(2); // create motor derecha
AF_DCMotor motorI(4); // create motor izquierda 
 
void setup()
{
  Serial.begin(9600); // Open serial monitor at 115200 baud
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode (led, OUTPUT);
  motorD.setSpeed(90);     // 90, set the speed from 0 to 255 90
  motorI.setSpeed(120);     // 120,set the speed form 0 to 255 120
  
}
 
void loop()
{
 delay(50);
 //dos variables vamos a definir para el trabajo del sensor ulrasónico
 //duration = tiempo de duración del pulso ida y vuelta
 //y range = distancia en cm al obstáculo
 long duration, range; 
 digitalWrite(trigPin, LOW);   // Resetea el disparador ulstrasónico
 delayMicroseconds(2);   //damos un tiempo de espera antes de lanzar un pulso  
 digitalWrite(trigPin, HIGH);  // Manda EL PULSO
 delayMicroseconds(10);    //el pulso dura 10 microsegundos
 digitalWrite(trigPin, LOW); // Deshabilita la transimison de otros pulsos
 //y espera a que el pin echo recoja el pulso rebotado
 duration = pulseIn(echoPin, HIGH) ; //mide el tiempo de ida y vuelta del pulso en µs
 range = duration / 58.28  ; // Calcula la distancia al obstáculo en cm.
 delay(300);
//imprimimos la distancia al obstáculo en el monitor serie
 Serial.println(String(range) + " cm."); // Tools-->Serial Monitor to see the range
 
 /*
 //SI el sensor se cuelga enviando continuos 0 cm, lo solucionamos en el bucle while      
 while (range == 0 && ++intentos < 3); {
      delay(50);//100
      pinMode(echoPin, OUTPUT);
      digitalWrite(echoPin, LOW);
      delay(50);//100
      pinMode(echoPin, INPUT);
      motorD.run(RELEASE);
      motorI.run(RELEASE);
    }
*/ 
 if (range < 40 ) { // si el obstáculo está a menos de 25 cm 
    //&& range!=0 incluirlo dentro del if sólo si el sensor se cuelga con 0,0,0,...
    motorD.run(RELEASE);
    motorI.run(RELEASE);
    delay(1000);
    motorD.setSpeed(120);     
    motorI.setSpeed(120); 
    motorD.run(BACKWARD);
    motorI.run(BACKWARD);
    delay (500);
    //giro del coche entre 45-90º aproximadamente
    motorD.setSpeed(90);     
    motorI.setSpeed(90); 
    motorD.run(BACKWARD);
    motorI.run(RELEASE);
    delay (500);
    motorD.run(RELEASE);
    motorI.run(RELEASE);
    delay(500);    
  }//fin del if
  else { // si no hay ningún obstáculo
    motorD.setSpeed(90);  // 90, set the speed from 0 to 255 90
    motorI.setSpeed(120); // este motorI nec mayor veloc para que el coche vaya recto.
    motorD.run(FORWARD);
    motorI.run(FORWARD);
  }//fin del else
}//fin del loop()
 
