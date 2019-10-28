#ifndef WORKING_SET_H
#define WORKING_SET_H

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

        /* SENSORS DATA */
        bool getLimitSwitch();
        float getTemperature();
    private:
        static WorkingSet* _instance;
        WorkingSet();
};


#endif
