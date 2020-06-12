On one of the earlier versions the only special character I introduced was '/' which
differentiated between the message and pin. This was still creating errors on some
tasks and I wanted the master to read nothing else no empty strings or spaces. I 
wanted the master to read only one set of 20 bytes so I introduced 2 more characters.



Before introducing the p variable and the period i was facing a problem where,
 lets say I want to send a message "bheem". What it did was sent all the three 
special characters(*/@) and the message letter by letter. Master was receiving 
*(b          )/(pin)@
*(bh         )/(pin)@
*(bhe        )/(pin)@
*(bhee       )/(pin)@
*(bheem      )/(pin)@
I realized that each time the readmsg function was called it wasnt getting enough
time to read the entire message and the control was being passed onto request
fuction. So I had to create a condition which wouldnt pass over the control and
thats why I had to introduce a period and P variable. 
So now whats happening is the readmsg func is still not getting enough time to read
the entire message in one go but the request function cant deliver empty spaces as
the condition p isnt fullfilled.
The catch is if you forget to put a period the message will not be sent.

Right now the message stength is capped at 20 bytes so I tried to use sizeof(message)
to initialize the string. But what that is doing is only sending in 5 bytes of
message data. If the message is more than 5 bytes, its dropping the rest. 
This funciton is restricting the value to 5.
I had to use .length function instead of sizeof(). solved!

One more problem was that the pin I sent was limited to 7 bits only so any number 
greater than 127 would not work(as in one byte sent the first bit represents if you
 want the master to read(1) or write(0), the rest contains the data). So i converted
 the pin into a string which means each digit gets a space of 7 bits. 

This created one more issue, the while loop(in setup) passed control so fast that the monitor
didnt have enough time to read the string. So I thought of adding functions like
Serial.flush() but still, no dice. Then i thought of adding a delay of 10ms and 
then it worked! Turns out delay is needed for slave to stabilize the data.