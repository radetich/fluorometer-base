#define HWSERIAL Serial1 // this makes it easier for us to reference the TX/RX, since serial as a keyword here references USB OTG mode and not RX/Tx
const int sensorPin = 14; //sensor0 (hamamatsu)
const int sensor1Pin = 15; //sensor1 (hammamatsu, probably emission return. Check this.)
const int ledPin = 2; //driving LEDs
const int boardLedPin = 13; //little orange fella

int emmReturn, filReturn;

//extra pin info: https://www.pjrc.com/store/teensy40.html#pins

//setup
void setup() 
{
  //init TX/RX pins
  HWSERIAL.begin(115200);
  HWSERIAL.setTimeout(100);
  //init debug LED (maybe turn this off for production? or leave it. Could be useful)
  pinMode(boardLedPin, OUTPUT);
}

void loop() 
{
  //make sure we are at 0 for LED
  analogWrite(boardLedPin, 0);
  analogWrite(ledPin, 0);
  //wait for initial ack
  if (HWSERIAL.available() > 0) 
  {
    String data = HWSERIAL.readStringUntil('\n');
    //send ack back w some extra
    HWSERIAL.print("GOT ");
    HWSERIAL.println(data);
    while(data == "BEGIN TRANSFER")
    {
      analogWrite(boardLedPin, 255);
      //We are transferring! begin transfer.
      //turn led on
      analogWrite(ledPin, 255);
      //record values from sensor
      emmReturn = analogRead(sensorPin);
      HWSERIAL.print("EMM ");
      HWSERIAL.println(emmReturn);
      filReturn = analogRead(sensor1Pin); 
      HWSERIAL.print("FIL ");
      HWSERIAL.println(filReturn);
      //wait a lil so we can see the action
      delay(10);
      //turn the led off
      analogWrite(ledPin, 0);
      //wait a lil so we can see the action
      delay(10);
      if (HWSERIAL.available() > 0)
      {
        data = HWSERIAL.readStringUntil('\n');
        analogWrite(boardLedPin, 0);
      }
    }
  }
}