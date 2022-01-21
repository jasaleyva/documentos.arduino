#include <AFMotor.h>
AF_DCMotor motorIZQ(1); 
AF_DCMotor motorDER(2);

//la siguiente función reduce poco a poco la velocidad hasta parar el coche
void stopCoche () {
  for(int i=200; i>1; i=i-10) {
    motorIZQ.setSpeed(i);
    motorDER.setSpeed(i);
    delay(100);
    }//FIN DEL BUCLE FOR
  motorIZQ.run(RELEASE);
  motorDER.run(RELEASE);
}


void setup() {
  motorIZQ.setSpeed(200);//valores entre 0-255
  motorDER.setSpeed(200); 

}

void loop() {
  //usamos la funcion para detener el coche   
  stopCoche();

}
