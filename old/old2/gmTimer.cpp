/**
* Quest'opera è distribuita con Licenza Creative Commons Attribuzione - 
* Non commerciale - Condividi allo stesso modo 4.0 Internazionale.
* - http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#include "gmTimer.h"

int OneSecondTimer::_s; 
bool OneSecondTimer::_si; 

OneSecondTimer::OneSecondTimer() {
  OneSecondTimer::_s = 0;
  OneSecondTimer::_si = false;
}

void OneSecondTimer::start() {
  OneSecondTimer::_s = 0;
  OneSecondTimer::_si = false;
  
  // initialize Timer1
  //cli();         // disable global interrupts
  //TCCR1A = 0;    // set entire TCCR1A register to 0
  //TCCR1B = 0;    // set entire TCCR1A register to 0
  this->stop();

  // enable Timer1 overflow interrupt:
  TIMSK1 |= (1 << TOIE1);
  TCNT1=17143;
  
  // Set CS10 bit so timer runs at clock speed: (no prescaling)
  TCCR1B |= (1 << CS12); // Sets bit CS12 in TCCR1B
  
  // This is achieved by shifting binary 1 (0b00000001)
  // to the left by CS12 bits. This is then bitwise
  // OR-ed into the current value of TCCR1B, which effectively set
  // this one bit high. Similar: TCCR1B |= _BV(CS12);
  //  or: TCCR1B= 0x04;
  
  // enable global interrupts:
  sei();
}

void OneSecondTimer::stop() {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
}

int OneSecondTimer::getSeconds() {
  OneSecondTimer::_si = false;
  return OneSecondTimer::_s;
}

bool OneSecondTimer::getSignal() {
  return OneSecondTimer::_si;
}


ISR(TIMER1_OVF_vect)
{
  OneSecondTimer::_si = true;
  OneSecondTimer::_s++;
  PORTB ^= 1<<7;
  Serial.println("ISR ON ARDUINO MEGA");
  TCNT1=17143;  
}

