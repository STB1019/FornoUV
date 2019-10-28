#ifndef WORKING_SET_H
#define WORKING_SET_H

class WorkingSet {
    public:
        static WorkingSet* getInstance();
    private:
        static WorkingSet* _instance;
        WorkingSet();

};


#endif
