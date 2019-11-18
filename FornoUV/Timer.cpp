#include "Timer.h"

#include <Arduino.h>


// public members
Timer::Timer() {
    end = Time();
    passed = Time(0);
    running = 0;
    finished = 0;
}
Timer::Timer(int h, int m, int s) : Timer::Timer() {
    this->setTime(h, m, s);
}
Timer::Timer(Timer* timer) : Timer::Timer() {
    Time toEnd = timer->end;
    end.set(toEnd.time);
}

Timer::~Timer() {}

void Timer::setTime(int h, int m, int s) {
    long secs = 3600 * h + 60 * m + s;
    end.set(secs);
}


void Timer::decr(int pos, int amt) {
    this->change(pos, -amt);
}

void Timer::incr(int pos, int amt) {
    this->change(pos, +amt);
}

void Timer::change(int pos, int amt) {
    finished = 0;
    long inc = 0;
    switch (pos) {
        case 0:
        inc = 36000L * amt;
        break;
        case 1:
        inc = 3600L * amt;
        break;
        case 2:
        inc = 600L * amt;
        break;
        case 3:
        inc = 60L * amt;
        break;
        case 4:
        inc = 10L * amt;
        break;
        case 5:
        inc = amt;
        break;
    }

    end.time += inc;
}

int Timer::isGoing() {
    return running && !paused;
}

int Timer::clamp(long low, long high) {
    if (end.time <= low) {
        end.time = low + 1;
        return 1;
    }

    if (end.time >= high) {
        end.time = high - 1;
        return 1;
    }

    return 0;
}

void Timer::pause() {
    paused = 1;
}

void Timer::start() {
    //passed.set(0);
    lastMillis = millis();
    running = 1;
    paused = 0;
    finished = 0;
}

int Timer::isPaused() {
    return paused;
}

Time Timer::update() {
    if (!running || paused) return rem();

    unsigned long now = millis();
    //unsigned long mills = now - lastMillis;
    // if (mills > 20) {
    // }
    passed.increase(now - lastMillis);
    lastMillis = now;
    if (rem().isNull()) {
        running = 0;
        finished = 1;
        passed.set(0);
    }
    return rem();
}

Time Timer::rem() {
    if (!finished || running)
        return end - passed;

    return Time();
}

int Timer::isDone() {
    return finished;
}

int Timer::isRunning() {
    return running;
}

char* Timer::getPrintable(const char* format = "@h:@m:@s left") {
    Time remaining = this->rem();

    return remaining.getPrintable(format);
}
