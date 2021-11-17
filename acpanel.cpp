#include "acpanel.h"
#include "globalsetting.h"
#include <QDateTime>
#include <QStyle>
#include <QDebug>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSizePolicy>
#include <QThread>
#include <qmath.h>
/*
** constructor of AcPanel
** @QWidget * : parent
*/
AcPanel::AcPanel(QWidget *parent)
    : QWidget(parent)
{
    delaytime = 0;
    m_airCtrl = new AirCondCtrl();
    m_qssmanager = new QssManager();
    m_delaytmanager = new DelayTimerManager();

    m_timer = new QTimer(this);
    m_timer->stop();
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timerout()));
    m_timer->start();

    m_offBtn_Panel = new OffBtn_Panel(this);
    m_homeBtn_Panel = new HomeBtns_Panel(this);
    m_modeBtn_Panel = new ModeBtns_Panel(this);
    m_windspeedBtn_Panel = new WindSpeedBtns_Panel(this);
    m_winddirBtn_Panel = new WindDirBtns_Panel(this);
    m_offBtn_Panel->setGeometry(0, 370, 800, 110);
    m_homeBtn_Panel->setGeometry(0, 370, 800, 110);
    m_modeBtn_Panel->setGeometry(10, 340, 780, 140);
    m_windspeedBtn_Panel->setGeometry(10, 340, 780, 140);
    m_winddirBtn_Panel->setGeometry(10, 340, 780, 140);
    //QPalette palette;
    //QPixmap pixmap(":/images/background.jpg");
    //palette.setBrush(QPalette::Window, QBrush(pixmap));
    //this->setPalette(palette);

    setFocusPolicy(Qt::StrongFocus);
    SetLayout();
    widgetsInit();  //note: this func should be exec after SetLayout()
    setStyleSheet(m_qssmanager->LoadQssData(":/resources/qss/global.qss"));
    BindSigSlot();
}

/*
** destructor of AcPanel
*/
AcPanel::~AcPanel()
{
    //qDebug() << "acpanel destructure" << endl;
    delete m_airCtrl;
    delete m_qssmanager;
    delete m_delaytmanager;
}

/*
** setlayout
*/
void AcPanel::SetLayout()
{
    m_arc = new TempArc(this);
    m_arc->setFixedSize(230, 230);

    QFont font = this->font();
    font.setPointSize(30);
    m_pBtn_Minus = new QPushButton(this);
    m_pBtn_Minus->setFixedSize(PBTN_SIZE);
    m_pBtn_Minus->setFont(font);
    m_pBtn_Minus->setText("-");
    m_pBtn_Minus->setObjectName(QString("m_pBtn_Minus"));
    m_pBtn_Add = new QPushButton(this);
    m_pBtn_Add->setFixedSize(PBTN_SIZE);
    m_pBtn_Add->setFont(font);
    m_pBtn_Add->setText("+");
    m_pBtn_Add->setObjectName(QString("m_pBtn_Add"));

    QHBoxLayout *hlayout_arc = new QHBoxLayout();
    hlayout_arc->addStretch();
    hlayout_arc->addWidget(m_pBtn_Minus);
    hlayout_arc->addWidget(m_arc);
    hlayout_arc->addWidget(m_pBtn_Add);
    hlayout_arc->addStretch();

    m_label_showtime = new QLabel(this);
    m_label_showtime->setObjectName(QString("m_label_showtime"));
    m_label_showtime->setFixedSize(400, 40);
    m_label_showtime->setAlignment(Qt::AlignCenter);

    m_pBtn_timerset = new QPushButton(this);
    m_pBtn_timerset->setObjectName(QString("m_pBtn_timerset"));
    m_pBtn_timerset->setFixedSize(250, 40);
    m_pBtn_timerset->setIcon(QIcon(":/resources/images/homepage/timer.png"));
    //m_pBtn_timerset->setIconSize(QSize(20, 20));
    m_pBtn_timerset->setText(QString("定时未开启"));
    m_pBtn_timerset->setVisible(false);

    m_label_sleepmode = new QLabel(this);
    m_label_sleepmode->setObjectName("m_label_sleepmode");
    m_label_sleepmode->setFixedSize(60, 40);
    m_label_sleepmode->setVisible(false);

    QHBoxLayout *hlayout_timerset = new QHBoxLayout();
    hlayout_timerset->addStretch();
    hlayout_timerset->addWidget(m_pBtn_timerset);
    hlayout_timerset->setAlignment(m_pBtn_timerset, Qt::AlignCenter);
    hlayout_timerset->addWidget(m_label_sleepmode);
    hlayout_timerset->addStretch();

    QVBoxLayout *vlayout_showarea = new QVBoxLayout();
    vlayout_showarea->addLayout(hlayout_arc);
    //vlayout_showarea->addStretch();
    vlayout_showarea->addWidget(m_label_showtime);
    vlayout_showarea->setAlignment(m_label_showtime, Qt::AlignHCenter);
    vlayout_showarea->addLayout(hlayout_timerset);
    vlayout_showarea->addStretch();
    vlayout_showarea->addSpacing(10);

    QGridLayout *glayout_global = new QGridLayout(this);
    glayout_global->addLayout(vlayout_showarea, 1, 0);
    //glayout_global->addWidget(m_offBtn_Panel);
    this->setLayout(glayout_global);
}

