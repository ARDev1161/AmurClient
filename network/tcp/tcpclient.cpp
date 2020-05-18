#include "tcpclient.h"

/*!
  Создаёт экземпляр класса сетевого клиента с протоколом TCP.
  \param[in] host Адрес сервера
  \param[in] port Порт сервера
*/
TCPClient::TCPClient(std::string host, unsigned int port):
    sockfd(-1),
    connected(false)
{
    setTimeval();
    connect(host, port);
}

/*!
  Создаёт экземпляр класса сетевого клиента с протоколом TCP.
  \param[in] sock Установленный сокет
*/
TCPClient::TCPClient(int sock):
    sockfd(sock)
{
    setTimeval();
    connected = true;
}

/*!
  Создаёт экземпляр класса сетевого клиента с протоколом TCP.
*/
TCPClient::TCPClient():
    sockfd(-1),
    connected(false)
{
    setTimeval();
}

TCPClient::~TCPClient()
{
    disconnect();
}

void TCPClient::setTimeval()
{
    tv.tv_sec = timeout;
    tv.tv_usec = 0;//Not init'ing this can cause strange errors
}

/*!
  Проверка активности подключения к серверу.
  \return Результат подключения, true если соединение установлено
*/
bool TCPClient::checkAlive()
{
    return (connected && (sockfd != -1));
}

/*!
  Инициирует подключение к серверу.
  \param[in] host Адрес сервера
  \param[in] port Порт сервера
  \param[in] keepAlive Флаг режима KeepAlive по умолчанию false
  \return Результат подключения, true если соединение установлено
*/
bool TCPClient::connect(std::string host, unsigned int port, bool nonBlocking, bool keepAlive)
{
    struct sockaddr_in servAddr;
    struct hostent *server;

    if(connected)
        disconnect();

    std::memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;

    server = gethostbyname(host.data());
    memmove((char*) &servAddr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
    servAddr.sin_port = htons(port);

    sockfd = socket( servAddr.sin_family , SOCK_STREAM, IPPROTO_TCP);

    if(keepAlive) // If flag keepAlive is set, then enable keepAlive flags for socket
        enable_keepalive(sockfd);
    else{
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval)); // Set time interval for recieve
        setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(struct timeval)); // Set time interval for sending
    }

    if(nonBlocking){
        int optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); // Reuse addr if app restarted
    }

    if(::connect(sockfd, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){//рандомно зависает в ожидании syn-ack
        clientError("Error on connecting to " + host + " : ");
        connected = false;
    }
    else {
        connected = true;
        std::cout << "Connected to " << host << ":" << port <<" : Success!!! " << std::endl;
    }

    if(hasError())
        disconnect();

    return connected;
}

/*!
  Вывод в консоль сообщения об ошибке.
  \param[in] &msg Ссылка на выводимое сообщение
*/
inline void TCPClient::clientError(std::string const& msg)
{
    std::cerr << msg << errno << "  " << strerror(errno) << std::endl;
}

/*!
  Проверка сокета на ошибки.
  \return Результат проверки сокета на ошибки, true если ошибки обнаружены
*/
bool TCPClient::hasError() {
    if(sockfd == -1)
        return true;

    int error = 0;
    socklen_t len = sizeof(error);

    int retval = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len);

    if(retval != 0 || error != 0){
        clientError("Error: ");
        return true;
    }
    else
        return false;
}

/*!
  Включение у сокета неблокирующего режима.
  \param[in] sockfd Дескриптор сокета
  \return Значение флага дескриптора. В случае ошибки, возвращается -1 и значение errno устанавливается соответствующим образом.
*/
int TCPClient::set_nonblock(int sockfd)
{
    int flags;
#if defined(O_NONBLOCK)
    if(-1 == (flags = fcntl(sockfd, F_GETFL, 0)))
        flags = 0;
    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
#else
    flags = 1;
    return ioctl(sockfd, FIONBIO, &flags);
#endif
}

/*!
  Включение у сокета функции KEEPALIVE.
  \param[in] sock Установленный сокет
  \return Результат включения KEEPALIVE, -1 если не удалось
*/
int TCPClient::enable_keepalive(int sock) {
    int yes = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) == -1)
        return -1;

    int idle = 1;
    if(setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) == -1)
        return -1;

    int interval = 1;
    if(setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) == -1)
        return -1;

    int maxpkt = 10;
    if(setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int)) == -1)
        return -1;

    return 0;
}

/*!
  Инициирует отключение от сервера.
*/
inline void TCPClient::disconnect() {
    if(connected){
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);

        connected = false;
    }
}

/*!
  Отправляет строку на сервер.
  \param[in] &mesg Ссылка на отправляемую строку
  \return Результат отправки строки, 0 если строка отправлена
*/
int TCPClient::write(std::string const& dataString) {

    if(!connected)
        return 1;

    fd_set writefds;

    int sentBytes = 0;

    for(size_t i = 0; i < dataString.length(); i += sentBytes) {

        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);
        int rv = select(sockfd + 1, NULL, &writefds, NULL, &tv);

        if(rv == -1)
            clientError("Error: ");
        else if(rv == 0)
            sentBytes = 0;
        else if(rv > 0 && FD_ISSET(sockfd, &writefds)) {

            sentBytes = ::send(sockfd, (dataString.substr(i, dataString.length() - i)).c_str(), dataString.length() - i, MSG_NOSIGNAL);

            if(sentBytes == -1) {
                clientError("Error sending IDs: ");
                disconnect();
                return 1;
            }
        }
    }

    return 0;
}

/*!
  Принимает строку с сервера.
  \return Принятая строка
*/
std::string TCPClient::read() {

    if(!connected)
        return "";

    fd_set readfds;

    std::string resp = "";
    unsigned int n = 0;

    do {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        int selectResult = select(sockfd + 1, &readfds, NULL, NULL, &tv);

        if(selectResult <= -1)
            clientError("Error: ");
        else if(selectResult == 0)
            break;
        else if(selectResult > 0 && FD_ISSET(sockfd, &readfds)) {

            int recvResult = ::recv(sockfd, buffer, sizeof(buffer) - 1, MSG_NOSIGNAL);//avoid signcompare warning

            if(recvResult > 0) {
                n = recvResult;
                buffer[n] = '\0';
                std::string tResp(buffer, n);
                resp += tResp;
            }
            else if(recvResult == -1) {
                if(errno == 11) { //get the good part of the received stuff also if the connection closed during receive -> happens sometimes with short messages
                    std::string tResp(buffer);

                    if(tResp.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") == std::string::npos) //but only allow valid chars
                        resp += tResp;
                }
                else
                    clientError("Error: ");

                break;
            }
            else
                break;

        }
        else
            clientError( "Error: selectResult -> " + std::to_string(selectResult) );

    }
    while(n >= sizeof(buffer) - 1);

    return resp;
}

/*!
  Принимает набор строк с сервера и конкатенирует их в одну.
  \return Результирующая принятая строка
*/
std::string TCPClient::readAll() {
    std::string full = read();

    while(full.find("END") == std::string::npos)
        full += read();

    full = full.substr(0, full.find("END"));

    return full;
}
