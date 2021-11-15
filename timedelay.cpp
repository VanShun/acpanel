#include "timedelay.h"
#include <QVBoxLayout>

TimeDelay::TimeDelay(QWidget *parent) : QWidget(parent)
{
    m_pBtn_delayset = new QPushButton(this);
    m_pBtn_delayset->setObjectName(QString("m_pBtn_delayset"));
    m_pBtn_delayset->setFixedSize(60, 60);
    m_qssmanager = new QssManager();
    setStyleSheet(m_qssmanager->LoadQssData(":/qss/timedelay.qss"));
    m_enable = false;
    bindSignalsandSlots();
}

TimeDelay::~TimeDelay()
{

}


void TimeDelay::bindSignalsandSlots()
{
    connect(m_pBtn_delayset, SIGNAL(clicked()), this, SLOT(on_pBtn_delayset_clicked()));
}



void TimeDelay::on_pBtn_delayset_clicked()
{
    m_enable = !m_enable;
}
