 #include "buffercontroller.h"
 
// TCP client
BufferController::BufferController(Control *control, QString *hostname)
{
    hostName = hostname;
    zanyaControl = control;

    protoInit();
    initNetwork();
}

void BufferController::protoInit()
{
    pControl = new ProtobufControl();
    serializedControl = new std::string();

    protoByControl();
}

void BufferController::protoByControl()
{
    pControl->mutable_servos()->set_xangle( zanyaControl->getXAngle() );
    pControl->mutable_servos()->set_yangle( zanyaControl->getYAngle() );

    pControl->mutable_motors()->set_lpower( zanyaControl->getLeftMotorPower() );
    pControl->mutable_motors()->set_ltime( zanyaControl->getLeftMotorTime() );
    pControl->mutable_motors()->set_rpower( zanyaControl->getRightMotorPower() );
    pControl->mutable_motors()->set_rtime( zanyaControl->getRightMotorTime() );

    pControl->mutable_light()->set_ledpower( zanyaControl->getLedPower() );
    pControl->mutable_light()->set_xenonenable( zanyaControl->getXenon() );

    pControl->mutable_system()->set_haltflag( zanyaControl->getFlagHalt() );
    pControl->mutable_system()->set_restartflag( zanyaControl->getFlagRestart() );

    protoSerialize();
}

void BufferController::protoSerialize()
{
    pControl->SerializeToString(serializedControl);
}

void TCPControl::initNetwork()
{

    QNetworkConfigurationManager manager;

    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {

        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered){
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &TCPControl::sessionOpened);

        networkSession->open();
    } else {
        sessionOpened();
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &TCPControl::sendControl);
}

void TCPControl::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
//        QMessageBox::critical(this, tr("Fortune Server"),
//                              tr("Unable to start the server: %1.")
//                              .arg(tcpServer->errorString()));
        tcpServer->close();
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
}

void TCPControl::sendControl()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);

    out << serializedControl;

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}


