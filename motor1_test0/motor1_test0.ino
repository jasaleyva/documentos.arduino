    #include <AFMotor.h> //incluimos la libreria que permite manejar la placa motorshield v1
     
    AF_DCMotor motor1(1); // crea un controlador llamado motor1 y lo conectado a M1 en la placa motorshield
    AF_DCMotor motor2(2); //crea motor2 y lo conectamos a M2 
    void setup() {
      motor1.setSpeed(200);     // la velocidad del motor 1 entre 0-255
      motor2.setSpeed(200);     
    }
     
    void loop() {
            
      motor1.run(FORWARD);      // gira adelante el motor1
      motor2.run(FORWARD);      
      delay(3000);              //retardo 3 s, mientras siguen girando ambos motores
            
      motor1.run(BACKWARD);     // gira atras el motor1
      motor2.run(BACKWARD);     
      delay(1000);              //retardo 1 s, mientras siguen girando ambos motores
      
      motor1.run(RELEASE);      // motor1 PARA
      motor2.run(RELEASE);     
      delay(1000);              //retardo 1 s, mientras siguen parados
    }
