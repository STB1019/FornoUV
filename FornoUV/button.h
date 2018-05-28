#ifndef BUTTON_h
#define BUTTON_h

typedef struct {
  bool _signal; // true if the button has been pressed enough to use the signal
  bool _down; // ??? couldn't really find the utility and rewrote the program without using it
  bool _current; // true if the button is currently presed
  char _bounce; // the number of times in the loop the button has been held pressed
  char _pin; // the pin of the button
  volatile unsigned char* _ppin; // ???
}Button;

Button btnCreate(volatile unsigned char* ppin, char pin) {
  Button btnOne = {false,false,false,0,pin,ppin};
  return btnOne;
}

/**
 * Checks the status of a button
 * In order to determine the "pressed" status, it uses the following method
 *  - A button is pressed only once it was actually pressed for 20 calls
 *  - A button is released only once it was actually released for 20 calls
 * 
 * @param[out] btn the button to be updated
 * @return A boolean value determined by the status of the button (true if pressed)
 */
bool btnUpdate(Button *btn) {
  btn->_current = !( *(btn->_ppin) & (B1 << btn->_pin) == B1 << btn->_pin );

  if (!btn->_signal) { // the button isn't considered pressed
    if (btn->_current) { // the button is currently pressed
      if (btn->_bounce > 20) // CASE: button released for a long time -> pressed and enough time has passed (20 loops) -> consider it pressed
        btn->_signal = true; // if the button has been held pressed for 20 (possibly configurable) times in the loop, then consider it pressed
      else // CASE: the button is pressed but not enough time has passed
        btn->_bounce++; // else, increase the count (_bounce) of loops passed with the button pressed
    }
    else if (bounce > 0) // CASE: button not pressed for a long time -> pressed for a short time (< 20 loops) -> released afterwards
      btn->_bounce--; // possibly set it to 0, must check the reading for a pressed button
      //btn->_bounce = 0;
    else { // the button is currently considered pressed
      if (btn->_current) { // the button is still pressed
        if (btn->_bounce <= 20) // CASE: button pressed for a long time -> released for a short time (< 20 loops) -> pressed afterwards
          btn->_bounce++; // possibly set it to the max value, must check the readings for a pressed button
          //btn->_bounce = 20 + 1; // if the count (_bounce) of loops passed with the button pressed is smaller than 20 (possibly configurable), set it to max
      }
      else { // the button is not pressed anymore
        if (btn->_bounce > 0) // CASE: button pressed for a long time -> released but not enough time has passed
          btn->_bounce--; // if the count is positive, then decrease it incrementally before
        else // CASE: button pressed for a long time -> released and enough time has passed (20 loops) -> consider it released
          btn->_signal = false;
      }
    }

    return btn->_signal;
  }

 /* Old implementation (inefficient and messy)
  if (!btn->_signal) { // if the button has not been fully pressed
    if (btn->_down) { // if the button 
      if (btn->_current) { // if the button is currently pressed
        if (btn->_bounce > 20) { // if the button has been held pressed for 20 times in a row in the loop
          btn->_signal = true; // signals that the button is now considered pressed
        }
        else
          btn->_bounce++; // increase the number of times the button has been held pressed if it hasn't reached 20
      }
      else { // if the button isn't currently pressed
        if (btn->_bounce > 0) // decrease _bounce if positive
          btn->_bounce--; 
        else  // if the button has been not pressed for 20 loops, it turns the status of _down to false
          btn->_down = false; 
      }
    }
    else { // if _down is false
      if (btn->_current) // if the button is pressed, then _down is true
        btn->_down = true;
    }   
  }
  else { // if the _signal is true (the button is now pressed)
    // if (btn->_signal) { Looks pointless if the program reaches this section then _signal is necessarily true (else at line 76 and if at line 54)
    
    if (btn->_current) { // if the button is still pressed increase the value of _bounce (never over 21)
      if (btn->_bounce <= 20)
        btn->_bounce++;
    }
    else { // if the button is not pressed anymore
      if (btn->_bounce > 0) // decrease _bounce
        btn->_bounce--; 
      else { // if _bounce is zero then set the button to unpressed
        btn->_signal = false;
        btn->_down = false; 
      }
    }
    
    //}
    // Unreachable code (just like row 48)
    //else {
    //  if (btn->_current)
    //    btn->_down = true;
    //}
  }
*/
  
  return btn->_signal;
}





#endif
