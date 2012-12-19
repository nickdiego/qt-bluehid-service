#include <QtCore/QDebug>

#include "hidserver.h"

HIDServer::HIDServer(QObject *parent) :
    QObject(parent),
    m_state(HIDServer::IDLE),
    m_serviceDescriptor(this),
    m_interruptChannel(this),
    m_controlChannel(this),
    m_interruptSocket(0),
    m_controlSocket(0)
{
    configureChannels();
}

void HIDServer::start()
{
    QBluetoothAddress any;

    m_serviceDescriptor.unregisterService();
    m_serviceDescriptor.registerService();

    m_interruptChannel.listen(any, INTERRUPT_PORT);
    Q_ASSERT(m_interruptChannel.isListening());
    qDebug() << "Starting INTERRUPT server - PSM: " << m_interruptChannel.serverPort()
             << " baddr: " << m_interruptChannel.serverAddress().toString();

    m_controlChannel.listen(any, CONTROL_PORT);
    Q_ASSERT(m_controlChannel.isListening());
    qDebug() << "Starting CONTROL server - PSM: " << m_controlChannel.serverPort()
             << " baddr: " << m_controlChannel.serverAddress().toString();

    connect(&m_interruptChannel, SIGNAL(newConnection()), this, SLOT(onInterruptChannelConnected()));
    connect(&m_controlChannel, SIGNAL(newConnection()), this, SLOT(onControlChannelConnected()));

    setState(HIDServer::LISTENING);
}

void HIDServer::stop()
{
    qDebug() << "stoping server...";
    disconnect(&m_interruptChannel, SIGNAL(newConnection()), this, SLOT(onInterruptChannelConnected()));
    disconnect(&m_controlChannel, SIGNAL(newConnection()), this, SLOT(onControlChannelConnected()));

    if (m_interruptSocket)
        releaseSocket(m_interruptSocket);

    if (m_controlSocket)
        releaseSocket(m_controlSocket);

    m_serviceDescriptor.unregisterService();

    setState(HIDServer::IDLE);
}

void HIDServer::configureChannels()
{
    m_interruptChannel.setSecurityFlags(QBluetooth::NoSecurity);
    m_controlChannel.setSecurityFlags(QBluetooth::Encryption);
}

void HIDServer::onInterruptChannelConnected()
{
    qDebug() << "NEW Interrupt connection";
    m_interruptSocket = m_interruptChannel.nextPendingConnection();
    connect(m_interruptSocket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    updateConnectionState();
}

void HIDServer::onControlChannelConnected()
{
    qDebug() << "NEW Control connection";
    m_controlSocket = m_controlChannel.nextPendingConnection();
    connect(m_controlSocket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    updateConnectionState();
}

void HIDServer::updateConnectionState() {
    if (m_interruptSocket != 0 && m_controlSocket != 0)
        setState(HIDServer::CONNECTED);
    else if (m_interruptChannel.isListening() && m_controlChannel.isListening())
        setState(HIDServer::LISTENING);
    else
        setState(HIDServer::IDLE);
}

void HIDServer::onSocketDisconnected()
{
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
    if (socket == m_interruptSocket) {
        releaseSocket(m_interruptSocket);

    } else if (socket == m_controlSocket) {
        releaseSocket(m_controlSocket);
    }

    updateConnectionState();
}

void HIDServer::releaseSocket(QBluetoothSocket* &socket)
{
    disconnect(socket, SIGNAL(disconnected()));
    if (socket->state() == QBluetoothSocket::ConnectedState)
        socket->close();
    socket->deleteLater();
    socket = 0;
}

void HIDServer::setState(HIDServer::State state)
{
    HIDServer::State old = m_state;
    m_state = state;
    if (old != state) {
        qDebug() << "Server State changed: " << state;
        emit stateChanged();
    }
}

