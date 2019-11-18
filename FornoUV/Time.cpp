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

char* Time::getPrintable(const char* format) {
    char* str = (char*) malloc(17*sizeof(char));
    int ok = 1;

    int i = 0;
    int o = 0;
    while (format[i] != '\0' && ok) {
        char ch = format[i];
        if (ch != '@') {
            str[o] = ch;
            i++; o++;
            continue;
        }

        i++;
        char nx = format[i];
        switch (nx) {
            case '@':
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
                long num = getValue(nx, this->time);
                int add = numIntoStr(str, num, o, 2);
                o += add;
                break;
            }
            case 'l':
            {
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

    char* out;
    if (ok) {
        out = (char*) malloc((o + 1) * sizeof(char));
        for (int k = 0; k < o; k++) {
            out[k] = str[k];
        }
        out[o] = '\0';
    }
    else {
        out = (char*) malloc(4 * sizeof(char));
        out[0] = 'E';
        out[1] = 'r';
        out[2] = 'r';
        out[3] = '\0';
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

    for (int i = 0; i < minlen - len; i++) {
        str[pos + i] = '0';
    }
    pos += minlen - len;

    for (int j = pos + len - 1; j >= pos; j--) {
        str[j] = '0' + (num % 10);
        num /= 10;
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
