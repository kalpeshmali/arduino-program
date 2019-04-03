#include <Servo.h>

#define ECHO 3
#define TRIG 4

 Servo servo;
 int distance;
 int temp,temp1;
 volatile long echoTime = 0;
 long trigTime = 0,sendTime = 0,timeServo = 0;
 bool scanning = false;
 byte servoDir = -1,servoAngle = 0;


void ultrasonic_setup(void)
{
  servo.attach(5);
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
 // servoMotorRotate();
  if((distance-8)<5)
  {
    servo.write(90);
  }
  else
  {
     servo.write(0);
  }
  sendingPulse();
}
