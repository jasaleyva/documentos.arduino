 // ---------------------------------------------------------------------------
// En este ejemplo, el sensor salvaobstaculos enciende un LED (pin 13) cuando encuentra un obstáulo 
// a una distancia menor del "límite" establecido medido en cm. Esta variable "límite" podemos modificarla manualmente.
//conexiones del sensor HC-SR04
//trigger 12
//echo    11
//+ motor se conecta al pin 10
//- motor se conecta a una tierra cualquiera (GND)
//Gnd     a cualquier pin de tierra (GND)
//Vcc     a cualquier pin 5V
// ---------------------------------------------------------------------------
 
 
 #include <NewPing.h>

     #define TRIGGER_PIN 12 // Arduino pin tied to trigger pin on the ultrasonic sensor.    
     #define ECHO_PIN 11    // Arduino pin tied to echo pin on the ultrasonic sensor.
     #define MAX_DISTANCE 200 
     
     NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance
 
     void setup() 
       
        
        {
           pinMode(13, OUTPUT); //PIN DEL LED
           pinMode(10, OUTPUT); //PIN DEL + MOTOR
           Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
        }
 
     void loop()
       {
           delay(50); 
           unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS)
           Serial.print("Ping: ");
           Serial.print(uS / US_ROUNDTRIP_CM); 
           Serial.println("cm");
           long distancia = uS / US_ROUNDTRIP_CM ; //distancia al obstáculo en cm
           int limite = 5 ;                       // A > distancia (cm) del obstaculo se enciende el LED
            if ( distancia < limite) {
                 digitalWrite ( 13 , HIGH) ; //Enciende el LED
                 digitalWrite ( 10 , HIGH) ; //Enciende el Motor
                 
            } //end if
            else
                 {digitalWrite( 13 , LOW) ;    //Apaga el LED
                 digitalWrite ( 10 , HIGH) ; //Apaga el Motor
                 delay (500) ;                  // Para limitar el número de mediciones
                 } //end Else
        }
       
