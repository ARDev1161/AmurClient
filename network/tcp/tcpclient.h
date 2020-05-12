#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <cstdlib>
#include <unistd.h> // Файл заголовка, который обеспечивает доступ к API операционной системы POSIX
#include <string> // String class
#include <cstring> // This header file defines several functions to manipulate C strings and arrays.
#include <sys/types.h>
#include <sys/socket.h> // Базовые функции сокетов BSD и структуры данных.
#include <netinet/tcp.h> // Header shall define the following macro for use as a socket option at the IPPROTO_TCP level
#include <netinet/in.h> // Семейства адресов/протоколов PF_INET и PF_INET6. Широко используются в сети Интернет, включают в себя IP-адреса, а также номера портов TCP и UDP.
#include <netdb.h> // Функции для преобразования протокольных имен и имен хостов в числовые адреса. Используются локальные данные аналогично DNS.
#include <arpa/inet.h> // Функции для работы с числовыми IP-адресами.
#include <chrono>
#include <thread>

#define COUNT_CONNECT_TRYING 3

/*!
    \brief Класс сетевого клиента с протоколом TCP

    Данный класс инкапсулирует логику сетевого клиента с протоколом TCP.
*/
class TCPClient
{
    int sockfd = 0;
    bool connected;
    char buffer[1024];

    bool hasError();
    inline void clientError(std::string const& msg);
    int enable_keepalive(int sock);
public:
    TCPClient(std::string host, unsigned int port);
    TCPClient(int sock);
    TCPClient();
    ~TCPClient();

    bool checkAlive();
    bool connect(std::string host, unsigned int port);
    inline void disconnect();

    int write(std::string const& mesg);
    std::string read();
    std::string readAll();
};

#endif // TCPCLIENT_H
