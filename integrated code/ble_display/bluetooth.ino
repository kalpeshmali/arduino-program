#include <SoftwareSerial.h>
SoftwareSerial BT(12,2); //TX, RX respetively
String readdata;
#define left1 (6)                                         //Left Motor pin initialization//
#define left2 (7)
#define right1 (8)                                       //right Motor pin initialization//
#define right2 (9)


void bluetooth_setup(void)
{
  BT.begin(38400);
  pinMode(left1,OUTPUT);                          //Left Motor pin declaration//
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);                        //Right Motor pin declaration//
  pinMode(right2,OUTPUT);
}

void Forward()
{
  digitalWrite(left1,HIGH);
  digitalWrite(left2,LOW);          // forward move function //
  digitalWrite(right1,HIGH);
  digitalWrite(right2,LOW);
}

void Reverse()
{
  digitalWrite(left1,LOW);
  digitalWrite(left2,HIGH);          // backward move function //
  digitalWrite(right1,LOW);
  digitalWrite(right2,HIGH);
}

void Right()
{
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);          //  right turn function //
  digitalWrite(right1,HIGH);
  digitalWrite(right2,LOW);
}

void Left()
{
  digitalWrite(left1,HIGH);
  digitalWrite(left2,LOW);          // left turn function //
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
}

void Stop()
{
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);          //stop//
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
}

void Reverse_left(void)
{
  digitalWrite(left1,HIGH);
  digitalWrite(left2,LOW);          // reverse left turn function //
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);  
}

void Reverse_Right()
{
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);          //  reverse right turn function //
  digitalWrite(right1,HIGH);
  digitalWrite(right2,LOW);
}

void ReadBluetoothData (void)
{
  while (BT.available())
  {          //Check if there is an available byte to read
  //delay(10);                       //Delay added to make thing stable
  char c = BT.read();              //Conduct a serial read
  readdata += c;                   //build the string- "forward", "reverse", "left" and "right"
  }  
}


void BluetoothDirectionControl(void)
{
  if (readdata.length() > 0) 
  {
    Serial.println(readdata);    
    if(readdata == "FORWORD")
    {
      Serial.println("Forward");
      Forward();
    }
    else if(readdata == "BACKWORD")
    {
      Serial.println("Backword");
      Reverse();
    }    
    else if (readdata == "RIGHT")
    {
      Serial.println("Right");
      Right();    
    }    
    else if ( readdata == "LEFT")
    {
      Serial.println("Left");
      Left();
    }    
    else if (readdata == "STOP")
    {
      Serial.println("Stop");
      Stop();
    }    
    readdata="";
  }  
}
