#ifndef ACTUATOR_H
#define ACTUATOR_H

class Actuator {
    public:
        static Actuator* getInstance();
    private:
        static Actuator* _instance;
        Actuator();

};


#endif
