/*****
 *
 * PIN:
 * - 8,9,4,5,6,7 LCD
 *
 * -53 BtnStart
 * -52 BtnStop
 *
 * -36 MOTOR_CW
 * -37 MOTOR_CCW
 * -35 Resistenza scalda
 * -34 Resistenza scalda
 * -33 Resistenza scalda
 * -32 Resistenza scalda
 * -31 Ventola
 * -30 UVLED
 *
 * -22 SERVOMOTOR
 *
 * -43 BtnServo
 * -51 Time+
 * -50 Time-
 *
 * -49 LedVerde
 * -48 Led Rosso
 *
 *
 * -42 Input DHT11
 */

#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#include <Servo.h>
Servo servo;

// libraried used for the humidity and temperature sensors (see https://github.com/adafruit/DHT-sensor-library and https://github.com/adafruit/Adafruit_Sensor)
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            42
#define DHTTYPE           DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);


#include "gmTime.h"
#include "button.h"

#define STATE_BASE      0
#define STATE_START     1
#define STATE_WORK      2
#define STATE_STOP      3
#define STATE_TIME      4
#define STATE_TIME_UP   5
#define STATE_TIME_DOWN 6


#define TINF 25 // Temperatura INFeriore
#define TSUP 55 // Temperature SUPeriore

#define MOTOR_CW 36 // pin for the motor (clockwise rotation)
#define MOTOR_CCW 37 // pin for the motor (counter-clockwise rotation)


/**
 * Handles the BASE state of the state-machine
 *
 * Changes the state to:
 * - START if (BTNSTART is pressed) AND (BTNSTOP is released) AND (the time of OBJTIMEONE > 0)
 * - TIME if (BTNTIME+ is pressed) OR (BTNTIME- is pressed)
 */
void state_base();

/**
 * Handles the START state of the state-machine
 *
 * Increases the angle of the servo by 1 degree until it reaches 91 degrees
 * If the servo is closed, then the signal for BTNSERVO will be true, therefore changing the state
 * Changes the state to:
 * - WORK if (BTNSERVO is pressed)
 *   -> resets all of the values used for update_time()
 *   -> starts the motor and the UV
 */
void state_start();

/**
 * Handles the WORK state of the state machine
 *
 * Every two seconds, it checks the temperature in order to keep it right
 * Every second, it updates the value of objTimeTwo, which stores the remaining time
 * Changes the state to:
 *  - STOP if (BTNSERVO is released) -> i.e. the door is opened
 *  - STOP if (the time reaches the limit) OR (BTNSTOP is pressed)
 */
void state_work();

/**
 * Turns everything off (motor, UV, resistor and fan) and proceeds to open the servo to unlock the door
 * Once the door opens (BTNSERVO returning false), it changes state accordingly
 * Changes the state to:
 *  - BASE if (BTNSERVO is released) -> i.e. the door is opened
 */
void state_stop();

/**
 * First get here by pressing BTNTIME+ or BTNTIME-
 * Then, pressing and holding BTNTIME+ xor BTNTIME- will increase/decrease the time by a speeding amount of seconds
 * Instead, pressing BTNTIME+ xor BTNTIME- for less than one second, the time will increase/decrease by 1 minute
 * Changes the state to:
 *  - TIME+ if (BTNTIME+ is pressed) AND (BTNTIME- is released)
 *  - TIME- if (BTNTIME- is pressed) AND (BTNTIME+ is released)
 *  - BASE if (BTNSTART is pressed and then released) -> this is represented in the diagram with the virtual state WAIT, not actually implemented here
 */
void state_time();

/**
 * Allows the user to increase the time, as explained in state_time()
 * Changes the state to:
 *  - TIME if (BTNTIME+ is released)
 */
void state_time_up();

/**
 * Allows the user to decrease the time, as explained in state_time()
 * Changes the state to:
 *  - TIME if (BTNTIME- is released)
 */
void state_time_down();



/**
 * Turns on the motor that spins the plate in the oven
 */
void motor_on();

/**
 * Turns off the motor that spins the plate in the oven
 */
void motor_off();

/**
 * Updates the state of the state machine to a new one
 * @param new_state The new state of the machine
 */
void change_state(int new_state);

