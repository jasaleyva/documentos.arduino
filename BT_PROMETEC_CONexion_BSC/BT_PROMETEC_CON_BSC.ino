//https://www.prometec.net/bt-hc06/
//En el Monitor Serie de arduino seleccionar "Ambos NL & CR"
#include <SoftwareSerial.h>
//SoftwareSerial BT1(4,2); // RX, TX recorder que se cruzan
SoftwareSerial BT1(A0,A1); // RX, TX recorder que se cruzan
//Conectar el BT->RXD al pin2 de arduino
//Conectar el BT->TXD al pin4 de arduino
void setup()
   {
       Serial.begin(9600);
       Serial.println("PROMETEC___Enter AT commands:");
       BT1.begin(9600);
   }

void loop()
   {
       if (BT1.available())
           Serial.write(BT1.read());
       
       if (Serial.available())
          {  String S = GetLine();
             BT1.print(S);
             Serial.println("---> " + S);
          }
}

String GetLine()
   {   String S = "" ;
       if (Serial.available())
          {    char c = Serial.read(); ;
                while ( c != '\n')            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial.read();
                  }
                return( S + '\n') ;
          }
   }
