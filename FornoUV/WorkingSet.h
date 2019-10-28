#ifndef WORKING_SET_H
#define WORKING_SET_H

#include <Arduino.h>
#include "Timer.h";

#define BUTTON_RIGHT  0
#define BUTTON_UP     1
#define BUTTON_DOWN   2
#define BUTTON_LEFT   3
#define BUTTON_SELECT 4
#define BUTTON_NONE   5

class WorkingSet {
    public:
        static WorkingSet* getInstance();

        /* DEVICE STATUS */
        bool getLedG();
        bool getLedY();
        bool getLedR();
        bool getLedUV();
        bool getEngine();
        bool getFan();
        int getButton();

        /* SENSORS DATA */
        bool getLimitSwitch();
        float getTemperature();


        /* OTHER STUFF */
        Timer* getTimer();
        void setTimer(Timer* timer);
    private:
        static WorkingSet* _instance;
        WorkingSet();

        Timer* _timer;
};

#endif
