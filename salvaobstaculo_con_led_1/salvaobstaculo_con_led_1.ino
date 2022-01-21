 // ---------------------------------------------------------------------------
// En este ejemplo, el sensor salvaobstaculos enciende un LED (pin 13) cuando encuentra un obstáulo 
// a una distancia menor del "límite" establecido medido en cm. Esta variable "límite" podemos modificarla manualmente.
//conexiones del sensor HC-SR04
//trigger 12
//echo    11
//Gnd     tierra (GND)
//Vcc     5V
// ---------------------------------------------------------------------------
 
 
 #include <NewPing.h> //incluimos la librería para manejar más fácilmente el sensor

     #define TRIGGER_PIN 12 // Pin 12 de la placa conectado al TRIGGER (disparador) del sensor ultrasónico.    
     #define ECHO_PIN 11    // Pin 11 de la placa conectado al ECHO (eco) del sensor.
     #define MAX_DISTANCE 200 //máxima distancia medida por el sensor 200 cm = 2 m
     
     NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance
 
     void setup() 
       
        
        {
           pinMode(13, OUTPUT);
           Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
        }
 
     void loop()
       {
           delay(50); 
           unsigned int uS = sonar.ping(); // Envia un ping, y mide el tiempo hasta su regreso en microsegundos (uS)
           long distancia = uS / US_ROUNDTRIP_CM ; //distancia al obstáculo en cm
           
           Serial.print("Ping: "); //Vemos la distancia en el Monitor Serie (Ctrl+Mayús+M)
           Serial.print(distancia); 
           Serial.println("cm");
           
           
           int limite = 20 ;     // Si el obstáculo está a MENOR distancia del límite establecido en cm se enciende el LED
            if ( distancia < limite)
                 digitalWrite ( 13 , HIGH) ;
            else
                 digitalWrite( 13 , LOW) ;
            delay (200) ;                  // Para limitar el número de mediciones
        }
       
