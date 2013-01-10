#include "hidstringsender.h"
#include "hidserver.h"

#include <QDebug>

#define KEY_SEND_INTERVAL 1

HIDStringSender::HIDStringSender(HIDServer *hidServer, QObject *parent) :
    QObject(parent),
    m_hidServer(hidServer),
    m_keyMapper(this),
    m_currentIndex(0),
    m_busy(false)
{
    qDebug() << "Construct StringSender";
}

bool HIDStringSender::send(const QString &str)
{
    if (m_hidServer->state() != HIDServer::CONNECTED) {
        qWarning() << "Error! HIDServer not connected";
        return false;
    }

    if (m_busy) {
        qWarning() << "Error! processing " << m_str;
        return false;
    }

    m_str = "" + str;
    m_currentIndex = 0;
    m_busy = true;
    sendNextKeyDown();
    return true;
}

void HIDStringSender::sendNextKeyDown()
{
    if (m_currentIndex >= m_str.length()) {
        m_busy = false;
        emit sent();
        return;
    }

    QPair<int, int> code = m_keyMapper.getCode(m_str.at(m_currentIndex));
    //qDebug() << "down " << code.second;
    m_hidServer->sendKeyDown(code.first, code.second);
    m_currentIndex += 1;

    QTimer::singleShot(KEY_SEND_INTERVAL, this, SLOT(sendkeyUp()));
}

void HIDStringSender::sendkeyUp()
{
    //qDebug() << "up";
    m_hidServer->sendKeyUp();
    QTimer::singleShot(KEY_SEND_INTERVAL, this, SLOT(sendNextKeyDown()));
}
