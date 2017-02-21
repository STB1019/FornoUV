#ifndef TIME_h
#define TIME_h

typedef struct {
  int h;
  int m;
  int s;  
}Time;


Time time_new() {
  Time t = {0,0,0};
  return t;
}
int time_get_seconds(Time t) {
  return t.s;
}
int time_get_minutes(Time t) {
  return t.m;
}
int time_get_hours(Time t) {
  return t.h;
}
void time_set(int h, int m, int s, Time* t) {
}
void time_set_up(Time* t,int up) {
  t->s += up;
  while(t->s>=60) {
    t->m++;
    t->s -= 60;
  }
  while(t->m>=60) {
    t->h++;
    t->m -= 60;
  }
}
void time_set_down(Time* t, int dw) {
  while(dw>0) {
    if(t->s>0)t->s--;
    else {
      t->s=59;
      if(t->m>0)t->m--;
      else {
        t->m=59;
        if(t->h>0)t->h--;
      }
    }
    dw--;
  }
}

char* time_to_str(Time t) {
  char str[16];
  sprintf(str,"hh:mm - %02d:%02d   ",t.h,t.m);
  return str;
}
char* time_to_str_hms(Time t) {
  char str[16];
  sprintf(str,"%02d:%02d:%02d       ",t.h,t.m,t.s);
  return str;
}

bool time_is(Time t,int h,int m,int s) {
  return (t.h==h) && (t.m==m) && (t.s==s);
}
bool time_leq(Time t,int h,int m,int s) {
  if(t.h>h)return false;
  if(t.h==h) {
    if(t.m>m) return false;
    if(t.m==m){
    if(t.s>s) return false;
    }
  }
  return true;
}
bool time_geq(Time t,int h,int m,int s) {
  if(t.h<h)return false;
  if(t.h==h) {
    if(t.m<m) return false;
    if(t.m==m){
    if(t.s<s) return false;
    }
  }
  return true;
}

int TimeToSeconds(Time t) {
  return t.h*3600+t.m*60+t.s;
}



#endif
