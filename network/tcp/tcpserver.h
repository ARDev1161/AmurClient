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

class TCPServer
{
    int enable_keepalive(int sock);

    int sockfd;//start server to listen for clients to send them ids
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    static const unsigned int buffSize = 1000;
    char mesg[buffSize];

    unsigned int listeningPort;
    bool started;
    bool stopSock;

    inline void serverError(std::string const& msg);
public:
    TCPServer(unsigned int port);
    TCPServer();
    ~TCPServer();

    TCPClient accept();

    bool inited;

    int init(unsigned int port);//!<Necessary only if not already done by using constructor with port
    int start();
    int run(std::function<void(TCPServer* sock)> fn);
    int runBlocking(std::function<void(TCPServer* sock)> fn);
    int stop();

protected:
    future<void> thr;

};

#endif // TCPSERVER_H
