#ifndef HIDSTRINGSENDER_H
#define HIDSTRINGSENDER_H

#include <QObject>

#include "hidkeymapper.h"

class HIDServer;

class HIDStringSender : public QObject
{
    Q_OBJECT
public:
    explicit HIDStringSender(HIDServer *hidServer, QObject *parent = 0);

signals:
    void sent();

public slots:
    bool send(const QString &str);
    void sendNextKeyDown();
    void sendkeyUp();

private:
    HIDServer *m_hidServer;
    HIDAlphaNumKeyMapper m_keyMapper;
    QString m_str;
    int m_currentIndex;
    bool m_busy;
};

#endif // HIDSTRINGSENDER_H
