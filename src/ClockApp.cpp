#pragma once

#include "config.h"

#include "ClockApp.h"

//#include "App.cpp"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>



//Basic Clock App
//class ClockApp : public CoreApp{

int16_t x_touch = 0, y_touch = 0;

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
        if (this->updates >= 1)
        {
            if (this->targetTime < millis()) {
                this->targetTime = millis() + 1000;
                if(updates == 1)
                {
                    TTGOClass::getWatch()->bl->on();
		            TTGOClass::getWatch()->displayWakeup();
                    this->display_time();  
                }
                else{
                    this->update_time();
                }
                //this->display_time(); // Call every second but only update time every minute
                (this->updates)++;

                if(this->updates > 5)
                {
                    TTGOClass::getWatch()->displaySleep();
		            TTGOClass::getWatch()->bl->off();
                    this->updates = 0;
                }
            }
        }
        else
        {
            /* wait for touch to turn backlit on*/
            //sleep...

            //TODO: external touch handle
            if(TTGOClass::getWatch()->getTouch(x_touch, y_touch)){
                this->updates = 1;
                //TODO: haptics using DRV2605
                //TTGOClass::getWatch()->motor->onec(150);
            }

        }
    };

void ClockApp::display_time(){

        this->xpos = 40; // Stating position for the display
        this->ypos = 90;
        
        TTGOClass::getWatch()->tft->setTextSize(1);

        RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

        TTGOClass::getWatch()->tft->setTextColor(0xFBE0, TFT_BLACK); // Orange

        this->hour = tnow.hour;
        this->draw_number(this->hour, 0, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 64, 90, 7);

        this->min = tnow.minute;
        this->draw_number(this->min, 76, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 140, 90, 7);

        this->sec = tnow.second;
        this->draw_number(this->sec, 152, 90, 7);

    }

void ClockApp::update_time(){
    RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();

    update_hour(tnow);
    update_min(tnow);
    update_sec(tnow);

}

void ClockApp::draw_number(unsigned int val, unsigned int xpos, unsigned int ypos, unsigned int fontsize){
    int16_t sumX = 0;
    if (val < 10){
        sumX = TTGOClass::getWatch()->tft->drawNumber(0, xpos, ypos, fontsize);    
    }
    TTGOClass::getWatch()->tft->drawNumber(val, xpos + sumX, ypos, fontsize);
}

void ClockApp::update_hour(RTC_Date tnow){
    if (this->hour != tnow.hour) {
        this->hour = tnow.hour;
        //TTGOClass::getWatch()->tft->drawNumber(this->hour, 0, 90, 7);
        this->draw_number(this->hour, 0, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 64, 90, 7);
    }
}



void ClockApp::update_min(RTC_Date tnow){
    if (this->min != tnow.minute) {
        this->min = tnow.minute;
        //TTGOClass::getWatch()->tft->drawNumber(this->min, 76, 90, 7);
        this->draw_number(this->min, 76, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 140, 90, 7);
    }
}

void ClockApp::update_sec(RTC_Date tnow){
    if (this->sec != tnow.second) {
        this->sec = tnow.second;
        //TTGOClass::getWatch()->tft->drawNumber(this->sec, 152, 90, 7);
        this->draw_number(this->sec, 152, 90, 7);
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