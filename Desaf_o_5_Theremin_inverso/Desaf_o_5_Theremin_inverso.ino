int pinAltavoz = 13; //defino pin digital del altavoz
void setup()
     {
      Serial.begin(9600);
      pinMode (pinAltavoz , OUTPUT);
     }
void loop()
     {
       int sensor = analogRead(A0); //sensor luz 0-1023
       int nota = map (sensor, 500,900, 1000, 50);
       tone ( pinAltavoz, nota);
       Serial.println(sensor);
     }
