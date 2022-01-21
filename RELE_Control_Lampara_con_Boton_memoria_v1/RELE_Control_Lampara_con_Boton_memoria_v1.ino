//control de LAMPARA CON BOTÓN Y RELE  v.1
//JAVIER S. 
//Una lámpara conectada al RELE es controlado por un botón
//Mientras se presiona el botón la lampara se enciende y al soltarlo se apaga


//CONEXIONES RELE-ARDUINO

//RELE D+  - a 5V Arduino
//RELE D-  - a GND Arduino
//RELE IN  - a D9 Arduino 

/*** Global variables ***/ 
int estado_pulsador=1023; //el pulsador pulsado=1023, no = 0
int estado_lampara=0;     // lampara ON=1, OFF=0

 
void setup() {
  pinMode(A0,INPUT); //A0 = ESTADO DEL PULSADOR
  pinMode(9,OUTPUT); //D9 = SEÑAL DE CONTROL que entra en RELE
  Serial.begin(9600);
  } 
  
void loop() {
  estado_pulsador=analogRead(A0);
  Serial.println(estado_pulsador);
  
  if ((estado_pulsador >1000) && (estado_lampara == 1)) {
    estado_lampara=0; 
    }
  else if ((estado_pulsador >1000) && (estado_lampara == 0)) {
    estado_lampara=1; 
    } 
  digitalWrite(9,estado_lampara);
  delay(200); 
  } 
  
