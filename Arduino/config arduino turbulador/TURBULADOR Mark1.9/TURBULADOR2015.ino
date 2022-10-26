
/*         Panel Controlador Turbulador

Programacion para control de ventiladores a travéz de señales PWM
INTITUTO DE FISICA, Pontificia Universidad Católica de Valparaiso
alumno: CAMILO WEINBERGER
profesor guia: DARIO GABRIEL PEREZ
año: 2015
*/
int cold=5;
int hot=3;
int valc=0;
int valh=0;
int lech=0;
int lecc=0;
// ponciometros A1 y A2
//control pin 3,5
//lectura A8 y A9-
/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 20
 * LCD Enable pin to digital pin 21
 * LCD D4 pin to digital pin 14
 * LCD D5 pin to digital pin 15
 * LCD D6 pin to digital pin 16
 * LCD D7 pin to digital pin 17
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public doma
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(20, 21, 14, 15, 16, 17);

void setup(){
  Serial.begin(9600);
  TCCR3A = 0X00; //pin2,3,5 (3,5 turb)
  TCCR3B = 0X12;
  ICR3 = 40;
  pinMode(hot,OUTPUT);
  pinMode(cold,OUTPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A8,INPUT);
  pinMode(A9,INPUT);
  

  //pantalla
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  lcd.setCursor(4, 1);
  // Print a message to the LCD.
  lcd.print("BIENVENIDO!!");
  delay(2000);
  lcd.begin(20, 4);
  lcd.setCursor(2, 1);
  lcd.print("Panel Turbulador");
  lcd.setCursor(4, 2);
  lcd.print("modelo 2015");
  delay(2000);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("PWM HOT:");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Lecture:");
  lcd.setCursor(0, 2);
  // Print a message to the LCD.
  lcd.print("PWM COLD:");
  lcd.setCursor(0, 3);
  // Print a message to the LCD.
  lcd.print("Lecture:");
}

void loop(){
  lcd.clear()
  valc = analogRead(A1)/25;
  valh = analogRead(A2)/25;
float  lech = analogRead(A8);
float  lecc = analogRead(A9);
  analogWrite(hot, valh);
  analogWrite(cold,valc);
//pantalla
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(10, 0);
  // Con. HOT:
  lcd.print(valh);
  lcd.setCursor(10, 1);
  // print the number of seconds since reset:
  lcd.print(lech);
  lcd.setCursor(10, 2);
  // Con. COlD
  lcd.print(valc);
  lcd.setCursor(10, 3);
  // print the number of seconds since reset:
  lcd.print(lecc);
}
