#ifndef TIME_H
#define TIME_H

#include <Arduino.h>

class Time {
  friend class Timer;
  friend void loop();
  public:
    Time(long init = 0);
    ~Time();
    /**
     * This function is used to get a humanly readable version of the current time.
     * The format parameter lets the user choose the format of the print:
     *  - use "@h" to print the hours
     *  - use "@m" to print the number of minutes past the hour (e.g: "@h:@m" will return something like "12:23")
     *  - use "@s" to print the number of seconds past the minute (e.g: "@m:@s" will return something like "02:04")
     *  - use "@H" to print the total time, converted to hours
     *  - use "@M" to print the total time, converted to minutes
     *  - use "@S" to print the total time, converted to seconds
     *  - use "@@" to print the char '@'
     * @param  format [description]
     * @return        [description]
     */
    char* getPrintable(const char* format = "@h:@m:@s time");
    Time operator-(const Time t);
    int isNull();
    Time clone();
    void set(long amount);
    long get();

  private:
    void increase(long mills);

    long time;
    unsigned long spareMillis;
    char * str;
};








#endif