/*
** bind signals and slots throught connect func
*/
void AcPanel::BindSigSlot()
{
    connect(m_pBtn_Add, SIGNAL(clicked()), this, SLOT(on_pBtn_Add_clicked()));
    connect(m_pBtn_Minus, SIGNAL(clicked()), this, SLOT(on_pBtn_Minus_clicked()));
    connect(m_pBtn_timerset, SIGNAL(clicked()), this, SLOT(on_m_pBtn_timerset_clicked()));
}

/*
** tasks to do after control mode changed
** @enum AirCondCtrl::CtrlMode : mode
*/
void AcPanel::CtrlmodeChanged(enum AirCondCtrl::CtrlMode mode)
{
    switch (mode) {
        case AirCondCtrl::AutoMode:
            m_homeBtn_Panel->m_pBtn_mode_setStyleSheet("border-image: url(:/resources/images/homepage/mode/mode_auto_home.png);");
        break;
        case AirCondCtrl::Cold:
            m_homeBtn_Panel->m_pBtn_mode_setStyleSheet("border-image: url(:/resources/images/homepage/mode/mode_cold_home.png);");
        break;
        case AirCondCtrl::Dehumid:
            m_homeBtn_Panel->m_pBtn_mode_setStyleSheet("border-image: url(:/resources/images/homepage/mode/mode_dehumid_home.png);");
        break;
        case AirCondCtrl::Blow:
            m_homeBtn_Panel->m_pBtn_mode_setStyleSheet("border-image: url(:/resources/images/homepage/mode/mode_wind_home.png);");
        break;
        case AirCondCtrl::Heat:
            m_homeBtn_Panel->m_pBtn_mode_setStyleSheet("border-image: url(:/resources/images/homepage/mode/mode_heat_home.png);");
        break;
        default:
        break;
    }
}

/*
** tasks to do after wind speed changed
** @enum AirCondCtrl::WindSpeed : speed
*/
void AcPanel::WindSpeedChanged(enum AirCondCtrl::WindSpeed speed)
{
    switch (speed) {
        case AirCondCtrl::WindSpeed_Auto:
            m_homeBtn_Panel->m_pBtn_windspeed_setStyleSheet("border-image: url(:/resources/images/homepage/windspeed/windspeed_auto_home.png);");
        break;
        case AirCondCtrl::WindSpeed_Gear1:
            m_homeBtn_Panel->m_pBtn_windspeed_setStyleSheet("border-image: url(:/resources/images/homepage/windspeed/windspeed_g1_home.png);");
        break;
        case AirCondCtrl::WindSpeed_Gear2:
            m_homeBtn_Panel->m_pBtn_windspeed_setStyleSheet("border-image: url(:/resources/images/homepage/windspeed/windspeed_g2_home.png);");
        break;
        case AirCondCtrl::WindSpeed_Gear3:
            m_homeBtn_Panel->m_pBtn_windspeed_setStyleSheet("border-image: url(:/resources/images/homepage/windspeed/windspeed_g3_home.png);");
        break;
        default:
        break;
    }
}

