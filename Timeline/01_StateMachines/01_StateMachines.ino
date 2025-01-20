#define IDLE 0
#define BUSY 1

int state = IDLE;

#define BUTTON_PIN 4

unsigned long pressEvent = 0;

void setup() {

  initSerial();
  initPins();
}

void loop() {

  updateButton();
  updateState();
}

void changeState(int newState) {
  //this is done to change state only once
  if (state == newState) {
    return;
  }
  switch (newState) {
    case BUSY:
      Serial.println("entering BUSY state");
      pressEvent = millis();
      break;
    case IDLE:
      Serial.println("entering IDLE state");
      break;
  }
  state = newState;
}

void updateButton() {
  int buttonValue = digitalRead(BUTTON_PIN);

  delay(25);
  if (buttonValue == LOW) {
    changeState(BUSY);
  }
}
void updateState() {
  switch (state) {
    case BUSY:
      if (millis() - pressEvent > 3000) {
        changeState(IDLE);
      }
      break;
  }
}