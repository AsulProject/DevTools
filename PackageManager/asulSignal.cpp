#include "asulSignal.h"
#include "asulPackage.h"

asulSignal::asulSignal(asulPackage *H, const QString &N)
{
    this->host=H;
    this->id=N;
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
