#ifndef QSTRINGMODIFIER_H
#define QSTRINGMODIFIER_H

#include <QObject>
#include <QMap>
#include "stdafx.h"

class QStringModifier : public QObject
{
    Q_OBJECT
public:
    explicit QStringModifier(QObject *parent = nullptr);
    ~QStringModifier();
    void installModifier(QMap<QString,QString> modifier);
    QString get(QString content);
private:
    QMap<QString,QString> mod;
signals:
};

#endif // QSTRINGMODIFIER_H
