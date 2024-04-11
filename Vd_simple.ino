#include<Servo.h>//servo library
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>//16x2 library

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;//lcd pin = i2c pin //d = data pin

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27; // 0x3F

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
// define tcs230 pin
#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 9


Servo myservo;//set servo name, here servo name is "myservo"
//colour value storage var
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
// pushbutton pin
int button1 = 2;
// pushbutton val storage
int buttonState = 0;




void setup() {

  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);//scale pin
  pinMode(S1, OUTPUT);//scale pin
  pinMode(S2, OUTPUT);//colour o/p pin
  pinMode(S3, OUTPUT);//colour o/p pin

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  pinMode(button1, INPUT_PULLUP);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Setup Serial Monitor
  Serial.begin(9600);//baud rate//data transfer rate
  //set servo pin
  myservo.attach(10);//servo pin
  lcd.begin(16, 2);//lcd model

  // Print on first row
  lcd.setCursor(0, 0);//Row,Column
  lcd.print("Vending Machine");
  delay(500);
}

void loop() {

  buttonState = digitalRead(button1);//input state from button

  // Read Red Pulse Width
  redPW = getRedPW();



  // Read Green Pulse Width
  greenPW = getGreenPW();


  // Read Blue Pulse Width
  bluePW = getBluePW();
  delay(500);
  // Delay to stabilize sensor


  // Print output to Serial Monitor
  Serial.print("Red PW = ");
  Serial.print(redPW);
  Serial.print(" - Green PW = ");
  Serial.print(greenPW);
  Serial.print(" - Blue PW = ");
  Serial.println(bluePW);

  if (redPW >= 118 && redPW <= 148 ) //Change value for 20 taka if required
    // first range   bangabandhu ,Second range reverse bangabandhu
  {

    Serial.print("20 taka");
    lcd.setCursor(0, 1); //Row,Column.For 16x2 Row must be 0 or 1.Column is 0-9
    lcd.print("20 taka found,Take a Coke,Press Button 1"); //Change Sentence if required
    but1();
    delay(1000);

  }


  else
  {
    Serial.print("Correct Taka Not Found");
    lcd.setCursor(0, 1);
    lcd.print("Correct Taka Not Found.Please Try again");//Change Sentence if required
  }
}


// Function to read Red Pulse Widths
int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Green Pulse Widths
int getGreenPW() {

  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}

// Function to read Blue Pulse Widths
int getBluePW() {

  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}
void but1()
{
  if (buttonState == HIGH) {

    digitalWrite(LED_BUILTIN, LOW);
    myservo.write(0);
  } else {
    // turn LED on
    digitalWrite(LED_BUILTIN, HIGH);
    myservo.write(45);
  }
}
void but2()
{
  if (buttonState2 == HIGH) {

    digitalWrite(LED_BUILTIN, LOW);
    myservo2.write(0);
  } else {
    // turn LED on
    digitalWrite(LED_BUILTIN, HIGH);
    myservo2.write(45);
  }

}
