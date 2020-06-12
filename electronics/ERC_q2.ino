//Link to tinkercad:  https://www.tinkercad.com/things/kQKTFsRlOth-erc-q2/editel?sharecode=Scaf8EvC-HMcFqGuWIxErKrQ_-i-0-AYVdFTFWsaYzg

//The decoder will require less wiring to the arduino. 
//Since there was no 3 digit 7 segment display on tinkercad I use the 1 digit display and created a delay after each digit was displayed
//In the circuit the latch enable is pulled to ground as we want the display to change else if it pulled to the supply the display will remain constant
//We have to also set the display to common cathode
//The lamp test and blanking pin are pulled high as we dont have any use of it in this project
//Connect the potentiometer to analog
#include<Servo.h>     //Include the servo library
Servo servo;          //Create an object servo of type servo

int servopin = 9;
int inp_pin[4] = {2,3,4,5};
int potpin = A2;                          //Analog pins dont need to be set as input while digital need to be set as input/output as they can do both

void setup() {
  servo.attach(servopin);   //This takes care of pinmode
 Serial.begin(9600);
  for (int i=0; i<4; i++)
    {
        pinMode(inp_pin[i], OUTPUT);
      digitalWrite(inp_pin[i],LOW);
    }
}

void digit(int num)              //Initialize the highs and lows correspoding to the digits
{                                //The values are given in the truth table in the data sheet
   if (num==0){
  for (int i=3; i>=0; i++)
  {
    digitalWrite(inp_pin[i], 0);
  }
    }
  
  else if (num==1){
   digitalWrite(inp_pin[3],0);
   digitalWrite(inp_pin[2],0);
   digitalWrite(inp_pin[1],0);
   digitalWrite(inp_pin[0],1);
    }

  else if (num==2){
    digitalWrite(inp_pin[3],0);
    digitalWrite(inp_pin[2],0);
    digitalWrite(inp_pin[0],0);  
    digitalWrite(inp_pin[1],1);
    }

  else if (num==3){
  digitalWrite(inp_pin[3],0);
  digitalWrite(inp_pin[2],0);
  digitalWrite(inp_pin[1],1);
  digitalWrite(inp_pin[0],1); 
    }

  else if (num==4){
    digitalWrite(inp_pin[3],0);
    digitalWrite(inp_pin[1],0);
    digitalWrite(inp_pin[0],0);
    digitalWrite(inp_pin[2],1);
    }

  else if (num==5){
    digitalWrite(inp_pin[3],0);
    digitalWrite(inp_pin[2],1);
    digitalWrite(inp_pin[1],0);
    digitalWrite(inp_pin[0],1);
    }

  else if (num==6){
    digitalWrite(inp_pin[3],0);
    digitalWrite(inp_pin[0],0);  
    digitalWrite(inp_pin[2],1);
    digitalWrite(inp_pin[1],1);
      }

  else if (num==7){
    digitalWrite(inp_pin[2],1);
    digitalWrite(inp_pin[1],1);
    digitalWrite(inp_pin[0],1);
    digitalWrite(inp_pin[3],0);
    }

  else if (num==8){
    digitalWrite(inp_pin[2],0);
    digitalWrite(inp_pin[1],0);
    digitalWrite(inp_pin[0],0);
    digitalWrite(inp_pin[3],1);
    }

  else if (num==9){
    digitalWrite(inp_pin[2],0);
    digitalWrite(inp_pin[0],1);
    digitalWrite(inp_pin[3],1);
    digitalWrite(inp_pin[1],0);
  }
  delay(1000);
}

void loop() {
  int arr[3] = {0,0,0};   //This where the digits of the angle will be stored
  int i=0;
  int pot = analogRead(potpin);
  int val = map(pot, 0,1023,0,180);     //Map the values from  0 to 180 degrees of the 10 bit analog input
    servo.write(val);               //Rotate the servo accordingly
  Serial.println(val);
  while(val>0)          //Put the digits into an array
  {
    int num = val%10;
    arr[i] = num;
    Serial.println(arr[i]);
    i++;
    val /=10;
  }
  if (pot>=100)
  {for (i=2;i>=0;i--){digit(arr[i]);}}    //Call the function that displays the digit
  else
  {for (i=1;i>=0;i--){digit(arr[i]);}}   
}
