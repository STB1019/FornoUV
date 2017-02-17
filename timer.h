#ifndef TIMER_h
#define TIMER_h

long timer_centi_seconds;
long timer_deci_seconds;
long timer_seconds;


ISR(TIMER1_COMPA_vect)
{
  if(timer_centi_seconds == 10) {
    timer_centi_seconds = 0;
    if(timer_deci_seconds == 10){
      timer_deci_seconds = 0;
      timer_seconds++;
      PORTB ^= 1<<7;
    } else timer_deci_seconds++;
  } else timer_centi_seconds++;
}

void stop_timer() { 
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
}

void start_timer() {

  timer_centi_seconds = 0;
  timer_deci_seconds = 0;
  timer_seconds = 0;

  stop_timer();
  OCR1A = 2500;
  TCCR1B |= (1 << WGM12);   // CTC mode
  /**
  *  TCCR1B 2-1-0: clockselct, prescaler
  *  ->000:  timer disabled
  *  ->001: clk/1
  *  ->010: clk/8
  *  ->011: clk/64
  *  ->100: clk/256
  *  ->101: clk/1024
  *  ->110: external
  *  ->111: external
  **/
  TCCR1B |= B00000011;    // 64 prescaler 
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  sei();   
}


long timer_CentiSeconds() {
  return timer_centi_seconds;
}
long timer_DeciSeconds() {
  return timer_deci_seconds;
}
long timer_Seconds() {
  return timer_seconds;
}





#endif
