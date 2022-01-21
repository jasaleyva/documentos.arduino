int led13 = 13;
String scadena = "";
char character;

void setup() {

  pinMode (led13, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    while (Serial.available()){
    delay(5);
      character = Serial.read();
      scadena.concat(character);
    }
  }

 if (scadena == "a"){
  Serial.println("LED encendido");
  digitalWrite(led13, HIGH);
  }
 if (scadena == "b"){
  Serial.println("LED apagado");
  digitalWrite(led13, LOW);
  }
  scadena ="";
}

