#include <Servo.h>
#include "servo_spider.h"
int servo_pins [12] = {2,3,4,5,6,7,8,9,10,11,13};
Servo servo1;
void setup() {
  Serial.begin(9600);
  for (int i = 2; i < 14; i++){ 
  servo1.attach(i);
  }
  Serial.println(" ||  ||");
  Serial.println(" \\()//");
  Serial.println("//(__)\\");
  Serial.println("||    ||");
}

void loop() {

}
