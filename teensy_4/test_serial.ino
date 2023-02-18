#define HWSERIAL Serial1

void setup() {
  HWSERIAL.begin(9600);
}
void loop() {
  if (HWSERIAL.available() > 0) {
    String data = HWSERIAL.readStringUntil('\n');
    HWSERIAL.print("Pi sent to firmware: ");
    HWSERIAL.println(data);
  }
}