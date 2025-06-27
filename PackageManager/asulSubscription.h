#ifndef ASULSUBSCRIPTION_H
#define ASULSUBSCRIPTION_H

#include <QString>
#include <QVector>
#include <QMap>

class asulPackage;
class asulSignal;

class asulSubscription
{
    asulPackage* host;
    asulSignal* signal;
    QVector<QString> commandList;
    QMap<QString,QString> argList;

public:
    asulSubscription(asulPackage* H,asulSignal* S);

    void addCommand(const QString& command);
    void addCommand(const QVector<QString>& commands);
    bool addArg(const QString& key,const QString& value);

    asulPackage* getHost()const;
    asulSignal* getSignal()const;
    const auto& getCommandList()const;
    const auto& getArgList()const;
};

#endif // ASULSUBSCRIPTION_H
