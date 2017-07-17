/**
* Quest'opera è distribuita con Licenza Creative Commons Attribuzione - 
* Non commerciale - Condividi allo stesso modo 4.0 Internazionale.
* - http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

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
  sprintf(this->_str,"hh:mm - %02d:%02d   ",this->_h,this->_m);
  return this->_str;
}
char* Time::toStringHMS() {
  sprintf(this->_str,"%02d:%02d:%02d        ",this->_h,this->_m,this->_s);
  return this->_str;
}
