void initSerial()
{
  Serial.begin(115200);
  Serial.println("begin");
}

void initPins()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}