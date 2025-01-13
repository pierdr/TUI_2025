
#include <Arduino.h>
/*
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
*/

class Motor {
    public:
        Motor(int pwmPin, int dirPin, int brakePin);
        void begin();
        void setSpeed(int speed);  // -255 to 255
        int getSpeed();
        void forward(int speed);
        void backward(int speed);
        void disable();
        void enable();

    private:
        int _pwmPin;
        int _dirPin;
        int _enablePin;
        int _currentSpeed;
};


