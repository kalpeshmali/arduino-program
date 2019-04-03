
void tactile_setup()
{
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
}

void Tactile(void)
{
  int Left_tactile = analogRead(A1);
  int Right_tactile = analogRead(A2);
  Serial.println("Tactile sensor values");
  Serial.print("Left tactile = ");
  Serial.print(Left_tactile);
  Serial.print("Right tactile = ");
  Serial.print(Right_tactile);
  if(Left_tactile>=500 && Right_tactile <500)
  {
    Reverse_left();
    delay(1000);
    Stop();
  }
  else if(Left_tactile<500 && Right_tactile >=500)
  {
    Reverse_Right();
    delay(1000);
    Stop();
  }
  else if(Left_tactile>=500 && Right_tactile >=500)
  {
    Reverse();
    delay(1000);
    Stop();
  }
  else
  {
    //Do Nothing
  }
}
