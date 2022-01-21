//Coche Robot con sensor de US montado sobre un servo 0-180º
//tomado de https://www.youtube.com/watch?v=jQwYBc7YBXs
//Version 1.0 de javier s leyva, Ene 2018

#include <AFMotor.h> 
#include <Servo.h>    
#include <NewPing.h>

#define TRIG_PIN A1 //pin TRIGGER del sensor US
#define ECHO_PIN A0 //pin ECHO del sensor US
#define MAX_DISTANCE_POSSIBLE 1000 // max distancia que mide el sensor = 1m
#define MAX_SPEED 150 // maxima velocidad de los motores
#define MOTORS_CALIBRATION_OFFSET 3
#define DISTANCIA_CHOQUE 20 //distancia a la que disparamos las maniobras antichoque
#define TURN_DIST COLL_DIST+10 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_POSSIBLE);

AF_DCMotor leftMotor(3); 
AF_DCMotor rightMotor(4); 
Servo motor_sensorUS;

int pos = 0; 
int maxDist = 0;
int maxAngle = 0;
int maxRight = 0;
int maxLeft = 0;
int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;


void setup() {
  motor_sensorUS.attach(9);  
  motor_sensorUS.write(90); //el sensorUS mira de frente 2s 
  delay(2000);
//  compruebaCamino(); 
//  motorSet = "FORWARD"; 
 // neckControllerServoMotor.write(90);
 // moveForward();

 Serial.begin(9600);
}



void loop() {
//  checkForward();  
//  checkPath();
compruebaCamino();  

}

void compruebaCamino() {
  int dist_obstaculo = 30;//inicializamos la variable que almacena la dist a los obstaculos
  motor_sensorUS.write(180);//el sensor se orienta mirando hacia su izqu
  delay(120);
  //cada 90 ms el sensor gira 20º en sentido horario
  for(pos = 180; pos >= 0; pos-=20)
  {
    motor_sensorUS.write(pos);
    delay(90);
    // Herramientas-->Serial Monitor para ver la distancia
    Serial.println(String(dist_obstaculo) + " cm."); 
    Serial.println("Angulo de giro del sensor" + String(pos) + "º");
    dist_obstaculo = medir_distancia_obstaculo();
    if (dist_obstaculo < DISTANCIA_CHOQUE) { //¡Choque inminente, hay que hacer algo!
      if (pos<180 and pos>105) {
        //El obstáculo esta a la izq del coche... hay que evitarlo
        gira_derecha();
        break;
        } else if (pos<105 and pos>75) {
                //el obstaculo esta delante del coche
                parar();
                atras();
                delay(500);//0.5s
                gira_derecha();
                break;
        } else if (pos<75 and pos >0) {
                //El obstáculo esta a la derecha del coche... hay que evitarlo
                gira_izquierda();
                break;
                
        } else {adelante();
               }
     // checkCourse();
     // break;
    }   
  }
  
}




void changePath() {
  if (pos < 90) {lookLeft();} 
  if (pos > 90) {lookRight();}
}

//Con el sensor de US medimos
//la distancia a los obstaculos en cm
int medir_distancia_obstaculo() {
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

void checkForward() { if (motorSet=="FORWARD") {leftMotor.run(FORWARD); rightMotor.run(FORWARD); } }

void checkBackward() { if (motorSet=="BACKWARD") {leftMotor.run(BACKWARD); rightMotor.run(BACKWARD); } }

void parar() {leftMotor.run(RELEASE); rightMotor.run(RELEASE);}

void adelante() {
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

void atras() {
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
void gira_izquierda() {
  leftMotor.setSpeed(MAX_SPEED/10);
  rightMotor.setSpeed(MAX_SPEED);
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(1000);
  leftMotor.setSpeed(MAX_SPEED);
   
}  
void gira_derecha() {
  //motorSet = "RIGHT";
  leftMotor.setSpeed(MAX_SPEED);
  rightMotor.setSpeed(MAX_SPEED/10);
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
  delay(1000);
  rightMotor.setSpeed(MAX_SPEED);
 }  


void turnLeft() {
  motorSet = "LEFT";
  leftMotor.run(BACKWARD);
  rightMotor.run(FORWARD);
  delay(600);
  motorSet = "FORWARD";
  leftMotor.run(FORWARD);
  rightMotor.run(FORWARD);
}  

void lookRight() {rightMotor.run(BACKWARD); delay(400); rightMotor.run(FORWARD);}
void lookLeft() {leftMotor.run(BACKWARD); delay(400); leftMotor.run(FORWARD);}

//!!! If you see this error; 'No such file or directory'  Please see this tutorial; https://youtu.be/Es8D1q_b-c4
