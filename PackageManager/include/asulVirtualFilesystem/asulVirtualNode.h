#ifndef ASULVIRTUALNODE_H
#define ASULVIRTUALNODE_H

#include <QObject>
#include <QString>

class asulVirtualNode : public QObject {
    Q_OBJECT

public:
    explicit asulVirtualNode(QObject* parent = nullptr);
    virtual ~asulVirtualNode();

    virtual void setName(const QString& N) = 0;

    inline virtual QString getName() const = 0;
    virtual void exportTo(const QString& path) const = 0;

    virtual QString toString() const = 0;
};

#endif // ASULVIRTUALNODE_H
