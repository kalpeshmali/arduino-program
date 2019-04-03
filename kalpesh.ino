void setup() {
// put your setup code here, to run once:
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(5,INPUT);
Serial.begin(9600);
}

void loop() {
// put your main code here, to run repeatedly:
int s1=digitalRead(3);
int s2=digitalRead(4);
int s3=digitalRead(5);
Serial.println("s1");
Serial.println(s1);
//delay(1000);
Serial.println("s2");
Serial.println(s2);
//delay(1000);
Serial.println("s3");
Serial.println(s3);



if(s1==LOW && s3==LOW)
{
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
digitalWrite(10,HIGH);
digitalWrite(11,LOW);
}
else if(s1==HIGH && s3==LOW)
{
digitalWrite(8,LOW);
digitalWrite(9,LOW);
digitalWrite(10,HIGH);
digitalWrite(11,LOW);
delay(500);


}
else if(s1==LOW && s3==HIGH)
{
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
delay(500);
}
else if(s1==HIGH && s3==HIGH)
{
digitalWrite(8,LOW);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
}
}
