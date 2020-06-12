  #include<Wire.h>
  #define SLAVE_ADDR 9

  String message;             //This will store the message that the user want to send
  String code;             //The pin
  int p=0;          //I explained this in the readme
  int len;          // Length of the input string
  void setup()
  {
    Wire.begin(SLAVE_ADDR);


      Serial.begin(9600);
      Serial.println("Enter a pin:");
      while(Serial.available()==0);
        int counter=0;
        while(counter<4)
        {
          char c = Serial.read();
          code += c;
          delay(10);
          counter++;  
        }
      Serial.println(code);

    Serial.println("Enter the secret message");
    Wire.onRequest(request); //The array of bytes that we will send to master

  }

  void request()
  {
    readmsg();   //Read the secret message :)
        
    byte msg_to_binary[len+7];   //Convert that msg to binary which can be stored in a byte
    char a = '*';          //This will tell that master to start reading characters
    char b = '/';         //To start rading integers
    char c = '@';         //To stop reading 
    
    msg_to_binary[0] = (byte)a;       //Convert the chracter to byte
    for (int i=1; i<len+1; i++)          
    {
      msg_to_binary[i] = (byte)message.charAt(i-1)-1;     //Since for starts with 1, subtract 1 to read the entire message and -1 to encrypt message   
    }
      msg_to_binary[len+1] = (byte)b;
    for (int i=0; i<4; i++)
    {
    msg_to_binary[len+2+i] = (byte)code.charAt(i); //Append the last place of the message which contains the secret code!
    }
    msg_to_binary[len+6] = (byte)c;
    if (p){
      Serial.println("Sent.");
      Wire.write(msg_to_binary, len+7); } //Send master an array of 20 bytes
    
  }

  void readmsg()
  {

      if (Serial.available())   //Append message character by character
      {
        char c = Serial.read();
        message += c;
        if (c == '.'){
          p=1; len = message.length();
          Serial.println(message);}    //Stop appending when it hits a period. Reason for this explained in readme.
      }
    
   }

  void loop()
  {

      delay(50);

  }
