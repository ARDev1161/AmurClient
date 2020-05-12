#include "tcpserver.h"

/*!
  Создаёт экземпляр класса сетевого сервера с протоколом TCP.
  \param[in] port Порт сервера
*/
TCPServer::TCPServer(unsigned int port) : stopSock(false) {
    inited = false;
    init(port);
    inited = true;
}

/*!
  Создаёт экземпляр класса сетевого сервера с протоколом TCP.
*/
TCPServer::TCPServer() {
    listeningPort = 0;
}

TCPServer::~TCPServer() {
    stop();
}

/*!
  Инициирует работу сервера.
  \param[in] port Порт сервера
*/
void TCPServer::init(unsigned int port) {
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
}

/*!
  Вывод в консоль сообщения об ошибке.
  \param[in] &msg Ссылка на выводимое сообщение
*/
inline void TCPServer::serverError(std::string const& msg)
{
    std::cerr << msg << errno << "  " << strerror(errno) << std::endl;
}

/*!
  Включение у сокета функции KEEPALIVE.
  \param[in] sock Установленный сокет
  \return Результат включения KEEPALIVE, -1 если не удалось
*/
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

/*!
  Принимает запрос на установление соединения.
  \return Возвращает экземпляр сетевого клиента, связанный с принятым соединением
*/
TCPClient TCPServer::accept() {
    if(started) {
        int newsockfd = ::accept(sockfd, (struct sockaddr*) &cliaddr, &clilen);

        if(newsockfd == -1)
            serverError("Error: ");

        return TCPClient(newsockfd);
    }
    else return TCPClient();
}

/*!
  Запуск сервера.
  \return Результат запуска сервера, 0 если удалось
*/
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

/*!
  Остановка сервера.
  \return Результат остановки сервера, 0 если удалось
*/
int TCPServer::stop() {
    stopSock = true;
    int res = close(sockfd);

    if(res < 0)
        serverError("Error: ");

    return res;
}
