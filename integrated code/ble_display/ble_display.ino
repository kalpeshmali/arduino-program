#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define test_pin A0

#define menu_pin 1
#define select_pin 0
//#define TEST_PIN_DEBUG
enum robot_functionality {MANUAL=0,LINE_FOLLOWER,OBSTACLE_AVOIDER,TACTILE, ROBOTIC_ARM};
robot_functionality Robot_functionality = MANUAL;
Adafruit_SSD1306 display(OLED_RESET); /* Object of class Adafruit_SSD1306 */

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()
{
   Serial.begin(9600);
   pinMode(test_pin,INPUT);
   displaysetup();
   bluetooth_setup();
   tactile_setup();
   ultrasonic_setup();
   Serial.println("SETUP COMPLETE");
}

//--------------------MAIN PROGRAM---------------------------------------------------//
void loop() {
  Display();
  ReadBluetoothData();  
 // Display_functionality(func);
  switch(Robot_functionality)
  {
  case MANUAL: BluetoothDirectionControl();
            //  Serial.println("MANUAL MODE");
              break;
  case LINE_FOLLOWER: LineFollower();
              
              break;
  case OBSTACLE_AVOIDER: Obstacle_avoider();
            //  Serial.println("OBSTACLE_AVOIDER");
              break;
  case TACTILE: Tactile();
             //   Serial.println("TACTILE MODE");
              break;
  case ROBOTIC_ARM: Robotic_arm();
  }
} //Reset the variable

void Display_functionality(char *ptr)
{
   display.setCursor(10,13);
  while(*ptr)
  {
   display.print(*ptr);
   ptr++;
  }
}

void displaysetup(void)
{
  pinMode(menu_pin,INPUT_PULLUP);
  pinMode(select_pin,INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); /* Initialize display with address 0x3C */
  display.clearDisplay(); /* Clear display */

  display.setCursor(10,0); /* Set x,y coordinates */
  display.setTextSize(1);
}

/*----------MENU SELECTION------------*/


int Display(void)
{
  bool static mvalue=digitalRead(menu_pin),prev_mvalue=0;
  bool static menu=0;
  if((HIGH==prev_mvalue) && (LOW == mvalue))
  {
    if(1==menu)
    {
      menu =0;
    }
    else
    {
      menu=0;
    }
  }
  prev_mvalue = mvalue;  
  if(menu==1)/*----entering to menu--------*/
  {
    menu_options();
  }
  else
  {
    menu_normal();
  }
}

void menu_normal(void)
{
 // Sensor_module_display();
 // functionality_display();
  display.setCursor(10,6);/* Select font size of text. Increases with size of argument. */
  display.println("-------------------");
  display.setCursor(10,19);/* Select font size of text. Increases with size of argument. */
  display.println("-------------------");
  display.setCursor(10,13);  
  display.println("KARMIC ALA CARTE");
  display.setCursor(10,25);
  display.println("Menu");
  display.setTextColor(WHITE);
/*------------------------------------------------------*/
  
   /* Text to be displayed */
  display.display();
 // delay(1000);
  display.clearDisplay();
  display.setCursor(10,0); /* Set x,y coordinates */
  display.setTextSize(1);
  int test_value=analogRead(test_pin);
  #ifdef TEST_PIN_DEBUG
  Serial.println("Test pin value");
  Serial.println(test_value);
  #endif
  if(test_value>=1015 && test_value<=1030)
  {
    display.println("Line follower");
  }
   else if(test_value>=500 && test_value<=525)
  {
    display.println("Ultrasonic");
    Robot_functionality = OBSTACLE_AVOIDER;
  }
    else if(test_value>=400 && test_value<=420)
  {
    display.println("Tactile sensor");
    Robot_functionality = TACTILE;
  }
   else if(test_value>=310 && test_value<=325)
  {
    display.println("Color sensor");
  }
  else
  {
    display.println(" NO Sensor module");
    Robot_functionality = MANUAL;
  }  
}


void menu_options(void)
{
  bool static svalue=digitalRead(select_pin);
  int static select=0;
  if(svalue==LOW)/*---selection of function----*/
  {
    select++;
    if(select>2)
    {
      select=select%2;
    }
  }
    display.setCursor(10,0); /* Set x,y coordinates */
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("Line follower");
    display.setCursor(10,6);/* Select font size of text. Increases with size of argument. */
    display.println("-------------------");
    display.setCursor(10,13);
    display.println("Tactile");
    display.setCursor(10,19);/* Select font size of text. Increases with size of argument. */
    display.println("-------------------");
    display.setCursor(10,25);
    display.println("Ultrasonic");
    display.display();
    if(select==0)
    {
      display.setCursor(0,0);
      display.println("#");
    }
    else if(select==1)
    {
      display.setCursor(0,13);
      display.println("#");
    }
    else if(select==2)
    {
      display.setCursor(0,25);
      display.println("#");
    }
    
  display.setCursor(10,13);  
   if(select==0)
  {
   display.println("LINE FOLLOWER");
  }
  else if(select==1)
  {
    display.println("TACTILE  ");
  }
    else if(select==2)
  {
    display.println("ULTRASONIC");
  }
  else
  {
    display.println("FUNCTIONALTY");
  }    
}
