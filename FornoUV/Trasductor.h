#ifndef TRASDUCTOR_H
#define TRASDUCTOR_H

#include <Arduino.h>

#define BUTTON_RIGHT  0
#define BUTTON_UP     1
#define BUTTON_DOWN   2
#define BUTTON_LEFT   3
#define BUTTON_SELECT 4
#define BUTTON_NONE   5

#define PIN_BUTTON  A0
#define PIN_TEMP_SENSOR 42

class Trasductor {
    public:
        static Trasductor* getInstance();

        /* SENSORS READING */
        void readLimitSwitch();
        void readTemperature();
        void readButton();

        /* SENSORS GETTERS */
        bool getLimitSwitch();
        float getTemperature();
        int getButton();
    private:
        static Trasductor _instance;
        Trasductor();
        int _button;
        bool _limitSwitchStatus;
        float _temperature;
        int _buttonHeld;

};


#endif
