#ifndef ACPANEL_H
#define ACPANEL_H

#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include "aircondctrl.h"
#include "qssmanager.h"
#include "temparc.h"
#include "delaytimermanager.h"
#include "offbtn_panel.h"
#include "homebtns_panel.h"
#include "modebtns_panel.h"
#include "windspeedbtns_panel.h"
#include "winddirbtns_panel.h"

class AcPanel : public QWidget
{
    Q_OBJECT
public:
    AcPanel(QWidget *parent = nullptr);

    virtual ~AcPanel();

    void CtrlmodeChanged(enum AirCondCtrl::CtrlMode mode);

    void WindSpeedChanged(enum AirCondCtrl::WindSpeed speed);

    void WindDirChanged(enum AirCondCtrl::WindDir dir);

    void SetLayout();

    void BindSigSlot();

    void widgetsInit();

    void enableButtons(bool en);

    void widgetChgStyleSheet(QWidget *widget, const QString &qssfilename);

    void showOffbtnPanel();

    void showHomebtnsPanel();

    void showModebtnsPanel();

    void showWindSpeedbtnsPanel();

    void showWindDirbtnsPanel();

    void showTimersetPanel(bool visible);

    void timerset_chgvalue(double value);

    void updateSettedTemp(double value);
protected:
    virtual void keyPressEvent(QKeyEvent *keyset) override;

private slots:
    void on_pBtn_Add_clicked();

    void on_pBtn_Minus_clicked();

    void on_m_pBtn_timerset_clicked();

    void on_timerout();
private:
    QLabel *m_label_showtime, *m_label_sleepmode;
    QPushButton *m_pBtn_Add, *m_pBtn_Minus, *m_pBtn_timerset;
    QTimer *m_timer;
    TempArc *m_arc;
    AirCondCtrl *m_airCtrl;
    QssManager *m_qssmanager;
    DelayTimerManager *m_delaytmanager;

    OffBtn_Panel *m_offBtn_Panel;
    HomeBtns_Panel *m_homeBtn_Panel;
    ModeBtns_Panel *m_modeBtn_Panel;
    WindSpeedBtns_Panel *m_windspeedBtn_Panel;
    WindDirBtns_Panel *m_winddirBtn_Panel;
    double delaytime;
};
#endif // ACPANEL_H
