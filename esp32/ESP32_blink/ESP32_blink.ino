const int ledPin = 15; // GPIO pin connected to red LED
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  delay(1000); // delay 1 second
  buttonState ^= 1;
  digitalWrite(ledPin, buttonState);
  Serial.println("LED toggled");
}
