#ifndef TCP_H
#define TCP_H

#include "tcpworker.h"

class TCP
{
    Control *amurControl;
    Sensors *amurSensors;

    string *hostName;

public:
    TCP(Control *control, Sensors *sensors, string *hostname);
    ~TCP();

    void addThread();
    void stopThreads();

signals:
    void stopAll(); //остановка всех потоков

};

#endif // TCP_H
