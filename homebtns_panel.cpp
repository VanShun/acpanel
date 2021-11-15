#include "homebtns_panel.h"
#include "globalsetting.h"
#include "acpanel.h"
#include <QHBoxLayout>

static AcPanel *pacpanel = nullptr;
static bool showtimerset = false;

HomeBtns_Panel::HomeBtns_Panel(QWidget *parent) : QWidget(parent)
{
    pacpanel = (AcPanel*)this->parentWidget();
    m_pBtn_poweron = new QPushButton(this);
    m_pBtn_poweron->setFixedSize(60, 60);
    m_pBtn_poweron->setStyleSheet("border-image: url(:/resources/images/homepage/poweron.png);");

    m_pBtn_mode = new QPushButton(this);
    m_pBtn_mode->setFixedSize(PBTN_SIZE);
    m_pBtn_mode->setStyleSheet("border-image: url(:/resources/images/homepage/mode/mode_auto_home.png);");
    m_txt_mode = new QLabel(this);
    m_txt_mode->setFixedSize(PBTN_WIDTH, 20);
    m_txt_mode->setText(QString("模式"));
    m_txt_mode->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(m_pBtn_mode);
    vlayout1->addWidget(m_txt_mode);

    m_pBtn_windspeed = new QPushButton(this);
    m_pBtn_windspeed->setFixedSize(PBTN_SIZE);
    m_pBtn_windspeed->setStyleSheet("border-image: url(:/resources/images/homepage/windspeed/windspeed_auto_home.png);");
    m_txt_windspeed = new QLabel(this);
    m_txt_windspeed->setFixedSize(PBTN_WIDTH, 20);
    m_txt_windspeed->setText(QString("风速"));
    m_txt_windspeed->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(m_pBtn_windspeed);
    vlayout2->addWidget(m_txt_windspeed);

    m_pBtn_winddir = new QPushButton(this);
    m_pBtn_winddir->setFixedSize(PBTN_SIZE);
    m_pBtn_winddir->setObjectName("m_pBtn_winddir");
    m_pBtn_winddir->setStyleSheet("border-image: url(:/resources/images/homepage/winddir/windir_cycle_home.png);");
    m_txt_winddir = new QLabel(this);
    m_txt_winddir->setFixedSize(PBTN_WIDTH, 20);
    m_txt_winddir->setText(QString("风向"));
    m_txt_winddir->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(m_pBtn_winddir);
    vlayout3->addWidget(m_txt_winddir);


    m_pBtn_others = new QPushButton(this);
    m_pBtn_others->setFixedSize(PBTN_SIZE);
    m_pBtn_others->setStyleSheet("border-image: url(:/resources/images/homepage/others.png);");
    m_txt_others = new QLabel(this);
    m_txt_others->setFixedSize(PBTN_WIDTH, 20);
    m_txt_others->setText(QString("其它"));
    m_txt_others->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout4 = new QVBoxLayout();
    vlayout4->addWidget(m_pBtn_others);
    vlayout4->addWidget(m_txt_others);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addSpacing(5);
    hlayout->addLayout(vlayout1);
    hlayout->addStretch();
    hlayout->addLayout(vlayout2);
    hlayout->addStretch();
    hlayout->addWidget(m_pBtn_poweron);
    hlayout->addStretch();
    hlayout->addLayout(vlayout3);
    hlayout->addStretch();
    hlayout->addLayout(vlayout4);
    hlayout->addSpacing(5);
    m_gbox = new QGroupBox(this);
    m_gbox->setFixedSize(800, 110);
    m_gbox->setLayout(hlayout);

    this->setVisible(false);
    connect(m_pBtn_poweron, SIGNAL(clicked()), this, SLOT(on_m_pBtn_poweron_clicked()));
    connect(m_pBtn_mode, SIGNAL(clicked()), this, SLOT(on_m_pBtn_mode_clicked()));
    connect(m_pBtn_winddir, SIGNAL(clicked()), this, SLOT(on_m_pBtn_winddir_clicked()));
    connect(m_pBtn_windspeed, SIGNAL(clicked()), this, SLOT(on_m_pBtn_windspeed_clicked()));
    connect(m_pBtn_others, SIGNAL(clicked()), this, SLOT(on_m_pBtn_others_clicked()));
}

HomeBtns_Panel::~HomeBtns_Panel()
{

}

void HomeBtns_Panel::m_pBtn_mode_setStyleSheet(const QString qss_str)
{
    m_pBtn_mode->setStyleSheet(qss_str);
}

void HomeBtns_Panel::m_pBtn_winddir_setStyleSheet(const QString qss_str)
{
    m_pBtn_winddir->setStyleSheet(qss_str);
}

void HomeBtns_Panel::m_pBtn_windspeed_setStyleSheet(const QString qss_str)
{
    m_pBtn_windspeed->setStyleSheet(qss_str);
}

void HomeBtns_Panel::on_m_pBtn_poweron_clicked()
{
    this->hide();
    pacpanel->showOffbtnPanel();
    pacpanel->showTimersetPanel(false);
}

void HomeBtns_Panel::on_m_pBtn_mode_clicked()
{
    this->hide();
    pacpanel->showModebtnsPanel();
    //pacpanel->showTimersetPanel(false);
}

void HomeBtns_Panel::on_m_pBtn_winddir_clicked()
{
    this->hide();
    pacpanel->showWindDirbtnsPanel();
    //pacpanel->showTimersetPanel(false);
}

void HomeBtns_Panel::on_m_pBtn_windspeed_clicked()
{
    this->hide();
    pacpanel->showWindSpeedbtnsPanel();
    //pacpanel->showTimersetPanel(false);
}

void HomeBtns_Panel::on_m_pBtn_others_clicked()
{
    if (showtimerset) {
        pacpanel->showTimersetPanel(false);
    } else {
        pacpanel->showTimersetPanel(true);
        pacpanel->timerset_chgvalue(0);
    }
    showtimerset = !showtimerset;
}

