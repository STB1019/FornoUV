#ifndef BUTTON_h
#define BUTTON_h

#define MAXBOUNCE 20

class Button {
public:
  Button(volatile unsigned char* ppin, char pin, int maxbounce = MAXBOUNCE);
  ~Button();
  void update();
  bool isPressed();
  void print();

private:
  bool _signal; // true if the button has been pressed enough to use the signal
  bool _current; // true if the button is currently presed
  char _bounce; // the number of times in the loop the button has been held pressed
  char _pin; // the pin of the button
  volatile unsigned char* _ppin; // ???

  int _maxbounce;
};


void Button::print() {
  Serial.print(_signal);
  Serial.print("   ");
  Serial.print(_current);
  Serial.print("   ");
  Serial.print((int)_bounce);
  Serial.println("   ");
}

Button::Button(volatile unsigned char* ppin, char pin, int maxbounce) {
  _signal = false;
  _current = false;
  _bounce = 0;
  _pin = pin;
  _ppin = ppin;

  _maxbounce = maxbounce;
}

Button::~Button() {}

void Button::update() {
  
  _current = !( ((*(_ppin)) & (B1 << _pin)) == (B1 << _pin) );

  if (!_signal) { // the button isn't considered pressed
    if (_current) { // the button is currently pressed
      if (_bounce > MAXBOUNCE) // CASE: button released for a long time -> pressed and enough time has passed (MAXBOUNCE loops) -> consider it pressed
        _signal = true; // if the button has been held pressed for MAXBOUNCE (possibly configurable) times in the loop, then consider it pressed
      else // CASE: the button is pressed but not enough time has passed
        _bounce++; // else, increase the count (_bounce) of loops passed with the button pressed
    }
    else if (_bounce > 0) // CASE: button not pressed for a long time -> pressed for a short time (< MAXBOUNCE loops) -> released afterwards
      _bounce = 0;
  }
  else { // the button is currently considered pressed
    if (_current) { // the button is still pressed
      if (_bounce <= MAXBOUNCE) // CASE: button pressed for a long time -> released for a short time (< MAXBOUNCE loops) -> pressed afterwards
        _bounce = MAXBOUNCE + 1; // if the count (_bounce) of loops passed with the button pressed is smaller than MAXBOUNCE (possibly configurable), set it to max
    }
    else { // the button is not pressed anymore
      if (_bounce > 0) // CASE: button pressed for a long time -> released but not enough time has passed
        _bounce--; // if the count is positive, then decrease it incrementally before
      else // CASE: button pressed for a long time -> released and enough time has passed (MAXBOUNCE loops) -> consider it released
        _signal = false;
    }
  }

}

bool Button::isPressed() {
  return _signal;
}

// typedef struct {
//   bool _signal; // true if the button has been pressed enough to use the signal
//   bool _current; // true if the button is currently presed
//   char _bounce; // the number of times in the loop the button has been held pressed
//   char _pin; // the pin of the button
//   volatile unsigned char* _ppin; // ???
// }Button;

// Button btnCreate(volatile unsigned char* ppin, char pin) {
//   Button btnOne = {false,false,false,0,pin,ppin};
//   return btnOne;
// }

// /**
//  * Checks the status of a button
//  * In order to determine the "pressed" status, it uses the following method
//  *  - A button is pressed only once it was actually pressed for MAXBOUNCE calls
//  *  - A button is released only once it was actually released for MAXBOUNCE calls
//  * 
//  * @param[out] btn the button to be updated
//  * @return A boolean value determined by the status of the button (true if pressed)
//  */
// bool btnUpdate(Button *btn) {
//   btn->_current = !( ((*(btn->_ppin)) & (B1 << btn->_pin)) == (B1 << btn->_pin) );

//   if (!btn->_signal) { // the button isn't considered pressed
//     if (btn->_current) { // the button is currently pressed
//       if (btn->_bounce > MAXBOUNCE) // CASE: button released for a long time -> pressed and enough time has passed (MAXBOUNCE loops) -> consider it pressed
//         btn->_signal = true; // if the button has been held pressed for MAXBOUNCE (possibly configurable) times in the loop, then consider it pressed
//       else // CASE: the button is pressed but not enough time has passed
//         btn->_bounce++; // else, increase the count (_bounce) of loops passed with the button pressed
//     }
//     else if (btn->_bounce > 0) // CASE: button not pressed for a long time -> pressed for a short time (< MAXBOUNCE loops) -> released afterwards
//       btn->_bounce--; // possibly set it to 0, must check the reading for a pressed button
//       //btn->_bounce = 0;
//   }
//   else { // the button is currently considered pressed
//     if (btn->_current) { // the button is still pressed
//       if (btn->_bounce <= MAXBOUNCE) // CASE: button pressed for a long time -> released for a short time (< MAXBOUNCE loops) -> pressed afterwards
//         btn->_bounce++; // possibly set it to the max value, must check the readings for a pressed button
//         //btn->_bounce = MAXBOUNCE + 1; // if the count (_bounce) of loops passed with the button pressed is smaller than MAXBOUNCE (possibly configurable), set it to max
//     }
//     else { // the button is not pressed anymore
//       if (btn->_bounce > 0) // CASE: button pressed for a long time -> released but not enough time has passed
//         btn->_bounce--; // if the count is positive, then decrease it incrementally before
//       else // CASE: button pressed for a long time -> released and enough time has passed (MAXBOUNCE loops) -> consider it released
//         btn->_signal = false;
//     }
//   }
 
//   return btn->_signal;
// }

#endif
