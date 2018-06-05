#include <Servo.h>
#include "servo_spider.h"
int servo_pins [12] = {2,3,4,5,6,7,8,9,10,11,13};
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;
Servo servo12;
Servo servos[12]={servo1, servo2,servo3,servo4,servo5,servo6,servo7,servo8,servo9,servo10,servo11,servo12};
int command =90 ;
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 12; i++){ 
  servos[i].attach(servo_pins [i]);
  }
  Serial.println(" ||  ||");
  Serial.println(" \\()//");
  Serial.println("//(__)\\");
  Serial.println("||    ||");
}

void loop() {

  for (int i = 0; i < 12; i++)
  {
    
    servos[i].write(command);
    Serial.println("servo :" + (String) i + "=" + (String) command);
    if (Serial.available())
    {
      //command = Serial.readString();
      command = Serial.parseInt();
      digitalWrite((int)command,HIGH);
    }
    delay(1000);

    
    /*
    servos[i].write(0);
    Serial.println("servo :" + (String)i + "=" + "0");
    delay(100);
    servos[i].write(90);
    Serial.println("servo :" + (String)i + "=" + "90");
    delay(100);
    servos[i].write(45);
    Serial.println("servo :" + (String)i + "=" + "45");
    delay(100);
    */
  }
}
