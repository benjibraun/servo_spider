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
Servo servos[4][3]={{servo1,servo2,servo3},{servo4,servo5,servo6},{servo7,servo8,servo9},{servo10,servo11,servo12}};
int leg_num = 90;
int servo_num = 90;
int servo_angle = 90;
void setup() {
  int servo_num = 0;
  Serial.begin(115200);
  for (int i = 0; i < 4; i++){
    for (int j = 0; i < 3; i++){
        servos[i][j].attach(servo_pins [servo_num]);
        servo_num++;
    }
  }
  Serial.println(" ||  ||");
  Serial.println(" \\()//");
  Serial.println("//(__)\\");
  Serial.println("||    ||");
  Serial.println("Enter leg number (0-3) :"); 
}

void loop() {    
    manual_serov_test();
}
void manual_serov_test()
{
    if (Serial.available() && state == 0){
      leg_num = Serial.parseInt();
      Serial.println("ok");
      Serial.println(leg_num);
      Serial.flush();
      Serial.println("servo number (0-2) :") ;
      state++;
    }
    if (Serial.available() && state == 1){
      
      servo_num = Serial.parseInt();
      Serial.println("ok");
      Serial.println(servo_num);
      Serial.flush();
      Serial.println("degre (0-180) :");
      state++;
    }
    if (Serial.available() && state == 2){
      servo_angle = Serial.parseInt();
      Serial.println(servo_angle);
      Serial.println("ok");
      Serial.flush();
      Serial.println("Enter leg number (0-3) :"); 
      state++;
    }
    if (state == 3){
      servos[leg_num][servo_num].write(servo_angle);
      Serial.println("leg:" + (String) leg_num + "servo :" + (String) servo_num + "=" + (String) servo_angle);
      state = 0;
    }
}
