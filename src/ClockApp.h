#include "config.h"
#include <LilyGoWatch.h>

//Basic Clock App
//class ClockApp : public CoreApp{

class ClockApp{
    public:
    bool isactive = true;
    unsigned int app_id = 0;
    char *name = nullptr;

    unsigned int updates = 1;

    public:
    static ClockApp *getInstance(unsigned int _app_id, char *_name);

    protected:
    static ClockApp *clockapp;

    protected:
    unsigned int hour = 0;
    unsigned int min = 0;
    unsigned int sec = 0;
    unsigned int targetTime = 0;

    

    ClockApp(unsigned int _app_id, char *_name);

    void open_app();

    void close_app();

    void display_time();

    void update_time();

    void draw_number(unsigned int val, unsigned int xpos, unsigned int ypos, unsigned int fontsize);

    void update_hour(RTC_Date tnow);
    void update_min(RTC_Date tnow);
    void update_sec(RTC_Date tnow);
    

    

    public:
    void loop();
    void background_loop();

};

