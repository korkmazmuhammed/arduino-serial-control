int my_pin = 13;
int external_pin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(my_pin, OUTPUT);
  pinMode(external_pin, OUTPUT);
}

void loop() {

  if (Serial.available() >= 2) {
    int caller = Serial.read();
    long value = Serial.read();

    switch (caller) {
      case 1:
        digitalWrite(my_pin, HIGH);
        break;
      case 2:
        digitalWrite(my_pin, LOW);
        break;
      case 3:
        flashLED();
        break;
      case 4:
        fact_calculate(value);
        break;
      case 5:
        digitalWrite(external_pin, HIGH);
        delay(3000);
        digitalWrite(external_pin, LOW);
        break;
    }
  }
}

void flashLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(my_pin, HIGH);
    delay(500);
    digitalWrite(my_pin, LOW);
    delay(500);
  }
}

void fact_calculate(int num) {
  long result = 1;

  for (int i = 2; i <= num; i++) {
    result *= i;
  }

  Serial.println(result);
}
