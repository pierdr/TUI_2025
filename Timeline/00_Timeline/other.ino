void initLed()
{
  WiFiDrv::pinMode(25, OUTPUT); //define GREEN LED

  WiFiDrv::pinMode(26, OUTPUT); //define RED LED

  WiFiDrv::pinMode(27, OUTPUT); //define BLUE LED
}
void initSerial()
{
  Serial.begin(115200);
  Serial.println("started");
}


void setLed(float r, float g, float b)
{
  WiFiDrv::analogWrite(25,(int) g); //GREEN

  WiFiDrv::analogWrite(26,(int) r);   //RED

  WiFiDrv::analogWrite(27,(int) b);   //BLUE
}