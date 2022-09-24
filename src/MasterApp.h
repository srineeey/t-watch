#include "config.h"
#include <LilyGoWatch.h>

//Master App

class MasterApp{
    public:
    bool isactive = true;
    unsigned int app_id = 0;
    char *name = nullptr;

    public:
    static MasterApp *getInstance(unsigned int _app_id, char *_name);

    protected:
    static MasterApp *masterapp;

    //add list for apps

    

    MasterApp(unsigned int _app_id, char *_name);

//    void open_app();

//    void close_app();
    

    public:
    void loop();
    void background_loop();

};

