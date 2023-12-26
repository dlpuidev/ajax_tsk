#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <MainModel.h>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainModel* mainModel READ mainModel CONSTANT)

protected:
    QTcpSocket* mpClient;

private:
    MainModel   mMainModel;
    QList<QString> colors;

public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    Q_INVOKABLE void run();
    Q_INVOKABLE void stop();
    MainModel* mainModel();

private:
    void initialize(const QString& host, int port);
    void write();

signals:
    void startDownload(int num);//signal which is sent when downloading is starting. num - number of elements fro downloading
    void finishDownload();//signal which is sent when downloading is finished
    void elementDownloaded(int count);//signal which is sent when elements is downloaded. num - number of downloaded element
    void errorSignal(const QString& err);//signal which is sent when error occured. err - error text
    void updateGridModel(const QString& color);

private slots:
    void receiveData();
    void handleNewColor(const QString& color);//slot for handling new color from server
};

#endif // CLIENT_H
