#include <FourBitDisplay.h>
#include <string.h>

//FourBitDisplay fbd(4,6,3);//pin 4=rclk, 6=sclk, 3=dio
FourBitDisplay fbd(7,8,1); //pin 7= rclk, 8=sclk, 1 = dio
void setup()
{
}
float aciertos= 00.00;
//int aciertos =2589;
void loop()
{
  char buf[4];
  //dtostrf(aciertos,4,2, buf)... 4=tamaño del número "aciertos", 
  //2= cantidad de decimales de "aciertos"
  dtostrf(aciertos,4,2, buf); //Convert from float to char array
  char *val = buf;
  short arraySize = strlen(val);
  char *just = "r";
  fbd.printToDisplay(val,arraySize,just);
  aciertos =aciertos+0.01;
  delay(20);
  if (aciertos >=6300){
    aciertos =00.00;}
  }

