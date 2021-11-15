#ifndef OFFBTN_PANEL_H
#define OFFBTN_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>

class OffBtn_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit OffBtn_Panel(QWidget *parent = nullptr);

    virtual ~OffBtn_Panel();

private slots:
    void on_m_pBtn_poweroff_clidked();

private:
    QPushButton *m_pBtn_poweroff;
    QGroupBox *m_gbox;
};

#endif // OFFBTN_PANEL_H
