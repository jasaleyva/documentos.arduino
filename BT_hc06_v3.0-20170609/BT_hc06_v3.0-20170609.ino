//https://juangiraldo0.blogspot.com/2018/07/configuracion-modulo-bluetooth-hc-06.html
//eXPLICA EN LA WEB COMANDOS AT HC06 V.3.0-20170609
#include <SoftwareSerial.h>
SoftwareSerial BT1(10,11); // RX, TX recordar que se cruzan,
//Conectar así, HC06_RX-> PIN11, HC06_TX->PIN10

//Monitor Serie 9600 baudios y Nueva Línea

void setup()
   {
       Serial.begin(9600);
       Serial.println("Enter AT commands:");
       BT1.begin(9600);
   }

void loop()
   {
       if (BT1.available())
           Serial.write(BT1.read());
       
       if (Serial.available())
          {  String S = GetLine();
             BT1.println(S); // Si no está respondiendo el Bluetooth quitar salto de linea osea, cambiar por BT1.print(S);
           //Si es HC06 V.3.0-20170609 dejar línea anterior
             Serial.println("---> " + S);
          }
}

String GetLine()
   {   String S = "" ;
       if (Serial.available())
          {    char c = Serial.read(); ;
                while (c != '\n')            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial.read();
                  }
                return( S ) ;
          }
   }
