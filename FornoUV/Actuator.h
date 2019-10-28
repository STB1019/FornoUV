#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {
    public:
        static Actuator* getInstance();

        void setLedG(bool status);
        void setLedY(bool status);
        void setLedR(bool status);
        void setLedUV(bool status);
        void setEngine(bool status);
        void setFan(bool status);
    private:
        static Actuator* _instance;
        Actuator();

};


#endif
