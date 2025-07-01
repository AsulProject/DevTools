#ifndef ASULSIGNALMANAGER_H
#define ASULSIGNALMANAGER_H

#include <asulPackage/asulPackage.h>

#include <QFile>
#include <QList>
#include <QObject>

class asulSignal;

class asulSignalManager : public QObject {
    Q_OBJECT

    asulPackage* host;
    QFile targetFile;
    QList<asulSignal*> signalList;

public:
    explicit asulSignalManager(asulPackage* H, const QString& T);

    void addSignal(asulSignal* S);

    const asulPackage* getHostPackage() const { return this->host; }
    const auto& getTargetFile() const { return this->targetFile; }
    const auto& getSignalList() const { return this->signalList; }
};

#endif // ASULSIGNALMANAGER_H
