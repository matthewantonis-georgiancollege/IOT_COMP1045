// Final Project (Digital Safe)
// Matthew Antonis
// 2023-04-19
// COMP1045-23W-21344

// Intdended purpose of the Project:
// This digital safe project is designed to simulate a secure, password-protected safe that can 
// store a virtual "bank balance" representing money held in the safe. The project uses an Arduino 
// microcontroller, an LCD screen, a keypad, and a servo motor to simulate the functionality of a real safe.

// To operate the safe: 
// Begin by entering the appropriate numbers or letters on the Keypad to both set and unlock it. 
// The maximum amount of Numbers and characters in a password is 4. 
// Press the "#" key to confirm your input.
// Next, select from the available options by choosing A, B, or C. 
// These correspond to the actions of depositing, withdrawing, or logging off, respectively.
// When making a deposit or withdrawal, use the numbers on the Keypad to indicate the desired amount. 
// The maximum amount that can be deposited or withdrawn is $999,999,999. 
// It's important to note that you won't be able to withdraw an amount greater 
// than the cash currently held in the safe.
// When using "C" the log off option. The servo will turn simulatiing the locking of the safe. 
// The LCD will then allow you to unlock it by reentering your previously set password. 
// Once again, confirm your selection by pressing the "#" key.
// The program will continue to run in a loop until you manually stop the simulation, 
// ensuring uninterrupted operation of the safe.

// Libraries 
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// Pins for the LCD screen
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);

// Define the pin for the LEDs
const int redPin = 13;
const int greenPin = 12;

// Define the pin for the Servo
const int servoPin = 8;

// Keypad configuration
// Define the number of rows and columns for the keypad
const int ROWS = 4;
const int COLS = 4;

// This 2D array represents the layout of the keypad.
// The characters correspond to the labels on the keypad buttons.
char keys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// These arrays define the Arduino pins that are connected to the keypad's row and column pins.
byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

// Create a Keypad object using the previously defined key layout and Arduino pin connections.
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo motor object used to control the lock mechanism.
Servo myservo;

// Variables to store the password and input
String password = "";
String input = "";

// Booleans to keep track of password state and access state.
bool passwordSet = false; 
bool accessGranted = false;

// Variable to keep track of the user's account balance.
long bankBalance = 0;

// Define the possible user actions using an enumeration
// This provides a way to assign names to a set of related constants
// Allows for better readability and easier maintenance for my code
// Used CHAT GPT Here to figure this out and applied this logic where applicable in my code
enum UserAction {
  NONE,     // No action selected (default state)
  DEPOSIT,  // User chooses to deposit money
  WITHDRAW, // User chooses to withdraw money
  LOG_OFF   // User chooses to log off
};

// Variable named 'action' of the type 'UserAction'
// This variable will be used to store the current user action
UserAction action = NONE;

// Setup function initializes the hardware and displays a welcome message
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  myservo.attach(servoPin);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Set a Password:");
}

// Function to print the user action menu
void printUserAction() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A:Deposit C:Off");
  lcd.setCursor(0, 1);
  lcd.print("B:Withdraw");
}

