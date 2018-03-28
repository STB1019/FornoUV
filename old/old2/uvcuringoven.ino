/**
* Quest'opera è distribuita con Licenza Creative Commons Attribuzione - 
* Non commerciale - Condividi allo stesso modo 4.0 Internazionale.
* - http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

/*****
 * 
 * PIN:
 * - 8,9,4,5,6,7 -> LCD da capire cosa fanno
 * 
 * -53 BtnStart
 * -52 BtnStop
 * 
 * -51 Time+
 * -50 Time-
 * 
 * -49 LedVerde
 * -48 Led Rosso
 * 
 * -36 MOTOR_CW
 * -37 MOTOR_CCW
 * 
 * -22 SERVOMOTOR
 */

/*
void pwm_init(int duty)
{
  
  DDRB |= (1 << PB4);
   
  // PB3 as output
  OCR2A = duty;
  // set PWM for 50% duty cycle
  TCCR2A |= (1 << COM2A1);
  // set non-inverting mode
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  // set fast PWM Mode
  TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
  // set prescaler to 8 and starts PWM
}
*/


#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define MOTOR_CW 36
#define MOTOR_CCW 37

#include "gmTime.h"
#include "gmTimer.h"

#include "com.h"
#include "button.h"

#define STATE_BASE      0
#define STATE_START     1
#define STATE_WORK      2
#define STATE_STOP      3
#define STATE_TIME      4
#define STATE_TIME_UP   5
#define STATE_TIME_DOWN 6
#define STATE_OPENING   7
#define STATE_CLOSING   8


OneSecondTimer timer;
char state;
Time objTime,objTimeOne;
Button btnOne, btnTwo, btnTimeUp, btnTimeDown;
int ServoPos = 0;



void setup() {

  /*
    PORTB
    PB0 PB1 PB2 PB3 PB4 PB5 PB6 PB7
     53  52  51  50  10  11  12  13
  */
  DDRB  &= B11110000;
  PORTB |= B00001111;

  /*
    PORTL
    PL0 PL1 PL2 PL3 PL4 PL5 PL6 PL7
     49  48  47  46  45  44  43  42
  */
  DDRL  = B00111111;
  PORTL = B00000010;

  /*
    PORTL
    PC0 PC1 PC2 PC3 PC4 PC5 PC6 PC7
     42  43  44  45  46  47  48  49
  */
  DDRC  =  B11111111;
  PORTC =  B00000000;

  btnOne = btnCreate(&PINB, PB0);
  btnTwo = btnCreate(&PINB, PB1);
  btnTimeUp = btnCreate(&PINB, PB2);
  btnTimeDown = btnCreate(&PINB, PB3);
  objTime = Time();
  objTimeOne = Time();

  state = STATE_BASE;
  timer = OneSecondTimer();
  timer.stop();

  
  setup_com();
  state = 0;
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Il Fornaio UV :)");
  lcd.setCursor(0, 1);
  lcd.print("STATE: BASE");

  Serial.println("ENTRYPOINT");

}

void loop() {

  btnUpdate(&btnOne);
  btnUpdate(&btnTwo);
  btnUpdate(&btnTimeUp);
  btnUpdate(&btnTimeDown);

  switch (state) {
    case STATE_BASE:
      lcd.setCursor(0, 0);
      lcd.print("Il Fornaio UV :)");
      lcd.setCursor(0, 1);
      lcd.print("STATE: BASE     ");
      state_base();
      break;
    case STATE_START:
      lcd.setCursor(0,0);
      lcd.print("STATE: START    ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      state_start();
      break;
    case STATE_WORK:
      lcd.setCursor(0,0);
      lcd.print("STATE: WORK     ");
      lcd.setCursor(0,1);
      lcd.print(objTimeOne.toStringHM());
      state_work();
      break;
    case STATE_STOP:
      lcd.setCursor(0,0);
      lcd.print("STATE: STOP     ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      state_stop();
      break;
    case STATE_TIME:
      lcd.setCursor(0, 0);
      lcd.print("STATE: TIME     ");
      state_time();
      lcd.setCursor(0, 1);
      lcd.print(objTime.toStringHM());
      break;
    case STATE_TIME_UP:
      lcd.setCursor(0, 0);
      lcd.print("STATE: TIME UP  ");
      state_time_up();
      lcd.setCursor(0, 1);
      lcd.print(objTime.toStringHM());
      break;
    case STATE_TIME_DOWN:
      lcd.setCursor(0, 0);
      lcd.print("STATE: TIME DOWN");
      state_time_down();
      lcd.setCursor(0, 1);
      lcd.print(objTime.toStringHM());
      break;
     case STATE_OPENING:
      lcd.setCursor(0, 0);
      lcd.print("OPENING         ");
      state_opening();
      lcd.setCursor(0, 1);
     break;
     case STATE_CLOSING:
      lcd.setCursor(0, 0);
      lcd.print("CLOSING         ");
      state_closing();
      lcd.setCursor(0, 1);
     break;
  }
}


void state_base() {
  if (btnOne._signal && !btnTwo._signal) {
    if (objTime.toSeconds() > 0)state = STATE_START;
    else state = STATE_TIME;//PICCOLO BUG LOGICO MA PER ORA ME LO TENGO ... direbbero pocomale i sommi
  }
  if (btnTimeUp._signal || btnTimeDown._signal) {
    state = STATE_TIME;
    timer.start();
  }
}

void state_start() {
  state = STATE_CLOSING;
  PORTL ^= 3;
}

void state_closing() {
//  pwm_init(24); 
  //if(true) return;
  timer.start();
  state = STATE_WORK;
}

void state_work() {
  if (timer.getSignal()) {
    objTimeOne = objTime;
    objTimeOne.decSeconds(timer.getSeconds());
  }
  if ((timer.getSeconds() == objTime.toSeconds()) || btnTwo._signal) state = STATE_OPENING;
}

void state_opening() {
//  pwm_init(12);
  //if(true) return;;
  state = STATE_STOP;
}


void state_stop() {
  motorStop();
  state = STATE_BASE;
  PORTL ^= 3;
}

void state_time() {
  Serial.println("DIOOOOCANNNNEEE");
  if (btnTimeUp._signal && btnTimeDown._signal) return;
  else {
    if (btnTimeUp._signal) {
      state = STATE_TIME_UP;
      timer.start();
    }
    if (btnTimeDown._signal) {
      state = STATE_TIME_DOWN;
      timer.start();
    }
  }
  if (btnOne._signal) {
    state = STATE_BASE;
    while (btnOne._signal) btnUpdate(&btnOne); //NON E' TROPPO BELLO PER STARE IN UNA SPECIE DI MACCHINA A STATI
  }
}
void state_time_up() {
  int up_s = pow(timer.getSeconds() + 1, 2);
  if(objTime.lessEqual( 2, 59, 60 - up_s)) {
    objTime.incSeconds(up_s);
  }
  if (!btnTimeUp._signal) {
    state = STATE_TIME;
    timer.stop();
  }
}
void state_time_down() {
  int dw_s = pow(timer.getSeconds() + 1, 2);
  if (objTime.aboveEqual(0, 0, dw_s)) {
    objTime.decSeconds(dw_s);
  }
  if (!btnTimeDown._signal) {
    state = STATE_TIME;
    timer.stop();
  }
}


void motorCW() {
  digitalWrite(MOTOR_CW,HIGH);
}
void motorCCW() {
  digitalWrite(MOTOR_CCW,HIGH);
}
void motorStop(){
  digitalWrite(MOTOR_CW,LOW);
  digitalWrite(MOTOR_CCW,LOW);
}



