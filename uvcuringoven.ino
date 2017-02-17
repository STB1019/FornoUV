#include "timer.h"
#include "com.h"
#include "button.h"

#define STATE_BASE    0
#define STATE_START   1
#define STATE_WORK    2
#define STATE_STOP    3

/*
 * PORTB
 * PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7 
 *  53  52  51  50  10  11  12  13
 */

char state;
Button btnOne,btnTwo;

int stop_work_time = 5;

void setup() {
  /*
   * PIN 13 : D-Out
   * PIN 53 : D-In
   * PIN 52 : D-In
   */
  DDRB  = B11111100;  
  PORTB = B00001011;

  btnOne = btnCreate(&PINB,PB0);
  btnTwo = btnCreate(&PINB,PB1);
  
  state = STATE_BASE;
  
  stop_timer();

  setup_com();

  state = 0;
}


void loop() {
  
  btnUpdate(&btnOne);
  btnUpdate(&btnTwo);

  switch(state) {
    case STATE_BASE:
      state_base();
    break;
    case STATE_START:
      state_start();
    break;
    case STATE_WORK:
      state_work();
    break;
    case STATE_STOP:
      state_stop();
    break;
  }

}


void state_base() {
  if(btnOne._signal && !btnTwo._signal) state = STATE_START;
}
void state_start() {
  start_timer();
  state = STATE_WORK; 
  PORTB ^= 3<<2;
}
void state_work() {
  if((timer_Seconds() == stop_work_time) || btnTwo._signal) state = STATE_STOP;
}
void state_stop() {
  stop_timer();
  state = STATE_BASE;
  PORTB ^= 3<<2;
}

