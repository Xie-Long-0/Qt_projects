#include "propertychang.h"

PropertyChang::PropertyChang(QObject *parent) : QObject(parent)
{

}

const QString &PropertyChang::nickName()
{
    return m_nickName;
}

int PropertyChang::count()
{
    return m_count;
}

void PropertyChang::setNickName(const QString &strNewName)
{
    //数值没变化直接返回
    if (strNewName == m_nickName) return;

    m_nickName = strNewName;
    emit nickNameChanged(strNewName);
}

void PropertyChang::setCount(int nNewCount)
{
    if (nNewCount == m_count) return;

    m_count = nNewCount;
    emit countChanged(nNewCount);
}
