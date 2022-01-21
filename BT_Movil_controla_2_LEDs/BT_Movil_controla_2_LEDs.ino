int Do#sos = 23;
int led_1 = 12;
int led_2 = 13;
char valor;
  
void setup() {
pinMode(led_1, OUTPUT);
pinMode(led_2, OUTPUT);   
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available()){
  valor = Serial.read();
  if (valor == 'A'){digitalWrite(led_1, HIGH);}
  if (valor == 'B'){digitalWrite(led_1, LOW);}
  if (valor == 'C'){digitalWrite(led_2, HIGH);}
  if (valor == 'D'){digitalWrite(led_2, LOW);}
  }
}
