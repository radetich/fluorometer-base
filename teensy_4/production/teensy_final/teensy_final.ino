#define HWSERIAL Serial1 // this makes it easier for us to reference the TX/RX, since serial as a keyword here references USB OTG mode and not RX/Tx
const int sensorPin = 14; //sensor0 (hamamatsu)
const int sensor1Pin = 15; //sensor1 (hammamatsu, probably emission return. Check this.)
const int ledPin = 2; //driving LEDs
const int boardLedPin = 13; //little orange fella

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

void loop() {
  if (HWSERIAL.available() > 0) {
    String data = HWSERIAL.readStringUntil('\n');
    HWSERIAL.print("Pi sent to firmware: ");
    HWSERIAL.println(data);
  }
}


/* old led code
  analogWrite(ledPin, 255);
  lightLevel = analogRead(sensorPin);
  Serial.println(lightLevel);
  delay(100);
  analogWrite(ledPin, 0);
  lightLevel = analogRead(sensorPin); 
  Serial.println(lightLevel);
  delay(100);
  */