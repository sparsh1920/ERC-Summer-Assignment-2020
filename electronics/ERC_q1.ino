//https://www.tinkercad.com/things/cBmpUbPXdXv-erc-q1/editel?sharecode=-b1w7d1-eqHGqvON3oMreG3wbefH2RzVsaPkrLIbYg8  Link to tinkercad

//Contrast pin is connected to the potentiometer to contorl the brightness
//Read/Write is pulled to ground 
//2,3 of arduino are connected to register and enable rest all are the data pins.
//To caclulate the unknown resistance we connect a known resistance and the unknown in series and we connect them to the 
//analog pin of the ic to read the voltage of the junction
//Add a 1k resistance to the led's anode or cathode too to reduce the supplied current.
//Include the library liquid crystal(by Frank de brabandar) that makes it easier to use the lcd 

#include <LiquidCrystal.h>
LiquidCrystal  lcd(2,3,4,5,6,7);

int respin = A5;


void setup()
{
  lcd.begin(16,2);     //Initialise the number of columns and rows to be used with the display
  Serial.begin(9600);
}

void loop()
{
  float val = analogRead(respin); //Reference res is 1K

  val = val/1023.0;     //Convert the 10bit value read by arduino into actual value i.e. in voltage
   float r = 1000 * val/(5.0-val);      //Deriving the resistance using loop law 
  lcd.setCursor(0,0);     //Sets the position where we want to display the output
  lcd.print("Res is: ");  
  lcd.print(r);
  
  delay(100);
    lcd.clear();
}
