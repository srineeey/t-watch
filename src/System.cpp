#pragma once

#include "config.h"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>

#include "System.h"

//TODO: multiple threads for system handles and apps
//TODO: templates for handles and apps

bool TouchHandle::is_touched(){
    this->touched = TTGOClass::getWatch()->getTouch(this->x_touch, this->y_touch);
    return this->touched;
}


TouchHandle *TouchHandle::touchhandle;

TouchHandle *TouchHandle::createInstance() {
    if (TouchHandle::touchhandle == nullptr) {
        TouchHandle::touchhandle = new TouchHandle();
    }
    return TouchHandle::touchhandle;
}

TouchHandle *TouchHandle::getInstance() {
    return TouchHandle::touchhandle;
}


void DisplayHandle::turn_display_on(){
    if(DisplayHandle::display_is_on == false)
    {
        TTGOClass::getWatch()->bl->on();
        TTGOClass::getWatch()->displayWakeup();
        DisplayHandle::display_is_on = true;
    }
    
}

void DisplayHandle::turn_display_off(){
    if(DisplayHandle::display_is_on == true)
    {
        TTGOClass::getWatch()->displaySleep();
        TTGOClass::getWatch()->bl->off();
        DisplayHandle::display_is_on = false;
    }
}

DisplayHandle *DisplayHandle::displayhandle;

DisplayHandle *DisplayHandle::createInstance() {
    if (DisplayHandle::displayhandle == nullptr) {
        DisplayHandle::displayhandle = new DisplayHandle();
    }
    return DisplayHandle::displayhandle;
}

DisplayHandle *DisplayHandle::getInstance() {
    return DisplayHandle::displayhandle;
}