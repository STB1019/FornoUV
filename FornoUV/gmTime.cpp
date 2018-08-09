#include "gmTime.h"

#include <Arduino.h>

/**
 * Constructor: initializes a timer at zero
 */
Time::Time() {
  this->_s = 0;
  this->_m = 0;
  this->_h = 0;
}

/**
 * Set the current time to a given number of _seconds
 * @param s The number of seconds
 */
void Time::fromSeconds(int s) {
  this->_h = s/3600;
  s = s-_h*3600;
  this->_m = s/60;
  s = s-_m*60;
  this->_s = s;
}

/**
 * Returns the current time in seconds
 * @return The current time in seconds
 */
int Time::toSeconds() {
  return this->_h*3600+this->_m*60+this->_s;
}

/**
 * Increments the current timer by a given amount of seconds
 * @param s A time interval in seconds
 */
void Time::incSeconds(int s) {
  int curr = this->toSeconds();
  int next = curr+s;
  if (next>=3*3600) next = (3600*3)-1;
  this->fromSeconds(next);
}

/**
 * Decreases the current timer by a given amount of seconds
 * @param s A time interval in seconds
 */
void Time::decSeconds(int s) {
  int curr = this->toSeconds();
  int next = 0;
  if (curr>s) next = curr-s;
  this->fromSeconds(next);
}

/**
 * Compares the current time in this object to a given one
 * @param  h Hours
 * @param  m Minutes
 * @param  s Seconds
 * @return   True if the current time in this object is less or equal to the provided one
 */
bool Time::lessEqual(int h, int m, int s) {
  return (this->toSeconds()<=(h*3600+m*60+s));
}

/**
 * Compares the current time in this object to a given one
 * @param  h Hours
 * @param  m Minutes
 * @param  s Seconds
 * @return   True if the current time in this object is greater or equal to the provided one
 */
bool Time::aboveEqual(int h, int m, int s) {
  return (this->toSeconds()>=(h*3600+m*60+s));

}

/**
 * Retrurns a pointer to a the current time as a string (only including hours and minutes)
 * The string will be structured as follows: 'hh:mm - HH:MM   ', where 'HH' and 'MM' are substituted
 * by the two digits of the hours and minutes, respectively
 * @return The computed string
 */
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
    this->_str[i++] = this->_h+48; // converts to ascii char
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

/**
 * Retrurns a pointer to a the current time as a string (including hours, minutes and seconds)
 * The string will be structured as follows: 'HH:MM:SS        ', where 'HH', 'MM' and 'SS' are
 * substituted by the two digits of the hours, minutes and seconds, respectively
 * @return The computed string
 */
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
