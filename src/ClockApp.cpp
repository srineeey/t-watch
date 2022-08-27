#pragma once

#include "config.h"

#include "ClockApp.h"

//#include "App.cpp"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>



//Basic Clock App
//class ClockApp : public CoreApp{

    

ClockApp::ClockApp(unsigned int _app_id, char *_name) : 
isactive(true), 
app_id(_app_id), 
name(_name)
{
    Serial.println("ClockApp started");
};

void ClockApp::open_app(){
    TTGOClass::getWatch()->tft->setTextFont(1);
    TTGOClass::getWatch()->tft->setTextSize(1);
    TTGOClass::getWatch()->tft->fillScreen(TFT_BLACK);
    TTGOClass::getWatch()->tft->setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
    this->loop();
};

void ClockApp::close_app(){
        TTGOClass::getWatch()->tft->fillScreen(TFT_BLACK);
    };

void ClockApp::loop()
    {
        if (this->targetTime < millis()) {
            this->targetTime = millis() + 1000;
            //this->display_time(); // Call every second but only update time every minute
            this->update_time();
            }
    };

void ClockApp::display_time(){

        this->xpos = 40; // Stating position for the display
        this->ypos = 90;
        
        TTGOClass::getWatch()->tft->setTextSize(1);

        RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

                if (this->sec != tnow.second) {

            this->hour = tnow.hour;
            this->min = tnow.minute;
            this->sec = tnow.second;

            // Font 7 is a 7-seg display but only contains
            // characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .

            //TTGOClass::getWatch()->tft->setTextColor(0x39C4, TFT_BLACK); // Set desired color
            TTGOClass::getWatch()->tft->drawString("88:88", xpos, ypos, 7);
            TTGOClass::getWatch()->tft->setTextColor(0xFBE0, TFT_BLACK); // Orange

            if (this->hour < 10) xpos += TTGOClass::getWatch()->tft->drawChar('0', xpos, ypos, 7);
            xpos += TTGOClass::getWatch()->tft->drawNumber(this->hour, xpos, ypos, 7);
            xcolon = xpos + 3;
            xpos += TTGOClass::getWatch()->tft->drawChar(':', xcolon, ypos, 7);
            if (this->min < 10) xpos += TTGOClass::getWatch()->tft->drawChar('0', xpos, ypos, 7);
            TTGOClass::getWatch()->tft->drawNumber(this->min, xpos, ypos, 7);
        }


        if (this->sec % 2) { // Toggle the colon every second
            TTGOClass::getWatch()->tft->setTextColor(0x39C4, TFT_BLACK);
            xpos += TTGOClass::getWatch()->tft->drawChar(':', xcolon, ypos, 7);
            TTGOClass::getWatch()->tft->setTextColor(0xFBE0, TFT_BLACK);
        //    Serial.println("colon on");
        } else {
            TTGOClass::getWatch()->tft->drawChar(':', xcolon, ypos, 7);
        //    Serial.println("colon off");
        }

    }

void ClockApp::update_time(){
    RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

    update_hour(tnow);
    update_min(tnow);
    update_sec(tnow);

}



void ClockApp::update_hour(RTC_Date tnow){
    if (this->hour != tnow.hour) {
        this->hour = tnow.hour;
        TTGOClass::getWatch()->tft->drawNumber(this->hour, 0, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 64, 90, 7);
    }
}

void ClockApp::update_min(RTC_Date tnow){
    if (this->min != tnow.minute) {
        this->min = tnow.minute;
        TTGOClass::getWatch()->tft->drawNumber(this->min, 76, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 140, 90, 7);
    }
}

void ClockApp::update_sec(RTC_Date tnow){
    if (this->sec != tnow.second) {
        this->sec = tnow.second;
        TTGOClass::getWatch()->tft->drawNumber(this->sec, 152, 90, 7);
    }
}

void ClockApp::background_loop(){

};

ClockApp *ClockApp::clockapp;

ClockApp *ClockApp::getInstance(unsigned int _app_id, char *_name) {
    if (ClockApp::clockapp == nullptr) {
        ClockApp::clockapp = new ClockApp(_app_id, _name);
    }
    return ClockApp::clockapp;
}