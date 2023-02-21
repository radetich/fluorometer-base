#define HWSERIAL Serial1 // this makes it easier for us to reference the TX/RX, since serial as a keyword here references USB OTG mode and not RX/Tx
const int sensorPin = 14; //sensor0 (hamamatsu)
const int sensor1Pin = 15; //sensor1 (hammamatsu, probably emission return. Check this.)
const int ledPin = 2; //driving LEDs, PWM**
const int boardLedPin = 13; //little orange fella

int emmReturn, filReturn, pwm_on;

//extra pin info: https://www.pjrc.com/store/teensy40.html#pins

//setup
void setup() 
{
  //init TX/RX pins
  HWSERIAL.begin(115200);
  HWSERIAL.setTimeout(100);
  //init debug LED (maybe turn this off for production? or leave it. Could be useful)
  //pinMode(boardLedPin, OUTPUT);
}

void loop() 
{
  //make sure we are at 0 for LED, set PWM flag value to 0
  //analogWrite(boardLedPin, 0);
  analogWrite(ledPin, 0);
  pwm_on = 0;
  //wait for initial ack. This will allow some nonsense data to come through
  if (HWSERIAL.available() > 0) 
  {
    String data = HWSERIAL.readStringUntil('\n');
    //return command to pi. this is for debugging.
    //HWSERIAL.print("Pi sent to firmware: ");
    //HWSERIAL.println(data);

    //send ack back w the GOT header, handshake complete!
    HWSERIAL.print("GOT ");
    HWSERIAL.println(data);
    while(data == "BEGIN TRANSFER")
    {
      if(pwm_on == 0)
      {
        //turn led on and set flag variable. This allows us to begin at 100% of our 4 KHz PWM and remain at that through capture.
        analogWrite(ledPin, 255);
        pwm_on = 1;
      }
      //orange debug light
      //analogWrite(boardLedPin, 255);
      //We are transferring! begin transfer.

      //record values from sensor until HWSERIAL responds to stop...
      emmReturn = analogRead(sensorPin);
      HWSERIAL.print("EMM ");
      HWSERIAL.println(emmReturn);
      filReturn = analogRead(sensor1Pin); 
      HWSERIAL.print("FIL ");
      HWSERIAL.println(filReturn);
      if (HWSERIAL.available() > 0)
      {
        data = HWSERIAL.readStringUntil('\n');
      }
    }
    //redundent sometimes but keeps LED off if we are stuck in a recieving loop on the pi side. We don't want to drain the battery in this scenario. The Pi should get itself back on track.
    //analogWrite(boardLedPin, 0);
    analogWrite(ledPin, 0);
    pwm_on = 0;
  }
}