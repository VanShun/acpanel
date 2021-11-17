#ifndef WINDSPEEDBTNS_PANEL_H
#define WINDSPEEDBTNS_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QPoint>
#include "qssmanager.h"

class WindSpeedBtns_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit WindSpeedBtns_Panel(QWidget *parent = nullptr);
    virtual ~WindSpeedBtns_Panel();
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
public slots:
    void on_m_pBtn_low_clicked();

    void on_m_pBtn_mid_clicked();

    void on_m_pBtn_high_clicked();

    void on_m_pBtn_auto_clicked();

    void on_m_pBtn_hide_clicked();
private:
    QPushButton *m_pBtn_low, *m_pBtn_mid, *m_pBtn_high, *m_pBtn_auto, *m_pBtn_hide;
    QLabel *m_txt_low, *m_txt_mid, *m_txt_high, *m_txt_auto;
    QGroupBox *m_gbox;
    QssManager *m_qssmanager;
    QPoint m_presspoint, m_releasepoint;
};

#endif // WINDSPEEDBTNS_PANEL_H
