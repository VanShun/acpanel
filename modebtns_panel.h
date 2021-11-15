#ifndef MODEBTNS_PANEL_H
#define MODEBTNS_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include "qssmanager.h"

class ModeBtns_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit ModeBtns_Panel(QWidget *parent = nullptr);
    virtual ~ModeBtns_Panel();

private slots:
    void on_m_pBtn_cold_clicked();

    void on_m_pBtn_blow_clicked();

    void on_m_pBtn_heat_clicked();

    void on_m_pBtn_dehumid_clicked();

    void on_m_pBtn_auto_clicked();

    void on_m_pBtn_hide_clicked();
private:
    QPushButton *m_pBtn_cold, *m_pBtn_blow, *m_pBtn_heat, *m_pBtn_dehumid, *m_pBtn_auto, *m_pBtn_hide;
    QLabel *m_txt_cold, *m_txt_blow, *m_txt_heat, *m_txt_dehumid, *m_txt_auto;
    QGroupBox *m_gbox;
    QssManager *m_qssmanager;
};

#endif // MODEBTNS_PANEL_H
