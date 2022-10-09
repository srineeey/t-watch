#pragma once

//#include <Arduino.h>
//#include "config.h"
//#include <LilyGoWatch.h>
//#include <soc/rtc.h>

//#include "ClockApp.h"
#include "MasterApp.h"


//TTGOClass *ttgo;


char mastername[] = "masterapp";

void setup() {
  // put your setup code here, to run once:

//TODO:Serial messages not working
  //Serial.begin(9600);
  
  MasterApp::getInstance(0, mastername);
}



void loop() {
  // put your main code here, to run repeatedly:

  MasterApp::getInstance(0, mastername)->loop();

}
