//Link to tinkercad: https://www.tinkercad.com/things/jBPrdI6ypnH-erc-q4/editel?sharecode=CTWbzTqa178D_Gd9unzFoxhT4gfH8F5jC6ErcFnmldw

//Some changes were made so please read readme_slave and readme_master first.

//enjoyed solving this one! 
//I created many different versions so ill try my best to recall why i did what i did.
//You can type in any pin less than or equal to 4 digits. If you input 5 or more digits 5th onwards will be read as a message.
//Also after typing in a message from slave dont forget to add a period else communication wouldnt proceed.

#include<Wire.h>   //Include the wire library for i2c communication

#define SLAVE_ADDR 9 //The second arduino board location 
String code = "";               //The pin that is going to be input in the slave, made some changes check out readme slave!
String received = "";      //The message received from slave
int message, password, end_loop = 0;         //Markers that will differentiate between the message, pin and when to end the loop

void setup() {
  Wire.begin();       //Begin transmission
  pinMode(13, OUTPUT); //The Alarm
  Serial.begin(9600);
}

void print()           //This function is the beginning of the end i.e. when all 20 bytes have been reveived
{                      //I had to put this function as a recursion and its explained why in readme
    Serial.println("Type the code:");
    int code_int = code.toInt();
    while(Serial.available()==0);
    int val = Serial.parseInt();
  if (val == code_int)
    {
        Serial.println(received);
        digitalWrite(13, LOW);
      while(1);                     //This infinite loop will halt everything and keep the message displayed in the serial monitor
    }
    else
    {Serial.println("Incorrect pin");
     digitalWrite(13, HIGH);
     print();                     //Recurse
    }
}

void loop() {
  delay(50);
   Wire.beginTransmission(SLAVE_ADDR);          //Begin transmission to slave address 
  Wire.write(0);                                //Call for the slave registery 0
  Wire.endTransmission();
  
  
  Wire.requestFrom(SLAVE_ADDR, 32);         //Request all of 32 bytes from the slave as we dont know how big the mesasge is
 
  char c;    //This will store the message letter by letter and transfer it to string
  
   while(Wire.available())          //Pass the control as soon as it receives some data
   {
      //Serial.println("Receive");
      c = Wire.read();              //Start reading the message
      if (c == '*')
      {message = 1; continue;}      //The marker * will start storing chracter bytes 

      else if (message == 1)
      {
        if (c == '/'){message = 0; password = 1; continue;}     // Stop reading chracters and start reading integers when you hit a '/'
        received += c;                                          //else store the message in reveived string
      }     

      else if (password == 1)
      {
        if (c == '@'){password = 0; end_loop = 1; continue;}    //Stop receiving data when you hit a '@'
        c+=1;                                                   //Decrypt message
        code += c;                                               //Else start reading the byte as integers
      }
   }
    if(end_loop == 1)
      {
        Serial.println("End");
        print();                      //After receving the full 20 bytes ask the user for a password
      }
}
