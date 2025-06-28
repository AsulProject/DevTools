#ifndef ASULEXCEPTION_H
#define ASULEXCEPTION_H

#include <QList>
#include <QString>

class asulSubscription;

// base exception
namespace asulException {
class Exception : public std::runtime_error {
public:
    explicit Exception(const QString& msg)
        : std::runtime_error(msg.toStdString()) {}
};

// circular dependency when building packages
class circularDependencyError : public Exception {
    QList<QString> circle;

public:
    explicit circularDependencyError(const QList<QString>& C)
        : Exception("Circular Dependency Detected")
        , circle(C) {}
    inline const auto& getCircle() const { return this->circle; }
};

// subscribe to unknown signal
// this should be an issue of the package itself
// the author may forgot to add dependency for subscription
class unkownSignal : public Exception {
    asulSubscription* subscription;

public:
    explicit unkownSignal(asulSubscription* S)
        : Exception("unknown signal")
        , subscription(S) {}
    inline auto getSubscription() const { return this->subscription; }
};

} // namespace asulException

#endif // ASULEXCEPTION_H