/**
 * SUGGESTION: this should be a class (or a struct) of its own: it uses 5 global variables and a function: why not make it an object or a struct?
 *
 * Uses or updates the global variables ta, _seconds, one_seconds_flag, two_seconds_flag and cnt_seconds_flag,
 * in order to keep a timer (or interval).
 * To start the timer, set:
 *   ta = millis();
 *   _seconds = 0;
 *   one_seconds_flag = false;
 *   two_seconds_flag = false;
 *   cnt_seconds_flag = 0;
 * The values of these global variables will be modified:
 *  - _seconds: it will contain the number of seconds passed since starting the interval
 *  - one_seconds_flag: this becomes true every single second. (this must be reset to false once it has been found true)
 *  - two_seconds_flag: this becomes true once evry two second. (this must be reset to false once it has been found true)
 */
void update_time();

/**
 * Turns on the resistor that heats the oven
 */
void resistor_on();

/**
 * Turns off the resistor that heats the oven
 */
void resistor_off();

/**
 * Turns on the fan that makes the air circulate and cools the oven
 */
void fan_on();

/**
 * Turns off the fan that makes the air circulate and cools the oven
 */
void fan_off();

/**
 * Turns on the ultraviolet leds used in the heating and curing process
 */
void UV_on();

/**
 * Turns on the ultraviolet leds used in the heating and curing process
 */
void UV_off();


/**
 * Stores the angle of the servo motor.
 * The servo motor will then be rotated using "servo.write(servo_angle)"
 */
int servo_angle;

/**
 * Stores the current state of the program
 */
int program_state;

/**
 * WARNING: this will break and never stop if the interval lasts more than about 49 days (= 2^32 milliseconds)
 *
 * Marks a certain point in time using millis()
 * This will be used within update_time() to update the value of _seconds to the amount of seconds
 * passed since the start of the interval
 */
long ta;

/**
 * Stores the amount of seconds since the start of an interval, marked by assigning
 * the return value of millis() to the variable ta
 */
int _seconds;

/**
 * Simple flag used for debug
 * It allowed for the current state of the machine to be printed on serial, before the code was commented
 */
bool serial_flag;

/**
 * Using update_time, this flag becomes true once every second
 * The usage mandates setting this value back to false after it has been found true
 */
bool one_seconds_flag;

/**
 * Using update_time(), this flag becomes true once every two seconds
 * Just like one_seconds_flag, the usage mandates setting this value back to false after it has been found true
 */
bool two_seconds_flag;

/**
 * Internal value for update_time(), counts how many seconds have passed by,
 * in order to update the value of two_seconds_flag
 * This variable should be set to 0 on setup and NEVER be modified
 */
int cnt_seconds_flag;

/**
 * Time object, used to store the total amount of time required for the current/upcoming job
 */
Time objTimeOne,

/**
 * Time object, it is updated inside state_work() to contain the amount of time remaining to the end of the job
 */
Time objTimeTwo;

/**
 * Five instances of the struct Button, representing various buttons or sensor in the machine:
 * - btnStart: represents the START button, used for example to begin the curing process
 * - btnStop: represents the STOP button, used to stop the ongoing curing process
 * - btnTimeUp: represents the TIME UP button, used to increase the necessary time for the upcoming curing process
 * - btnTimeDown: represents the TIME UP button, used to decrease the necessary time for the upcoming curing process
 * - btnServo: not actually a button, this instance represents a sensor, used to detect if the door of the oven is open
 */
