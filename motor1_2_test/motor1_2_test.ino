    #include <AFMotor.h>
     
    AF_DCMotor motorIz(2, MOTOR12_1KHZ); // create motor #1, 1KHz pwm
    AF_DCMotor motorDer(3, MOTOR12_1KHZ); // create motor #2, 1KHz pwm
    void setup() {
      Serial.begin(9600);           // set up Serial library at 9600 bps
      Serial.println("Motor test!");
      
      motorIz.setSpeed(255);     // set the speed to 200/255
      motorDer.setSpeed(255);     // set the speed to 200/255
    }
     
    void loop() {
      Serial.print("tick ");
      
      motorIz.run(FORWARD);      // turn it on going forward
      motorDer.run(FORWARD);      // turn it on going forward
      delay(2000);
      Serial.print("tock ");
      
      motorIz.run(BACKWARD);     // the other way
      motorDer.run(BACKWARD);     // the other way
      delay(1000);
      
      Serial.print("tack");
      motorIz.run(RELEASE);      // stopped
      motorDer.run(RELEASE);      // stopped
      delay(1000);
    }
