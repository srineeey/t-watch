#pragma once

#include "config.h"

#include <Arduino.h>
#include <LilyGoWatch.h>
#include <soc/rtc.h>

#include "System.h"

//TODO: multiple threads for system handles and apps
//TODO: templates (inheritance!) for handles and apps

bool TouchHandle::is_touched(){
    this->touched = TTGOClass::getWatch()->getTouch(this->x_touch, this->y_touch);
    return this->touched;
}

int16_t TouchHandle::get_x_touch(){
    //TODO: check xvalue!
    return this->x_touch;
};

int16_t TouchHandle::get_y_touch(){
    //TODO: check xvalue!
    return this->y_touch;
};


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







uint8_t PowerHandle::get_capacity(){
//TODO: check formula
    int _capacity = (int)(TTGOClass::getWatch()->power->getBattVoltage() - 30) * 100 / 4170;
    _capacity = std::max(_capacity, 0);
    this->capacity = std::min(_capacity, 100);
    return this->capacity;
}

PowerHandle *PowerHandle::powerhandle;

PowerHandle *PowerHandle::createInstance() {
    if (PowerHandle::powerhandle == nullptr) {
        PowerHandle::powerhandle = new PowerHandle();
    }
    return PowerHandle::powerhandle;
}

PowerHandle *PowerHandle::getInstance() {
    return PowerHandle::powerhandle;
}




MotorHandle::MotorHandle(){
    TTGOClass::getWatch()->enableDrv2650();
    TTGOClass::getWatch()->drv->selectLibrary(1);
    TTGOClass::getWatch()->drv->setMode(DRV2605_MODE_INTTRIG);
}

void MotorHandle::vibrate(uint8_t effect){
    //1 = hard bump
    TTGOClass::getWatch()->drv->setWaveform(0, effect); // play effect
    TTGOClass::getWatch()->drv->setWaveform(1, 0);      // end waveform
    TTGOClass::getWatch()->drv->go();                   // play the effect!
}


MotorHandle *MotorHandle::motorhandle;

MotorHandle *MotorHandle::createInstance() {
    if (MotorHandle::motorhandle == nullptr) {
        MotorHandle::motorhandle = new MotorHandle();
    }
    return MotorHandle::motorhandle;
}

MotorHandle *MotorHandle::getInstance() {
    return MotorHandle::motorhandle;
}









String translateEncryptionType(wifi_auth_mode_t encryptionType) {
 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
  return "UNKNOWN";
}





void RadioHandle::turn_wifi_on(bool scan){
    this->turn_wifi_off();
	WiFi.mode(WIFI_MODE_STA);
    if(scan) this->wifi_scan();
}

void RadioHandle::turn_wifi_off(){
    WiFi.disconnect(true);	
	WiFi.mode(WIFI_OFF);
}

void RadioHandle::wifi_scan(){
    int number_nets = WiFi.scanNetworks();
    int i_net_to_connect = 0;

    for(; i_net_to_connect < number_nets; i_net_to_connect++){
        if(WiFi.SSID(i_net_to_connect) == this->ssid){
            break;
        }
    }

    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i_net_to_connect));
 
    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i_net_to_connect));
 
    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i_net_to_connect));
 
    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i_net_to_connect));
}


bool RadioHandle::wifi_connect(String ssid, String password){
    
    WiFi.begin(ssid.c_str(), password.c_str());
    int n_delays = 0;
    while ( (WiFi.status() != WL_CONNECTED) || (n_delays >= 20)) {
        delay(1000);
        n_delays++;
        Serial.println("Establishing connection to WiFi..");
    }

    return (bool)(n_delays < 20);
}

bool RadioHandle::wifi_is_connected(){
    return (bool)(WiFi.status() == WL_CONNECTED);
}

bool RadioHandle::wifi_connect(){
    
    WiFi.begin(this->ssid, this->password);
    int n_delays = 0;
    while ( (WiFi.status() != WL_CONNECTED) || (n_delays >= 5)) {
        delay(1000);
        n_delays++;
        Serial.println("Establishing connection to WiFi..");
    }
    return this->wifi_is_connected();
}





RadioHandle *RadioHandle::radiohandle;

RadioHandle *RadioHandle::createInstance() {
    if (RadioHandle::radiohandle == nullptr) {
        RadioHandle::radiohandle = new RadioHandle();
    }
    return RadioHandle::radiohandle;
}

RadioHandle *RadioHandle::getInstance() {
    return RadioHandle::radiohandle;
}
