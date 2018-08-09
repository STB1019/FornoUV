#ifndef gmTIME_h
#define gmTIME_h

/**
 * Represents a time interval
 */
class Time {

  public:
    Time();
    void incSeconds(int s);
    void decSeconds(int s);
    int toSeconds();
    void fromSeconds(int s);
    char* toStringHM();
    char* toStringHMS();
    bool lessEqual(int h, int m, int s);
    bool aboveEqual(int h, int m, int s);

  private:
    int _s;
    int _m;
    int _h;
    char _str[16];

};


#endif
