#include <LiquidCrystal.h> // includes the LiquidCrystal Library 

const int brightnessPin = 3;

const int deletePin = 8;
const int equalsPin = 9;
const int operationSelectPin = 10;
const int numberSelectPin = 11;
const int clearPin = 12;
// Note that the potentiometer is connected to A5 Pin.

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 

void setup() { 
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(brightnessPin, OUTPUT); 
  analogWrite(brightnessPin, 50);

  pinMode(clearPin, INPUT);
  pinMode(equalsPin, INPUT);
  pinMode(operationSelectPin, INPUT);
  pinMode(numberSelectPin, INPUT);

  // Startup animation:
  for (int i = 0; i < 16; i++){
    lcd.setCursor(i + 1,0);
    lcd.print(">");
    lcd.setCursor(i + 1,1);
    lcd.print(">");
  // Text is "Made by: Nabil NY Mansour"
    if (i >= 0){
      lcd.setCursor(0,1);
      lcd.print("N");
    }

    if (i >= 1){
      lcd.setCursor(1,1);
      lcd.print("a");
    }

    if (i >= 2){
      lcd.setCursor(2,1);
      lcd.print("b");
    }

    if (i >= 3){
      lcd.setCursor(3,1);
      lcd.print("i");

      lcd.setCursor(3,0);
      lcd.print("M");
    }

    if (i >= 4){
      lcd.setCursor(4,1);
      lcd.print("l");

      lcd.setCursor(4,0);
      lcd.print("a");
    }

    if (i >= 5){
      lcd.setCursor(5,0);
      lcd.print("d");
    }
    
    if (i >= 6){
      lcd.setCursor(6,1);
      lcd.print("N");

      lcd.setCursor(6,0);
      lcd.print("e");
    }

    if (i >= 7){
      lcd.setCursor(7,1);
      lcd.print("Y");
    }

    if (i >= 8){
      lcd.setCursor(8,0);
      lcd.print("b");
    }
    
    if (i >= 9){
      lcd.setCursor(9,1);
      lcd.print("M");

      lcd.setCursor(9,0);
      lcd.print("y");
    }

    if (i >= 10){
      lcd.setCursor(10,1);
      lcd.print("a");

      lcd.setCursor(10,0);
      lcd.print(":");
    }

    if (i >= 11){
      lcd.setCursor(11,1);
      lcd.print("n");
    }

    if (i >= 12){
      lcd.setCursor(12,1);
      lcd.print("s");
    }

    if (i >= 13){
      lcd.setCursor(13,1);
      lcd.print("o");
    }

    if (i >= 14){
      lcd.setCursor(14,1);
      lcd.print("u");
    }

    if (i >= 15){
      lcd.setCursor(15,1);
      lcd.print("r");
      delay(2900);
    }
    
    delay(100);
    lcd.clear();
  }
}
bool numberSelect = true;
bool Blink = true;
String toPrint = "";


