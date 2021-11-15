#ifndef QSSMANAGER_H
#define QSSMANAGER_H
#include <QFile>
#include <QString>
#include <QWidget>
#include <QStyle>

class QssManager
{
public:
    QssManager();

    virtual ~QssManager();

    const QString &LoadQssData(const QString &filename);

private:
    QString m_qssdatastr;
};

#endif // QSSMANAGER_H
