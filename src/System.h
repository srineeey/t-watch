#pragma once

#include "config.h"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>

//TODO: multiple threads for system handles and apps


class TouchHandle{
    int16_t x_touch = -1;
    int16_t y_touch = -1;
    bool touched = false;

    public:
    static TouchHandle *createInstance();
    static TouchHandle *getInstance();

    protected:
    static TouchHandle *touchhandle;

    public:
    bool is_touched();
    int16_t get_x_touch();
    int16_t get_y_touch();
};




class DisplayHandle{
    bool display_is_on = false;

    public:
    static DisplayHandle *createInstance();
    static DisplayHandle *getInstance();

    protected:
    static DisplayHandle *displayhandle;

    public:
    void turn_display_on();
    void turn_display_off();
};


class PowerHandle{
    uint8_t capacity = 200;

    public:
    static PowerHandle *createInstance();
    static PowerHandle *getInstance();

    protected:
    static PowerHandle *powerhandle;

    public:
    uint8_t get_capacity();
};
