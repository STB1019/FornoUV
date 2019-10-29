#ifndef WORKING_SET_H
#define WORKING_SET_H

#define TEMPERATURE_SENSOR_GPIO 42

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

        /* SENSORS DATA */
        void readLimitSwitch();
        void readTemperature();
        bool getLimitSwitch();
        float getTemperature();
    private:
        friend class Actuator;
        static WorkingSet* _instance;
        bool _ledGStatus;
        bool _ledYStatus;
        bool _ledRStatus;
        bool _ledUVStatus;
        bool _motorStatus;
        bool _fanStatus;
        bool _limitSwitchStatus;
        float _temperature;
        WorkingSet();

        /* DEVICE STATUS */
        void setLedG(bool status);
        void setLedY(bool status);
        void setLedR(bool status);
        void setLedUV(bool status);
        void setMotor(bool status);
        void setFan(bool status);
};


#endif
