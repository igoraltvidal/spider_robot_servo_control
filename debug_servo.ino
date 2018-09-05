#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define FIRST_TEXT 1
#define SECOND_TEXT 2
#define NUMBER_SERVO 12

int number_input_id;
int number_input_value;
int vector_values[NUMBER_SERVO] = {150,120,90,   //arm 1
                                   20, 10, 45,   //arm 2
                                   30, 20, 105,  //arm 3
                                   150, 150, 80}; //arm 4

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void set_initial(){
  //arm 1
  pwm.setPWM(0, 0,map(vector_values[0],0,180,SERVOMIN,SERVOMAX)); // hand
  pwm.setPWM(1, 0,map(vector_values[1],0,180,SERVOMIN,SERVOMAX)); // elbow
  pwm.setPWM(2, 0,map(vector_values[2],0,180,SERVOMIN,SERVOMAX)); // shoulder

  //perna 2
  pwm.setPWM(3, 0,map(vector_values[3],0,180,SERVOMIN,SERVOMAX)); // hand
  pwm.setPWM(4, 0,map(vector_values[4],0,180,SERVOMIN,SERVOMAX)); // elbow
  pwm.setPWM(5, 0,map(vector_values[5],0,180,SERVOMIN,SERVOMAX)); // shoulder

  //perna 3
  pwm.setPWM(6, 0,map(vector_values[6],0,180,SERVOMIN,SERVOMAX)); // hand
  pwm.setPWM(7, 0,map(vector_values[7],0,180,SERVOMIN,SERVOMAX)); // elbow
  pwm.setPWM(8, 0,map(vector_values[8],0,180,SERVOMIN,SERVOMAX)); // shoulder

  //perna 4
  pwm.setPWM(9, 0,map(vector_values[9],0,180,SERVOMIN,SERVOMAX)); // hand
  pwm.setPWM(10, 0,map(vector_values[10],0,180,SERVOMIN,SERVOMAX)); // elbow
  pwm.setPWM(11, 0,map(vector_values[11],0,180,SERVOMIN,SERVOMAX)); // shoulder
}

void set_value(int id_servo, int value){

  pwm.setPWM(id_servo, 0,map(value,0,180,SERVOMIN,SERVOMAX));
  vector_values[id_servo] = value;
  
}

void setup() {
  Serial.begin(9600);
  //Serial.println("Chose: ");
  //Serial.println("1 - Lift  2 - Initial");

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  set_initial();
  delay(10);
}

void new_page_terminal(){
  for(int i = 0; i < 30; i++){
    Serial.println();
  }
}

void print_values(){
  Serial.println();
  Serial.println("ACTUAL VALUES: ");
  for(int i = 0; i < NUMBER_SERVO; i++){
    Serial.print("Servo: ");
    Serial.print(i);
    Serial.print(" | value: ");
    Serial.println(vector_values[i]);
  }
}

void print_index(){

    Serial.println();
    Serial.println("Arm 1:");
    Serial.println("    0 - hand");
    Serial.println("    1 - elbow");
    Serial.println("    2 - shoulder");
    Serial.println("Arm 2:");
    Serial.println("    3 - hand");
    Serial.println("    4 - elbow");
    Serial.println("    5 - shoulder");
    Serial.println("Arm 3:");
    Serial.println("    6 - hand");
    Serial.println("    7 - elbow");
    Serial.println("    8 - shoulder");
    Serial.println("Arm 4:");
    Serial.println("    9 - hand");
    Serial.println("    10 - elbow");
    Serial.println("    11 - shoulder");  
    Serial.println();
  
}

void print_text(int id_text){

  new_page_terminal();
  print_values();
  print_index();

  if(id_text == FIRST_TEXT){
    Serial.println("SELECT AN SERVO ID:");
  }
  if(id_text == SECOND_TEXT){
    Serial.println("SELECT AN INPUT VALUE:");
  }

}

int wait_input(){

  int number_input = 0;
  int garbage = 0;
  
  while(1){
    if(Serial.available() > 0){
      number_input = Serial.parseInt();
      break;
    }
    delay(100);
  }
  //delay(100);
  //Serial.flush();
  if(Serial.available() > 0){
      garbage = Serial.parseInt();
    }
    
  return number_input;
}

void loop() {

  print_text(FIRST_TEXT);
  number_input_id = wait_input();

  print_text(SECOND_TEXT);
  number_input_value = wait_input();

  set_value(number_input_id,number_input_value);
    
}
