
#include <Servo.h>. 
const int trigPin = 10;
const int echoPin = 11;
// defining time and distance
long duration;
int distance;
Servo myServo; // Object servo
void setup() {
  pinMode(trigPin, OUTPUT); // trigPin as an Output
  pinMode(echoPin, INPUT); // echoPin as an Input
  Serial.begin(9600);
  myServo.attach(9); // Pin Connected To Servo
}
void loop() {
  // rotating servo i++ depicts increment of one degree
  for(int i=15;i<=165;i++){  
  myServo.write(i);
  delay(5);
  distance = calculateDistance();
  if(distance<100)
  Serial.println(distance); 
  }

  for(int i=165;i>15;i--){  
  myServo.write(i);
  delay(5);
  distance = calculateDistance();
  if(distance<100)
  Serial.println(distance);

  }
}
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(3);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
}
