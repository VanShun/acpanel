#include "qssmanager.h"
#include <QStyle>

QssManager::QssManager()
{

}

QssManager::~QssManager()
{

}

/*
** load qssdata from filename
** @const QString & : filename
*/
const QString &QssManager::LoadQssData(const QString &filename)
{
    QFile qssfile(filename);
    m_qssdatastr = "";
    if (qssfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_qssdatastr = QLatin1String(qssfile.readAll());
        qssfile.close();
    }
    return m_qssdatastr;
}