Button btnStart, btnStop, btnTimeUp, btnTimeDown, btnServo;


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
  PORTL = B01000010;

  /*
    PORTL
    PC0 PC1 PC2 PC3 PC4 PC5 PC6 PC7
     37  36  35  34  33  32  31  30
  */
  DDRC  =  B11111111;
  PORTC =  B00000000;

  // creates the buttons
  btnStart = btnCreate(&PINB, PB0);
  btnStop = btnCreate(&PINB, PB1);
  btnTimeUp = btnCreate(&PINB, PB2);
  btnTimeDown = btnCreate(&PINB, PB3);
  btnServo = btnCreate(&PINL, PL6);

  objTimeOne = Time();
  objTimeTwo = Time();

  servo_angle = 0;
  serial_flag = false;
  one_seconds_flag = false;
  two_seconds_flag = false;
  cnt_seconds_flag = 0;

  _seconds = 0;

  change_state((int)STATE_BASE);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Il Fornaio UV :)");
  lcd.setCursor(0, 1);
  lcd.print("STATE: BASE");

  servo.attach(22);
  servo.write(servo_angle);
  //Serial.begin(9600);
  //while(!Serial) continue;
  //Serial.println("ENTRYPOINT");

  dht.begin();
  ////Serial.println("DHTxx Unified Sensor Example");
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  //Serial.println("------------------------------------");
  //Serial.println("Temperature");
  //Serial.print  ("Sensor:       "); //Serial.println(sensor.name);
  //Serial.print  ("Driver Ver:   "); //Serial.println(sensor.version);
  //Serial.print  ("Unique ID:    "); //Serial.println(sensor.sensor_id);
  //Serial.print  ("Max Value:    "); //Serial.print(sensor.max_value); //Serial.println(" *C");
  //Serial.print  ("Min Value:    "); //Serial.print(sensor.min_value); //Serial.println(" *C");
  //Serial.print  ("Resolution:   "); //Serial.print(sensor.resolution); //Serial.println(" *C");
  //Serial.println("------------------------------------");
  dht.humidity().getSensor(&sensor);
  //Serial.println("------------------------------------");
  //Serial.println("Humidity");
  //Serial.print  ("Sensor:       "); //Serial.println(sensor.name);
  //Serial.print  ("Driver Ver:   "); //Serial.println(sensor.version);
  //Serial.print  ("Unique ID:    "); //Serial.println(sensor.sensor_id);
  //Serial.print  ("Max Value:    "); //Serial.print(sensor.max_value); //Serial.println("%");
  //Serial.print  ("Min Value:    "); //Serial.print(sensor.min_value); //Serial.println("%");
  //Serial.print  ("Resolution:   "); //Serial.print(sensor.resolution); //Serial.println("%");
  //Serial.println("------------------------------------");
}

