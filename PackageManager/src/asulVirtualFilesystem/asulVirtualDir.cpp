#include <asulVirtualFilesystem/asulVirtualDir.h>

asulVirtualDir::asulVirtualDir(QObject* parent)
    : asulVirtualNode(parent) {}

void asulVirtualDir::append(asulVirtualNode* F) {
    this->list.append(F);
    F->setParent(this);
}

QString asulVirtualDir::toString() const {
    QString ret = "{";
    for (asulVirtualNode* F : this->getList()) {
        if (ret != "{")
            ret += ",";
        ret += F->toString();
    }
    ret += "}";
    return ret;
}

void asulVirtualDir::exportTo(const QString& path) const {
    // to do
    Q_UNUSED(path);
}
