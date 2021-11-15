#ifndef HOMEBTNS_PANEL_H
#define HOMEBTNS_PANEL_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>

class HomeBtns_Panel : public QWidget
{
    Q_OBJECT
public:
    explicit HomeBtns_Panel(QWidget *parent = nullptr);

    virtual ~HomeBtns_Panel();    
public:
    void m_pBtn_mode_setStyleSheet(const QString qss_str);

    void m_pBtn_winddir_setStyleSheet(const QString qss_str);

    void m_pBtn_windspeed_setStyleSheet(const QString qss_str);

private slots:
    void on_m_pBtn_poweron_clicked();

    void on_m_pBtn_mode_clicked();

    void on_m_pBtn_winddir_clicked();

    void on_m_pBtn_windspeed_clicked();

    void on_m_pBtn_others_clicked();

private:
    QPushButton *m_pBtn_poweron, *m_pBtn_mode, *m_pBtn_winddir, *m_pBtn_windspeed, *m_pBtn_others;
    QLabel *m_txt_mode, *m_txt_windspeed, *m_txt_winddir, *m_txt_others;
    QGroupBox *m_gbox;
};

#endif // HOMEBTNS_PANEL_H
