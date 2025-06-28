#ifndef ASULSUBSCRIPTION_H
#define ASULSUBSCRIPTION_H

#include <QList>
#include <QMap>
#include <QString>

class asulSubscription {
    QString host;
    QString signal;
    QList<QString> commandList;
    QMap<QString, QString> argList;

public:
    asulSubscription(const QString& H, const QString& S);

    void addCommand(const QString& command);
    void addCommand(const QList<QString>& commands);
    void addArg(const QString& key, const QString& value);

    auto getHost() const { return this->host; }
    auto getSignal() const { return this->signal; }
    const auto& getCommandList() const { return this->commandList; }
    const auto& getArgList() const { return this->argList; }
};

#endif // ASULSUBSCRIPTION_H
