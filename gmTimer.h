#ifndef TIMER_h
#define TIMER_h

#include <Arduino.h>


class OneSecondTimer {

  public:
  
    OneSecondTimer();
    void start();
    void stop();
    int getSeconds();
    bool getSignal();
    
    static int _s;
    static bool _si;
};

#endif
