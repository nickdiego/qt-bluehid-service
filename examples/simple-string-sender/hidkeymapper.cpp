#include "hidkeymapper.h"

HIDAlphaNumKeyMapper::HIDAlphaNumKeyMapper(QObject *parent):
    QObject(parent)
{
    initMap();
}

void HIDAlphaNumKeyMapper::initMap()
{
    m_keyMap['a'] = 4;
    m_keyMap['b'] = 5;
    m_keyMap['c'] = 6;
    m_keyMap['d'] = 7;
    m_keyMap['e'] = 8;
    m_keyMap['f'] = 9;
    m_keyMap['g'] = 10;
    m_keyMap['h'] = 11;
    m_keyMap['i'] = 12;
    m_keyMap['j'] = 13;
    m_keyMap['k'] = 14;
    m_keyMap['l'] = 15;
    m_keyMap['m'] = 16;
    m_keyMap['n'] = 17;
    m_keyMap['o'] = 18;
    m_keyMap['p'] = 19;
    m_keyMap['q'] = 20;
    m_keyMap['r'] = 21;
    m_keyMap['s'] = 22;
    m_keyMap['t'] = 23;
    m_keyMap['u'] = 24;
    m_keyMap['v'] = 25;
    m_keyMap['w'] = 26;
    m_keyMap['x'] = 27;
    m_keyMap['y'] = 28;
    m_keyMap['z'] = 29;

    m_keyMap['1'] = 30;
    m_keyMap['2'] = 31;
    m_keyMap['3'] = 32;
    m_keyMap['4'] = 33;
    m_keyMap['5'] = 34;
    m_keyMap['6'] = 35;
    m_keyMap['7'] = 36;
    m_keyMap['8'] = 37;
    m_keyMap['9'] = 38;
    m_keyMap['0'] = 39;
}

QPair<int, int> HIDAlphaNumKeyMapper::getCode(const QChar &ch)
{

    if (!ch.isLetterOrNumber()) {
        return QPair<int, int>(-1, -1);
    }
    if (ch.isDigit() || ch.isLower()) {
        return QPair<int, int>(0, m_keyMap[ch]);
    }
    // A = <shift, 'a'> ;-)
    return QPair<int, int>(2, m_keyMap[ch.toLower()]);
}
