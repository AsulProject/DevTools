#ifndef ASULSUBSCRIPTION_H
#define ASULSUBSCRIPTION_H

#include <asulPackage/asulPackage.h>

#include <QList>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVariant>

class asulSubscription : public QObject {
    Q_OBJECT

    QString signal;
    QStringList commandList;

public:
    asulSubscription();

    inline void setHost(asulPackage* H) { QObject::setParent(H); }
    inline void setSignal(const QString& S) { this->signal = S; }

    void addCommand(const QString& command);
    void addCommand(const QStringList& commands);

    const asulPackage* getHostPackage() const { return static_cast<asulPackage*>(this->parent()); }
    auto getSignal() const { return this->signal; }
    const auto& getCommandList() const { return this->commandList; }
};

#endif // ASULSUBSCRIPTION_H
