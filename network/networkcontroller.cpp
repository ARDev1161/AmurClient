#include "networkcontroller.h"

networkController::networkController()
{
    client = new TCPClient();
}

networkController::~networkController()
{
    delete client;
}
