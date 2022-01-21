//Coche robot con sensor ultrasonico HC SR04 montado sobre motor SERVO
//y 2 ruedas con motores DC manejados con placa MOTOR SHIELD V1 de ADAFRUIT
//Javier S. Leyva
//Tomado de: https://www.youtube.com/watch?v=jQwYBc7YBXs

#include <AFMotor.h> 
#include <Servo.h>    
#include <NewPing.h>

#define TRIG_PIN A1 
#define ECHO_PIN A0
#define MAX_DISTANCE_POSSIBLE 1000 
#define MAX_SPEED 150 // 
#define MOTORS_CALIBRATION_OFFSET 3 //para el motor izquierdo respecto del derecho
#define COLL_DIST 20 // distancia de colisión
#define TURN_DIST COLL_DIST+10 // distacia para girar
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_POSSIBLE);

AF_DCMotor leftMotor(3, MOTOR12_8KHZ); 
AF_DCMotor rightMotor(4, MOTOR12_8KHZ); 
//Servo neckControllerServoMotor;
Servo siervoMotor;
int pos = 0; 
//int maxDist = 0;
//int maxAngle = 0;
//int maxRight = 0;
//int maxLeft = 0;
//int maxFront = 0;
//int course = 0;
//int curDist = 0;
//String motorSet = "";
int speedSet = 0;

//variables nuevas
int x45= 200; //distancia al coche a 45º
int x90= 200; //distancia delante del coche 
int x135= 200;//distancia al coche a 135º
int x_max = 200;//dist max de un obstáculo
int pos_x_max = 90;//indica la orientación del sensor donde la dista al obstaculo es max





void setup() {
  Serial.begin(9600);
  siervoMotor.attach(9); //indico donde he conectado el servo en el motorshield 
  siervoMotor.write(90); //el servo orienta al sensor hacia adelante
  delay(5000);//durante 5s el servo mira hacia adelante.
  parar();//se para el coche en el inicio
}
void giraDer(){}//falta 
void giraIzq(){}//falta
void salvarObstaculo(){}//falta



//reOrientar gira el coche hacia donde la dist al obstáculo sea mayor
void reOrientar(){
  switch (pos_x_max){
      case 45:  giraDer();
      break;
      case 90:  //no cambiamos el rumbo
      break;
      case 135: giraIzq();
      break;     
      }//fin de switch
  }


int leer_dist_x(){
  //mide las 3 dist de obstáculos a 45, 90 y 135º y calcula su max
  //guarda la orientación (pos_x_max) a la que la dist es max
    siervoMotor.write(45);//oriento el sensor mirando a la derecha
    int x45 = readPing(); //incluye un delay de 70 ms
   
    siervoMotor.write(90);//oriento el sensor hacia adelante
    int x90 = readPing(); //incluye un delay de 70 ms
    
    siervoMotor.write(135);//oriento el sensor mirando a la izquierda
    int x135 = readPing(); //incluye un delay de 70 ms
    
    //calculamos la distacia máxima comparando de 2 en 2 valores
    x_max = max (x45, x90);
    x_max = max (x_max, x135);
    //averiguamos la orientacion del servo para la dist del obstaculo máx
    //usar la función max para comparar dos dist x45 con x90
    switch (x_max){
      case x45:  pos_x_max = 45;
      break;
      case x90:  pos_x_max = 90;
      break;
      case x135: pos_x_max = 135;
      break;     
      }//fin de switch
      
      return x_max //dist máx en cm
  }

void checkPath() { //va girando el sensor entre 144-36º y midiento la distancia a los obstáculos
  int curLeft = 0;
  int curFront = 0;
  int curRight = 0;
  int curDist = 0;
  neckControllerServoMotor.write(144);
  delay(120); 
  for(pos = 144; pos >= 36; pos-=18)
  {
    neckControllerServoMotor.write(pos);
    delay(90);
    checkForward(); //mueve el coche hacia adelante
    curDist = readPing(); //cada 70 ms se lee la dist actual al obstáculo
    
    //while (curDist == 0){readPing();} //mientras lee 0 cm repite la lectura
    
    Serial.println(curDist);
    if (curDist>0 && curDist < COLL_DIST) { //hay que evitar el obstáculo de delante
      checkCourse(); //marcha atrás, para y define nueva ruta girando a DER o IZQU
      break;
    }
    if (curDist < TURN_DIST) {
      changePath(); //el robot gira y se reorienta a la DER o IZQU
    }
    if (curDist > curDist) {maxAngle = pos;} 
    //se almacena el ángulo del sensor hacia donde la dist al obstaculo es mayor
    if (pos > 90 && curDist > curLeft) { curLeft = curDist;}
    if (pos == 90 && curDist > curFront) {curFront = curDist;}
    if (pos < 90 && curDist > curRight) {curRight = curDist;}
  }
  maxLeft = curLeft;
  maxRight = curRight;
  maxFront = curFront;
}

void setCourse() { //el robot se reorienta a la DER o a la IZQU
    if (maxAngle < 90) {turnRight();}
    if (maxAngle > 90) {turnLeft();}
    maxLeft = 0;
    maxRight = 0;
    maxFront = 0;
}

void checkCourse() { //hay que evitar el obstáculo que hay delante del robot
  moveBackward(); //se mueve marcha ATRÁS
  delay(500);
  moveStop(); //se DETIENE
  setCourse(); //el robot se reorienta a la DER o a la IZQU
}

void changePath() { //el robot se reorienta hacia la DER o la IZQU
  if (pos < 90) {lookLeft();} 
  if (pos > 90) {lookRight();}
}


int readPing() { //el sensor mide la distancia hasta el obstáculo
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void checkForward() { if (motorSet=="FORWARD") {leftMotor.run(FORWARD); rightMotor.run(FORWARD); } }

void checkBackward() { if (motorSet=="BACKWARD") {leftMotor.run(BACKWARD); rightMotor.run(BACKWARD); } }

void parar() {leftMotor.run(RELEASE); rightMotor.run(RELEASE);}

void avanzar() {
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
  }
void moveForward() {
    motorSet = "FORWARD";
    leftMotor.run(FORWARD);
    rightMotor.run(FORWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
  {
    leftMotor.setSpeed(speedSet+MOTORS_CALIBRATION_OFFSET);
    rightMotor.setSpeed(speedSet);
    delay(5);
  }
}
void moveBackward() {
    motorSet = "BACKWARD";
    leftMotor.run(BACKWARD);
    rightMotor.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
  {
    leftMotor.setSpeed(speedSet+MOTORS_CALIBRATION_OFFSET);
    rightMotor.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motorSet = "RIGHT";
  leftMotor.run(FORWARD);
  rightMotor.run(BACKWARD);
  delay(400);
  motorSet = "FORWARD";
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);      
}  

void turnLeft() {
  motorSet = "LEFT";
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(400);
  motorSet = "FORWARD";
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}  

void lookRight() {rightMotor.run(BACKWARD); delay(400); rightMotor.run(FORWARD);}
void lookLeft() {leftMotor.run(BACKWARD); delay(400); leftMotor.run(FORWARD);}

//!!! If you see this error; 'No such file or directory'  Please see this tutorial; https://youtu.be/Es8D1q_b-c4

void loop() {
  //checkForward();  //coche hacia adelante
  //checkPath(); //va girando el sensor entre 144-36º y midiento la distancia a los obstáculos
  //
  x_max = leer_dist_x();
  if (x_max<20){
    salvarObstaculo();
    } 
  else {
    reOrientar();
    avanzar();
    } 
}//fin del loop
