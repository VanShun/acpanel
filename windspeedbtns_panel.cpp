#include "windspeedbtns_panel.h"
#include "globalsetting.h"
#include "acpanel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

static AcPanel *pacpanel = nullptr;

WindSpeedBtns_Panel::WindSpeedBtns_Panel(QWidget *parent) : QWidget(parent)
{
    pacpanel = (AcPanel*)this->parentWidget();
    m_qssmanager = new QssManager();

    m_pBtn_low = new QPushButton(this);
    m_pBtn_low->setFixedSize(PBTN_SIZE);
    m_pBtn_low->setObjectName("m_pBtn_low");
    //m_pBtn_low->setStyleSheet("border-image: url(:/resources/images/windspeed/windspeed_g1.png);");
    m_txt_low = new QLabel(this);
    m_txt_low->setFixedSize(PBTN_WIDTH, 20);
    m_txt_low->setText(QString("低速"));
    m_txt_low->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(m_pBtn_low);
    vlayout1->addWidget(m_txt_low);

    m_pBtn_mid = new QPushButton(this);
    m_pBtn_mid->setFixedSize(PBTN_SIZE);
    m_pBtn_mid->setObjectName("m_pBtn_mid");
    //m_pBtn_mid->setStyleSheet("border-image: url(:/resources/images/windspeed/windspeed_g2.png);");
    m_txt_mid = new QLabel(this);
    m_txt_mid->setFixedSize(PBTN_WIDTH, 20);
    m_txt_mid->setText(QString("中速"));
    m_txt_mid->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(m_pBtn_mid);
    vlayout2->addWidget(m_txt_mid);

    m_pBtn_high = new QPushButton(this);
    m_pBtn_high->setFixedSize(PBTN_SIZE);
    m_pBtn_high->setObjectName("m_pBtn_high");
    //m_pBtn_high->setStyleSheet("border-image: url(:/resources/images/windspeed/windspeed_g3.png);");
    m_txt_high = new QLabel(this);
    m_txt_high->setFixedSize(PBTN_WIDTH, 20);
    m_txt_high->setText(QString("高速"));
    m_txt_high->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(m_pBtn_high);
    vlayout3->addWidget(m_txt_high);

    m_pBtn_auto = new QPushButton(this);
    m_pBtn_auto->setFixedSize(PBTN_SIZE);
    m_pBtn_auto->setObjectName("m_pBtn_auto");
    //m_pBtn_auto->setStyleSheet("border-image: url(:/resources/images/windspeed/windspeed_auto.png);");
    m_txt_auto = new QLabel(this);
    m_txt_auto->setFixedSize(PBTN_WIDTH, 20);
    m_txt_auto->setText(QString("自动"));
    m_txt_auto->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout4 = new QVBoxLayout();
    vlayout4->addWidget(m_pBtn_auto);
    vlayout4->addWidget(m_txt_auto);

    m_pBtn_hide = new QPushButton(this);
    m_pBtn_hide->setFixedSize(PBTN_WIDTH, 20);
    m_pBtn_hide->setObjectName("m_pBtn_hide");
    //m_pBtn_hide->setStyleSheet("border-image: url(:/resources/images/homepage/hide.png);");

    QHBoxLayout *hlayout = new QHBoxLayout();
    //hlayout->addSpacing(10);
    hlayout->addStretch();
    hlayout->addLayout(vlayout1);
    hlayout->addStretch();
    hlayout->addLayout(vlayout2);
    hlayout->addStretch();
    hlayout->addLayout(vlayout3);
    hlayout->addStretch();
    hlayout->addLayout(vlayout4);
    hlayout->addStretch();
    //hlayout->addSpacing(10);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_pBtn_hide);
    vlayout->setAlignment(m_pBtn_hide, Qt::AlignHCenter);
    m_gbox = new QGroupBox(this);
    m_gbox->setFixedSize(780, 140);
    m_gbox->setLayout(vlayout);

    this->setVisible(false);
    connect(m_pBtn_low, SIGNAL(clicked()), this, SLOT(on_m_pBtn_low_clicked()));
    connect(m_pBtn_mid, SIGNAL(clicked()), this, SLOT(on_m_pBtn_mid_clicked()));
    connect(m_pBtn_high, SIGNAL(clicked()), this, SLOT(on_m_pBtn_high_clicked()));
    connect(m_pBtn_auto, SIGNAL(clicked()), this, SLOT(on_m_pBtn_auto_clicked()));
    connect(m_pBtn_hide, SIGNAL(clicked()), this, SLOT(on_m_pBtn_hide_clicked()));

    setStyleSheet(m_qssmanager->LoadQssData(":/resources/qss/windspeedBtns_panel.qss"));
}

WindSpeedBtns_Panel::~WindSpeedBtns_Panel()
{
    delete m_qssmanager;
}

void WindSpeedBtns_Panel::on_m_pBtn_low_clicked()
{
    pacpanel->WindSpeedChanged(AirCondCtrl::WindSpeed_Gear1);
}

void WindSpeedBtns_Panel::on_m_pBtn_mid_clicked()
{
    pacpanel->WindSpeedChanged(AirCondCtrl::WindSpeed_Gear2);
}

void WindSpeedBtns_Panel::on_m_pBtn_high_clicked()
{
    pacpanel->WindSpeedChanged(AirCondCtrl::WindSpeed_Gear3);
}

void WindSpeedBtns_Panel::on_m_pBtn_auto_clicked()
{
    pacpanel->WindSpeedChanged(AirCondCtrl::WindSpeed_Auto);
}

void WindSpeedBtns_Panel::on_m_pBtn_hide_clicked()
{
    this->hide();
    pacpanel->showHomebtnsPanel();
}
