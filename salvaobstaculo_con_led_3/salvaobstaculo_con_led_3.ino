 // ---------------------------------------------------------------------------
// MODIFICAMOS EL PARPADEO DE UN LED SEGÚN 
// LA DISTANCIA DEL SENSOR HC-SR04 A UN OBSTÁCULO.
// si DISTANCIA es 0 cm SE ENCIENDE el LED.
//
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
    int led =8;
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
           x = uS / US_ROUNDTRIP_CM; 
           Serial.print(x); 
           Serial.println("cm");
            if (x==0){
              digitalWrite ( led , HIGH) ; 
              }
            else if (x<14){
              digitalWrite ( led , HIGH) ; 
              delay(50);
              digitalWrite( led , LOW) ;
              delay(50);
            }//fin del if
            else {
            digitalWrite ( led , HIGH) ; 
            delay(200);
            digitalWrite( led , LOW) ;
            delay(200);
            }//fin del else
         
           }//fin del loop()
           


           
       
