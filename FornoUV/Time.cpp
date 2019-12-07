#include "Time.h"

#include <Arduino.h>

long getValue(char format, long time);
long numIntoStr(char* str, long num, int pos, int minlen);

// public members
Time::Time(long init) {
    time = init;
    spareMillis = 0;
}
Time::~Time() {
}

/* Requires the string where set the result as parameter.
 * Returns the lenght of the generated string.
 * Minimum size is 4 char string because in case of error the result is "Err" ['E','r','r','\0'].
 * NB: size of string is always (num of char + 1). Every special symbol is two digit string, but special symbol @l is three.
 */
int Time::getStaticPrintable(const char* format, char* str) {
    int ok = 1;

    int i = 0;
    int o = 0;
    /* start and check if the first char is not @: in this case set the result to the char, otherwise skip @ and check the special char.
     */
    while (format[i] != '\0' && ok) {
        //if the current char is not @ then set the string to this character
        char ch = format[i];
        if (ch != '@') {
            str[o] = ch;
            i++; o++;
            continue;
        }

        //else skip @ and elab the special character
        i++;
        char nx = format[i];
        switch (nx) {
            case '@':
                //is to add @ as character into the string
                str[o] = '@';
                o++;
                break;
            case 'H':
            case 'M':
            case 'S':
            case 'h':
            case 'm':
            case 's':
            {
                //is to add a two digit string
                long num = getValue(nx, this->time);
                int add = numIntoStr(str, num, o, 2);
                o += add;
                break;
            }
            case 'l':
            {
                //is to add a three digit string
                int add = numIntoStr(str, spareMillis, o, 3);
                o += add;
                break;
            }
            default:
                ok = 0;
                continue;
        }
        i++;
    }

    if (ok) {
        str[o] = '\0';

        return o+1;
    }
    else {
        str[0] = 'E';
        str[1] = 'r';
        str[2] = 'r';
        str[3] = '\0';

        return 4;
    }
}

char* Time::getPrintable(const char* format) {
    char* str = (char*) malloc(17*sizeof(char));
    char * out = NULL;
    int strLen = 0;

    strLen = getStaticPrintable(format, str);

    out = (char*) malloc(strLen * sizeof(char));
    for (int k = 0; k < strLen; k++) {
        out[k] = str[k];
    }
    
    free(str);

    return out;
}

Time Time::operator-(const Time t) {
    Time out;

    out.time = time - t.time;
    out.increase((long)spareMillis - (long)t.spareMillis);

    return out;
}



// private members
void Time::set(long amount) {
    time = amount;
    spareMillis = 0;
}

void Time::increase(long mills) {
    while (mills < 0) {
        time--;
        mills += 1000;
    }
    spareMillis += mills;
    long spareSecs = spareMillis / 1000;
    spareMillis %= 1000;

    time += spareSecs;
}

int Time::isNull() {
    if (time == 0 && spareMillis == 0)
        return 1;

    if (time >= 0)
        return 0;

    if (time < 0)
        return 1;

}

Time Time::clone() {
    Time out(time);
    out.spareMillis = spareMillis;
    return out;
}

long Time::get() {
    return time;
}

long numIntoStr(char* str, long num, int pos, int minlen) {
    int cnt = 0;
    int len = 0;
    for (long k = 1; k <= num; k *= 10, len++);

    //Set '0' to the empty position (minimum length is > than length of the number)
    int emptyLen = minlen - len;
    for (int i = 0; i < emptyLen; i++) {
        str[pos + i] = '0';
    }

    //If has length do
    if (len > 0) {
        //Move cursor at the first position to fill (after empty positions)
        pos += emptyLen > 0 ? emptyLen : 0;

        //Fill the string starting from the end
        for (int j = pos + (len - 1); j >= pos; j--) {
            str[j] = '0' + (num % 10);
            num /= 10;
        }
    }

    return len > minlen ? len : minlen;
}


long getValue(char format, long time) {
    switch (format) {
        case 'H':
        case 'h':
        return (time / 3600);
        case 'M':
        return (time / 60);
        case 'm':
        return (time / 60) % 60;
        case 'S':
        return time;
        case 's':
        return (time % 60);
        default:
        return -1;
    }
}
