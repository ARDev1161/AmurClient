#include "tcpclient.h"

TCPClient::TCPClient(std::string host, unsigned int port):
    sockfd(-1),
    connected(false)
{
    connect(host, port);
}

TCPClient::TCPClient(int sock):
    sockfd(sock)
{
    connected = true;
}

TCPClient::TCPClient()
{

}

TCPClient::~TCPClient()
{
    disconnect();
}

int TCPClient::connect(std::string host, unsigned int port)
{
    struct sockaddr_in servAddr;
    struct hostent *server;

    std::memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;

    server = gethostbyname(host.data());
    memmove((char*) &servAddr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
    servAddr.sin_port = htons(port);

    if(connected)
        disconnect();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

//    struct timeval tv;
//    tv.tv_sec = 5; //5 Secs Timeout
//    tv.tv_usec = 0; //Not init'ing this can cause strange errors
//    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(struct timeval)); // Set time interval for recieve

    enable_keepalive(sockfd);

    for(size_t i = 0; i < COUNT_CONNECT_TRYING; i++) { //try to connect several times
        if(::connect(sockfd, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
            clientError("Error on connecting: ");
        else {
            connected = true;
            return 0;
        }
        sleep(1); // Wait 1 second
    }

    connected = false;
    return 1;
}

inline void TCPClient::clientError(std::string const& msg)
{
    std::cerr << msg << errno << "  " << strerror(errno) << std::endl;
}

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

inline void TCPClient::disconnect() {
    if(connected){
        close(sockfd);
        connected = false;
    }
}

int TCPClient::write(std::string const& mesg) {
    if(!connected)
        return 1;

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    fd_set writefds;
    FD_ZERO(&writefds);
    FD_SET(sockfd, &writefds);

    //cout << "w: " << mesg << endl;

    int sentBytes = 0;

    for(size_t i = 0; i < mesg.length(); i += sentBytes) {
        FD_ZERO(&writefds);
        FD_SET(sockfd, &writefds);
        int rv = select(sockfd + 1, NULL, &writefds, NULL, &tv);

        if(rv == -1)
            clientError("Error: ");
        else if(rv == 0)
            sentBytes = 0;
        else if(rv > 0 && FD_ISSET(sockfd, &writefds)) {
            sentBytes = ::write(sockfd, mesg.substr(i, mesg.length() - i).c_str(), mesg.length() - i);

            if(sentBytes == -1) {
                clientError("Error sending IDs: ");
                return 1;
            }
        }
    }

    return 0;
}

std::string TCPClient::read() {
    if(!connected)
        return "";

    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);

    std::string resp = "";
    unsigned int n = 0;


    do {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);

        if(rv <= -1)
            clientError("Error: ");
        else if(rv == 0)
            break;
        else if(rv > 0 && FD_ISSET(sockfd, &readfds)) {

            int tn = ::read(sockfd, buffer, sizeof(buffer) - 1);//avoid signcompare warning

            if(tn > 0) {
                n = tn;
                buffer[n] = '\0';
                std::string tResp(buffer, n);
                resp += tResp;
            }
            else if(tn == -1) {
                if(errno == 11) { //get the good part of the received stuff also if the connection closed during receive -> happens sometimes with short messages
                    std::string tResp(buffer);

                    if(tResp.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") == std::string::npos) //but only allow valid chars
                        resp += tResp;
                }
                //    perror(msg);
                else
                    clientError("Error: ");

                break;
            }
            else
                break;

        }
        else
            clientError( "ERROR: rv: " + std::to_string(rv) );

    }
    while(n >= sizeof(buffer) - 1);

    //if(resp != "")
    //cout << "r: " << resp << endl;

    return resp;
}

std::string TCPClient::readAll() {
    std::string full = read();

    while(full.find("END") == std::string::npos)
        full += read();

    full = full.substr(0, full.find("END"));

    return full;
}
