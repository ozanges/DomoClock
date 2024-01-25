
#ifndef _SERIAL_DATA_
#define _SERIAL_DATA_

struct RequestData {
    char key[5];
    long unsigned int  previousMillis;
    int  refreshDelay;
    int  acknowledgeState; // 0 = must be initialized ; 1 = sent notification; 2 = acknowledged
};

struct ResponseData {
    char *key;
    const char *value;
};

#endif