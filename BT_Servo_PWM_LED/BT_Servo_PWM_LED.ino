//https://www.youtube.com/watch?v=OO7vKKuJ9a0
//http://arduparatodos.blogspot.com/2017/06/modulo-bluetooth-hc-06-con-arduino-y.html



#include <Servo.h>
Servo servomotor;

int led_1 = 5;  //Pin PWM donde va conectado el LED

//Variables de control y/o lectura
char valor; //un solo byte, un caracter ASCII
String estado;// texto

void setup() {

  servomotor.attach(6); //Pin PWM 6 del Arduino para el servo
  servomotor.write(90);  //Inicia el servo en una posición de 90 grados
  pinMode(led_1, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {

  if (Serial.available())  //Si el puerto serie (Bluetooth) está disponible
  {
    valor = Serial.read();  //Lee el dato entrante via Bluetooth

    if (valor == 'A')   //Si el dato entrante es una A
    {
      servo();   //Llama la función que controla el giro del servo
    }
    if (valor == 'B')   //Si el dato entrante es una B
    {
      led();     //Llama la función que controla el brillo del LED
    }
  }
}

void led()
{
  delay(30); 
  while (Serial.available())
  {
    char c = Serial.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    estado += c;     //Crea una cadena tipo String con los datos entrantes
  }
  if (estado.length() > 0)  //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
    analogWrite(led_1, estado.toInt());  //Manda al LED el dato en forma de entero (int)
    estado = "";      //Limpia la variable para poder leer posteriormente nuevos datos
  }
}

void servo()
{
  delay(30);
  while (Serial.available())
  {
    char c = Serial.read();   //Lee el dato entrante y lo almacena en una variable tipo char
    estado += c;    //Crea una cadena tipo String con los datos entrantes
  }
  if (estado.length() > 0)  //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
    servomotor.write(estado.toInt());   //Manda al servo el dato en forma de entero (int)
    estado = "";    //Limpia la variable para poder leer posteriormente nuevos datos
  }
}
