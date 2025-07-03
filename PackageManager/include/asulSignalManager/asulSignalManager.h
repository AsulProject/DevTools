#ifndef ASULSIGNALMANAGER_H
#define ASULSIGNALMANAGER_H

#include <asulPackage/asulPackage.h>

#include <QFile>
#include <QList>
#include <QObject>

class asulSignal;

class asulSignalManager : public QObject {
    Q_OBJECT

    QString targetFile;
    QList<asulSignal*> signalList;

public:
    explicit asulSignalManager();

    inline void setHost(asulPackage* H) { QObject::setParent(H); }
    inline void setTargetFile(const QString& T) { this->targetFile = T; }

    void addSignal(asulSignal* S);

    const asulPackage* getHostPackage() const { return static_cast<asulPackage*>(this->parent()); }
    const auto& getTargetFile() const { return this->targetFile; }
    const auto& getSignalList() const { return this->signalList; }
};

#endif // ASULSIGNALMANAGER_H
