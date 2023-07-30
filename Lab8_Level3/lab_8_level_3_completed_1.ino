// Lab 8 Level 3
// Matthew Antonis
// 2023-03-09


//Problems 
//Maybe use interrpts 
//Figure out how to display items correctly

//Display what was selected at the end
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int buttonPin = 7;
int buttonPress = 0;
int newTopic = 0;
int newItem1 = 0;
int newItem2 = 0;
int newItem3 = 0;
int i=0;

//Array of items to cycle through for Food
String items1[] = {"Fries", "Burger", "Onion Rings", "Pop", "Milkshake"};
int numItems1 = 5;

//Array of items to cycle through for Pets
String items2[] = {"Dog", "Cat", "Turtle", "Bird", "Lizard"};
int numItems2 = 5;

//Array of items to cycle through for Sports
String items3[] = {"Hockey", "Soccer", "Football", "Basketball", "Baseball"};
int numItems3 = 5;

void setup()
{
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
}

void loop()
{ 
  // Display a welcome message if button hasn't been pressed yet
  if(buttonPress == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("Welcome!");
    delay(200);
  }
  
  // If button is pressed, increment the buttonPress counter
  if(digitalRead(buttonPin) == HIGH) 
  {
    buttonPress++;
    delay(200);
  }
  
  // Display the items and let user choose one
 if(buttonPress == 1)
{
  for(i = 0; i < numItems1; i++) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(items1[i]);
    delay(1000);
    
    if(digitalRead(buttonPin) == HIGH)
    {
      newItem1 = i;
      break;
    }
  }
}

if(buttonPress == 2) 
{
  for(i = 0; i < numItems2; i++) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(items2[i]);
    delay(1000);
    
    if(digitalRead(buttonPin) == HIGH)
    {
      newItem2 = i;
      break;
    }
  }
}

if(buttonPress == 3) 
{
  for (i = 0; i < numItems3; i++) 
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(items3[i]);
    delay(1000);
    
    if(digitalRead(buttonPin) == HIGH)
    {
      newItem3 = i;
      break;
    }
  }    
}

 if(buttonPress == 4)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(items1[newItem1]);
  delay(500);
  lcd.setCursor(0, 8);
  lcd.print(items2[newItem2]);
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(items3[newItem3]);
  delay(500);
}

  
    if(buttonPress == 5)
    {
      lcd.clear();
      buttonPress = 0;
      delay(200);
    }
  }
 



