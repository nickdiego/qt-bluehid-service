#ifndef HIDKEYMAPPER_H
#define HIDKEYMAPPER_H

#include <QObject>
#include <QMap>
#include <QPair>

class HIDAlphaNumKeyMapper: public QObject
{
    Q_OBJECT

public:
    HIDAlphaNumKeyMapper(QObject *parent = 0);
    QPair<int, int> getCode(const QChar &ch);

private:
    void initMap();

    QMap<QChar, int> m_keyMap;
};

#endif // HIDKEYMAPPER_H
