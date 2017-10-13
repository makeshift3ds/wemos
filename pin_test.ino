void setup() {
  // put your setup code here, to run once:
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  Serial.begin(9600);
}

void loop() {

  Serial.println('1');
  digitalWrite(16, HIGH);
  delay(200);
  digitalWrite(16, LOW);
  delay(200);
}
