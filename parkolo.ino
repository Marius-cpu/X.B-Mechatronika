#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//int obstaclePin = 13;
int hasObstacle = LOW; // LOW MEANS NO OBSTACLE

int IRSensor = 12;
int IRSensor2 = 13;
LiquidCrystal_I2C mylcd(0x27, 16, 2);

Servo servo;
void setup() {
  pinMode(IRSensor, INPUT);
  mylcd.init();
  mylcd.backlight();
  mylcd.setCursor(0,1);
  // put your setup code here, to run once:
  servo.attach(4);
   pinMode(IRSensor, INPUT);
  Serial.begin(9600);
 
  //servo.write(90);
}

void loop() {
  hasObstacle = digitalRead(IRSensor);

  // put your main code here, to run repeatedly:
  //int sensorStatus = digitalRead(IRSensor);
  //int sensor2 = digitalRead(IRSensor2);
  //Serial.println(sensorStatus);
  //Serial.println(sensor2);
  //if(sensorStatus == 1){
    if(hasObstacle == HIGH){
    mylcd.print("Nyilik a kapu");
    servo.write(180);
    //delay(3000);
    mylcd.clear();

  }else {
    mylcd.print("Zarva");
    //servo.write(180);
    delay(2000);
    servo.write(0);
    mylcd.clear();
  }

 
}
