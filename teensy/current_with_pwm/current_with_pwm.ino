/*
* TEENSYv4 CODE FOR THE BALL AEROSPACE IN WATER FLUOROMETER
* COLE RADETICH 2023
*/

/*
 ███████╗██╗     ██╗   ██╗ ██████╗ ██████╗  ██████╗ 
 ██╔════╝██║     ██║   ██║██╔═══██╗██╔══██╗██╔═══██╗
 █████╗  ██║     ██║   ██║██║   ██║██████╔╝██║   ██║
 ██╔══╝  ██║     ██║   ██║██║   ██║██╔══██╗██║   ██║
 ██║     ███████╗╚██████╔╝╚██████╔╝██║  ██║╚██████╔╝
 ╚═╝     ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ 


 ╔═╗┌┐┌  ┬┌┐┌  ┬ ┬┌─┐┌┬┐┌─┐┬─┐  ┌─┐┬  ┬ ┬┌─┐┬─┐┌─┐┌┬┐┌─┐┌┬┐┌─┐┬─┐
 ╠═╣│││  ││││  │││├─┤ │ ├┤ ├┬┘  ├┤ │  │ ││ │├┬┘│ ││││├┤  │ ├┤ ├┬┘
 ╩ ╩┘└┘  ┴┘└┘  └┴┘┴ ┴ ┴ └─┘┴└─  └  ┴─┘└─┘└─┘┴└─└─┘┴ ┴└─┘ ┴ └─┘┴└─
*/

#define HWSERIAL Serial1 //this makes it easier for us to reference the TX/RX, since serial as a keyword here references USB OTG mode and not RX/Tx
//CROSS CHECK THESE WITH HARDWARE VALUES, ENSURE THAT WE ARE REFERENCING THE CORRECT DIODES
const int sensorPin = 14; //sensor0 (hamamatsu, not filtered)
const int sensor1Pin = 15; //sensor1 (hammamatsu, filtered)
const int ledPin = 2; //driving LEDs, PWM**
const int boardLedPin = 13; //little orange fella
const int opAmp = 18; //OP Amp

int ret1, ret2, pwm_on, timestep; //variables
//extra pin info: https://www.pjrc.com/store/teensy40.html#pins
//setup
void setup() 
{
  //init TX/RX pins
  HWSERIAL.begin(115200);
  HWSERIAL.setTimeout(100);
  //init LED pin for PWM output
  pinMode(opAmp, OUTPUT);
  pinMode(ledPin, OUTPUT);
  //init debug LED (this MUST remain off for the final unit, both for battery life purposes and light pollution)
  //pinMode(boardLedPin, OUTPUT);
  //init pwm flag. this is off since the device is off
  pwm_on = 0;
}

void loop() 
{
  String delim = ", ";
  //wait for initial ack. This will allow some nonsense data to come through, and will allow our device to have its desired delay
  if(HWSERIAL.available() > 0) 
  {
    //begin ack
    String data = HWSERIAL.readStringUntil('\n');
    //send ack back w the GOT header, handshake complete!
    HWSERIAL.print("GOT ");
    HWSERIAL.println(data);

    //while loop to initiate transfer. a response back from the Pi will break this loop and put everything back to waiting mode.
    while(data == "BEGIN TRANSFER")
    {
      if(pwm_on == 0)
      {
        digitalWrite(opAmp, HIGH);
        analogWrite(ledPin, 127);
        analogWriteFrequency(ledPin, 1000);
        pwm_on = 1;
      }

      //We are transferring! begin transfer.
      ret1 = analogRead(sensorPin);
      ret2 = analogRead(sensor1Pin); 
      HWSERIAL.println(delim + ret1 + delim + ret2);
      //this shows the Pi has responded and wants data to stop. shut off pwm and wait for next ack.
      if(HWSERIAL.available() > 0)
      {
        digitalWrite(opAmp, LOW);
        analogWrite(ledPin, 0);
        pwm_on = 0;
        timestep = 0;
        data = HWSERIAL.readStringUntil('\n');
      }
    }
  }
}