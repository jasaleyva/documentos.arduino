/*** Global variables ***/
int  estado_pulsador=1;
int led=1;//led encendido
/*** Function declaration ***/
void setup() {
  pinMode(A1,INPUT);//pulsador conectado a A1
  pinMode(11,OUTPUT);// Led conectados a D11
  }
void loop() {
  estado_pulsador=analogRead(A1);
  if ((estado_pulsador == 0) && (led == 1)) {
    led=0; 
    }else if ((estado_pulsador == 0) && (led == 0)) {
      led=1;
      }
  digitalWrite(11,led);
  delay(200);
  }
