#include <FourBitDisplay.h>
#include <string.h>

//FourBitDisplay fbd(4,6,3);
FourBitDisplay fbd(7,8,1); //pines libres en simón
void setup()
{
}
float aciertos= 23.97;
//int aciertos =2589;
void loop()
{
void  mostrar_aciertos();// mostramos la variable aciertos en el display
}
//Definimos función para mostrar los aciertos en el display
void mostrar_aciertos(){
  char buf[4];
  //dtostrf(aciertos,4,2, buf)... 4=tamaño del número "aciertos", 
  //2= cantidad de decimales de "aciertos"
  dtostrf(aciertos,4,2, buf); //Convert from float to char array
  char *val = buf;
  short arraySize = strlen(val);
  char *just = "r";
  fbd.printToDisplay(val,arraySize,just);
}

