#include <Servo.h>
#include "servo_spider.h"
const int servo_pins [12] = {2,3,4,5,6,7,8,9,10,11,12,13};
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
const Servo servos[4][3]={{servo1,servo2,servo3},{servo4,servo5,servo6},{servo7,servo8,servo9},{servo10,servo11,servo12}};
int leg_num = 90;
int servo_num = 90;
int servo_angle = 90;
void setup() 
{
  pinMode(TRIGER, OUTPUT);
  pinMode(ECHO, INPUT); 
  int servo_num = 0;
  Serial.begin(115200);
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++){
        servos[i][j].attach(servo_pins [servo_num]);
        servo_num++;
    }
  }  
  /*
  Serial.println(" ||  ||");
  Serial.println(" \\()//");
  Serial.println("//(__)\\");
  Serial.println("||    ||");
  Serial.println("Enter leg number (0-3) :"); 
  */
}

void loop() 
{    
  
    //manual_serov_test();
    if (Serial.available()){
      process_massage();
      move_leg(move_data);
      //Serial.write(Serial.read());
      Serial.flush();
    }
    //Serial.println(get_distance());
    if (is_stend == 0){
      //stendup();
    }
       
}
void move_forwald(int steps)
{
  
}
void move_leg(int* leg_ot_move)
{
  
  servos[leg_ot_move[0]][leg_ot_move[1]].write(leg_ot_move[2]);
  
}

void stendup()
{
  for (int i = 0; i < 4;i++){
    servos[i][0].write(180); 
    servos[i][2].write(150); 
  }
  is_stend = 1;
}
int get_distance()
{
  int distance;
  unsigned long echo_time;
  digitalWrite(TRIGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGER, LOW);
  echo_time = pulseIn(ECHO, HIGH);
  distance = echo_time*0.034/2;
  return round(distance);
  
}

void process_massage(){
  byte raw_massage[1];
  Serial.readBytes(raw_massage, 1);
  move_data[0] = raw_massage[0] & 0b00000011; 
  move_data[1] = raw_massage[0] & 0b00001100;
  move_data[2] = raw_massage[0] & 0b11110000;  
  Serial.write(move_data[0]|move_data[1]|move_data[2]);
  move_data[1] =  move_data[1] >> 2;
  move_data[2] = ((int) (move_data[2] >> 4)) * 10 ;
  
  //Serial.write(massage[0]|massage[1]|massage[2]);
}
void manual_serov_test()
{
    if (Serial.available() && Serial.parseInt() == 999){
      Serial.flush();
      Serial.println("ok");
      while (!Serial.available()){
        
      }
      int legnum = Serial.parseInt();
      Serial.println("ok");
      Serial.flush();
      while (!Serial.available()){
        
      }
       int servonum = Serial.parseInt();
      Serial.println( servos[legnum][servonum].read());
    }
    
    if (Serial.available() && state == 0){ // swich !!!!!!!!!!!!!!!!
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
