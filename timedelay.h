#ifndef TIMEDELAY_H
#define TIMEDELAY_H

#include <QWidget>
#include <QPushButton>
#include "qssmanager.h"

class TimeDelay : public QWidget
{
    Q_OBJECT
public:
    explicit TimeDelay(QWidget *parent = nullptr);
    virtual ~TimeDelay();
public:
    void bindSignalsandSlots();
private slots:
    void on_pBtn_delayset_clicked();
private:
    bool m_enable;
    QPushButton *m_pBtn_delayset;
    QssManager *m_qssmanager;
};

#endif // TIMEDELAY_H
