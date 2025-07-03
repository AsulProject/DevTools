#ifndef ASULVIRTUALDIR_H
#define ASULVIRTUALDIR_H

#include <asulVirtualFilesystem/asulVirtualNode.h>

#include <QList>
#include <QObject>

class asulVirtualDir : public asulVirtualNode {
    Q_OBJECT

    QString name;
    QList<asulVirtualNode*> list;

public:
    explicit asulVirtualDir(QObject* parent = nullptr);

    inline void setName(const QString& N) override { this->name = N; }
    void append(asulVirtualNode* F);

    inline QString getName() const override { return this->name; }
    inline const auto& getList() const { return this->list; }
    void exportTo(const QString& path) const override;

    QString toString() const override;
};

#endif // ASULVIRTUALDIR_H