/*
** tasks to do after wind direction changed
** @enum AirCondCtrl::WindDir : dir
*/
void AcPanel::WindDirChanged(enum AirCondCtrl::WindDir dir)
{
    switch (dir) {
        case AirCondCtrl::WindDir_Auto:
            m_homeBtn_Panel->m_pBtn_winddir_setStyleSheet("border-image: url(:/resources/images/homepage/winddir/windir_cycle_home.png);");
        break;
        case AirCondCtrl::WindDir_UpDown:
            m_homeBtn_Panel->m_pBtn_winddir_setStyleSheet("border-image: url(:/resources/images/homepage/winddir/windir_updown_home.png);");
        break;
        case AirCondCtrl::WindDir_LeftRight:
            m_homeBtn_Panel->m_pBtn_winddir_setStyleSheet("border-image: url(:/resources/images/homepage/winddir/windir_leftright_home.png);");
        break;
        default:
        break;
    }
}

void AcPanel::on_pBtn_Add_clicked()
{
    double settemp = m_airCtrl->SettedTemp();
    //qDebug() << "on_pBtn_Add_clicked ,settemp:" << settemp << endl;
    if (settemp < 30) {
        m_airCtrl->SetTemp(settemp + 0.5);
        //m_meter->updateAngle_S(settemp + 0.5);
        m_arc->updateAngle_S(settemp + 0.5);
    }
}

void AcPanel::on_pBtn_Minus_clicked()
{
    double settemp = m_airCtrl->SettedTemp();
    if (settemp > 18) {
        m_airCtrl->SetTemp(settemp - 0.5);
        //m_meter->updateAngle_S(settemp - 0.5);
        m_arc->updateAngle_S(settemp - 0.5);
    }
}

void AcPanel::on_m_pBtn_timerset_clicked()
{
    double value = m_delaytmanager->getDelaytime();
    if (qFabs(value - 12) > 0.00001) {
        value += 0.5;
    } else {
        value = 0.5;
    }
    m_delaytmanager->setDelaytime(value);
    m_pBtn_timerset->setText(QString("定时%1小时后关闭").arg(value));
}
/*
** SLOT on_timerout
*/
void AcPanel::on_timerout()
{
    QDateTime curdatetime = QDateTime::currentDateTime();
    m_label_showtime->clear();
    m_label_showtime->setText(curdatetime.toString("yyyy-MM-dd   hh:mm:ss   ddd"));
}

/*
** init some parameters of the widgets
*/
void AcPanel::widgetsInit()
{
    enableButtons(true);
}
/*
** enable/disable buttons
** @ en: enable/disable
*/
void AcPanel::enableButtons(bool en)
{
    m_pBtn_Add->setEnabled(en);
    m_pBtn_Minus->setEnabled(en);
}

void AcPanel::widgetChgStyleSheet(QWidget *widget, const QString &qssfilename)
{
    style()->unpolish(widget);
    widget->setStyleSheet("");
    widget->setStyleSheet(m_qssmanager->LoadQssData(qssfilename));
    style()->polish(widget);
}

void AcPanel::showOffbtnPanel()
{
    m_offBtn_Panel->setVisible(true);
    m_arc->setSvalueVisible(false);
    m_arc->update();
}

void AcPanel::showHomebtnsPanel()
{
    m_homeBtn_Panel->setVisible(true);
    m_arc->setSvalueVisible(true);
    m_arc->update();
}

void AcPanel::showModebtnsPanel()
{
    m_modeBtn_Panel->setVisible(true);
}

void AcPanel::showWindSpeedbtnsPanel()
{
    m_windspeedBtn_Panel->setVisible(true);
}

void AcPanel::showWindDirbtnsPanel()
{
    m_winddirBtn_Panel->setVisible(true);
}

void AcPanel::showTimersetPanel(bool visible)
{
    m_pBtn_timerset->setVisible(visible);
    m_label_sleepmode->setVisible(visible);
}

void AcPanel::timerset_chgvalue(double value)
{
    m_delaytmanager->setDelaytime(value);
    if (qFabs(value - 0.0) < 0.00001) {
        m_pBtn_timerset->setText(QString("定时未开启"));
    }
}

void AcPanel::updateSettedTemp(double value)
{
    if (value > 30 || value < 18) return;
    m_airCtrl->SetTemp(value);
}

/*
** keyPressEvent of the window
** @QKeyEvent * keyset: pressed key
*/
void AcPanel::keyPressEvent(QKeyEvent *keyset)
{
    if (keyset->key() == Qt::Key_Escape) {
        this->setWindowState(Qt::WindowNoState);
        this->close();
    }
}
