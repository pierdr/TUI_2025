void initLED() {
  WiFiDrv::pinMode(25, OUTPUT);  //define GREEN LED

  WiFiDrv::pinMode(26, OUTPUT);  //define RED LED

  WiFiDrv::pinMode(27, OUTPUT);  //define BLUE LED
}

void setLED(int r, int g, int b)
{
  WiFiDrv::analogWrite(25, g); //GREEN

  WiFiDrv::analogWrite(26, r);   //RED

  WiFiDrv::analogWrite(27, b);   //BLUE
}