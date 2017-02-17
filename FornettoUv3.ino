#include "timer.h"
#include "com.h"
#include "button.h"


#define STATE_BASE
#define STATE_STARTING
#define STATE_WORKING
#define STATE_STOPPING


/*
 * PORTB
 * PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7 
 *  53  52  51  50  10  11  12  13
 */

char state;
Button btnOne,btnTwo;

void setup() {
  /*
   * PIN 13 : D-Out
   * PIN 53 : D-In
   * PIN 52 : D-In
   */
  DDRB  = B11111100;  
  PORTB = B00000011;

  btnOne = btnCreate(&PINB,PB0);
  btnTwo = btnCreate(&PINB,PB1);
  
  state = STATE_BASE;
  
  stop_timer();

  setup_com();
}

void loop() {
  
  btnUpdate(&btnOne);
  btnUpdate(&btnTwo);


  if(btnOne._signal) {
    start_timer();
  } 

  if(btnTwo._signal) {
    stop_timer();
  }
  
}

