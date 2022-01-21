/* 
  LED controlado por sensor ultrasonico HC-SR04 
  Este sensor mide la distancia a un obstaculo en cm

*/

int trigPin = 12; // pin de disparo del pulso ultrasonico
const int echoPin = 11; //pin de medida del tiempo de rebote del pulso
int led = 13; //pin LED

void setup() 
{	Serial.begin (9600); // Se inicia la comunicacion con el monitor serie
  	pinMode(trigPin, OUTPUT);
  	pinMode(echoPin, INPUT);
  	pinMode(led, OUTPUT);
}

void loop()
{	long duracion, distancia ;
  
	  digitalWrite(trigPin, LOW);  	// apaga el disarador del pulso ultrasonico
    delayMicroseconds(2); 		
    digitalWrite(trigPin, HIGH);	// Inicia el pulso ultrasonico
    delayMicroseconds(10); 		//el pulso dura 10 microsegundos
    digitalWrite(trigPin, LOW);	// apaga el pulso y espera el echo

    duracion = pulseIn(echoPin, HIGH) ;
 	  distancia = duracion / 58.28  ; // Si hay rebote del pulso calcula la distancia en cm.
    delay(300);
		
    Serial.println(String(distancia) + " cm."); // Herramientas-->Serial Monitor para ver la distancia
	 
    //Según la distancia medida en cm hasta el obstaculo...
    //Determinamos diferentes frecuencias de parpadeo del LED
    
    if (distancia<5){
    digitalWrite ( led , HIGH) ; 
    delay(20);
    digitalWrite( led , LOW) ;
    delay(20);
     } else if (distancia<10){
            digitalWrite ( led , HIGH) ; 
            delay(50);
            digitalWrite( led , LOW) ;
            delay(50);
            } else if (distancia<20){
                    digitalWrite ( led , HIGH) ; 
                    delay(100);
                    digitalWrite( led , LOW) ;
                    delay(100);
                    } else if (distancia<30){
                            digitalWrite ( led , HIGH) ; 
                            delay(400);
                            digitalWrite( led , LOW) ;
                            delay(400);
                            } else if (distancia<40){
                                    digitalWrite ( led , HIGH) ; 
                                    delay(600);
                                    digitalWrite( led , LOW) ;
                                    delay(600);
                                    } else {
                                        digitalWrite ( led , HIGH) ; 
                                        }
 } //fin del loop()
 

