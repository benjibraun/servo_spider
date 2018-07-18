#include <Servo.h>
#include "servo_spider.h"
const uint8_t servo_pins [12] = {2,3,4,5,6,7,8,9,10,11,12,13};
const Servo servos[4][3]={{servo1,servo2,servo3},{servo4,servo5,servo6},{servo7,servo8,servo9},{servo10,servo11,servo12}};
uint8_t leg_moov_delay = 2;
uint8_t leg_num = 90;
uint8_t servo_num = 90;
uint8_t servo_angle = 90;

void setup() 
{
  pinMode(TRIGER, OUTPUT);
  pinMode(ECHO, INPUT); 
  uint8_t servo_num = 0;
  Serial.begin(115200);
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++){
        servos[i][j].attach(servo_pins [servo_num]);
        move_data[i][j] = 90;
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
      
      //Serial.write(Serial.read());
      Serial.flush();
    }
    //Serial.println(get_distance());
    if (is_stend == 0){
      //stendup();
    }
    move_leg(move_data);   
}
void move_forwald(int steps)
{
  
}
void move_leg(uint8_t leg_ot_move[4][3])
{
  uint8_t angle;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++){
        
        if ((i == 1 || i == 2) && (j == 0 || j==  1 )){
          angle = 180 - move_data[i][j]; 
        }
        else if  ((i == 0 || i== 3) && j == 2){
          angle = 180 - move_data[i][j];
        }
        else {
          angle = move_data[i][j];
        }
        
        if (servos[i][j].read() < angle){
          servos[i][j].write(servos[i][j].read()+1);
          //Serial.println(servos[i][j].read());
        }
        else if  (servos[i][j].read() > angle){
          servos[i][j].write(servos[i][j].read()-1);
         //Serial.println(servos[i][j].read());
        }
    }
    delay(leg_moov_delay);
  } 
  
  //servos[leg_ot_move[0]][leg_ot_move[1]].write(leg_ot_move[2]);
  
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
void send_ack(byte massage [1]){
  byte data[3];
  data[0] = massage[0] & 0b00000011; 
  data[1] = massage[0] & 0b00001100;
  data[2] = massage[0] & 0b11110000;  
  Serial.write(data[0]|data[1]|data[2]);
}
void process_massage(){
  byte raw_massage[1];
  Serial.readBytes(raw_massage, 1);
  move_data[raw_massage[0] & 0b00000011][((raw_massage[0] & 0b00001100 )>> 2)] = ((uint8_t)(raw_massage[0] & 0b11110000) >> 4) * 10; 
  send_ack(raw_massage);
  /*
  move_data[1] =  move_data[1] >> 2;
  move_data[2] = ((int) (move_data[2] >> 4)) * 10 ;
  */
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
