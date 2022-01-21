// ---------------------------------------------------------------------------
// MODIFICAMOS EL PARPADEO DE UN LED SEGÚN
// LA DISTANCIA DEL SENSOR HC-SR04 A UN OBSTÁCULO.
// UMBRAL a 14 cm
// SI no regresa la señal al pin ECHO (lack of timeout)
// muestra 0,0,0... cm reiteradamente
// SOLUCION AL 0,0,0,0,0,0,...
/*When I detect the sensor is stuck, I simply switch echo pin to OUTPUT,
put it into LOW state, and after a while re-set it to INPUT, then cycle
again. */
//conexiones del sensor HC-SR04
//trigger A1
//echo    A0
//Gnd     tierra (GND)
//Vcc     5V
//LED     8
// ---------


#include <NewPing.h> //libreria que maneja el sensor HC-SR04
#define TRIGGER_PIN A1 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN A0    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200
int x;//distancia hasta el obstaculo
int intentos = 0;//num de veces que pone 0 cm
int led = 8;
// NewPing configura los pines y la distancia max detectada
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#include <AFMotor.h>
AF_DCMotor motorD(1); // create motor derecha
AF_DCMotor motorI(4); // create motor izquierda 
 
void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud
  //pinMode (led, OUTPUT);
  motorD.setSpeed(90);     // set the speed from 0 to 255
  motorI.setSpeed(120);     // set the speed form 0 to 255
}
 
void loop()
{
  delay(50);
  // Envia el ping, recibe ping time en microsegundos (uS)
  unsigned int uS = sonar.ping();
  Serial.print("Ping: ");
  x = uS / US_ROUNDTRIP_CM; // distancia en cm
  Serial.print(x);
  Serial.println("cm");
 //Solucion  do{} ... while()
 //para cuando el pin ECHO no recibe rebote de señal
 //y el timer no se detiene y aparecen 0,0,0,... cm constantemente.
    
 while (x == 0 && ++intentos < 3); {
      delay(100);
      pinMode(ECHO_PIN, OUTPUT);
      digitalWrite(ECHO_PIN, LOW);
      delay(100);
      pinMode(ECHO_PIN, INPUT);
      motorD.run(RELEASE);
      motorI.run(RELEASE);
    }
 
 if (x < 25 && x!=0) { //x = distancia umbral obstaculo 
   /* digitalWrite ( led , HIGH) ;
    delay(50);
    digitalWrite( led , LOW) ;
    delay(50);*/
    motorD.run(RELEASE);
    motorI.run(RELEASE);
    delay(1000);
    motorD.run(BACKWARD);
    motorI.run(BACKWARD);
    delay (500);
    motorD.run(BACKWARD);
    motorI.run(RELEASE);
    delay (500);
    motorD.run(RELEASE);
    motorI.run(RELEASE);
    delay(500);    
  }//fin del if
  else {
   /* digitalWrite ( led , HIGH) ;
    delay(250);
    digitalWrite( led , LOW) ;
    delay(250);*/
    motorD.run(FORWARD);
    motorI.run(FORWARD);
  }//fin del else
}//fin del loop()
 
