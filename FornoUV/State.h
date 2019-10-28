#ifndef STATE_H
#define STATE_H

class State {
    public:
        virtual State* execute(State* prevState) = 0;
        int getStateId();
    protected:
        virtual void printLCD() = 0;
        void setStateId(int id);
    private:
        int _id;
};






#endif
