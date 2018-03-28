/**
* Quest'opera è distribuita con Licenza Creative Commons Attribuzione - 
* Non commerciale - Condividi allo stesso modo 4.0 Internazionale.
* - http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef gmTIME_h
#define gmTIME_h

#include <stdio.h>


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
