#include "asulSignal.h"
#include "asulPackage.h"

asulSignal::asulSignal(asulPackage *H, const QString &N,const QString& T)
    :targetFile(T)
{
    this->host=H;
    this->id=N;
}


// adds

void asulSignal::addSubscriber(asulSubscription *S)
{
    this->subscriberList.append(S);
}













// gets

asulPackage* asulSignal::getHost()const
{
    return this->host;
}

QString asulSignal::getID()const
{
    return this->id;
}

QString asulSignal::getFullID()const
{
    return this->host->getName()+"."+this->getID();
}

const auto& asulSignal::getTargetFile() const
{
    return this->targetFile;
}

const auto &asulSignal::getSubscriberList() const
{
    return this->subscriberList;
}
