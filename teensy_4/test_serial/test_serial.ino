#define HWSERIAL Serial1

void setup() 
{
  HWSERIAL.begin(9600);
  //while (!HWSERIAL) {}
}

void loop() {
  HWSERIAL.println("Hello from Teensy Firmware!");
  delay(1000);
}