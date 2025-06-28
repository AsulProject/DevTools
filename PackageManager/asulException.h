#ifndef ASULEXCEPTION_H
#define ASULEXCEPTION_H

#include <QList>
#include <QString>

namespace asul {

class Exception : public std::runtime_error {
public:
    explicit Exception(const QString& msg)
        : std::runtime_error(msg.toStdString()) {}
};

class PackageManagerCircularDependencyError : Exception {
    QList<QString> circle;

public:
    explicit PackageManagerCircularDependencyError(const QList<QString>& C)
        : Exception("Circular Dependency Detected")
        , circle(C) {}
    inline const auto& getCircle() const { return this->circle; }
};

} // namespace asul

#endif // ASULEXCEPTION_H
