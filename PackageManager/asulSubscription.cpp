#include "asulSubscription.h"

#include <QDebug>

asulSubscription::asulSubscription(asulPackage *H, asulSignal *S)
{
    this->host=H;
    this->signal=S;
}




// adds

void asulSubscription::addCommand(const QString &command)
{
    this->commandList.append(command);
}

void asulSubscription::addCommand(const QVector<QString> &commands)
{
    this->commandList.append(commands);
}

bool asulSubscription::addArg(const QString &key, const QString &value)
{
    // check if this arg exsits
    if(this->argList.contains(key)){
        qDebug()<<QString("arg {%1,%2} already exsits.").arg(key).arg(value);
        return false;
    }

    // add it to argList
    this->argList.insert(key,value);
    return true;
}




// gets

asulPackage *asulSubscription::getHost() const
{
    return this->host;
}

asulSignal *asulSubscription::getSignal() const
{
    return this->signal;
}

const auto &asulSubscription::getCommandList() const
{
    return this->commandList;
}

const auto &asulSubscription::getArgList() const
{
    return this->argList;
}


