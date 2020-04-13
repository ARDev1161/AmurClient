#include "tcp.h"

TCP::TCP(Control *control, Sensors *sensors, string *hostname)
{
    zanyaControl = control;
    zanyaSensors = sensors;
    hostName = hostname;
}

TCP::~TCP()
{
    stopThreads();
}

void TCP::addThread()
{
    TCPWorker* tcpWorker = new TCPWorker(zanyaControl, zanyaSensors, hostName);
    QThread* tcpThread = new QThread;
    tcpWorker->moveToThread(tcpThread);

    connect(tcpThread, SIGNAL(started()), tcpWorker, SLOT(process()));
    connect(tcpWorker, SIGNAL(finished()), tcpThread, SLOT(quit()));
    connect(this, SIGNAL(stopAll()), tcpWorker, SLOT(stop()));
    connect(tcpWorker, SIGNAL(finished()), tcpWorker, SLOT(deleteLater()));
    connect(tcpThread, SIGNAL(finished()), tcpThread, SLOT(deleteLater()));

    tcpThread->start();
}

void TCP::stopThreads()
{
    emit  stopAll();
}
