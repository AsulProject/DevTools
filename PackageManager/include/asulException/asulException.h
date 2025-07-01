#ifndef ASULEXCEPTION_H
#define ASULEXCEPTION_H

#include <QList>
#include <QString>

class asulSubscription;
class asulSignal;
class asulSignalManager;

// base exception
namespace asulException {
class Exception : public std::runtime_error {
public:
    explicit Exception(const QString& msg)
        : std::runtime_error(msg.toStdString()) {}
};

// circular dependency when building packages
class circularDependency : public Exception {
    QStringList circle;

public:
    explicit circularDependency(const QStringList& C)
        : Exception("Circular Dependency Detected")
        , circle(C) {}
    inline const auto& getCircle() const { return this->circle; }
};

// the package author delacred duplicate signal Manager
class duplicateSignalManagerDeclaration : public Exception {
    asulSignalManager* signalManager;

public:
    explicit duplicateSignalManagerDeclaration(asulSignalManager* S)
        : Exception("duplicate signalManager declaration was detetced")
        , signalManager(S) {}
    inline const auto& getSignalManager() const { return this->signalManager; }
};

// the package author delacred duplicate signal
class duplicateSignalDeclaration : public Exception {
    asulSignal* signal;

public:
    explicit duplicateSignalDeclaration(asulSignal* S)
        : Exception("duplicate signal declaration was detetced")
        , signal(S) {}
    inline const auto& getSignal() const { return this->signal; }
};

// depend on unknown package
// the dependency may be disabled
// or deoendency pkg does not exsit
class unkownDependency : public Exception {
    QString host;
    QString dependency;

public:
    explicit unkownDependency(const QString& H, const QString& D)
        : Exception("unknown denpendency package")
        , host(H)
        , dependency(D) {}
    inline const auto& getHost() const { return this->host; }
    inline const auto& getDependency() const { return this->dependency; }
};

// subscribe to unknown signal
// the author may forget to add dependency for subscription
// or dependency was disabled
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
