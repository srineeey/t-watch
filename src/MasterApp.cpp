#pragma once

#include "config.h"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>

//TODO: handles for watch system
#include "System.h"

#include "MasterApp.h"

#include "ClockApp.h"







MasterApp::MasterApp(unsigned int _app_id, char *_name) : 
isactive(true), 
app_id(_app_id), 
name(_name)
{
    //initialize watch

//TODO: startup shutdown restart functions
    //ttgo = TTGOClass::getWatch();
    TTGOClass::getWatch()->begin();

//TODO: system handle (apps?) for sensor readings

//TODO: function for handle initialization
    //initialize handles
    TouchHandle::createInstance();
    DisplayHandle::createInstance()->turn_display_on();
    PowerHandle::createInstance();

//TODO: timehandle
    //Synchronize time to system time
    TTGOClass::getWatch()->rtc->syncToSystem();

    //Check if the RTC clock matches, if not, use compile time
    TTGOClass::getWatch()->rtc->check();

    //get sensor readings
    RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

    //Initialize lvgl
    TTGOClass::getWatch()->lvgl_begin();

//TODO: app startup functionality (list of apps, function)
    //initialize startup apps
    // Start ClockApp
    char clockname[] = "clock";
    ClockApp::getInstance(0, clockname);
    
    Serial.println("MasterApp started");
};

void MasterApp::loop()
{
//TODO: app/handle (loop) management (synchronous?)
    char clockname[] = "clock";

    if(ClockApp::getInstance(0, clockname)->isactive){
        ClockApp::getInstance(0, clockname)->loop();
    }
    
}



MasterApp *MasterApp::masterapp;

MasterApp *MasterApp::getInstance(unsigned int _app_id, char *_name) {
    if (MasterApp::masterapp == nullptr) {
        MasterApp::masterapp = new MasterApp(_app_id, _name);
    }
    return MasterApp::masterapp;
}