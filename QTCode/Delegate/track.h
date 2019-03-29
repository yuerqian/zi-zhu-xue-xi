#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QWidget>

class Track
{
public:
    Track(const QString &title="",int duration=0);
    QString title;
    int duration;
};

#endif // TRACK_H
