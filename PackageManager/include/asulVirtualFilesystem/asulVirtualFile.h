#ifndef ASULVIRTUALFILE_H
#define ASULVIRTUALFILE_H

#include <asulVirtualFilesystem/asulVirtualNode.h>

#include <QDebug>
#include <QObject>

class asulVirtualFile : public asulVirtualNode {
    Q_OBJECT

    QString name;

    QString content;

public:
    explicit asulVirtualFile(QObject* parent = nullptr);

    inline void setName(const QString& N) override { this->name = N; }
    inline void setContent(const QString& C) { this->content = C; }
    void append(const QString& S);
    void appendLine(const QString& L);

    asulVirtualFile& operator<<(const QString& S);

    inline QString getName() const override { return this->name; }
    inline const QString& getContent() const { return this->content; }
    void exportTo(const QString& path) const override;

    QString toString() const override;
};

#endif // ASULVIRTUALFILE_H
