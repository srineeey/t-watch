#pragma once

//#include <Arduino.h>

//#include "config.h"


//#include <LilyGoWatch.h>
//#include <soc/rtc.h>

//#include "ClockApp.h"
#include "MasterApp.h"


//TTGOClass *ttgo;


//unsigned int targetTime = 0;       // for next 1 second display update
// uint32_t clockUpTime = 0;      // track the time the clock is displayed

//byte xcolon = 0;

//unsigned int hh, mm, ss, mmonth, dday; // H, M, S variables
//unsigned int yyear; // Year is 16 bit int
char mastername[] = "masterapp";

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  MasterApp::getInstance(0, mastername);
}



void loop() {
  // put your main code here, to run repeatedly:

  MasterApp::getInstance(0, mastername)->loop();

}
