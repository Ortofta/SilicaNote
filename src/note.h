#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Note : public QObject
{
    Q_OBJECT
    double _row_id;
    double _remote_id;
    QString _title;
    QString _body;
public:
    explicit Note(QObject *parent = 0);
    void setRowId(double rowId);
    double getRowId();
    void setRemoteId(double remoteId);
    double getRemoteId();
    void setTitle(const QString title);
    QString getTitle();
    void setBody(const QString body);
    QString getBody();
signals:

public slots:

};

#endif // NOTE_H
