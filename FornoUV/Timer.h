#ifndef TIMER_H
#define TIMER_H

#include "Time.h"
#include <Arduino.h>


class Timer {
  friend void loop();
  friend void cng(Timer* t, int amt, int pos, long thresh);
  public:
    Timer();
    void setTime(int h, int m, int s);
    void start();
    Time update();
    Time rem();
    int isDone();
    int isRunning();
    ~Timer();
    void decr(int pos, int amt);
    void incr(int pos, int amt);
    int clamp(long low, long high);
    void pause();
    int isPaused();
    int isGoing();
  private:
    void change(int pos, int amt);
    Time end;
    Time passed;
    unsigned long lastMillis;
    int running;
    int finished;
    int paused;
};


#endif