// Function to process user action input and set the action state
void processUserAction(char key) { 
  // If the user chooses to deposit (key 'A')
  if (key == 'A') {
    action = DEPOSIT;
  }
  // If the user chooses to withdraw (key 'B')
  else if (key == 'B') {
    action = WITHDRAW;
  }
  // If the user chooses to log off (key 'C')
  else if (key == 'C') {
    action = LOG_OFF;
  }
  // If the action state is set to LOG_OFF
  if (action == LOG_OFF) {
    accessGranted = false; // Set accessGranted to false, closing the access
    myservo.write(0); // Close the servo (lock)
    digitalWrite(greenPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:"); // Prompt to "Enter Password:"
    action = NONE; // Reset the action variable after logging off
  }
}

// Function to set the password
void setPassword() {
  password = input; // Store the user input as the new password
  passwordSet = true; // Set Bool True to indicate a password has been set
  input = ""; // Clear the input variable for future use
  
  // Update the LCD display to prompt the user to enter the password
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

// Function to check if the entered password is correct
void checkPassword() {
  if (input == password) {
    accessGranted = true;
    myservo.write(180); // Unlocks safe
    digitalWrite(greenPin, HIGH); // Identifies success
    digitalWrite(redPin, LOW);
    printUserAction();
  } else {
    lcd.clear();
    lcd.print("Access Denied");
    myservo.write(0); // Closses or Keeps Safe closed
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH); // Identifies Failure
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:"); // Restates to input Password
  }
  input = "";
}

// Function to perform the transaction (deposit or withdraw)
void performTransaction() {
   // Convert the input string to an integer to process the transaction amount
  long amount = input.toInt();
  
  // If the action is a deposit, add the amount to the bank balance
  if (action == DEPOSIT) {
    bankBalance += amount;
  }
  // Only processes withdraw if the requested amount is greater than or equal to the balance
  else if (action == WITHDRAW && bankBalance >= amount) {
    bankBalance -= amount;
  }
  input = ""; // Clear the input string for future use
  action = NONE; // Reset the action variable after the transaction is completed
  printUserAction();
}

// Function to handle key presses
void handleKeyPress(char key) {
  // If access is granted and there is no ongoing action (Deposit/Withdraw/Log Off)
  if (key != '*' && accessGranted && action == NONE) {
    processUserAction(key); // Determine the user action based on the key pressed ('A', 'B', or 'C')
    if (action != NONE) {
      lcd.clear();
      // If the user chooses to deposit
      if (action == DEPOSIT) {
        lcd.setCursor(0, 0);
        lcd.print("Enter Amount:");
      // If the user chooses to withdraw
      } else if (action == WITHDRAW) {
        lcd.setCursor(0, 0);
        lcd.print("Enter Amount:");
      // If the user chooses to log off
      } else if (action == LOG_OFF) {
        accessGranted = false;
        myservo.write(0);
        digitalWrite(greenPin, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
      }
    }
  // If there is an ongoing action (Deposit/Withdraw)
  } 
  else if (key != '*' && action != NONE) {
    if (key == 'A' || key == 'B' || key == 'C') {
      lcd.setCursor(0, 1);
      lcd.print("Invalid input");
      delay(2500); // Display the error message for 1 second
      
      // Clear and Re-prompt the user
      lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print("Enter Amount:");
      lcd.setCursor(0, 1);
      lcd.print("$");
      lcd.print(input);
    }
    else {
      if (input.length() < 9) { // Only allow input if the length is less than the limit
        input += key;
        lcd.setCursor(0, 1);
        lcd.print("$");
        lcd.print(input);
      } 
      else {
        lcd.setCursor(0, 1);
        lcd.print("Max length: 9");
        delay(2500);
        lcd.clear();
        lcd.setCursor(0, 0);
      	lcd.print("Enter Amount:");
        lcd.setCursor(0, 1);
        lcd.print("$");
        lcd.print(input);
      }
    }
  }
  // If access is not granted and password input is required
  else if (key != '*' && !accessGranted) {
    if (input.length() < 4) { // Only allow input if the length is less than the limit
      input += key;
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Max length: 4");
      delay(1000); 
      lcd.setCursor(0, 1);
      lcd.print(" ");
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    
    // Prompt to enter Password
    if (passwordSet) {
      lcd.print("Enter Password:");
    }
    
    // Prompt to set Password
    else {
      lcd.print("Set a Password:");
    }  
    
    // Print Hidden Key input to screen 
    lcd.setCursor(0, 1);
    for (int i = 0; i < input.length(); i++) {
      lcd.print('*');
    }
  }
}

// Display the bank balance after Withdraw and Deposit
void displayBankBalance() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bank Balance: ");
  lcd.setCursor(0, 1);
  lcd.print("$");
  lcd.print(bankBalance);
  delay(2000); 
}

// Main Loop
void loop() {
  // Store keypad input
  char key = keypad.getKey();

  if (key) {
    // If the password is not set
    if (key == '#' && !passwordSet) {
      setPassword();
    }
    // If the password is set and access is not granted
    else if (key == '#' && passwordSet && !accessGranted) {
      checkPassword();
    }
    // If access is granted and the user wants to perform a transaction (Deposit/Withdraw)
    else if (key == '#' && accessGranted && (action == DEPOSIT || action == WITHDRAW)) {
      performTransaction();
      displayBankBalance();
      printUserAction();
    }
    // Handle other key presses
    else {
      handleKeyPress(key);
    }
  }
}