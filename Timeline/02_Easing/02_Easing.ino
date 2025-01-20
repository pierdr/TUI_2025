/**** LED ****/
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

/**** ANIMATION ****/
#include <Tween.h>
Tween::Timeline timeline;
float animValue = 0.f;


void setup() {
  
  initLED();
  timeline.mode(Tween::Mode::REPEAT_SQ);

  timeline.add(animValue)
  .init(0)
  .then<Ease::Sine>(128,1000)
  .hold(1000)
  .then<Ease::Bounce>(0,1000)
  .hold(500);

  timeline.start();
  
}

void loop() {
  timeline.update();
  delay(10);
  setLED(animValue,0,0);
  

}
