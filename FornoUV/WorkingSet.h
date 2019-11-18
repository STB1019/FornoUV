#ifndef WORKING_SET_H
#define WORKING_SET_H

#define TEMPERATURE_SENSOR_GPIO 42
#include <Arduino.h>
#include "Timer.h";

#define BUTTON_RIGHT  0
#define BUTTON_UP     1
#define BUTTON_DOWN   2
#define BUTTON_LEFT   3
#define BUTTON_SELECT 4
#define BUTTON_NONE   5

#define PIN_BUTTON  A0

class WorkingSet {
    public:
        static WorkingSet* getInstance();

        /* DEVICE STATUS */
        bool getLedG();
        bool getLedY();
        bool getLedR();
        bool getLedUV();
        bool getMotor();
        bool getFan();

        /* SENSORS READING */
        void readLimitSwitch();
        void readTemperature();
        void readButton();

        /* SENSORS GETTERS */
        bool getLimitSwitch();
        float getTemperature();
        int getButton();


        /* OTHER STUFF */
        Timer* getTimer();
        void createTmpTimer();
        Timer* getTmpTimer();
        void confirmTmpTimer();
        void rejectTmpTimer();

        float getTargetTemp();
        void createTmpTargetTemp();
        float getTmpTargetTemp();
        void confirmTmpTargetTemp();
        void changeTmpTargetTemp(int amt);
    private:
        friend class Actuator;
        static WorkingSet* _instance;
        bool _ledGStatus;
        bool _ledYStatus;
        bool _ledRStatus;
        bool _ledUVStatus;
        bool _motorStatus;
        bool _fanStatus;
        int _button;
        bool _limitSwitchStatus;
        float _temperature;
        Timer* _timer;
        Timer* _tempTimer;
        int _targetTemp;
        int _tempTargetTemp;
        int _buttonHeld = BUTTON_NONE;
        WorkingSet();

        /* DEVICE STATUS */
        void setLedG(bool status);
        void setLedY(bool status);
        void setLedR(bool status);
        void setLedUV(bool status);
        void setMotor(bool status);
        void setFan(bool status);
        void setButton(int status);
};

#endif
