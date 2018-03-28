#ifndef COM_h
#define COM_h

#define BAUDRATE 9600

void setup_com() {
  Serial.begin(BAUDRATE);
}

// sembra abbastanza inutile come header


#endif
