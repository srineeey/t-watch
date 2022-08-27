#pragma once

//#include <Arduino.h>

//#include "config.h"


//#include <LilyGoWatch.h>
//#include <soc/rtc.h>

#include "ClockApp.h"


//TTGOClass *ttgo;


//unsigned int targetTime = 0;       // for next 1 second display update
// uint32_t clockUpTime = 0;      // track the time the clock is displayed

//byte xcolon = 0;

//unsigned int hh, mm, ss, mmonth, dday; // H, M, S variables
//unsigned int yyear; // Year is 16 bit int


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //ttgo = TTGOClass::getWatch();
  TTGOClass::getWatch()->begin();


  //Synchronize time to system time
  TTGOClass::getWatch()->rtc->syncToSystem();

  //Check if the RTC clock matches, if not, use compile time
  TTGOClass::getWatch()->rtc->check();

 //get sensor readings
  RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

  //Initialize lvgl
  TTGOClass::getWatch()->lvgl_begin();

  // Start ClockApp
  char clockname[] = "clock";
  ClockApp::getInstance(0, clockname);
  
  // Turn on the backlight
  TTGOClass::getWatch()->openBL();
}



void loop() {
  // put your main code here, to run repeatedly:
  
  char clockname[] = "clock";
  ClockApp::getInstance(0, clockname)->loop();

}
