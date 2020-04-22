#include "tcpserver.h"

TCPServer::TCPServer(unsigned int port) : stopSock(false) {
    inited = false;
    init(port);
    inited = true;
}

TCPServer::TCPServer() {
    listeningPort = 0;
}

TCPServer::~TCPServer() {
    stop();
}

int TCPServer::init(unsigned int port) {
    listeningPort = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
        serverError("Error: ");

    enable_keepalive(sockfd);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    started = false;
    return 0;
}

inline void TCPServer::serverError(std::string const& msg)
{
    std::cerr << msg << errno << "  " << strerror(errno) << std::endl;
}

int TCPServer::enable_keepalive(int sock) {
    int yes = 1;

    if(setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) == -1) {
        serverError("Error: ");
        return -1;
    }

    int idle = 1;

    if(setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) == -1) {
        serverError("Error: ");
        return -1;
    }

    int interval = 1;

    if(setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) == -1) {
        serverError("Error: ");
        return -1;
    }

    int maxpkt = 10;

    if(setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int)) == -1) {
        serverError("Error: ");
        return -1;
    }

    return 0;
}

TCPClient TCPServer::accept() {
    if(started) {
        int newsockfd = ::accept(sockfd, (struct sockaddr*) &cliaddr, &clilen);

        if(newsockfd == -1)
            serverError("Error: ");

        return TCPClient(newsockfd);
    }
    else return TCPClient();
}

int TCPServer::start() {
    if(listeningPort == 0) {
         serverError("ERROR No port defined to listen to");
        return 1;
    }

    if(bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
        serverError("Binding error: ");
        return 1;
    }

    listen(sockfd, 5);
    clilen = sizeof(cliaddr);

    started = true;
    stopSock = false;

    return 0;
}

int TCPServer::run(std::function<void(TCPServer* sock)> fn) {
    thr = std::async([this, fn]() {
        while(!stopSock)
            fn(this);
    });
    return 0;
}

int TCPServer::runBlocking(std::function<void(TCPServer* sock)> fn) {
    while(!stopSock)
        fn(this);

    return 0;
}

int TCPServer::stop() {
    stopSock = true;
    int res = close(sockfd);

    if(res < 0)
        serverError("Error: ");

    return 0;
}
