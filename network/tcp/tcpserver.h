#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <future>
#include <functional>

#include "tcpclient.h"

#include <errno.h>
#include <string.h>

#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <future>

/*!
    \brief Класс сетевого сервера с протоколом TCP

    Данный класс инкапсулирует логику сетевого сервера с протоколом TCP.
*/
class TCPServer
{
    int enable_keepalive(int sock);

    int timeout = 7; //timeout in seconds

    int sockfd;//start server to listen for clients to send them ids
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    static const unsigned int buffSize = 1000;
    char mesg[buffSize];

    unsigned int listeningPort = 7777;
    bool started = false;
    bool inited = false;
    bool stopSock;


    inline void serverError(std::string const& msg);
public:
    TCPServer(unsigned int port);
    TCPServer();
    ~TCPServer();

    TCPClient accept();

    bool init(unsigned int port, bool keepAlive=false);//!<Necessary only if not already done by using constructor with port
    int start();
    int run(std::function<void(TCPServer* sock)> fn);
    int runBlocking(std::function<void(TCPServer* sock)> fn);
    int stop();

protected:
    std::future<void> thr;

};

#endif // TCPSERVER_H
