#include "QStringModifier.h"
#include "QDebug"

QStringModifier::QStringModifier(QObject *parent)
    : QObject{parent}
{

}

QStringModifier::~QStringModifier()
{

}

void QStringModifier::installModifier(QMap<QString, QString> modifier)
{
    mod=modifier;
}

QString QStringModifier::get(QString content)
{
    QString modfix=content;
    QMap<QString,QString>::const_iterator iter;
    for (iter = mod.constBegin(); iter != mod.constEnd(); ++iter)
    {
        modfix=modfix.replace(iter.key(),iter.value());
    }
    return modfix;
}
