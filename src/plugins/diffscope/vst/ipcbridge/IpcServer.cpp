//
// Created by Crs_1 on 2023/5/12.
//

#include "IpcServer.h"
#include <QDataStream>
Vst::IpcServer::~IpcServer() {
}
void Vst::IpcServer::abort() {
    QMutexLocker locker(&mutex);
    if(socket) {
        socket->disconnectFromServer();
        socket->deleteLater();
        socket = nullptr;
        server.listen(key);
    }
}
Vst::IpcServer::IpcServer(const QString &key, QObject *parent): IpcConnect(key, parent) {
    IpcServer::server.setMaxPendingConnections(1);
    IpcServer::server.listen(key);
    connect(&server, &QLocalServer::newConnection, this, [=](){
        socket = IpcServer::server.nextPendingConnection();
        IpcServer::server.close();
        connect(socket, &QLocalSocket::disconnected, this, [=](){ emit disconnected(); });
        emit connected();
    });
}
