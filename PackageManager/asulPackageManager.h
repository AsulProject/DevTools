#ifndef ASULPACKAGEMANAGER_H
#define ASULPACKAGEMANAGER_H

#include "asulPackage.h"
#include "asulSignal.h"
#include <QVector>

class asulPackageManager
{
    QVector<asulPackage> packgeList;
    QVector<asulSignal> signalList;
public:
    asulPackageManager();
};

#endif // ASULPACKAGEMANAGER_H
