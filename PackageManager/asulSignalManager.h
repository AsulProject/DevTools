#ifndef ASULSIGNALMANAGER_H
#define ASULSIGNALMANAGER_H

#include <QFile>
#include <QList>
#include <QObject>

class asulSignal;

class asulSignalManager : public QObject {
    Q_OBJECT

    QString host;
    QFile targetFile;
    QList<asulSignal*> signalList;

public:
    explicit asulSignalManager(const QString& I, const QString& T, QObject* parent = nullptr);

    void addSignal(asulSignal* S);

    const auto& getHostPackage() const { return this->host; }
    const auto& getTargetFile() const { return this->targetFile; }
    const auto& getSignalList() const { return this->signalList; }
};

#endif // ASULSIGNALMANAGER_H
