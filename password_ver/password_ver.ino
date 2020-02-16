//set board to esp32 dev mode

  const int set_password[4] = {1, 2, 1, 2};
  const int allowed_attempts = 3;
  
void setup() {
  pinMode(12, INPUT); //touch sensor 0
  pinMode(14, INPUT); //touch sensor 1
  pinMode(27, OUTPUT); //Buzzer output


  Serial.begin(9600);




}
void loop() {

  
  int received[4];
  int i = 0;
  while (i < 4) {
    int val_tsensor1 = digitalRead(12);
    int val_tsensor2 = digitalRead(14);

    if (val_tsensor1 == HIGH && val_tsensor2 == LOW) {
      received[i] = 1;
      Serial.println(i);
      i++;
      delay(200);
    } else if (val_tsensor1 == LOW && val_tsensor2 == HIGH) {
      received[i] = 2;
      Serial.println(i);
      i++;
      delay(200);
    } else {
      continue;
    }
  }


  int incorrect_attempts = 0;
  bool correct = true;
  for (int j = 0; j < allowed_attempts; j++) {
    for (int k = 0; k < 4; k++) {
      if (received[k] == set_password[k]) {
        continue;
      } else {
        correct = false;
      }
    }
    if (correct) {
      break;
    }
    //set warning light to indicate incorrect password typed

  }

  if (!correct) {
    //set off alarm
    Serial.println("Alarm");
    for (int n = 0; n < 15; n++) {
      digitalWrite(27, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);
      digitalWrite(27, LOW);
      delay(100);
    }
  } else {
    //turn on green LED
  }
}
