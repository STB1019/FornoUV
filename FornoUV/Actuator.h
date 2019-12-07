#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

class Actuator {
    public:
        static Actuator* getInstance();
        void inhibitFromInterrupt(bool inhibite);
        bool isInhibitedByInterrupt();

        /* DEVICE GETTERS */
        bool getLedG();
        bool getLedY();
        bool getLedR();
        bool getLedUV();
        bool getMotor();
        bool getFan();

        /* DEVICE SETTERS */
        void setLedG(bool status);
        void setLedY(bool status);
        void setLedR(bool status);
        void setLedUV(bool status);
        void setMotor(bool status);
        void setFan(bool status);
    private:
        static Actuator _instance;
        Actuator();
        bool _inhibitedByInterrupt;
        bool _ledGStatus;
        bool _ledYStatus;
        bool _ledRStatus;
        bool _ledUVStatus;
        bool _motorStatus;
        bool _fanStatus;

};


#endif
