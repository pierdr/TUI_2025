/* 
 * Tangible User Interface class - CIID
 * written by Pierluigi Dalla Rosa (www.pierdr.com)
 * Teaching with Massimo Banzi and Jose Chavarria
 * 
 * This sketch reads the position of your motorized fader.
 * It's like having a digital ruler that constantly measures
 * where your fader is. The values go from 0 to 1023.
 */

void initSerial()
{
  Serial.begin(115200);
  Serial.println("Motor test - Fader");
}

void setup() {
  // put your setup code here, to run once:
  initSerial();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A2));


}