String selection  = "";
void loop() {
  // Making the selection:
  int potentiometerVal = analogRead(A5);
  if (numberSelect){
    if (potentiometerVal > 900){
      selection = "9";
    } else if (potentiometerVal > 800) {
      selection = "8";
    } else if (potentiometerVal > 700) {
      selection = "7";
    } else if (potentiometerVal > 600) {
      selection = "6";
    } else if (potentiometerVal > 500) {
      selection = "5";
    } else if (potentiometerVal > 400) {
      selection = "4";
    } else if (potentiometerVal > 300) {
      selection = "3";
    } else if (potentiometerVal > 200) {
      selection = "2";
    } else if (potentiometerVal > 100) {
      selection = "1";
    } else {
      selection = "0";
    }

    // If number selection pin is pressed:
    if (digitalRead(numberSelectPin)){
      toPrint+=selection;

      delay(50);
    }

    // If operation selection pin is pressed:
    if (digitalRead(operationSelectPin)){
      numberSelect = false;

      delay(50);
    }
  } else {
    // If number selection pin is pressed:
    if (potentiometerVal > 910){
      selection = '+';
    } else if (potentiometerVal > 780) {
      selection = '-';
    } else if (potentiometerVal > 650) {
      selection = '/';
    } else if (potentiometerVal > 520) {
      selection = 'x';
    } else if (potentiometerVal > 390) {
      selection = '^';
    } else if (potentiometerVal > 260) {
      selection = 'v';
    } else {
      selection = '.';
    }
    
    if (digitalRead(operationSelectPin)){
      toPrint+=selection;

      delay(50);
    }
    
    if (digitalRead(numberSelectPin)){
      numberSelect = true;

      delay(50);
    }
  }

  // If delete pin is pressed:
  if (digitalRead(deletePin)){
    toPrint.remove(toPrint.length() - 1);
    
    delay(50);
  }

  // If clear pin is pressed:
  if (digitalRead(clearPin)){
    toPrint = "";
    
    delay(50);
  }

  // If equals pin is pressed:
  if (digitalRead(equalsPin)){
    
    // If an invalid operation is placed first:
    if (toPrint[0] == '/' || toPrint[0] == 'x' || toPrint[0] == '^' || toPrint[0] == 'v'){
      lcd.clear();
      lcd.print("INVALID EQUATION");
      toPrint = "";
      delay(3000);
    }
    
    // If an operation is placed last:
    else if (toPrint[toPrint.length() - 1] == '/' || toPrint[toPrint.length()- 1] == 'x' || toPrint[toPrint.length()- 1] == '^' || toPrint[toPrint.length()- 1] == 'v' || toPrint[toPrint.length() - 1] == '.' || toPrint[toPrint.length()- 1] == '+' || toPrint[toPrint.length()- 1] == '-'){
      lcd.clear();
      lcd.print("INVALID EQUATION");
      toPrint = "";
      delay(3000);
    } 
    else {
      float result = 0;
      bool firstValFound = false;
      char currentSelectedOperator = '+';
      char newSelectedOperator = '+';
      int secondValStartingIndex = 0;
      String secondVal = "";

      toPrint+= "+0";
      
      // Going through the equation:
      for (int i = 0; i < toPrint.length(); i++){
        // Finding first val and adding it to result:
        if (!firstValFound) {
          if (toPrint[i] == '+' || toPrint[i] == '-' || toPrint[i] == '/' || toPrint[i] == 'x' || toPrint[i] == '^' || toPrint[i] == 'v') {
            secondVal = toPrint.substring(0, i);
            result += secondVal.toFloat();
            firstValFound = true;
            currentSelectedOperator = toPrint[i];
            secondValStartingIndex = i + 1;
          }
        } 
        // If first val is found:
        else {
          // Finding the second val:
          if (toPrint[i] == '+' || toPrint[i] == '-' || toPrint[i] == '/' || toPrint[i] == 'x' || toPrint[i] == '^' || toPrint[i] == 'v') {
            secondVal = toPrint.substring(secondValStartingIndex, i);
            // Do the operation:
            if (currentSelectedOperator == '+') {
               result += secondVal.toFloat(); 
            } else if (currentSelectedOperator == '-') {
               result -= secondVal.toFloat(); 
            } else if (currentSelectedOperator == '/') {
               result /= secondVal.toFloat();
            } else if (currentSelectedOperator == 'x') {
               result *= secondVal.toFloat(); 
            } else if (currentSelectedOperator == '^') {
               result = pow(result, secondVal.toFloat());
            } else if (currentSelectedOperator == 'v') {
               result = pow(result, 1.0f/secondVal.toFloat());
            }
            currentSelectedOperator = toPrint[i];
            secondValStartingIndex = i + 1;
          }
        }
      }

      if (String(result) == " INF") {
        lcd.clear();
        lcd.print("OVERFLOW");
        toPrint = "";
        delay(3000);
      } else {
        toPrint = String(result);
      }
    }
    
    delay(50);
  }
  
  // Printing:
  lcd.clear();

  lcd.print(toPrint);
  
  if (Blink){
   lcd.print(selection);
   Blink = false;
  } else {
    Blink = true;
  }
  delay(100); 
}
