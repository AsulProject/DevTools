#include <asulVirtualFilesystem/asulVirtualFile.h>

asulVirtualFile::asulVirtualFile(QObject* parent)
    : asulVirtualNode(parent) {}

void asulVirtualFile::append(const QString& S) {
    this->content.append(S);
}

void asulVirtualFile::appendLine(const QString& L) {
    if (this->content.isEmpty() == false && this->content.back() != '\n')
        this->content.append('\n');
    this->content.append(L);
}

asulVirtualFile& asulVirtualFile::operator<<(const QString& S) {
    this->append(S);
    return *this;
}

QString asulVirtualFile::toString() const {
    return QString("%1:\"%2\"").arg(this->getName(), this->getContent());
}

void asulVirtualFile::exportTo(const QString& path) const {
    // to do
    Q_UNUSED(path);
}
