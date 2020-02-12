int pelota = 7;

void setup() {
  pinMode(pelota, INPUT);
  Serial.begin(9600);
}//setup

void loop() {
  if (digitalRead(pelota) == HIGH) {
    Serial.println("victima viva");

    delay(600);
  }
  else {
    Serial.println("victima muentaaa");
    delay(600);
  }
}
