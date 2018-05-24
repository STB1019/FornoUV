#include "gmTime.h"

#include <Arduino.h>

Time::Time() {
  this->_s = 0;
  this->_m = 0;
  this->_h = 0;
}

void Time::fromSeconds(int s) {
  this->_h = s/3600;
  s = s-_h*3600;
  this->_m = s/60;
  s = s-_m*60;
  this->_s = s;
}

int Time::toSeconds() {
  return this->_h*3600+this->_m*60+this->_s;  
}

void Time::incSeconds(int s) {
  int curr = this->toSeconds();
  int next = curr+s;
  if(next>=3*3600) next = (3600*3)-1;
  this->fromSeconds(next);
}

void Time::decSeconds(int s) {
  int curr = this->toSeconds();
  int next = 0;
  if(curr>s) next = curr-s;
  this->fromSeconds(next);
}

bool Time::lessEqual(int h, int m, int s) {
  return (this->toSeconds()<=(h*3600+m*60+s));
}

bool Time::aboveEqual(int h, int m, int s) {
  return (this->toSeconds()>=(h*3600+m*60+s));
  
}

char* Time::toStringHM() {
  int i = 0;
  this->_str[i++] = 'h';
  this->_str[i++] = 'h';
  this->_str[i++] = ':';
  this->_str[i++] = 'm';
  this->_str[i++] = 'm';
  this->_str[i++] = ' ';
  this->_str[i++] = '-';
  this->_str[i++] = ' ';
  if(this->_h<=9) {
    this->_str[i++] = '0';
    this->_str[i++] = this->_h+48;
  } else {
    this->_str[i++] = this->_h/10+48;
    this->_str[i++] = this->_h%10+48;
  }
  this->_str[i++] = ':';
  if(this->_m<=9) {
    this->_str[i++] = '0';
    this->_str[i++] = this->_m+48;
  } else {
    this->_str[i++] = this->_m/10+48;
    this->_str[i++] = this->_m%10+48;
  }
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  //sprintf(this->_str,"hh:mm - %02d:%02d   ",this->_h,this->_m);
  return this->_str;
}

char* Time::toStringHMS() {
  int i = 0;
  if(this->_h<=9) {
    this->_str[i++] = '0';
    this->_str[i++] = this->_h+48;
  } else {
    this->_str[i++] = this->_h/10+48;
    this->_str[i++] = this->_h%10+48;
  }
  this->_str[i++] = ':';
    if(this->_m<=9) {
    this->_str[i++] = '0';
    this->_str[i++] = this->_m+48;
  } else {
    this->_str[i++] = this->_m/10+48;
    this->_str[i++] = this->_m%10+48;
  }
  this->_str[i++] = ':';
  if(this->_s<=9) {
    this->_str[i++] = '0';
    this->_str[i++] = this->_s+48;
  } else {
    this->_str[i++] = this->_s/10+48;
    this->_str[i++] = this->_s%10+48;
  }
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  this->_str[i++] = ' ';
  //sprintf(this->_str,"%02d:%02d:%02d        ",this->_h,this->_m,this->_s);
  return this->_str;
}
