/**
* Quest'opera è distribuita con Licenza Creative Commons Attribuzione - 
* Non commerciale - Condividi allo stesso modo 4.0 Internazionale.
* - http://creativecommons.org/licenses/by-nc-sa/4.0/
*/

#ifndef BUTTON_h
#define BUTTON_h

typedef struct {
  bool _signal;
  bool _down;
  bool _current;
  char _bounce;
  char _pin;
  volatile unsigned char* _ppin;//bellissimo
}Button;

Button btnCreate(volatile unsigned char* ppin, char pin) {
  Button btnOne = {false,false,false,0,pin,ppin};
  return btnOne;
}

bool btnUpdate(Button *btn) {
 btn->_current = !(((*(btn->_ppin))&(B1<<btn->_pin)) == B1<<btn->_pin);
  if(!btn->_signal) {
    if(btn->_down) {
      if(btn->_current) {
        if(btn->_bounce>20) {
          btn->_signal = true;
          //
        } else btn->_bounce++;
      }else{
        if(btn->_bounce>0) btn->_bounce--; 
        else btn->_down = false; 
      }
    } else {
      if(btn->_current) btn->_down = true;
    }   
  } else {
    if(btn->_signal) {
      if(btn->_current) {
        if(btn->_bounce>20) {
        } else btn->_bounce++;
      }else{
        if(btn->_bounce>0) btn->_bounce--; 
        else {
          btn->_signal = false;
          btn->_down = false; 
          //
        }
      }
    } else {
      if(btn->_current) btn->_down = true;
    }  
  }
  return btn->_signal;
}





#endif
