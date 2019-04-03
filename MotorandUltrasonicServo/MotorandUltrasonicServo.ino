#include <Servo.h>

#define ECHO 2
#define TRIG 3

 Servo servo;
 int distance;
 int temp,temp1;
 volatile long echoTime = 0;
 long trigTime = 0,sendTime = 0,timeServo = 0;
 bool scanning = false;
 byte servoDir = -1,servoAngle = 0;


void ultrasonic_setup(void)
{
  servo.attach(4);
  Serial.begin(9600);
  pinMode(ECHO,INPUT);
  pinMode(TRIG,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ECHO), echo_interupt, FALLING);  
}
void servoMotorRotate(void)
{
    // SERVO
     if((millis() - timeServo > 10)){
     if(servoAngle <= 0 || servoAngle >= 180)servoDir = -servoDir;
     servoAngle += servoDir;
    // temp=servoAngle;
     //Serial.println(servoAngle);
     servo.write(servoAngle);
     timeServo = millis();
   }
}
void left(void)
{
  Serial.println("Left");
}
void right(void)
{
  Serial.println("Right");
}
void  straight(void)
{
  Serial.println("straight");
}
void servoMotorStop()
{
  servo.write(temp);
}

void distanceCalculate(void)
{  
  // GETTING RESULTS
    if(echoTime > 0)
    {
      distance = echoTime - trigTime;

      distance /= 58;
      echoTime = 0;
      trigTime = 0;
     // Serial.println("Distance");
      Serial.println(distance-8);
    }
}
void sendingPulse(void)
{
  // SENDING PULSE
  if(millis() - sendTime > 20){
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  trigTime = micros();
  sendTime = millis();
  }
}
 // INTERUPT
void echo_interupt(){
  echoTime = micros();
}
void setup() 
{ 
  ultrasonic_setup();

} 
void loop() 
{
  distanceCalculate();
  servoMotorRotate();
  if((distance-8)>25)
  {
    
    straight();
  }
 else if(servoAngle>=90 && (distance-8)<25  && (distance-8)>0)
  {
    left();
  }
 else if(servoAngle<90 && (distance-8)<25 && (distance-8)>0)
  {
    right();
  }
  sendingPulse();
}
