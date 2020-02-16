//set board to esp32 dev mode
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
const char* ssid = "dandannoodles";
const char* password =  "carinaisanalcoholic";
AsyncWebServer server(80);
int relayPin = 23;
bool alarm_go = false;

const int set_password[4] = {1, 2, 1, 2};
const int allowed_attempts = 3;

void setup() {
  pinMode(12, INPUT); //touch sensor 0
  pinMode(14, INPUT); //touch sensor 1
  pinMode(27, OUTPUT); //Buzzer output
  pinMode(4, INPUT); //Zipper State (closed or open) (HIGH or LOW)
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());

  server.on("/alarm", HTTP_GET, [](AsyncWebServerRequest * request) {

    if (alarm_go) {
      request->send(200, "text/plain", "open");
    }

  });

  server.on("/locate/bag", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Your bag is located at St.DanDan");
  });

  server.on("/dismiss", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "ok");
    digitalWrite(relayPin, LOW);
  });

  server.begin();
}

void check_backpack_state(bool pass) {
  int val_zipper = digitalRead(4);

  if (!pass && val_zipper == LOW) {
    //Set off Alarm
    alarm();

    Serial.println(val_zipper);
  }
}

void get_input(int *received, bool pass) {

  int i = 0;
  while (i < 4) {
    check_backpack_state(pass);

    int val_tsensor1 = digitalRead(12);
    int val_tsensor2 = digitalRead(14);

    if (val_tsensor1 == HIGH && val_tsensor2 == LOW) {
      received[i] = 1;

      Serial.println("twelve");
      i++;
      delay(200);
    } else if (val_tsensor1 == LOW && val_tsensor2 == HIGH) {
      received[i] = 2;
      Serial.println("fourteen");
      i++;
      delay(200);
    } else {
      continue;
    }
  }
}

void alarm() {
  alarm_go = true;
  Serial.println("Alarm");
  for (int n = 0; n < 15; n++) {
    digitalWrite(27, HIGH);   //Buzzer
    delay(100);
    digitalWrite(27, LOW);
    delay(100);
  }
}

void loop() {


  int incorrect_attempts = 0;
  bool pass = false;
  bool fail = false;
  for (int j = 0; j < allowed_attempts; j++) {

    int received[4];
    get_input(received, pass);


    for (int k = 0; k < 4; k++) {
      if (received[k] == set_password[k]) {
        continue;
      } else {
        fail = true;
      }
    }

    if (!fail) {
      pass = true;
    }
    if (pass) {
      break;
    }
    //set warning light to indicate incorrect password typed
    Serial.println(j);
  }

  if (!pass) {
    //set off alarm
    alarm();
  } else {
    //let user open backpack without triggering alarm
    //turn on green LED
  }
}
