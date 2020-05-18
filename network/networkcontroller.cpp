#include "networkcontroller.h"

/*!
  Создаёт экземпляр класса для работы с сетью.
  \param[in] *controls Указатель на protobuf буффер AmurControls
  \param[in] *sensors Указатель на protobuf буффер AmurSensors
  \param[in] host Адрес сервера
  \param[in] port Порт сервера
*/
NetworkController::NetworkController(AmurControls *controls, AmurSensors *sensors, std::string host, unsigned int port):
    serverHost(host), serverPort(port),
    sensorsPeri(sensors), controlsPeri(controls)
{
    serializedSensors = new std::string();
    client = new TCPClient(serverHost, serverPort);
}

/*!
  Создаёт экземпляр класса для работы с сетью.
  \param[in] *controls Указатель на protobuf буффер AmurControls
  \param[in] *sensors Указатель на protobuf буффер AmurSensors
*/
NetworkController::NetworkController(AmurControls *controls, AmurSensors *sensors):
    sensorsPeri(sensors), controlsPeri(controls)
{
    client = new TCPClient();
}

NetworkController::~NetworkController()
{
    disconnect();

    delete serializedSensors;
    delete client;
}

/*!
  Инициирует подключение к серверу.
  \param[in] host Адрес сервера
  \param[in] port Порт сервера
  \return Результат подключения, true если соединение установлено
*/
bool NetworkController::connect(std::string host, unsigned int port)
{
    return client->connect(host, port);
}

/*!
  Инициирует подключение к серверу.
  \return Результат подключения, true если соединение установлено
*/
bool  NetworkController::connect()
{
    bool res = false;

    if((serverPort > 0) && (serverHost !=""))
        res = client->connect(serverHost, serverPort);

    return res;
}

/*!
  Инициирует отключение от сервера.
*/
void NetworkController::disconnect()
{
    client->disconnect();
}

/*!
  Проверяет активность подключения к серверу.
  \return Результат подключения, true если соединение установлено
*/
bool NetworkController::checkAlive()
{
    return client->checkAlive();
}

/*!
  Отправляет сериализованный буфер сенсоров на сервер.
*/
void NetworkController::sendBufferAsString()
{
    sensorsPeri->SerializeToString(serializedSensors);

    if((*serializedSensors)!=""){
        *serializedSensors += '\0'; // Need for ending message
        client->write(*serializedSensors);
    }
}

/*!
  Принимает сериализованный буфер управления с сервера.
*/
void NetworkController::recvBufferAsString()
{
    controlsPeri->ParseFromString( client->read() );
}

/*!
  Устанавливает адрес сервера в переменную класса.
  \param[in] &value Ссылка на строку с адресом сервера
*/
void NetworkController::setHost(const std::string &value)
{
    serverHost = value;
}

/*!
  Устанавливает порт сервера в переменную класса.
  \param[in] value Порт сервера для соединения
*/
void NetworkController::setPort(unsigned int value)
{
    serverPort = value;
}
