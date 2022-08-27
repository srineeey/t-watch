

//Generic App virtual class
class App{
    public:
    bool isactive = false;
    unsigned int app_id = 0;
    char *name = nullptr;

};

//Background App virtual class - may run in background
class BackgroundApp : App{
    public:

};

//Core App virtual class - can not be killed
class CoreApp : BackgroundApp{
    public:

};
