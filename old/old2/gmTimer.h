/**
* Quest'opera è distribuita con Licenza Creative Commons Attribuzione - 
* Non commerciale - Condividi allo stesso modo 4.0 Internazionale.
* - http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

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
