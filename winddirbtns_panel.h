#ifndef WINDDIRBTNS_PANEL_H
#define WINDDIRBTNS_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QPoint>
#include "qssmanager.h"

class WindDirBtns_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit WindDirBtns_Panel(QWidget *parent = nullptr);
    virtual ~WindDirBtns_Panel();

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void on_m_pBtn_updown_clicked();

    void on_m_pBtn_leftright_clicked();

    void on_m_pBtn_cycle_clicked();

    void on_m_pBtn_hide_clicked();
private:
    QPushButton *m_pBtn_updown, *m_pBtn_leftright, *m_pBtn_cycle, *m_pBtn_hide;
    QLabel *m_txt_updown, *m_txt_leftright, *m_txt_cycle;
    QGroupBox *m_gbox;
    QssManager *m_qssmanager;
    QPoint m_presspoint, m_releasepoint;
};

#endif // WINDDIRBTNS_PANEL_H
