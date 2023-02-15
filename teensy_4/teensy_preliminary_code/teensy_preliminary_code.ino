/*
PROTOTYPE 1 COLE J RADETICH
"I swear, I'm having fun!!! - me"
*/

//pins
const int sensorPin = 14;
const int sensor2Pin = 15;
const int ledPin = 2;
const int boardLedPin = 13;

// We'll also set up some global variables for the light level:

int lightLevel, high = 0, low = 1023;


void setup()
{
  // We'll set up the LED pin to be an output.
  // (We don't need to do anything special to use the analog input.)

  pinMode(boardLedPin, OUTPUT);
  Serial1.begin(9600);
}


void loop()
{

  //analogWrite(ledPin, 255);
  //lightLevel = analogRead(sensorPin);
  //Serial.println(lightLevel);
  //delay(100);
  //analogWrite(ledPin, 0);
  //lightLevel = analogRead(sensorPin); 
  //Serial.println(lightLevel);
  //delay(100);


  //if (Serial1.available()) 
  //{
    
  //analogWrite(boardLedPin, 0);
  //char data_rcvd = Serial.read();   // read one byte from serial buffer and save to data_rcv


  //right now these are two seperate tests:
  
  //enable on serial connnection
  analogWrite(ledPin, 255);
  lightLevel = analogRead(sensorPin);
  Serial.println(lightLevel);
  delay(100);
  analogWrite(ledPin, 0);
  lightLevel = analogRead(sensorPin); 
  Serial.println(lightLevel);
  delay(100);
  //send data


  //}
  //else
  //{
    //temp code: amber for no uart signal
    //analogWrite(boardLedPin, 255);
  //}

  //if (digitalRead(8) == HIGH) Serial.write('0');    // send the char '0' to serial if button is not pressed.
  //else Serial.write('1');                           // send the char '1' to serial if button is pressed.

}
