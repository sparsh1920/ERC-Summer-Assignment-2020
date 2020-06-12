(Note: Made a change in the code so I no longer nead to send constant 20 bytes)

As i explained in the slave readme I hadnt compartmentalized the code into 3 
characters before. This made the code more friendly and readable.

The problem I was facing here was master was reading empty spaces as well. And if
I was late to type in a message in slave then upon entering the pin, master would
display 20 empty spaces proportional to the amount of time it took me to type in a 
message from the slave.

Even after debugging that there was this problem where after reveiving all 20 bytes
it was still receiving the same message and appending it to the string
So the display would be so: bheembheembheembheem
Thats when I introduced recursion in the print function so that the control wouldnt
pass back to loop where it kept duplicating the message. So essentially whats
happening now is that even if the slave is sending a message the master woudlnt
be reading it and is stuck in an infinite loop. The master only accepts the 20 bytes
which have the special characters henceforth it stops reading.
