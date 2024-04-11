#include<Servo.h>
#include <Wire.h>
// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Define LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

// Define I2C Address - change if reqiuired
const int i2c_addr = 0x27;

LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 9

// Variables for Color Pulse Width Measurements
Servo myservo;//set servo name, here servo name is "myservo"
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
int button1 = 2;
int button2 = 3;
int buttonState = 0;
int buttonState2 = 0;
int ir = 1;
int ir_val = 0;

Servo myservo2;
void setup() {

  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(ir, INPUT);
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  // Set Pulse Width scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Setup Serial Monitor
  Serial.begin(9600);
  //set servo pin
  myservo.attach(10);
  lcd.begin(16, 2);
myservo2.attach(11);
  // Print on first row
  lcd.setCursor(0, 0);
  lcd.print("Vending Machine");
}

void loop() {
  ir_val = digitalRead(ir);
  buttonState = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  // Read Red Pulse Width
  redPW = getRedPW();
  // Delay to stabilize sensor
  delay(2000);

  // Read Green Pulse Width
  greenPW = getGreenPW();
  // Delay to stabilize sensor
  delay(2000);

  // Read Blue Pulse Width
  bluePW = getBluePW();
  // Delay to stabilize sensor
  delay(2000);

  // Print output to Serial Monitor
  Serial.print("Red PW = ");
  Serial.print(redPW);
  Serial.print(" - Green PW = ");
  Serial.print(greenPW);
  Serial.print(" - Blue PW = ");
  Serial.println(bluePW);
  if(ir_val==LOW)
  {
  if (redPW >= 310 && redPW <= 330 || redPW >= 250 && redPW <= 270 )//Change value for 20 taka if required
                                                                     // first range   bangabandhu ,Second range reverse bangabandhu
  {
  
    Serial.print("20 taka");
    lcd.setCursor(0, 1); //Row,Column.For 16x2 Row must be 0 or 1.Column is 0-9
    lcd.print("20 taka found,Take a Coke,Press Button 1"); //Change Sentence if required
    but1();

 
  }
  else if (redPW >= 280 && redPW <= 300)//Change value for 20 taka if required
  {
    Serial.print("Please insert Reverse Side of the taka or insert correct taka");
    lcd.setCursor(0, 1); //Row,Column.For 16x2 Row must be 0 or 1.Column is 0-9
    lcd.print("Please insert Reverse Side of the taka or insert correct taka");//Change Sentence if required
    
  }
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
  delay(60000);
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
