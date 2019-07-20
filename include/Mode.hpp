#include "Arduino.h"

struct Rgb_s{
    char red;
    char green;
    char blue;
};


class Mode{
private:
    Rgb_s * rgb_s;
    char  mode;
    char  bright;

public:
    Mode();
    ~Mode();
    
    void changeMode(void);
    void changeBright(void);
    void changeRgb(void);
    
    void setMode (char value);
    void setBright (char value);
    void setRgb(Rgb_s * value);
    
};