#ifndef QICOE_H
#define QICOE_H

#include <QObject>

class QICOE : public QObject
{
    Q_OBJECT
public:
    explicit QICOE(QObject *parent = nullptr);

signals:
    void emit_this();

};

#endif // QICOE_H
