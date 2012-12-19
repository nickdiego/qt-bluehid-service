#ifndef HIDSERVER_H
#define HIDSERVER_H

#include <QL2capServer>

#include "hidservicedescriptor.h"

QTM_USE_NAMESPACE

static const quint16 CONTROL_PORT   = 0x0011;
static const quint16 INTERRUPT_PORT = 0x0013;

class HIDServer : public QObject
{
    Q_OBJECT
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
    int sendKeyUp();

public slots:
    void debugKeyDown();
    void debugKeyUp();

private:
    void setState(HIDServer::State state);
    void configureChannels();
    void updateConnectionState();
    void releaseSocket(QBluetoothSocket* &socket);

private slots:
    void onInterruptChannelConnected();
    void onControlChannelConnected();
    void onSocketDisconnected();

signals:
    void stateChanged();

private:
    HIDServer::State m_state;
    HIDServiceDescriptor m_serviceDescriptor;

    QL2capServer m_interruptChannel, m_controlChannel;
    QBluetoothSocket *m_interruptSocket, *m_controlSocket;
};

#endif // HIDSERVER_H
