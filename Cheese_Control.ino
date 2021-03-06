//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include "DHT.h"

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int myNum = 50;
#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}
 
void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("CURR TEMP      ");
 pinMode(1,OUTPUT); // print a simple message
 pinMode(2, OUTPUT);
}
  
void loop()
{
  float myTemp = dht.readTemperature(true);
  float myHumid = dht.readHumidity();
 lcd.setCursor(12,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(myNum);      // display seconds elapsed since power-up
 lcd.setCursor(12,0);
 lcd.print(myTemp);
 if (myTemp > myNum) {
   digitalWrite(1, HIGH);
 }
 else {
   digitalWrite(1, LOW);
 }
 if (myHumid < 80) {
   digitalWrite(2, HIGH);
 }
 else {
   digitalWrite(2, LOW);
 }
  
 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons
 
 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("OFF ");
     pinMode(10, OUTPUT);
     digitalWrite(10,LOW);
     break;
     }
   case btnLEFT:
     {
     lcd.print("ON   ");
     pinMode(10, INPUT);
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     myNum = myNum++;
     delay(250);
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     myNum = myNum - 1;
     delay(250);
     break;
     }
   case btnSELECT:
     {
     lcd.setCursor(0,0);
     lcd.print("HUMIDITY ");
     lcd.setCursor(12,0);
     lcd.print(myHumid); 
     delay(1000);
     lcd.setCursor(0,0);
     lcd.print("CURR TEMP");
     break;
     }
     case btnNONE:
     {
     lcd.print("SET TEMP  ");
     break;
     }
 }
 
}
