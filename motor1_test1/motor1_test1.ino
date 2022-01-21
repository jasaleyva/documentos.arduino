    #include <AFMotor.h>
     
    AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1, 1KHz pwm
    AF_DCMotor motor2(2, MOTOR12_1KHZ); // create motor #2, 1KHz pwm
    void setup() {
      Serial.begin(9600);           // set up Serial library at 9600 bps
      Serial.println("Motor test!");
      
      motor1.setSpeed(200);     // set the speed to 200/255
      motor2.setSpeed(200);     // set the speed to 200/255
    }
     
    void loop() {
      Serial.print("tick ");
      
      motor1.run(FORWARD);      // turn it on going forward
      motor2.run(FORWARD);      // turn it on going forward
      delay(3000);
      Serial.print("tock ");
      
      motor1.run(BACKWARD);     // the other way
      motor2.run(BACKWARD);     // the other way
      delay(3000);
      
      Serial.print("tack");
      motor1.run(RELEASE);      // stopped
      motor2.run(RELEASE);      // stopped
      delay(1000);
    }
