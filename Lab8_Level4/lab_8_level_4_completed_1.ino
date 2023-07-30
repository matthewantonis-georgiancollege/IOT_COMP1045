// Lab 8 Level 4 Completed
// Matthew Antonis
// 2023-03-09

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int yesPin = 7;
int noPin = 8;

//Array for Questions
String questions[] = {"Is it snowing?", "Like sports?", "Like chocolate?", "Like spicy food?", "Like horror?"};
int numQuestions = 5;

//Counter for Yes and No answers
int yesCount = 0;
int noCount = 0;

void setup()
{
  pinMode(yesPin, INPUT);
  pinMode(noPin, INPUT);
  lcd.begin(16, 2);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Yes: Button A");
  lcd.setCursor(0, 1);
  lcd.print("No: Button B");

  delay(3000); 

  for (int i = 0; i < numQuestions; i++)
  {
    askQuestion(i);
  }

  displayResults();


  while (digitalRead(yesPin) != HIGH && digitalRead(noPin) != HIGH)
  {
    delay(10); 
  }


  yesCount = 0;
  noCount = 0;
  delay(1000); 
}

void askQuestion(int questionIndex)
{
  bool answered = false;

  while (!answered)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(questions[questionIndex]);

    if (digitalRead(yesPin) == HIGH)
    {
      yesCount++;
      answered = true;
      delay(500);
    }
    else if (digitalRead(noPin) == HIGH)
    {
      noCount++;
      answered = true;
      delay(500); 
    }
    delay(200); 
  }
}

void displayResults()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Yes: " + String(yesCount));
  lcd.setCursor(0, 1);
  lcd.print("No: " + String(noCount));
  delay(5000); 
}




