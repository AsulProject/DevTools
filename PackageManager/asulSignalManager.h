#ifndef ASULSIGNALMANAGER_H
#define ASULSIGNALMANAGER_H

#include <QFile>
#include <QList>
#include <QObject>

#include "asulSignal.h"

class asulSignalManager : public QObject {
    Q_OBJECT

    QFile targetFile;
    QList<asulSignal*> signalList;

public:
    explicit asulSignalManager(const QString& T, QObject* parent = nullptr);

    void addSignal(asulSignal* S);

    const auto& getTargetFile() const { return this->targetFile; }
    const auto& getSignalList() const { return this->signalList; }
};

#endif // ASULSIGNALMANAGER_H