void loop() {

  btnUpdate(&btnStart);
  btnUpdate(&btnStop);
  btnUpdate(&btnTimeUp);
  btnUpdate(&btnTimeDown);
  btnUpdate(&btnServo);

  switch (program_state) {
    case STATE_BASE:
      //if(serial_flag) {
        //Serial.println("STATO BASE");
        //serial_flag = false;
      //}
      lcd.setCursor(0, 0);
      lcd.print("Il Fornaio UV :)");
      lcd.setCursor(0, 1);
      lcd.print("STATE: BASE     ");
      state_base();
      break;
    case STATE_START:
      /*if(serial_flag) {
        Serial.println("STATO START");
        serial_flag = false;
      }*/
      lcd.setCursor(0,0);
      lcd.print("STATE: START    ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      state_start();
      break;
    case STATE_WORK:
      /*if(serial_flag) {
        Serial.println("STATO WORK");
        serial_flag = false;
      }
      if(one_seconds_flag) {
        Serial.println(objTimeTwo.toStringHMS());
        one_seconds_flag = false;
      }*/
      lcd.setCursor(0,0);
      lcd.print("STATE: WORK     ");
      lcd.setCursor(0,1);
      lcd.print(objTimeTwo.toStringHMS());
      state_work();
      break;
    case STATE_STOP:
      /*if(serial_flag) {
        Serial.println("STATO STOP");
        serial_flag = false;
      }*/
      lcd.setCursor(0,0);
      lcd.print("STATE: STOP     ");
      lcd.setCursor(0,1);
      lcd.print("                ");
      state_stop();
      break;
    case STATE_TIME:
      /*if(serial_flag) {
        Serial.println("STATO TIME");
        Serial.println(objTimeOne.toStringHM());
        serial_flag = false;
      }*/
      lcd.setCursor(0, 0);
      lcd.print("STATE: TIME     ");
      state_time();
      lcd.setCursor(0, 1);
      lcd.print(objTimeOne.toStringHM());
      break;
    case STATE_TIME_UP:
      /*if(serial_flag) {
        Serial.println("STATO TIME UP");
        serial_flag = false;
      }*/
      lcd.setCursor(0, 0);
      lcd.print("STATE: TIME UP  ");
      state_time_up();
      lcd.setCursor(0, 1);
      lcd.print(objTimeOne.toStringHM());
      break;
    case STATE_TIME_DOWN:
      /*if(serial_flag) {
        Serial.println("STATO TIME DW");
        serial_flag = false;
      }*/
      lcd.setCursor(0, 0);
      lcd.print("STATE: TIME DOWN");
      state_time_down();
      lcd.setCursor(0, 1);
      lcd.print(objTimeOne.toStringHM());
      break;
  }
}


void state_base() {

  if (btnStart._signal && !btnStop._signal) {
    if (objTimeOne.toSeconds() > 0) change_state((int)STATE_START);
  }

  if (btnTimeUp._signal || btnTimeDown._signal) {
    change_state((int)STATE_TIME);
  }

}


void state_start() {
  if(servo_angle<=90) servo_angle += 1;
  servo.write(servo_angle);
  delay(20);
  if(btnServo._signal) {
    PORTL ^= 3; // ???
    change_state(STATE_WORK);
    _seconds = 0;
    one_seconds_flag = false;
    two_seconds_flag = false;
    cnt_seconds_flag = 0;
    ta = millis();
    motor_on();
    UV_on();
  }
}

void state_work() {
  if(!btnServo._signal) {
    //UV_off();
    change_state(STATE_STOP);
  }
  update_time();
  if(two_seconds_flag) {
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (!isnan(event.temperature)) {
      //Serial.println(event.temperature);
      if(event.temperature<TINF) {
        resistor_on();
        fan_off();
      } else if(event.temperature>TSUP) {
        resistor_off();
        fan_on();
      } else {
        resistor_off();
        fan_off();
      }

    }
    two_seconds_flag = false;
  }
  if (one_seconds_flag) {
    objTimeTwo = objTimeOne;
    objTimeTwo.decSeconds(_seconds);
    one_seconds_flag = false;
  }
  if ((_seconds == objTimeOne.toSeconds()) || btnStop._signal) {
    //UV_off();
    change_state((int)STATE_STOP);
  }
}

void state_stop() {
  motor_off();
  fan_off();
  resistor_off();
  UV_off();
  if(servo_angle>=0) servo_angle -= 1;
  servo.write(servo_angle);
  delay(20);
  if(!btnServo._signal) {
    servo.write(0);
    PORTL ^= 3;
    change_state(STATE_BASE);
  }
}

void state_time() {
  if (btnTimeUp._signal && btnTimeDown._signal) return;
  else {
    if (btnTimeUp._signal) {
      change_state((int)STATE_TIME_UP);
      _seconds = 0;
      ta = millis();
    }
    if (btnTimeDown._signal) {
      change_state((int)STATE_TIME_DOWN);
      _seconds = 0;
      ta = millis();
    }
  }
  if (btnStart._signal) {
    change_state((int)STATE_BASE);
    while (btnStart._signal) btnUpdate(&btnStart);
  }
}


void state_time_up() {
  update_time();
  /*
    seems to be growing quite rapidly: after holding the button for:
    0s: nothing          -> tot:  0
    1s: increase by 4s   -> tot:  4
    2s: increase by 9s   -> tot: 13
    3s: increase by 16s  -> tot: 29
    4s: increase by 25s  -> tot: 54
    5+s: increase by 30s -> tot: 84, 114, 144...
   */
  int up_s = min(pow(_seconds + 1, 2),30); // looks quite inefficient to calculate a power even if we know it will be greater than 30...
  if (up_s > 1) objTimeOne.incSeconds(up_s);
  if (!btnTimeUp._signal) {
    if (up_s <= 1) objTimeOne.incSeconds(up_s*60); // why not just 60?
    change_state((int)STATE_TIME);
  }
}
void state_time_down() {
  update_time();
  int dw_s = min(pow(_seconds + 1, 2), 30);
  if (dw_s > 1) objTimeOne.decSeconds(dw_s);
  if (!btnTimeDown._signal) {
    if (dw_s <= 1) objTimeOne.decSeconds(dw_s * 60);
    change_state((int)STATE_TIME);
  }
}




/**
 * Writes whatever pins it needs to turn the motor on
 */
void motor_on() {
  digitalWrite(MOTOR_CW,HIGH);
  digitalWrite(MOTOR_CCW,LOW);

}
/**
 * Writes whatever pins it needs to turn the motor off
 */
void motor_off(){
  digitalWrite(MOTOR_CW,LOW);
  digitalWrite(MOTOR_CCW,LOW);
}

/**
 * Changes the state of the program to a new one
 * @param new_state
 */
void change_state(int new_state) {
  program_state = new_state;
  serial_flag = true;
}

void update_time(){
  int old = _seconds;
  _seconds = ((int)((millis()-ta)/1000));
  if(old!=_seconds)  {
    one_seconds_flag = true;
    cnt_seconds_flag+=1;
  }
  if(cnt_seconds_flag == 2){
    two_seconds_flag = true;
    cnt_seconds_flag = 0;
  }
}

void resistor_on() {
  PORTC |= B00111100;
}

void resistor_off() {
  PORTC &= ~(B00111100);
}

void fan_on() {
  digitalWrite(31,HIGH);
}

void fan_off() {
  digitalWrite(31,LOW);
}

void UV_on() {
  digitalWrite(30,HIGH);
}

void UV_off() {
  digitalWrite(30,LOW);
}
