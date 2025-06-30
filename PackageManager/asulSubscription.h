#ifndef ASULSUBSCRIPTION_H
#define ASULSUBSCRIPTION_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>

class asulSubscription : public QObject {
    Q_OBJECT

    QString host;
    QString signal;
    QStringList commandList;
    QMap<QString, QVariant> argList;

public:
    asulSubscription(const QString& H, const QString& S, QObject* parent = nullptr);

    void addCommand(const QString& command);
    void addCommand(const QList<QString>& commands);
    void addArg(const QString& key, const QVariant& value);

    auto getHost() const { return this->host; }
    auto getSignal() const { return this->signal; }
    const auto& getCommandList() const { return this->commandList; }
    const auto& getArgList() const { return this->argList; }
};

#endif // ASULSUBSCRIPTION_H
