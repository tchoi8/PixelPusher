/*

  Smoothing

  Reads repeatedly from an analog input, calculating a running average
  and printing it to the computer.  Keeps ten readings in an array and 
  continually averages them.
  
  The circuit:
    * Analog sensor (potentiometer will do) attached to analog input 0

  Created 22 April 2007
  By David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe
  http://www.arduino.cc/en/Tutorial/Smoothing
  
  This example code is in the public domain.


*/


// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 20;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A4;


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
int potpin = 3;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
 


void setup()
{
  // initialize serial communication with computer:
  Serial.begin(9600);                   
  // initialize all the readings to 0: 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;          

 
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600); 
}

void loop() {
  // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(inputPin); 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
  

  
  average = map(average, 0, 1020, 39, 179);     // scale it to use it with the servo (value between 0 and 180) 
//    average = map(average, 0, 1020, 40, 130);     // scale it to use it with the servo (value between 0 and 180) 
  
  myservo.write(average);             
 Serial.println(average);   
 delay(3);        // delay in between reads for stability            
}


