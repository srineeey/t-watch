#pragma once

#include "config.h"

#include "ClockApp.h"

//#include "App.cpp"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>

#include "System.h"



//Basic Clock App
//class ClockApp : public CoreApp{

ClockApp::ClockApp(unsigned int _app_id, char *_name) : 
isactive(true), 
app_id(_app_id), 
name(_name)
{
    Serial.println("ClockApp started");
    DisplayHandle::getInstance()->turn_display_on();
};

void ClockApp::open_app(){
    TTGOClass::getWatch()->tft->setTextFont(1);
    //TTGOClass::getWatch()->tft->setTextSize(1);
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
                    DisplayHandle::getInstance()->turn_display_on();
//TODO: update callbacks?
                    this->display_time();
                    this->update_capacity();
                    this->update_date();
                }
                else{
                    this->update_time();
                }
                (this->updates)++;

                if(this->updates > 5)
                {
                    DisplayHandle::getInstance()->turn_display_off();
                    this->updates = 0;
                }
            }
        }
        else
        {
            /* wait for touch to turn backlit on*/
            //sleep...

            background_loop();

//TODO: external touch handle
            if(TouchHandle::getInstance()->is_touched()){
                MotorHandle::getInstance()->vibrate(17);
                this->updates = 1;
//TODO: haptics using DRV2605
                //TTGOClass::getWatch()->motor->onec(150);
            }

        }
    };

void ClockApp::display_time(){
        
        //TTGOClass::getWatch()->tft->setTextSize(1);

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

void ClockApp::update_capacity(){
    uint8_t new_capacity = PowerHandle::getInstance()->get_capacity();
        if(this->capacity != new_capacity){
            this->capacity = new_capacity;
            int _width = TTGOClass::getWatch()->tft->drawNumber(this->capacity, 215, 0, 1);    
            TTGOClass::getWatch()->tft->drawChar('%', 215+_width, 0, 1);
        }
    }

void ClockApp::update_date(){
    RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();
    if(this->day != tnow.day){
        this->day = tnow.day;
        this->month = tnow.month;
        this->year = tnow.year;

        char date_str[10];

        sprintf(date_str, "%d/%d/%d", this->day, this->month, this->year);

        TTGOClass::getWatch()->tft->drawString(date_str, 0, 0);
    }
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
        this->draw_number(this->hour, 0, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 64, 90, 7);
        MotorHandle::getInstance()->vibrate();
    }
}



void ClockApp::update_min(RTC_Date tnow){
    if (this->min != tnow.minute) {
        this->min = tnow.minute;
        this->draw_number(this->min, 76, 90, 7);
        TTGOClass::getWatch()->tft->drawChar(':', 140, 90, 7);
    }
}

void ClockApp::update_sec(RTC_Date tnow){
    if (this->sec != tnow.second) {
        this->sec = tnow.second;
        this->draw_number(this->sec, 152, 90, 7);
        MotorHandle::getInstance()->vibrate(24);
    }
}

//TODO: Optimize background loop
void ClockApp::background_loop(){
    //delay(uint32_t ms);
    RTC_Date tnow = TTGOClass::getWatch()->rtc->getDateTime();
    if ((tnow.minute == 0) && this->min != tnow.minute) {
    //if (this->sec != tnow.second) {
        this->min = tnow.minute;
        MotorHandle::getInstance()->vibrate(16);
    }
    else if ((tnow.minute % 15 == 0 ) && this->min != tnow.minute) {
    //if (this->sec != tnow.second) {
        this->min = tnow.minute;
        MotorHandle::getInstance()->vibrate(15);
    }
};




ClockApp *ClockApp::clockapp;

ClockApp *ClockApp::getInstance(unsigned int _app_id, char *_name) {
    if (ClockApp::clockapp == nullptr) {
        ClockApp::clockapp = new ClockApp(_app_id, _name);
    }
    return ClockApp::clockapp;
}
