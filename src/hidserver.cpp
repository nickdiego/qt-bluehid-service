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
    qDebug() << "Construct HidServer";
}

void HIDServer::start()
{
    QBluetoothAddress any;

    m_interruptChannel.listen(any, INTERRUPT_PORT);
    m_controlChannel.listen(any, CONTROL_PORT);

    //Q_ASSERT(m_interruptChannel.isListening());
    //Q_ASSERT(m_controlChannel.isListening());
    if (!m_interruptChannel.isListening() || !m_controlChannel.isListening()) {
        qWarning("Couldn't start HIDServer!");
        emit error();
        return;
    }

    qDebug() << "Starting INTERRUPT server - PSM: " << m_interruptChannel.serverPort()
             << " baddr: " << m_interruptChannel.serverAddress().toString();
    qDebug() << "Starting CONTROL server - PSM: " << m_controlChannel.serverPort()
             << " baddr: " << m_controlChannel.serverAddress().toString();

    m_serviceDescriptor.registerService();

    connect(&m_interruptChannel, SIGNAL(newConnection()), this, SLOT(onInterruptChannelConnected()));
    connect(&m_controlChannel, SIGNAL(newConnection()), this, SLOT(onControlChannelConnected()));

    setState(HIDServer::LISTENING);
}

void HIDServer::stop()
{
    if (m_state == HIDServer::IDLE)
        return;

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
    if (m_interruptSocket != 0 && m_controlSocket != 0) {
        setState(HIDServer::CONNECTED);
    } else if (m_interruptChannel.isListening() && m_controlChannel.isListening())
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

/* Keyboard methods */

int HIDServer::sendKeyDown(int modifiers, int val)
{
    char th[10];
    int n;

    th[0] = 0xa1;
    th[1] = 0x01;
    th[2] = modifiers;  // 1 -left control ,2 - left shift, 4 left alt,
                        // 5- ctrl+ alt (01 + 04) 8 - left gui, 16 - right control,
                        // 32 - right sift, 64 - right alt, 128 - right gui
    th[3] = 0x00;
    th[4] = val;        // the key code
    th[5] = 0x00;
    th[6] = 0x00;
    th[7] = 0x00;
    th[8] = 0x00;
    th[9] = 0x00;

    QByteArray data(th, sizeof(th));
    n = m_interruptSocket->write(data);
//    qDebug() << "KeyDown " << n;
    return n;
}

int HIDServer::sendKeyUp()
{
    char th[10];
    int n;

    th[0] = 0xa1;
    th[1] = 0x01;
    th[2] = 0x00;
    th[3] = 0x00;
    th[4] = 0x00;
    th[5] = 0x00;
    th[6] = 0x00;
    th[7] = 0x00;
    th[8] = 0x00;
    th[9] = 0x00;

    QByteArray data(th, sizeof(th));
    n = m_interruptSocket->write(data);
//    qDebug() << "KeyUP " << n;
    return n;
}

// debug methods
void HIDServer::debugKeyDown()
{
    qDebug() << QDateTime::currentDateTime() <<  " Debug keyDown";
    int x = 0;
    int n = 10;

    x = sendKeyDown(0, 4);
    Q_ASSERT(x == n);
}


void HIDServer::debugKeyUp()
{
    qDebug() << QDateTime::currentDateTime() <<  "Forcing keyUp";
    int x = 0;
    int n = 10;

    x = sendKeyUp();
    Q_ASSERT(x == n);
}
