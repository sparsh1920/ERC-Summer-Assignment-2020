//Link to tinkercad: https://www.tinkercad.com/things/fa2KXthYP9L-erc-q3/editel?sharecode=Hv-fyE0t6m-8LDQuinY_sN-aUTwqhwHGb4kfw_6sdxs

//Include the irremote library
//I connected the dc motor such that multiple motors can be conencted too, a simple connection seemed too easy.
//First I tried to find the HEX value to the vol+, vol-, 0, 1, and 2 buttons on the remote by printing it in the serial monitor(the code is commented out in the loop)

#include <IRremote.h>

int bulb = 6;   
int motor = 9;
int val=0;
int num=0;
int i=0;    //This var will be used to control the brightness

const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);    //Create an object of type Irrecv
decode_results results;     //These are the decoded results of the buttons

void setup() {
  
  pinMode(bulb, OUTPUT);
  pinMode(motor, OUTPUT);
  //Serial monitor at 9600 baud rate
  Serial.begin(9600);
  //Enable the IR receiver
  irrecv.enableIRIn();       //Begin the receiving process

}

void loop() {
  
  //if (irrecv.decode(&results))
  //{
    // Print code in HEX
    //Serial.println(results.value, HEX);
    //irrecv.resume();
  //}


  if (irrecv.decode(&results))     //Move into the switch as soon as an ir code is sent i.e. button is pressed
  {
    // Print code in HEX
    switch(results.value)
    {
        case 0xFD807F:        //This is the vol+ button which will keep increasing the nits by 60 until it reaches 
         i+=60;               //its max value that is 255(8 bit)
        (i>255) ? i=255 : i=i;
        analogWrite(bulb, i);
        Serial.println(i);
        break;
        
        case 0xFD906F:        //This is the vol- button
        i=i-60;
        (i<0) ? i=0 : i=i;     
        analogWrite(bulb, i);
        Serial.println(i);
        break;
      
        case 0xFD30CF:     //This is on/off button for dc motor
        (num==0) ? num=1 : num=0;
        digitalWrite(motor, num);
        break;
      
        case 0xFD08F7:
        analogWrite(motor, 128);    //Set motor to mid speed
        break;
      
        case 0xFD8877:            //set the motor to highest speed 
        analogWrite(motor, 255);
        break;
    }
    irrecv.blink13(true);         //Blink the inbuilt led to check if it received the ir code
    irrecv.resume();             //Reset the receiver to prepare for another ir code
  }

}
