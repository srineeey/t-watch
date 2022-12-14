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
    MotorHandle::createInstance();
    RadioHandle::createInstance();

//TODO: move to timehandle
    //Synchronize time to system time
    TTGOClass::getWatch()->rtc->syncToSystem();
    //Check if the RTC clock matches, if not, use compile time
    TTGOClass::getWatch()->rtc->check();
    RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

//TODO: move to display/gui handle
    //Initialize lvgl
    TTGOClass::getWatch()->lvgl_begin();

//TODO: where to move startup?
    RadioHandle::getInstance()->turn_wifi_on(false);
    (RadioHandle::getInstance())->wifi_connect();
    Serial.println("WiFi connected: " + (String)((RadioHandle::getInstance())->wifi_connect()));

    RadioHandle::getInstance()->turn_ble_on();

    DisplayHandle::getInstance()->turn_display_on();

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
    else{
        ClockApp::getInstance(0, clockname)->background_loop();
    }
    
}



MasterApp *MasterApp::masterapp;

MasterApp *MasterApp::getInstance(unsigned int _app_id, char *_name) {
    if (MasterApp::masterapp == nullptr) {
        MasterApp::masterapp = new MasterApp(_app_id, _name);
    }
    return MasterApp::masterapp;
}