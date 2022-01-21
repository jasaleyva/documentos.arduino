 // ---------------------------------------------------------------------------
// En este ejemplo, el sensor salvaobstaculos CONTROLA DOS MOTORES,
//MOTOR1 = LADO DERECHO
//MOTOR2 = LADO IZQU. 
//Cuando el salvaobstáculos encuentra un obstáculo, gira hacia la IZQU. durante 2 segundos
//Luego continua su marcha normal
//INICIO: avanza 3s + para 0.5 s + retrocede 3s + para 0.5 s 
//        + gira derecha 3s + para 0.5 s + gira izquierda 3 s.
//Inicialmente  limite = 10 cm para los obstáculos
//Conexiones del sensor HC-SR04
   //trigger A5 en el motorshield
   //echo    A4 en el motorshield
   //Gnd     a cualquier pin de tierra (GND) en el motorshield
   //Vcc     a cualquier pin 5V en el motorshield
//Dos Motores DC se conectan en el motroshield a M1 y M2
// ---------------------------------------------------------------------------
 
 
 #include <NewPing.h> //libreria que controla el sensor de ultrasonidos
 #include <AFMotor.h> // librería que controla los motores en el motor shield
     
     #define TRIGGER_PIN A5 // MotorShield pin tied to trigger pin on the ultrasonic sensor.    
     #define ECHO_PIN A4    // MotorShield pin tied to echo pin on the ultrasonic sensor.
     #define MAX_DISTANCE 200 
     
     NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance
     AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1, 1KHz pwm
     AF_DCMotor motor2(2, MOTOR12_1KHZ); // create motor #1, 1KHz pwm
     boolean  sensorOn = false;
     int  velocidad  =  100;//  veloc de los motores definidas en setSpeed, valor entre 0-255  
     
     void setup() 
        {
           pinMode(13, OUTPUT); //PIN DEL LED
           Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
           motor1.setSpeed(velocidad);    // set the speed to 200/255
        }
 
     void loop()
       {
  
        if ( sensorOn) {          
           delay(50); 
           unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS)
           long distancia = uS / US_ROUNDTRIP_CM ; //distancia al obstáculo en cm
           int limite = 10 ;                       // A > distancia (cm) del obstaculo se enciende el LED
            if ( distancia < limite) {
                 Retroceso() ;
                 delay(1000);
                 giroDerecha() ;
                 delay(1000);
            } //end if distancia < limite
            else {Avance();//avanza normalmente
                  delay (500) ;                  // Para limitar el número de mediciones
            }
       } //end if(sensorOn)
       else {  testInicio(); //avanza + retroceso + giro 
       }
       }//end loop()

       
        void testInicio() {
          Avance();
          delay(2000);
          Paro();
          delay(2000);
          Retroceso();
          delay(2000);
          Paro();
          delay(2000);
          giroIzquierda();
          delay(2000);
          Paro();
          delay(2000);
          sensorOn = true; //variable que inicia el sensor de sonar        
          }

        void Avance()
        { motor1.setSpeed(velocidad);     // set the speed to 200/255
          motor2.setSpeed(velocidad);     // set the speed to 200/255
          
          motor1.run(FORWARD);     //MOTOR1 avanza
          motor2.run(FORWARD);      //MOTOR2 avanza
          }

        void Retroceso()
        { motor1.setSpeed(velocidad);     // set the speed to 200/255
          motor2.setSpeed(velocidad);     // set the speed to 200/255

          motor1.run(BACKWARD);    //MOTOR1 retrocede
          motor2.run(BACKWARD);     //MOTOR2 retrocede
          }
        void Paro()
        { 
          motor1.run(RELEASE) ;    //MOTOR1 para
          motor2.run(RELEASE);     //MOTOR2 para
          }

        void giroIzquierda()
        { motor1.setSpeed(velocidad); // set the speed to 200/255
          motor2.setSpeed(velocidad/2); // set the speed to 200/255

          motor1.run(FORWARD) ; // avanza el motor1 que es el DERECHO
          motor2.run(BACKWARD); //retrocede el motor2   que es el IZQUIERDO
        }
        void giroDerecha()
        { motor1.setSpeed(velocidad/2); // set the speed to 200/255
          motor2.setSpeed(velocidad); // set the speed to 200/255

          motor1.run(BACKWARD) ; // avanza el motor1 que es el DERECHO
          motor2.run(FORWARD); //retrocede el motor2   que es el IZQUIERDO
        }

        
       
