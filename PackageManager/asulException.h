#ifndef ASULEXCEPTION_H
#define ASULEXCEPTION_H

#include <QString>

class asulException : std::runtime_error {
public:
    explicit asulException(const QString& msg)
        : std::runtime_error(msg.toStdString()) {}
};

#endif // ASULEXCEPTION_H
