void setup() {
  // ponemos el pin 8 como SALIDA para usarlo con un LED
  pinMode(8, OUTPUT);
 // inicialización puerto serie a 9600 bps
  Serial.begin(9600);
}
 
void loop() {
  // creamos una variable para almacenar el valor del sensor
  int x ;
  // analogRead() lee en el pin A0 el voltaje y lo convierte en un valor entre 0-1023= 0-1023
  x = analogRead(A0);
  // enciende el LED
  digitalWrite(8, HIGH);
  delay(x); //retardo de x milisegundos
  // apaga el LED
  digitalWrite(8, LOW);
  delay(x); //retardo de x milisegundos
  // mostrar el valor de X en el Monitor Serie
  Serial.println(x);
}
