/** ---------------------------------- ANIMATION ---------------------------------- **/
#include <Tween.h>
Tween::Timeline timeline;
float animValue = 0;


/** ---------------------------------- LED ---------------------------------- **/
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

void setup() {
  
  initSerial();
  initLed();


  timeline.clear();

  timeline.mode(Tween::Mode::REPEAT_SQ);

    
  timeline.add(animValue)
        .init(0)
        .then(128, 1000)
        .hold(1000)
        .then(0, 500)
        .hold(1500);

     
      timeline.start();


}

void loop() {
  timeline.update();
  setLed((int)animValue,0,0);
  delay(10);
  Serial.println(animValue);
}
