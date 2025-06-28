#ifndef ASULSUBSCRIPTION_H
#define ASULSUBSCRIPTION_H

#include <QMap>
#include <QString>
#include <QVector>

class asulPackage;
class asulSignal;

class asulSubscription {
    asulPackage* host;
    asulSignal* signal;
    QVector<QString> commandList;
    QMap<QString, QString> argList;

public:
    asulSubscription(asulPackage* H, asulSignal* S);

    void addCommand(const QString& command);
    void addCommand(const QVector<QString>& commands);
    void addArg(const QString& key, const QString& value);

    asulPackage* getHost() const { return this->host; }
    asulSignal* getSignal() const { return this->signal; }
    const auto& getCommandList() const { return this->commandList; }
    const auto& getArgList() const { return this->argList; }
};

#endif // ASULSUBSCRIPTION_H
