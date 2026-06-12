#ifndef PROPERTYCHANG_H
#define PROPERTYCHANG_H

#include <QObject>

class PropertyChang : public QObject
{
    Q_OBJECT
public:
    explicit PropertyChang(QObject *parent = nullptr);

    //声明属性
    //不直接标出成员变量
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    //直接标出成员变量
    Q_PROPERTY(int count MEMBER m_count READ count WRITE setCount NOTIFY countChanged)
    //标出成员变量，可省略读写函数
    Q_PROPERTY(double value MEMBER m_value NOTIFY valueChanged)

    const QString &nickName();
    int count();

signals:
    //三个属性数值变化时发信号
    void nickNameChanged(const QString &strNewName);
    void countChanged(int nNewCount);
    void valueChanged(double dbNewValue);

public slots:
    void setNickName(const QString &strNewName);
    void setCount(int nNewCount);

private:
    //三个成员变量作为属性
    QString m_nickName;
    int m_count;
    double m_value;

};

#endif // PROPERTYCHANG_H
