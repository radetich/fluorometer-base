/*
* TEENSYv4 CODE FOR THE BALL AEROSPACE IN WATER FLUOROMETER
* VERSION 3.2
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

#define HWSERIAL Serial1 //this makes it easier for us to reference the TX/RX, since serial as a keyword here references USB mode and not RX/TX
const int sensorPin = 14; //sensor0 (hamamatsu)
const int sensor1Pin = 15; //sensor1 (hammamatsu)
const int ledPin = 2; //driving LEDs, PWM**
const int boardLedPin = 13; //little orange fella
const int opAmp = 18; //Operational Amplifier to ensure our valus are from about 500-1000 ish

// variables for analog read and boolean values
int ret1, ret2;
int pwm_on, timestep;

// timing code
unsigned long previousMillis = 0UL;
unsigned long interval = 10UL;

//extra pin info: https://www.pjrc.com/store/teensy40.html#pins

//setup
void setup() 
{
  //init TX/RX pins
  HWSERIAL.begin(115200);
  HWSERIAL.setTimeout(1000);
  //init output pins
  pinMode(opAmp, OUTPUT);
  pinMode(ledPin, OUTPUT);
  //init debug LED (this MUST remain off for the final unit, both for battery life purposes and light pollution)
  pinMode(boardLedPin, OUTPUT);
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
    //ack response
    if(data == "BEGIN TRANSFER")
    {
      //turn on operational amp, and set PWM frequency for LEDs
      digitalWrite(opAmp, HIGH);
      digitalWrite(boardLedPin, HIGH);
      analogWrite(ledPin, 127);
      analogWriteFrequency(ledPin, 1000);
      pwm_on = 1;

      //this checks to see if the Pi has said stop sending yet
      //while loop to initiate transfer. a response back from the Pi will break this loop and put everything back to waiting mode.
      while(HWSERIAL.available() < 1)
      {
        unsigned long currentMillis = millis();
        if(currentMillis - previousMillis > interval)
        {
          ret1 = analogRead(sensorPin);
          ret2 = analogRead(sensor1Pin); 
          HWSERIAL.println(ret1 + delim + ret2);
          previousMillis = currentMillis;
        }
      }
      digitalWrite(opAmp, LOW);
      digitalWrite(boardLedPin, LOW);
      analogWrite(ledPin, 0);
      pwm_on = 0;
      timestep = 0;
      data = HWSERIAL.readStringUntil('\n');
    }
  }
}