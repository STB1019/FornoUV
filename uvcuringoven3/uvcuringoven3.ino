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


#define TINF 25
#define TSUP 55

#define MOTOR_CW 36
#define MOTOR_CCW 37



void state_base();
void state_start();
void state_work();
void state_stop();
void state_time();
void state_time_up();
void state_time_down();
void motor_On();
void motor_Off();
void change_state(int new_state);
void update_time();
void resistor_on();
void resistor_off();
void fan_on();
void fan_off();
void UV_on();
void UV_off();


int servo_angle;
int program_state;

long ta;
int _seconds;

bool serial_flag;
bool one_seconds_flag;
bool two_seconds_flag;
int cnt_seconds_flag;

Time objTimeOne,objTimeTwo;
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
    PORTL ^= 3;
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
      }else if(event.temperature>TSUP) {
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
  int up_s = min(pow(_seconds + 1, 2),30);
  if(up_s>1)objTimeOne.incSeconds(up_s);
  if (!btnTimeUp._signal) {
    if(up_s<=1)objTimeOne.incSeconds(up_s*60);
    change_state((int)STATE_TIME);
  }
}
void state_time_down() {
  update_time();
  int dw_s = min(pow(_seconds + 1, 2),30);
  if(dw_s>1) objTimeOne.decSeconds(dw_s);
  if (!btnTimeDown._signal) {
    if(dw_s<=1) objTimeOne.decSeconds(dw_s*60);
    change_state((int)STATE_TIME);
  }
}


void motor_on() {
  digitalWrite(MOTOR_CW,HIGH);
  digitalWrite(MOTOR_CCW,LOW);
  
}
void motor_off(){
  digitalWrite(MOTOR_CW,LOW);
  digitalWrite(MOTOR_CCW,LOW);
}

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


