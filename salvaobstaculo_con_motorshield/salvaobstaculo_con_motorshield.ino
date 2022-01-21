 // ---------------------------------------------------------------------------
// En este ejemplo, el sensor salvaobstaculos pone en marcha al MOTOR1 cuando encuentra un obstáulo 
// a una distancia menor del "límite" establecido medido en cm.
//Esta variable "límite" podemos modificarla manualmente en el código de programa.
//inicialmente  limite = 10 cm
//conexiones del sensor HC-SR04
//trigger A5 en el motorshield
//echo    A4 en el motorshield
//Gnd     a cualquier pin de tierra (GND) en el motorshield
//Vcc     a cualquier pin 5V en el motorshield
//Motor DC se conecta en el motroshield a M1
// ---------------------------------------------------------------------------
 
 
 //#include <NewPing.h>
 #include <AFMotor.h>
     
     #define TRIGGER_PIN A5 // MotorShield pin tied to trigger pin on the ultrasonic sensor.    
     #define ECHO_PIN A4    // MotorShield pin tied to echo pin on the ultrasonic sensor.
     #define MAX_DISTANCE 200 
     
     NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance
     AF_DCMotor motor(1, MOTOR12_1KHZ); // create motor #1, 1KHz pwm

     
     void setup() 
       
        
        {
           pinMode(13, OUTPUT); //PIN DEL LED
           Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
           motor.setSpeed(200);     // set the speed to 200/255
        }
 
     void loop()
       {
           delay(50); 
           unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS)
           Serial.print("Ping: ");
           Serial.print(uS / US_ROUNDTRIP_CM); 
           Serial.println("cm");
           long distancia = uS / US_ROUNDTRIP_CM ; //distancia al obstáculo en cm
           int limite = 10 ;                       // A > distancia (cm) del obstaculo se enciende el LED
            if ( distancia < limite) {
                 digitalWrite ( 13 , HIGH) ; //Enciende el LED
                 motor.run(FORWARD);    //pone en marcha el motor
            } //end if
            else {digitalWrite( 13 , LOW) ;    //Apaga el LED
                  motor.run(RELEASE);      // para el motor, stopped
                  delay (500) ;                  // Para limitar el número de mediciones
            } //end Else
        }
       
