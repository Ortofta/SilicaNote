#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Note : public QObject
{
    Q_OBJECT
    double row_id;
    double remote_id;
    QString title;
    QString body;
public:
    explicit Note(QObject *parent = 0);

signals:

public slots:

};

#endif // NOTE_H
