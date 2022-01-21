#include <FourBitDisplay.h>
#include <string.h>

FourBitDisplay fbd(4,6,3);
void setup()
{
}
float aciertos= 25.89;
void loop()
{
  char buf[4];
  dtostrf(aciertos,4,2, buf); //Convert from float to char array
  char *val = buf;
  short arraySize = strlen(val);
  char *just = "r";
  fbd.printToDisplay(val,arraySize,just);
  
}

