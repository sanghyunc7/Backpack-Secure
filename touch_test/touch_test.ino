void setup() {
  pinMode(12, INPUT); //touch sensor 0
  pinMode(14, INPUT); //touch sensor 1
  pinMode(27, OUTPUT); //Buzzer output
 

  Serial.begin(9600);


  
}
void loop() {
  if (digitalRead(14) == HIGH) {
      digitalWrite(27, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("hjk"); 
    delay(500);
    digitalWrite(27, LOW);
    
  }
}
