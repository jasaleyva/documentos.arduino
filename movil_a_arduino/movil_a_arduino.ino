// Juan Antonio Villalpando
// juana1991@yahoo.com
// kio4.com

char val;
int ledPin12 = 12;
int ledPin13 = 13;

void setup() { 
Serial.begin(9600); // Aqui establecemos la velocidad
pinMode(ledPin12, OUTPUT); 
pinMode(ledPin13, OUTPUT); 
}

void loop() { 
if( Serial.available() ) {
val = Serial.read();

if( val == '0' )
{ 
digitalWrite(ledPin12, LOW);
}

if( val == '1' )
{ 
digitalWrite(ledPin12, HIGH);
} 
if( val == '2' )
{ 
digitalWrite(ledPin13, LOW);
}

if( val == '3' )
{ 
digitalWrite(ledPin13, HIGH);
} 
} 
}
