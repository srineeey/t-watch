#pragma once

#include "config.h"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>
#include <WiFi.h>

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


class MotorHandle{
    bool motor_is_on = false;

    public:
    static MotorHandle *createInstance();
    static MotorHandle *getInstance();
    MotorHandle();

    protected:
    static  MotorHandle *motorhandle;

    public:
    void vibrate(uint8_t effect = 1);

};

class RadioHandle{
    public:
    bool ble_is_on = false;
    bool ble_is_connected = false;
    bool wifi_is_on = false;
    bool wifi_is_connected = false;
    
    private:
    const char *ssid = "Jarvis";
    const char *password = "sweetWiFimakiroll2020";
    IPAddress ip = WiFi.localIP();
    String mac = WiFi.macAddress();


    public:
    static RadioHandle *createInstance();
    static RadioHandle *getInstance();

    protected:
    static  RadioHandle *radiohandle;

    public:
    void turn_ble_off();
    void turn_ble_on();

    void turn_wifi_off();
    void turn_wifi_on(bool scan = false);
    void wifi_scan();
    bool wifi_connect(String ssid, String password);
    bool wifi_connect();

};