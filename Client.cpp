#include "Conf.h"
#include "Client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::~Client()
{

}

MainModel* Client::mainModel()
{
    return &mMainModel;
}

void Client::initialize(const QString& host, int port)
{
    try
    {
        mpClient = new QTcpSocket();
        connect(mpClient, &QTcpSocket::readyRead, this, &Client::receiveData);
        connect(this, &Client::updateGridModel, &mMainModel, &MainModel::updateGridModel);

        mpClient->connectToHost(host, port);
        bool result = mpClient->waitForConnected(1000);

        if (!result)
        {
            throw std::runtime_error("Connection is timed out");
        }
        else
        {
            write();
        }
    }
    catch (const std::exception& ex)
    {
        emit errorSignal(ex.what());
        qWarning() << "Connect to host" << host << ":" << port << ", exception:" << ex.what();
    }
}


void Client::run()
{
    initialize(ADDRESS, PORT);
}

void Client::stop()
{
    mpClient->disconnectFromHost();
}

void Client::write()
{
    QString request;

    for(int i = 0; i < ITEMS_COUNT; i++)
        request += NEXT_MESSAGE_REQUEST;

    request += STOP_MESSAGE_REQUEST;

    mpClient->write(request.toUtf8());
    emit startDownload(ITEMS_COUNT);
}

void Client::handleNewColor(const QString &color)
{

}

void Client::receiveData()
{
    QByteArray data = mpClient->readAll();
    QList<QByteArray> colorStrings = data.split('\n');
    QStringList stringList;

    foreach (QByteArray byteArray, colorStrings) {
        stringList.push_back(QString(byteArray));
    }

    QString resultString = stringList.join("");

    colors.push_back(resultString);
    emit updateGridModel(resultString);
    emit elementDownloaded(colors.size());

    if(colors.size() == ITEMS_COUNT)
        emit finishDownload();
}
