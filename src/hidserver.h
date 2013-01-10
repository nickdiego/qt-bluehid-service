#ifndef HIDSERVER_H
#define HIDSERVER_H

#include <QL2capServer>
#include <QtDeclarative>

#include "hidservicedescriptor.h"

QTM_USE_NAMESPACE

#define CONTROL_PORT   0x0011
#define INTERRUPT_PORT 0x0013

class HIDServer : public QObject
{
    Q_OBJECT
    Q_ENUMS(State)
    Q_PROPERTY(State state READ state NOTIFY stateChanged FINAL)

public:
    enum State {
        IDLE,
        LISTENING,
        CONNECTED
    };

    explicit HIDServer(QObject *parent = 0);

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    int sendKeyDown(int modifiers, int val);
    int sendKeyDownUp(int modifiers, int val);
    int sendKeyUp();

    HIDServer::State state() { return m_state; }

public slots:
    void debugKeyDown();
    void debugKeyUp();

signals:
    void stateChanged();
    void error();

private slots:
    void onInterruptChannelConnected();
    void onControlChannelConnected();
    void onSocketDisconnected();

private:
    void setState(HIDServer::State state);
    void configureChannels();
    void updateConnectionState();
    void releaseSocket(QBluetoothSocket* &socket);

private:
    HIDServer::State m_state;
    HIDServiceDescriptor m_serviceDescriptor;

    QL2capServer m_interruptChannel, m_controlChannel;
    QBluetoothSocket *m_interruptSocket, *m_controlSocket;
};

QML_DECLARE_TYPE(HIDServer)

#endif // HIDSERVER_H
