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
//trigger 12
//echo    11
//Gnd     tierra (GND)
//Vcc     5V
//LED     8
// ---------
 
#include <NewPing.h> //libreria que maneja el sensor HC-SR04
#define TRIGGER_PIN 12 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 11    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200
int x;//distancia hasta el obstaculo
int intentos = 0;//num de veces que pone 0 cm
int led = 8;
// NewPing configura los pines y la distancia max detectada
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup()
{
  Serial.begin(115200); // Open serial monitor at 115200 baud
  pinMode (led, OUTPUT);
}
 
void loop()
{
  delay(50);
  // Send ping, get ping time in microseconds (uS)
  unsigned int uS = sonar.ping();
  Serial.print("Ping: ");
  x = uS / US_ROUNDTRIP_CM; // distancia en cm
  Serial.print(x);
  Serial.println("cm");
 //Solucion  do{} ... while()
 //para cuando el pin ECHO no recibe rebote de señal
 //y el timer no se detiene y aparecen 0,0,0,... cm constantemente.
    do
    {
      delay(100);
      pinMode(ECHO_PIN, OUTPUT);
      digitalWrite(ECHO_PIN, LOW);
      delay(100);
      pinMode(ECHO_PIN, INPUT);
    }   while (x == 0 && ++intentos < 3);
 
 if (x < 14) { //umbral = 14 cm, cambia el parpadeo
    digitalWrite ( led , HIGH) ;
    delay(50);
    digitalWrite( led , LOW) ;
    delay(50);
  }//fin del if
  else {
    digitalWrite ( led , HIGH) ;
    delay(250);
    digitalWrite( led , LOW) ;
    delay(250);
  }//fin del else
}//fin del loop()
 
