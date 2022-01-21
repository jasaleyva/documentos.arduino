/* 

    Ultra Sonic range measurement module HC-SR04

*/

const int trigPin = 12; // constant
const int echoPin = 11;
int led = 13;            // variable

void setup() 
{	Serial.begin (9600); // Initializes serial communication
  	pinMode(trigPin, OUTPUT);
  	pinMode(echoPin, INPUT);
  	pinMode(led, OUTPUT);
}

void loop()
{	long duration, range ;
  
	  digitalWrite(trigPin, LOW);  	// Resets trigger
    delayMicroseconds(2); 		
    digitalWrite(trigPin, HIGH);	// Enables transmission pulse
    delayMicroseconds(10); 		
    digitalWrite(trigPin, LOW);	// Disables transmission pulse and waits for echo

    duration = pulseIn(echoPin, HIGH) ;
 	  range = duration / 58.28  ; // Calculates the range in cm.
    delay(300);
		
    Serial.println(String(range) + " cm."); // Tools-->Serial Monitor to see the range
	 
    // Let's set the blinking rate
    if (range<5){
    digitalWrite ( led , HIGH) ; 
    delay(20);
    digitalWrite( led , LOW) ;
    delay(20);
     } else if (range<10){
            digitalWrite ( led , HIGH) ; 
            delay(50);
            digitalWrite( led , LOW) ;
            delay(50);
            } else if (range<20){
                    digitalWrite ( led , HIGH) ; 
                    delay(100);
                    digitalWrite( led , LOW) ;
                    delay(100);
                    } else if (range<30){
                            digitalWrite ( led , HIGH) ; 
                            delay(400);
                            digitalWrite( led , LOW) ;
                            delay(400);
                            } else if (range<40){
                                    digitalWrite ( led , HIGH) ; 
                                    delay(600);
                                    digitalWrite( led , LOW) ;
                                    delay(600);
                                    } else 
                                        digitalWrite ( led , HIGH) ; 
                                        
 }
 

