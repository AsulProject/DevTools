#ifndef ASULSUBSCRIPTION_H
#define ASULSUBSCRIPTION_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>

#include "asulPackage.h"

class asulSubscription : public QObject {
    Q_OBJECT

    asulPackage* host;
    QString signal;
    QStringList commandList;

public:
    asulSubscription(asulPackage* H, const QString& S);

    void addCommand(const QString& command);
    void addCommand(const QList<QString>& commands);

    const asulPackage* getHostPackage() const { return this->host; }
    auto getSignal() const { return this->signal; }
    const auto& getCommandList() const { return this->commandList; }
};

#endif // ASULSUBSCRIPTION_H
