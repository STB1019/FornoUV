
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

#include "time.h"
#include "timer.h"
#include "com.h"
#include "button.h"

#define STATE_BASE    0
#define STATE_START   1
#define STATE_WORK    2
#define STATE_STOP    3
#define STATE_TIME    4

/*
 * PORTB
 * PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7 
 *  53  52  51  50  10  11  12  13
 */
 /*
 * PORTL
 * PL0 PL1 PL2 PL3 PL4 PL5 PL6 PL7 
 *  49  48  47  46  45  44  43  42
 */

char state;
Time objTime;
Time objTimeOne;
Button btnOne,btnTwo;
Button btnTimeUp,btnTimeDown;



void setup() {
  /*
   * PIN 13 : D-Out
   * PIN 53 : D-In
   * PIN 52 : D-In
   */
  DDRB  &= B11110000;  
  PORTB |= B00001111;
  DDRL  = B11111111;  
  PORTL = B00000010;

  btnOne = btnCreate(&PINB,PB0);
  btnTwo = btnCreate(&PINB,PB1);
  btnTimeUp = btnCreate(&PINB,PB2);
  btnTimeDown = btnCreate(&PINB,PB3);
  objTime = time_new();
  objTimeOne = time_new();
  
  state = STATE_BASE;
  
  stop_timer();

  setup_com();

  state = 0;

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Il Fornaio UV");

}


void loop() {
  
  btnUpdate(&btnOne);
  btnUpdate(&btnTwo);
  btnUpdate(&btnTimeUp);
  btnUpdate(&btnTimeDown);

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
    case STATE_TIME:
      state_time();
    break;
  }

}


void state_base() {
  lcd.setCursor(0,1);
  lcd.print("STATE: KARIM");
  if(btnOne._signal && !btnTwo._signal) {
    if(TimeToSeconds(objTime)>0)state = STATE_START;
    else state = STATE_TIME;//PICCOLO BUG LOGICO MA PER ORA ME LO TENGO ... direbbero pocomale i sommi
    lcd.clear();
  }
  if(btnTimeUp._signal || btnTimeDown._signal) {
    state = STATE_TIME;
    lcd.clear();
  }
}
void state_start() {
  start_timer();
  state = STATE_WORK; 
  PORTL ^= 3;
}
void state_work() {
  if(timer_Seconds_Signal()) {
    lcd.setCursor(0, 1);
    lcd.print("STATE: WORK     ");
    lcd.setCursor(0, 2);
    objTimeOne = objTime;
    time_set_down(&objTimeOne,timer_Seconds());
    lcd.print(time_to_str_hms(objTimeOne));
  }
  if((timer_Seconds() == TimeToSeconds(objTime)) || btnTwo._signal) state = STATE_STOP;
}
void state_stop() {
  stop_timer();
  state = STATE_BASE;
  PORTL ^= 3;
  lcd.setCursor(0,2);
  lcd.print("END WORK");
  lcd.setCursor(0,2);
  lcd.print("                ");
}

void state_time() {
  lcd.setCursor(0,0);
  lcd.print("STATE: TIME");
  if(btnTimeUp._signal && btnTimeDown._signal) return;
  else {
    if(btnTimeUp._signal) {
      if(time_leq(objTime,2,59,59)) {
        time_set_up(&objTime,1);
      }
    }
    if(btnTimeDown._signal) {
      if(time_geq(objTime,0,0,1)) time_set_down(&objTime,1);
    }
  }
  lcd.setCursor(0,1);
  lcd.print(time_to_str(objTime));
  if(btnOne._signal) {
    state=STATE_BASE;
    while(btnOne._signal) btnUpdate(&btnOne);;//NON E' TROPPO BELLO PER STARE IN UNA SPECIE DI MACCHINA A STATI
    lcd.clear();
  }
}



